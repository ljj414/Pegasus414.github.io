# 本题要求对两个正整数m和n（m≤n）编写程序，计算序列和![](https://latex.codecogs.com/gif.latex?m^{2}&plus;\frac{1}{m}&plus;(m&plus;1)^{2}&plus;\frac{1}{m&plus;1}&plus;...&plus;n^{2}&plus;\frac{1}{n})。
### 输入格式:
输入在一行中给出两个正整数m和n（m≤n），其间以空格分开。
### 输出格式:
在一行中按照“sum = S”的格式输出部分和的值S，精确到小数点后六位。题目保证计算结果不超过双精度范围。
### 输入样例:
```
5 10
```
### 输出样例:
```
sum = 355.845635
```
### 解答:
```C
#include<stdio.h>
#include<math.h>
int main()
{
    float m,n,sum,sum1=0,sum2=0;        /*将和部分拆分为两部分各求和较为简单*/
    int i=0,j=0;
    scanf("%f %f",&m,&n);
    for(i=m;i<=n;i++)               
        sum1+=pow(i,2);
    for(j=m;j<=n;j++)
        sum2+=1.0/j;
    sum=sum1+sum2;
    printf("sum = %.6f",sum);
    return 0;
}
```
#### 心得体会:
#### 本题较为简单，仅需注意拆解原式使可以更简单的计算，同时也应注意编写程序时的细节不要出错。
*2020/7/2*

**by.Pegasus414**
