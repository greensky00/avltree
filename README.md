AVL-Tree
========
A high-performance generic AVL-Tree C implementation

author
======
Jung-Sang Ahn <jungsang.ahn@gmail.com>

build
=====
make

how to use
==========
refer to example/avl_example.c

simple benchmark
================
./bench_avl_rb

We estimated the performance of our implementation compared to Red Black Tree implemented in Linux kernel source code archive. Total 10M key-value pairs are used on a machine equipped with i7-3770 CPU (3.4GHz, 4-core 8-thread). The results are averaged over 5 runs, discarding the maximum and the minimum values.

== Sequential test ==

* Red Black Tree (in Linux)

Insertion: 3,468,228 ops/sec

Retrieval: 5,607,483 ops/sec

Range scan: 78,506,698 ops/sec

Removal: 49,582,187 ops/sec

* AVL-Tree 

Insertion: 6,802,096 ops/sec (96.15%)

Retrieval: 6,050,063 ops/sec (7.89%)

Range scan: 57,931,834 ops/sec (-26.2%)

Removal: 34,072,982 ops/sec (-31.28%)


== Random test ==

* Red Black Tree (in Linux)

Insertion: 1,061,217 ops/sec

Retrieval: 12,134,484 ops/sec

Range scan: 41,625,908 ops/sec

Removal: 44,442,469 ops/sec

* AVL-Tree 

Insertion: 1,279,334 ops/sec (20.55%)

Retrieval: 12,068,195 ops/sec (-0.55%)

Range scan: 44,533,511 ops/sec (6.99%)

Removal: 33,655,000 ops/sec (-24.27%)
