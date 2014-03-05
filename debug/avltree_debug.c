/*
Copyright (C) 2014 Jung-Sang Ahn <jungsang.ahn@gmail.com>
All rights reserved.

Last modification: Mar 5, 2014

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

#include "avltree_debug.h"

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

size_t _avl_integrity_check(struct avl_node *p)
{
    if (p) {
        int left_depth, right_depth, bf;

        left_depth = _avl_integrity_check(p->left);
        right_depth = _avl_integrity_check(p->right);
        bf = avl_bf(p);

        if (bf != (right_depth - left_depth)) {
            printf("balance factor mismatch!\n");
            printf("node %08lx bf:%d, left_depth:%d, right_depth:%d\n",
                (unsigned long)p, bf, left_depth, right_depth);
            _avl_display(p, 0);
            assert(0);
        }
        if (bf > 1 || bf < -1) {
            printf("balance factor is out of bound!\n");
            printf("bf:%d, left_depth:%d, right_depth:%d\n",
                bf, left_depth, right_depth);
            _avl_display(p, 0);
            assert(0);
        }

        return ((left_depth > right_depth)?(left_depth):(right_depth))+1;
    } else {
        return 0;
    }
}

