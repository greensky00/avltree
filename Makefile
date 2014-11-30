AVL_TREE = avltree/avltree.o 
RB_TREE = rbtree/rbtree.o rbtree/rbwrap.o
BENCH = bench/bench.o $(AVL_TREE) $(RB_TREE)
EXAMPLE = example/avl_example.o $(AVL_TREE) 

PROGRAMS = \
	avltree_example \
	bench_avl_rb \
	
LDFLAGS = -lpthread
CFLAGS = \
	-g -D_GNU_SOURCE \
	-I. -I./avltree -I./rbtree \
	-fPIC \
	-O2 \
	#-D__AVL_DEBUG \
	
all: $(PROGRAMS)

avltree_example: $(EXAMPLE)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
bench_avl_rb: $(BENCH)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
clean:
	rm -rf $(PROGRAMS) ./*.o ./*.so ./*/*.o ./*/*.so
