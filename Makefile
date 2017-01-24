AVL_TREE = avltree/avltree.o 
RB_TREE = rbtree/rbtree.o rbtree/rbwrap.o
BENCH = bench/bench.o $(AVL_TREE) $(RB_TREE)
EXAMPLE = example/avl_example.o $(AVL_TREE) 

PROGRAMS = \
	avl_example \
	avl_bench \
	
LDFLAGS = 

CFLAGS = \
	-g -D_GNU_SOURCE \
	-I. -I./avltree -I./rbtree \
	-O2 \
	-Wall \

CXXFLAGS = $(CFLAGS) --std=c++11 

all: $(PROGRAMS)

avl_example: $(EXAMPLE)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
avl_bench: $(BENCH)
	$(CXX) $(CFLAGS) $^ -o $@ $(LDFLAGS)
clean:
	rm -rf $(PROGRAMS) ./*.o ./*.so ./*/*.o ./*/*.so
