//
// Created by zxq on 2022/9/23.
//
#include <cstdio>
#include <cstring>
#include "BigInt.h"

void InputNumber(LinkList &L, char bignum[]) {
    // 输入大整数，最终存入链表L
    LinkList p, q;
    int i, tmp = 0;
    int pointer; // 指示元素开头应该在第几位断开
    int length = (int) strlen(bignum);
    // 读取位数，3位一断，转换格式，存入链表
    pointer = length % 3 == 0 ? 3 : length % 3; // 读取开头的几位
    L = new LNode;
    L->priv = nullptr;
    L->next = nullptr;
    for (i = 0; i < pointer; i++) {
        tmp = tmp * 10 + bignum[i] - 48; // accii表中48对应字符'0'
    }
    L->number = tmp;
    p = L;
    for (i = pointer; i < length; i += 3) {
        q = new LNode;
        p->next = q;
        q->priv = p;
        tmp = 0;
        for (int j = 0; j < 3; j++) {
            tmp = tmp * 10 + bignum[i + j] - 48; //accii表中48对应字符'0'
        }
        q->number = tmp;
        p = q;
    }
    p->next = nullptr;
}

void ShowNumber(LinkList &L) {
    // 展示数据，效果类似于2,147,483,648,904
    LinkList p = L;
    int tmp = p->number;
    if (!p->next) {   // 处理只有一节的数字
        printf("%d", tmp);
        return;
    } else {  // 多节数字，第一节带，正常显示
        printf("%d,", tmp);
        p = p->next;
    }
    while (p->next) {  //显示后面每一节，直到倒数第二节数字
        printf("%.3d,", p->number);
        p = p->next;
    }
    printf("%.3d", p->number);  // 显示最后一节数字
}

LinkList PlusNumber(LinkList &L1, LinkList &L2) {
    // 加法
    int tmp, jin = 0;
    LinkList point1 = L1, point2 = L2, result, temp, newnode;
    // 归尾
    while (point1->next || point2->next) {
        if (point1->next) {
            point1 = point1->next;
        }
        if (point2->next) {
            point2 = point2->next;
        }
    }
    temp = new LNode;
    temp->priv = nullptr;
    temp->next = nullptr;
    // 开始运算
    while (point1 && point2) {   // 从尾部开始
        newnode = new LNode;
        newnode->priv = nullptr;
        tmp = point1->number + point2->number + jin;
        if (tmp >= 1000) {
            jin = 1;
        } else {
            jin = 0;
        }
        newnode->number = tmp % 1000;
        newnode->next = temp;
        temp->priv = newnode;
        temp = newnode;
        point1 = point1->priv;
        point2 = point2->priv;
    }
    // 处理两数中较长位，直接落下
    if (!point1 && point2) {   // point2较长
        while (point2) {
            newnode = new LNode;
            newnode->priv = nullptr;
            tmp = point2->number + jin;
            if (tmp >= 1000) {
                jin = 1;
            } else {
                jin = 0;
            }
            newnode->number = tmp % 1000;
            newnode->next = temp;
            temp->priv = newnode;
            temp = newnode;
            point2 = point2->priv;
        }
    }
    if (point1) {   // point1较长
        while (point1) {
            newnode = new LNode;
            newnode->priv = nullptr;
            tmp = point1->number + jin;
            if (tmp >= 1000) {
                jin = 1;
            } else {
                jin = 0;
            }
            newnode->number = tmp % 1000;
            newnode->next = temp;
            temp->priv = newnode;
            temp = newnode;
            point1 = point1->priv;
        }
    }
    // 处理减法退位
    if (jin) {
        newnode = new LNode;
        newnode->priv = nullptr;
        newnode->number = jin;
        newnode->next = temp;
        temp = newnode;
    }
    result = temp;
    // 去除辅助尾结点
    while (temp->next) {
        temp = temp->next;
    }
    temp = temp->priv;
    temp->next = nullptr;
    return result;
}

