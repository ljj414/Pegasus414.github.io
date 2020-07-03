# 本题要求编写程序，计算学生们的平均成绩，并统计及格（成绩不低于60分）的人数。题目保证输入与输出均在整型范围内。
### 输入格式:
输入在第一行中给出非负整数N，即学生人数。第二行给出N个非负整数，即这N位学生的成绩，其间以空格分隔。
### 输出格式:
按照以下格式输出：
```
average = 成绩均值
count = 及格人数
```
其中平均值精确到小数点后一位。
### 输入样例:
```
5
77 54 92 73 60
```
### 输出样例:
```
average = 71.2
count = 4
```
### 解答:
```C
#include<stdio.h>
int main()
{
    int n,grade,i=1,sum=0,count=0;
    double aver;
    scanf("%d",&n);
    if(n>0)
    {
        for(i=1;i<=n;i++)
        {
            scanf("%d",&grade);
            sum+=grade;
            if(grade>=60)
                count++;
        }
        aver=sum*1.0/n;
        printf("average = %.1f\n",aver);
        printf("count = %d\n",count);
    }
    else
    {
        printf("average = 0.0\n");
        printf("count = 0");
    }
    return 0;
}
```
#### 心得体会:注意考虑学生数为零时的情况，其次在循环的设置中应注意步骤及所求数值的选取，在循环的适当位置去求所求的数值。
*2020/7/3*

**by.Pegasus414**
