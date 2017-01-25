AVL-Tree
========
A high performance generic AVL-Tree container C implementation

Author
======
Jung-Sang Ahn <jungsang.ahn@gmail.com>

Build
=====
```sh
$ make
```

How to use
==========
(refer to example/avl_example.c)

Below example describes how to use AVL-tree as an ordered map of integer pairs.

We define a node for an integer pair, and a comparison function of given two nodes:
```C
#include "avltree.h"

struct kv_node{
    struct avl_node avl;
    int key;
    int value;
};

int cmp_func(struct avl_node *a, struct avl_node *b, void *aux)
{
    struct node *aa, *bb;
    aa = _get_entry(a, struct kv_node, avl);
    bb = _get_entry(b, struct kv_node, avl);

    if (aa->key < bb->key)
        return -1;
    else if (aa->key > bb->key)
        return 1;
    else
        return 0;
}
```

Example code:
```C
// initialize tree
struct avl_tree tree;
avl_init(&tree, NULL);

// insert {1, 10} pair
struct kv_node node;
node.key = 1;
node.value = 10;
avl_insert(&tree, &node.avl, cmp_func);

// insert {2, 20} pair
struct kv_node node_another;
node_another.key = 2;
node_another.value = 20;
avl_insert(&tree, &node_another.avl, cmp_func);

// find the value corresponding to key '1'
struct kv_node query, *ret_kv_node;
struct avl_node *ret_avl_node;
query.key = 1;
ret = avl_search(&tree, &query.avl, cmp_func);
ret_kv_node = _get_entry(ret, struct kv_node, avl);
// Note: ret_kv_node == &node
printf("%d\n", ret_kv_node->value); // 10

// iteration
ret = avl_first(&tree);
while (ret) {
	ret_kv_node = _get_entry(ret, struct kv_node, avl);
	// ... do something with ret_kv_node ...
	ret = avl_next(ret);
}

// remove the pair corresponding to key '1'
query.key = 1;
avl_remove(&tree, &query.avl);
```

Simple benchmark
================
```Sh
$ ./avl_bench
```

Estimated the throughput compared to RB-tree implementation in Linux kernel source code archive and 'set' in STL. Total 10M key-value pairs are used on a machine equipped with i7-3770 CPU (3.4GHz, 4-core 8-thread). The results are averaged over 5 runs, discarding the maximum and the minimum values.

Overall, AVL-tree is up to 3x faster than STL set (or map).

* Throughput (absolute number)

![alt text](https://cloud.githubusercontent.com/assets/5001031/22307365/87d21794-e2f7-11e6-8515-b4b6bea1af3d.png "Throughput")

* Throughput (normalized to STL set)

![alt text](https://cloud.githubusercontent.com/assets/5001031/22307367/8a378e9c-e2f7-11e6-8127-7ebef53147b1.png "Normalized Throughput")



----------
