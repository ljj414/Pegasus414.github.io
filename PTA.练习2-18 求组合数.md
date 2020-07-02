# 本题要求编写程序，根据公式![](https://latex.codecogs.com/gif.latex?\inline&space;C_{n}^{m}=n!/(m!(n-m)!) )算出从n个不同元素中取出m个元素（m≤n）的组合数。
建议定义和调用函数`fact(n)`计算`n!`，其中`n`的类型是`int`，函数类型是`double`。
### 输入格式:
输入在一行中给出两个正整数m和n（m≤n），以空格分隔。
### 输出格式:
按照格式“result = 组合数计算结果”输出。题目保证结果在`double`类型范围内。
### 输入样例:
`2 7`
### 输出样例:
`result = 21`
### 解答：
```C
#include<stdio.h>
int main()
{
    double fact(int x);
    int m,n;
    double a,b,c,sum;
    scanf("%d %d",&m,&n);
    a=fact(n);
    b=fact(m);
    c=fact(n-m);
    sum=a/(b*c);                    /*切记(b*c)需带括号，否则会出现运行错误，使得运行结果出错*/
    printf("result = %.0f\n",sum);  /*由于sum为浮点型，输出时应输出整数*/
    return 0;
}
double fact(int x)                  /*使用递归函数求阶乘*/
{
    if(x<=1)  
        return 1;
    else
        return(x*fact(x-1));        /*依次减一，直至x<=1时返回所得的阶乘*/
}

```
**使用for循环求阶乘**
```C
double fact(int x)                  /*从小到大求阶乘*/
{
	int i;
	double product=1;           /*应为0!=1,1!=1，这里pro的初始值设为1,是为了处理传入0的情况*/
	for(i=1; i<=x; i++)
  {
		product=product*i;
	}
	
	return product;
}
```
```C
double fact(int x)                   /*从大到小求阶乘*/
{
	double pro=1;                /*应为0!=1,1!=1，这里pro的初始值设为1,是为了处理传入0的情况*/
	for (int i=x;i>0;i--)
	{
		pro=pro*i;
	}
	return pro;
}
```
**使用while循环求阶乘**
```C
double fact(int x)
{
	int i=1;
	double pro=1;                /*应为0!=1,1!=1，这里pro的初始值设为1,是为了处理传入0的情况*/
	while(i<=x)
	{
		pro=pro*i;
		i++;
	}
	return pro;
}
```
#### 心得体会：
#### 学会阶乘的几种不同的求法，熟练掌握循环的用法。在主函数中应记得带括号以免出错，且需注意输出时输出为整数。
*2020/7/1*

**by.Pegasus414**
