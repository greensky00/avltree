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
bench_avl_rb

Benchmark results compared to Red Black Trees implemented in Linux kernel archive, using 10M key-value pairs on a machine equipped with i7-3770 CPU (3.4GHz, 4-core 8-thread) are as follows:

RB-Tree insertion: 2.651830 sec elapsed
RB-Tree retrieval: 1.493996 sec elapsed
RB-Tree range scan: 0.175005 sec elapsed
AVL-Tree insertion: 2.655522 sec elapsed (0.14% slower)
AVL-Tree retrieval: 1.392298 sec elapsed (6.81% faster)
AVL-Tree range scan: 0.168931 sec elapsed (3.47% faster)

