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

#ifndef _JSAHN_AVL_DEBUG_H
#define _JSAHN_AVL_DEBUG_H

#include <stdio.h>
#include <assert.h>
#include "avltree.h"

#ifdef __AVL_DEBUG

#define __AVL_DEBUG_BF_CHECK(bf) assert((bf) >= -1 && (bf) <= 1)
#define __AVL_DEBUG_LL(p, c, pb, cb) \
    printf("LL %08lx parent (%d) %08lx child (%d)\n", \
        (unsigned long)(p), (pb), \
        (unsigned long)(c), (cb));
#define __AVL_DEBUG_RR(p, c, pb, cb) \
    printf("RR %08lx parent (%d) %08lx child (%d)\n", \
        (unsigned long)(p), (pb), \
        (unsigned long)(c), (cb));
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

#endif  // __AVL_DEBUG

void _avl_display(struct avl_node *p, int depth);
size_t _avl_integrity_check(struct avl_node *p);

#endif
