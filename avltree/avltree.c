/*
Copyright (C) 2014 Jung-Sang Ahn <jungsang.ahn@gmail.com>
All rights reserved.

Last modification: Mar 3, 2014

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef INLINE
    #ifdef __APPLE__
        #define INLINE extern inline
    #elif __linux__
        #define INLINE __inline
    #else
        #define INLINE
    #endif
#endif

#include "avltree.h"

INLINE int _abs(int n) {
    int mask = n>> ((sizeof(int)*8) -1);
    return (mask+n)^mask;
}

INLINE void avl_set_parent(struct avl_node *node, struct avl_node *parent)
{
    node->parent = (struct avl_node *)(
        (unsigned long)parent |((unsigned long)node->parent & 0x3));
}

#define avl_parent(node) \
        ((struct avl_node *)((unsigned long)(node)->parent & ~0x3))

#ifdef _AVL_SEPARATE_PARENT_BF
    #define avl_bf(node) ((node)->bf)
#else
    #define avl_bf(node) (((int)((unsigned long)(node)->parent & 0x3)) - 1)
#endif

#ifdef __AVL_DEBUG
#include <stdio.h>
#include <assert.h>
#include "avltree_debug.h"
#else
#define __AVL_DEBUG_BF_CHECK(bf)
#define __AVL_DEBUG_LL(p, c)
#define __AVL_DEBUG_RR(p, c)
#define __AVL_DEBUG_BAL_BEGIN(node, bf, height_diff)
#define __AVL_DEBUG_BAL_END(node)
#define __AVL_DEBUG_INSERT(node)
#define __AVL_DEBUG_REMOVE(node)
#define __AVL_DEBUG_DISPLAY(tree)
#endif

INLINE void avl_set_bf(struct avl_node *node, int bf)
{
    __AVL_DEBUG_BF_CHECK(bf);

#ifdef _AVL_SEPARATE_PARENT_BF
    node->bf = bf;
#else
    node->parent = (struct avl_node *)(
        (unsigned long)avl_parent(node) | (unsigned long)(bf+1));
#endif
}

INLINE struct avl_node* _rotate_LL(struct avl_node *parent)
{
    struct avl_node *child = parent->left;

    __AVL_DEBUG_LL(parent, child);

    avl_set_bf(parent, avl_bf(parent)+1);
    avl_set_bf(child, avl_bf(child)+1);

    parent->left = child->right;
    if (child->right != NULL) avl_set_parent(child->right, parent);
    child->right = parent;
    avl_set_parent(child, avl_parent(parent));
    avl_set_parent(parent, child);

    return child;
}

INLINE struct avl_node* _rotate_RR(struct avl_node *parent)
{
    struct avl_node *child = parent->right;

    __AVL_DEBUG_RR(parent, child);

    avl_set_bf(parent, avl_bf(parent)-1);
    avl_set_bf(child, avl_bf(child)-1);

    parent->right = child->left;
    if (child->left != NULL) avl_set_parent(child->left, parent);
    child->left = parent;
    avl_set_parent(child, avl_parent(parent));
    avl_set_parent(parent, child);

    return child;
}

INLINE struct avl_node* _rotate_LR(struct avl_node *parent)
{
    struct avl_node *child = parent->left;
    if (child->right != NULL) parent->left = _rotate_RR(child);
    return _rotate_LL(parent);
}

INLINE struct avl_node* _rotate_RL(struct avl_node *parent)
{
    struct avl_node *child = parent->right;
    if (child->left != NULL) parent->right = _rotate_LL(child);
    return _rotate_RR(parent);
}

#define _get_balance(node) ((node)?(avl_bf(node)):(0))

struct avl_node* _balance_tree(struct avl_node *node, int bf)
{
    int height_diff= _get_balance(node) + bf;

    __AVL_DEBUG_BAL_BEGIN(node, bf, height_diff);

    if(height_diff < -1 && node->left != NULL) {
        // balance left sub tree
        if(_get_balance(node->left) < 0) {
            node = _rotate_LL(node);
        } else {
            node = _rotate_LR(node);
            avl_set_bf(node, avl_bf(node) + bf);
        }
    } else if(height_diff > 1 && node->right != NULL) {
        // balance right sub tree
        if(_get_balance(node->right) > 0) {
            node = _rotate_RR(node);
        } else {
            node = _rotate_RL(node);
            avl_set_bf(node, avl_bf(node) + bf);
        }
    } else {
        avl_set_bf(node, avl_bf(node) + bf);
    }

    __AVL_DEBUG_BAL_END(node);

    return node;
}

struct avl_node* avl_first(struct avl_tree *tree)
{
    struct avl_node *p = NULL;
    struct avl_node *node = tree->root;

    while(node) {
        p = node;
        node = node->left;
    }
    return p;
}

struct avl_node* avl_last(struct avl_tree *tree)
{
    struct avl_node *p = NULL;
    struct avl_node *node = tree->root;

    while(node) {
        p = node;
        node = node->right;
    }
    return p;
}

struct avl_node* avl_next(struct avl_node *node)
{
    if (node == NULL) return NULL;

#ifdef _AVL_NEXT_POINTER
    return node->next;
#else

    struct avl_node *p;

    // smallest value of right subtree
    if (node->right) {
        p = node;
        node = node->right;
        while (node) {
            p = node;
            node = node->left;
        }
        return p;
    }

    // node does not have right child
    if (avl_parent(node)) {
        // find first parent that has right child
        p = node;
        node = avl_parent(node);
        while(node) {
            if (node->left == p) {
                return node;
            }
            p = node;
            node = avl_parent(node);
        }
    }
#endif
    return NULL;
}

struct avl_node* avl_prev(struct avl_node *node)
{
    if (node == NULL) return NULL;

#ifdef _AVL_NEXT_POINTER
    return node->prev;
#else

    struct avl_node *p;

    // largest value of left subtree
    if (node->left) {
        p = node;
        node = node->left;
        while (node) {
            p = node;
            node = node->right;
        }
        return p;
    }

    // node does not have left child
    if (avl_parent(node)) {
        // find first parent that has left child
        p = node;
        node = avl_parent(node);
        while(node) {
            if (node->right == p) {
                return node;
            }
            p = node;
            node = avl_parent(node);
        }
    }
#endif
    return NULL;
}

struct avl_node* avl_search(struct avl_tree *tree,
                            struct avl_node *node,
                            avl_cmp_func *func)
// exact match
{
    struct avl_node *p = tree->root;
    int cmp;

    while(p)
    {
        cmp = func(p, node, tree->aux);
        if (cmp > 0) {
            p = p->left;
        }else if (cmp < 0){
            p = p->right;
        }else {
            // search success
            return p;
        }
    }
    // search fail
    return NULL;
}

struct avl_node* avl_search_greater(struct avl_tree *tree,
                            struct avl_node *node,
                            avl_cmp_func *func)
// if an exact match does not exist,
// return smallest node greater than NODE
{
    struct avl_node *p = tree->root;
    struct avl_node *pp;
    int cmp;

    while(p)
    {
        cmp = func(p, node, tree->aux);
        pp = p;

        if (cmp > 0) {
            p = p->left;
        }else if (cmp < 0){
            p = p->right;
        }else {
            // search success
            return p;
        }
    }

    cmp = func(pp, node, tree->aux);
    if (cmp > 0) {
        return pp;
    }else{
        return avl_next(pp);
    }
}

void avl_init(struct avl_tree *tree, void *aux)
{
    tree->root = NULL;
    tree->aux = aux;
}

struct avl_node* avl_insert(struct avl_tree *tree,
                            struct avl_node *node,
                            avl_cmp_func *func)
{
    __AVL_DEBUG_INSERT(node);

    struct avl_node *p=NULL,*cur;
    int cmp, bf, bf_old;

    cur = tree->root;
    while(cur)
    {
        cmp = func(cur, node, tree->aux);
        p = cur;

        if(cmp > 0) {
            cur = cur->left;
        }else if (cmp < 0){
            cur = cur->right;
        }else {
            // duplicated key -> return
            return cur;
        }
    }

    avl_set_parent(node, p);
    avl_set_bf(node, 0);
    node->left = node->right = NULL;
#ifdef _AVL_NEXT_POINTER
    node->prev = node->next = NULL;
#endif

    // P is parent node of CUR
    if(p) {
        if(func(p, node, tree->aux) > 0) {
            p->left = node;
#ifdef _AVL_NEXT_POINTER
            node->next = p;
            node->prev = p->prev;
            if (p->prev) p->prev->next = node;
            p->prev = node;
#endif

        }else {
            p->right = node;
#ifdef _AVL_NEXT_POINTER
            node->prev = p;
            node->next = p->next;
            if (p->next) p->next->prev = node;
            p->next = node;
#endif
        }

    } else {
        // no parent .. make NODE as root
        tree->root = node;
    }

    // recursive balancing process .. scan from leaf to root
    bf = 0;
    while(node) {
        p = avl_parent(node);

        if (p) {
            // if parent exists
            cur = node;
            bf_old = avl_bf(node);

            if (p->right == node) {
                node = _balance_tree(node, bf);
                p->right = node;
            }else {
                node = _balance_tree(node, bf);
                p->left = node;
            }

            // calculate balance facter BF for parent
            if (node->left == NULL && node->right == NULL) {
                // leaf node
                if (p->left == node) bf = -1;
                else bf = 1;
            } else {
                // index ndoe
                bf = 0;
                if (_abs(bf_old) < _abs(avl_bf(node))) {
                    // if ABS of balance factor increases
                    // cascade to parent
                    if (p->left == node) bf = -1;
                    else bf = 1;
                }
            }

        } else if(node == tree->root){
            tree->root = _balance_tree(tree->root, bf);
            break;
        }

        node = p;
    }

    __AVL_DEBUG_DISPLAY(tree);

    return node;
}

struct avl_node* avl_remove(struct avl_tree *tree,
                            struct avl_node *node)
{
    __AVL_DEBUG_REMOVE(node);

    struct avl_node *p=NULL,*cur, *next=NULL;
    int cmp, bf, bf_old;

    // not found
    if (node == NULL) return NULL;

#ifdef _AVL_NEXT_POINTER
    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;
#endif

    // find next node
    next = avl_next(node);

    if (node->left || node->right) {
        // if NODE is not leaf node .. re-arrange links

        if (avl_parent(node) == next) {
            // 1. victim's parent == next
            if (next) next->left = node->left;
            avl_set_parent(node->left, next);
            cur = next;
            bf = 1;

        } else if (next) {
            // 2. victim's parent != next
            if (avl_parent(next)) {
                if (avl_parent(next) != node) {
                    avl_parent(next)->left = next->right;
                    if (next->right)
                        avl_set_parent(next->right, avl_parent(next));
                }
            }
            if (avl_parent(node)) {
                avl_parent(node)->left = next;
            }

            if (node->right != next) {
                next->right = node->right;
                if (node->right) avl_set_parent(node->right, next);
                cur = avl_parent(next);
                bf = 1;
            }else{
                cur = next;
                bf = -1;
            }

            next->left = node->left;
            if (node->left) avl_set_parent(node->left, next);
            avl_set_parent(next, avl_parent(node));

            avl_set_bf(next, avl_bf(node));

        } else {
            // 3. next == NULL
            if (avl_parent(node))
                avl_parent(node)->right = node->left;
            if (node->left) {
                avl_set_parent(node->left, avl_parent(node));
            }
            cur = avl_parent(node);
            bf = -1;
        }
    }else {
        // NODE is leaf node
        p = avl_parent(node);
        if (p) {
            if (p->left == node) {
                p->left = NULL;
                bf = 1;
            } else {
                p->right = NULL;
                bf = -1;
            }
        }
        cur = p;
    }

    // reset root
    if (tree->root == node) {
        tree->root = next;
        if (next == NULL) {
            if (node->left) tree->root = node->left;
        }
    }

    // recursive balancing process .. scan from CUR to root
    while(cur) {
        p = avl_parent(cur);
        if (p) {
            // if parent exists
            bf_old = avl_bf(cur);

            if (p->right == cur) {
                cur = _balance_tree(cur, bf);
                p->right = cur;
            }else {
                cur = _balance_tree(cur, bf);
                p->left = cur;
            }

            // calculate balance facter BF for parent
            if (cur->left == NULL && cur->right == NULL) {
                // leaf node
                if (p->left == cur) bf = 1;
                else bf = -1;
            } else {
                // index ndoe
                bf = 0;
                if (_abs(bf_old) > _abs(avl_bf(cur))) {
                    // if ABS of balance factor decreases
                    // cascade to parent
                    if (p->left == cur) bf = 1;
                    else bf = -1;
                }
            }

        } else if(cur == tree->root){
            tree->root = _balance_tree(tree->root, bf);
            break;
        }

        cur = p;
    }

    __AVL_DEBUG_DISPLAY(tree);

    return next;
}