LinkList MinusNumber(LinkList &L1, LinkList &L2){
    // 减法
    int tmp, tui = 0;
    int len1=0, len2=0;
    int equal = 0;
    LinkList point1 = L1, point2 = L2, result, temp, newnode;
    // 归尾
    while (point1->next || point2->next) {
        if (point1->next) {
            point1 = point1->next;
            len1++;
        }
        if (point2->next) {
            point2 = point2->next;
            len2++;
        }
    }
    // 处理因位数不足产生的负数
    if(len2 > len1){
        result = MinusNumber(L2, L1);
        printf("-");
        return result;
    }
    // 处理两数相等，直接返回0
    if(len1 == len2){
        point1 = L1, point2 = L2;
        while (point1 && point2) {
            if(point1->number == point2->number){
                equal++;
            }
            point1 = point1->next;
            point2 = point2->next;
        }
        if (equal == len1 + 1){
            result = new LNode;
            result->priv = nullptr;
            result->next = nullptr;
            result->number = 0;
            return result;
        }
        else{
            point1 = L1, point2 = L2;
            while (point1->next || point2->next) {
                if (point1->next) {
                    point1 = point1->next;
                }
                if (point2->next) {
                    point2 = point2->next;
                }
            }
        }
    }
    temp = new LNode;
    temp->priv = nullptr;
    temp->next = nullptr;
    // 开始运算
    while (point1 && point2) {  // 从尾部开始
        newnode = new LNode;
        newnode->priv = nullptr;
        tmp = point1->number - point2->number - tui;
        if (tmp < 0) {
            tui = 1;
            tmp += 1000;
        } else {
            tui = 0;
        }
        newnode->number = tmp % 1000;
        newnode->next = temp;
        temp->priv = newnode;
        temp = newnode;
        point1 = point1->priv;
        point2 = point2->priv;
    }
    // 处理两数中较长位，直接落下
    if (!point1 && point2) {  // point2较长
        while (point2) {
            newnode = new LNode;
            newnode->priv = nullptr;
            tmp = point2->number - tui;
            if (tmp < 0) {
                tui = 1;
                tmp += 1000;
            } else {
                tui = 0;
            }
            newnode->number = tmp % 1000;
            newnode->next = temp;
            temp->priv = newnode;
            temp = newnode;
            point2 = point2->priv;
        }
    }
    if (point1) {  // point1较长
        while (point1) {
            newnode = new LNode;
            newnode->priv = nullptr;
            tmp = point1->number - tui;
            if (tmp < 0) {
                tui = 1;
                tmp += 1000;
            } else {
                tui = 0;
            }
            newnode->number = tmp % 1000;
            newnode->next = temp;
            temp->priv = newnode;
            temp = newnode;
            point1 = point1->priv;
        }
    }
    // 处理减法退位
    while (temp) {
        if(temp->number){
            break;
        }
        temp = temp->next;
    }
    result = temp;
    // 处理因位数相同但不够减产生的负数
    if(tui){
        result = MinusNumber(L2, L1);
        printf("-");
        return result;
    }
    // 去除辅助尾结点
    while (temp->next) {
        temp = temp->next;
    }
    temp = temp->priv;
    temp->next = nullptr;
    return result;
}

LinkList MultiplyNumber(LinkList &L1, LinkList &L2){
    // 乘法
    LinkList point1 = L1, point2 = L2, result, temp, newnode;
    int tmp, i, j=1;
    int list[1000]; // 单步乘法数据存入该表格
    for(i=0; i<1000; i++){   // 表格数值归零
        list[i] = 0;
    }
    // 开始单步乘法运算
    while(point1){
        i = 1;
        while (point2){
            list[i+j] += (point1->number * point2->number);
            i++;
            point2 = point2->next;
        }
        point1 = point1->next;
        point2 = L2;
        j++;
    }
    // 处理进位
    for(tmp=(i+j-2); tmp>1; tmp--){
        if(list[tmp] >= 1000){
            list[tmp-1] += list[tmp] / 1000;
            list[tmp] = list[tmp] % 1000;
        }
    }
    if(list[1] == 0){  // 判断最终结果是否因进位有位数增加
        newnode = new LNode;
        newnode->priv = nullptr;
        for(tmp = 2; tmp <= (i+j-2); tmp++){
            newnode->number = list[tmp];
            temp = newnode;
            newnode = new LNode;
            temp->next = newnode;
            newnode->priv = temp;
            newnode->number = -1;
        }
    } else{
        newnode = new LNode;
        newnode->priv = nullptr;
        for(tmp = 1; tmp <= (i+j-2); tmp++){
            newnode->number = list[tmp];
            temp = newnode;
            newnode = new LNode;
            temp->next = newnode;
            newnode->priv = temp;
            newnode->number = -1;
        }
    }
    // 去除辅助尾结点
    if(newnode->number == -1){
        newnode = newnode->priv;
        newnode->next = nullptr;
    }
    // 回到起始点
    while(newnode->priv){
        newnode = newnode->priv;
    }
    result = newnode;
    return result;
}