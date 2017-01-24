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

#include <stdio.h>
#include <stdlib.h>

#include "avltree.h"

struct kv_node{
    struct avl_node avl;
    int key;
    int value;
};

int cmp_func(struct avl_node *a, struct avl_node *b, void *aux)
{
    struct kv_node *aa, *bb;
    aa = _get_entry(a, struct kv_node, avl);
    bb = _get_entry(b, struct kv_node, avl);

    if (aa->key < bb->key) return -1;
    else if (aa->key > bb->key) return 1;
    else return 0;
}

int main()
{
    int i;
    int n=7;
    struct avl_tree tree;
    struct avl_node *cur;
    struct kv_node *node, query;

    avl_init(&tree, NULL);

    // create and insert key-value pairs
    for (i=0;i<n;++i){
        node = (struct kv_node *)malloc(sizeof(struct kv_node));
        node->key = i*10;
        node->value = i*20;
        avl_insert(&tree, &node->avl, cmp_func);
    }

    // retrieve each key-value pair by key
    printf("retrieve by key\n");
    for (i=0;i<n;++i){
        query.key= i*10;
        cur = avl_search(&tree, &query.avl, cmp_func);
        node = _get_entry(cur, struct kv_node, avl);
        printf("key %d, value %d\n", node->key, node->value);
    }

    // retrieve smallest key greater than 35
    printf("retrieve smallest key greater than 35\n");
    query.key = 35;
    cur = avl_search_greater(&tree, &query.avl, cmp_func);
    node = _get_entry(cur, struct kv_node, avl);
    printf("key %d, value %d\n", node->key, node->value);

    // retrieve greatest key smaller than 35
    printf("retrieve greatest key smaller than 35\n");
    query.key = 35;
    cur = avl_search_smaller(&tree, &query.avl, cmp_func);
    node = _get_entry(cur, struct kv_node, avl);
    printf("key %d, value %d\n", node->key, node->value);

    // scan in an ascending order
    printf("scan in an ascending order\n");
    cur = avl_first(&tree);
    while(cur) {
        node = _get_entry(cur, struct kv_node, avl);
        printf("key %d, value %d\n", node->key, node->value);
        cur = avl_next(cur);
    }

    // scan in a descending order
    printf("scan in a descending order\n");
    cur = avl_last(&tree);
    while(cur) {
        node = _get_entry(cur, struct kv_node, avl);
        printf("key %d, value %d\n", node->key, node->value);
        cur = avl_prev(cur);
    }

    // remove all key-value pairs
    cur = avl_first(&tree);
    while(cur) {
        node = _get_entry(cur, struct kv_node, avl);
        printf("remove key %d, value %d\n", node->key, node->value);
        cur = avl_next(cur);
        avl_remove(&tree, &node->avl);
        free(node);
    }

    return 0;
}
