//
// Created by zxq on 2022/9/23.
//
#ifndef INC_0922_BIGINT_BIGINT_H
#define INC_0922_BIGINT_BIGINT_H

typedef struct LNode {
    struct LNode *priv;
    int number;
    struct LNode *next;
} LNode, *LinkList;

void InputNumber(LinkList &L, char bignum[]);
void ShowNumber(LinkList &L);
LinkList PlusNumber(LinkList &L1, LinkList &L2);
LinkList MinusNumber(LinkList &L1, LinkList &L2);
LinkList MultiplyNumber(LinkList &L1, LinkList &L2);

#endif //INC_0922_BIGINT_BIGINT_H
