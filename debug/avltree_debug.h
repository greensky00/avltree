#ifndef _JSAHN_AVL_DEBUG_H
#define _JSAHN_AVL_DEBUG_H

#ifdef __AVL_DEBUG

#define __AVL_DEBUG_BF_CHECK(bf) assert((bf) >= -1 && (bf) <= 1)
#define __AVL_DEBUG_LL(p, c) \
    printf("LL %08lx parent (%d) %08lx child (%d)\n", \
        (unsigned long)(p), avl_bf(p), \
        (unsigned long)(c), avl_bf(c));
#define __AVL_DEBUG_RR(p, c) \
    printf("RR %08lx parent (%d) %08lx child (%d)\n", \
        (unsigned long)(p), avl_bf(p), \
        (unsigned long)(c), avl_bf(c));
#define __AVL_DEBUG_BAL_BEGIN(node, bf, height_diff) \
    printf("balance node %08lx (%d + %d = %d)\n", \
        (unsigned long)(node), avl_bf(node), bf, height_diff);
#define __AVL_DEBUG_BAL_END(node) \
    printf("balance node end %08lx (%d)\n", \
        (unsigned long)(node), avl_bf(node));
#define __AVL_DEBUG_INSERT(node) \
    printf("insert %08lx\n", (unsigned long)(node));
#define __AVL_DEBUG_REMOVE(node) \
    printf("remove %08lx\n", (unsigned long)(node));
#define __AVL_DEBUG_DISPLAY(tree) _avl_display((tree)->root, 0)

char space[256];
char *_space(int n)
{
    int i;
    for (i=0;i<n;++i) space[i]=' ';
    space[i] = 0;
    return space;
}

void _avl_display(struct avl_node *p, int depth)
{
    if(p)
    {
        if (p->left) assert(avl_parent(p->left) == p);
        _avl_display(p->left, depth+1);

#ifdef _AVL_NEXT_POINTER
        printf("%s[%d %08lx %08lx %08lx %08lx %08lx %08lx %2d]\n",
            _space(depth), depth, (unsigned long)p,
            (unsigned long)avl_parent(p),
            (unsigned long)p->left, (unsigned long)p->right,
            (unsigned long)p->prev, (unsigned long)p->next,
            avl_bf(p));
#else
        printf("%s[%d %08lx %08lx %08lx %08lx %2d]\n",
            _space(depth), depth, (unsigned long)p,
            (unsigned long)avl_parent(p),
            (unsigned long)p->left, (unsigned long)p->right,
            avl_bf(p));
#endif

        if (p->right) assert(avl_parent(p->right) == p);
        _avl_display(p->right, depth+1);
    }
}

#endif

#endif
