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

Insertion: 3,798,630 ops/sec

Retrieval: 5,905,865 ops/sec

Range scan: 30,821,390 ops/sec

Removal: 43,072,629 ops/sec

* AVL-Tree 

Insertion: 6,993,814 ops/sec (84.11%)

Retrieval: 5,938,835 ops/sec (0.56%)

Range scan: 31,777,305 ops/sec (3.1%)

Removal: 36,972,404 ops/sec (-14.16%)


== Random test ==

* Red Black Tree (in Linux)

Insertion: 1,145,695 ops/sec

Retrieval: 11,364,515 ops/sec

Range scan: 32,776,246 ops/sec

Removal: 39,278,686 ops/sec

* AVL-Tree 

Insertion: 1,118,304 ops/sec (-2.39%)

Retrieval: 11,526,607 ops/sec (1.43%)

Range scan: 35,078,365 ops/sec (7.02%)

Removal: 30,172,648 ops/sec (-23.18%)
