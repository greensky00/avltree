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
#include <sys/time.h>

#include "avltree.h"
#include "rbwrap.h"

struct kv_node{
    int key;
    int value;
    struct avl_node avl;
};

struct kv_node_rb{
    int key;
    int value;
    struct rb_node rb;
};

static struct timeval _utime_gap(struct timeval a, struct timeval b)
{
    struct timeval ret;
    if (b.tv_usec >= a.tv_usec) {
        ret.tv_usec = b.tv_usec - a.tv_usec;
        ret.tv_sec = b.tv_sec - a.tv_sec;
    }else{
        ret.tv_usec = 1000000 + b.tv_usec - a.tv_usec;
        ret.tv_sec = b.tv_sec - a.tv_sec - 1;
    }
    return ret;
}

int cmp_func(struct avl_node *a, struct avl_node *b, void *aux)
{
    struct kv_node *aa, *bb;
    aa = _get_entry(a, struct kv_node, avl);
    bb = _get_entry(b, struct kv_node, avl);
    if (aa->key < bb->key) return -1;
    else if (aa->key > bb->key) return 1;
    else return 0;
}

int cmp_func_rb(struct rb_node *a, struct rb_node *b, void *aux)
{
    struct kv_node_rb *aa, *bb;
    aa = _get_entry(a, struct kv_node_rb, rb);
    bb = _get_entry(b, struct kv_node_rb, rb);
    if (aa->key < bb->key) return -1;
    else if (aa->key > bb->key) return 1;
    else return 0;
}

int main()
{
    int i, n=10000000;
    struct avl_tree avl_tree;
    struct rb_root rb_tree;
    struct avl_node *avl_node;
    struct rb_node *rb_node;
    struct kv_node *kv_avl, query_avl;
    struct kv_node_rb *kv_rb, query_rb;
    struct timeval begin, end, gap;

    rbwrap_init(&rb_tree, NULL);
    avl_init(&avl_tree, NULL);

    // rb-tree insertion
    gettimeofday(&begin, NULL);
    for (i=0;i<n;++i){
        kv_rb = (struct kv_node_rb*)malloc(sizeof(struct kv_node_rb));
        kv_rb->key = i;
        kv_rb->value = i;
        rbwrap_insert(&rb_tree, &kv_rb->rb, cmp_func_rb);
    }
    gettimeofday(&end, NULL);
    gap = _utime_gap(begin, end);
    printf("RB-Tree insertion: %d.%d sec elapsed\n",
        (int)gap.tv_sec, (int)gap.tv_usec);

    // rb-tree retrieval
    gettimeofday(&begin, NULL);
    for (i=0;i<n;++i){
        query_rb.key = i;
        rb_node = rbwrap_search(&rb_tree, &query_rb.rb, cmp_func_rb);
    }
    gettimeofday(&end, NULL);
    gap = _utime_gap(begin, end);
    printf("RB-Tree retrieval: %d.%d sec elapsed\n",
        (int)gap.tv_sec, (int)gap.tv_usec);

    // rb-tree range scan
    gettimeofday(&begin, NULL);
    rb_node = rb_first(&rb_tree);
    while(rb_node) {
        rb_node = rb_next(rb_node);
    }
    gettimeofday(&end, NULL);
    gap = _utime_gap(begin, end);
    printf("RB-Tree range scan: %d.%d sec elapsed\n",
        (int)gap.tv_sec, (int)gap.tv_usec);


    // avl-tree insertion
    gettimeofday(&begin, NULL);
    for (i=0;i<n;++i){
        kv_avl = (struct kv_node*)malloc(sizeof(struct kv_node));
        kv_avl->key = i;
        kv_avl->value = i;
        avl_insert(&avl_tree, &kv_avl->avl, cmp_func);
    }
    gettimeofday(&end, NULL);
    gap = _utime_gap(begin, end);
    printf("AVL-Tree insertion: %d.%d sec elapsed\n",
        (int)gap.tv_sec, (int)gap.tv_usec);

    // avl-tree retrieval
    gettimeofday(&begin, NULL);
    for (i=0;i<n;++i){
        query_avl.key = i;
        avl_node = avl_search(&avl_tree, &query_avl.avl, cmp_func);
    }
    gettimeofday(&end, NULL);
    gap = _utime_gap(begin, end);
    printf("AVL-Tree retrieval: %d.%d sec elapsed\n",
        (int)gap.tv_sec, (int)gap.tv_usec);

    // avl-tree range scan
    gettimeofday(&begin, NULL);
    avl_node = avl_first(&avl_tree);
    while(avl_node) {
        avl_node = avl_next(avl_node);
    }
    gettimeofday(&end, NULL);
    gap = _utime_gap(begin, end);
    printf("AVL-Tree range scan: %d.%d sec elapsed\n",
        (int)gap.tv_sec, (int)gap.tv_usec);

    return 0;
}
