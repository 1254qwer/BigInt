#include <iostream>
#include "BigInt.h"

int main() {
    system("chcp 65001");
    LinkList num1, num2, result;
    char PureNum1[30], PureNum2[30];

    printf("请输入第一个数字:");
    scanf("%s", PureNum1);
    InputNumber(num1, PureNum1);
    printf("请输入第二个数字:");
    scanf("%s", PureNum2);
    InputNumber(num2, PureNum2);
    printf("\n");

    printf("您输入的第一个数字是:");
    ShowNumber(num1);printf("\n");
    printf("您输入的第二个数字是:");
    ShowNumber(num2);
    printf("\n\n");

    printf("计算加法结果为:");
    result = PlusNumber(num1, num2);
    ShowNumber(result);
    printf("\n");

    printf("计算减法结果为:");
    result = MinusNumber(num1, num2);
    ShowNumber(result);
    printf("\n");

    printf("计算乘法结果为:");
    result = MultiplyNumber(num1, num2);
    ShowNumber(result);
    printf("\n");

//    system("pause");
    return 1;
}
