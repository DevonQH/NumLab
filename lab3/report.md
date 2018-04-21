# 第三章-回归分析实验

## 题目：

编程实现输出给定数据的一阶，二阶，三阶的回归多项式，及相应平方误差。

## 实现：

理解了算法， 不难实现所求的一阶回归多项式，推导部分教科书上写的很详细，这里就不作赘述，主要分析代码如下。

```
double phi00 = (double) n;
double phi01 = sum(n, x, 0);
double phi10 = phi01;
double phi11 = sum(n, x, 1);
double phi0f = sum(n, y, 0);
double phi1f = dot(n, x, y);

//calculate the parameters
double a = (phi11*phi0f - phi10*phi1f)/((double)n*phi11 - phi10*phi01);
double b = ((double)n*phi1f - phi10*phi0f)/((double)n*phi11 - phi10*phi01);

//calculate the error
int i = 0;
double error = 0;
for(i = 0; i < n; i++){
	error += (y[i] - (a*x[i]+b))*(y[i] - (a*x[i]+b));
}

//print the results
printf("The linear regression is: %f *x + %f.\n", a, b);
printf("The L2 error of linear regression is %f.\n", error);
```

其中部分函数参照代码中的实现，主要是辅助计算向量和，或者点积的。二阶的实现相对而言，不如一阶那么简单，但是也还可以接受。

```
double phi01 = sum(n, x, 0);
double phi0f = sum(n, y, 0);
double phi1f = dot(n, x, y);
double phi11 = sum(n, x, 1);

//calculate the parameters
double a1 = (n*phi1f - phi01*phi0f) / (n*phi11 - phi01*phi01);
double a0 = phi0f/n - a1*phi01/n;
double e = y[0] - a0 - a1*x[0];

//calculate the error
int i = 0;
float error = 0.0;
for(i = 0; i < n; i++){
	phi01 = y[i] - (e*x[i]*x[i] + a1*x[i] + a0);
	error += phi01*phi01;
}

//print the function and error
printf("The quadratic regression is %f * x^2 + %f * x + %f.\n", e, a1, a0);
printf("The L2 error of the quadratic regression is %f.\n", error);
```

但是，要实现三阶的回归分析，我感觉编程实现的难度就很大了，没有实现这个功能。

## 结果

运行的结果是

The linear regression is: -0.954464 *x + 2.004357.
The L2 error of linear regression is 90.151105.
The quadratic regression is -1.508179 * x^2 + 2.004357 * x + -0.954464.
The L2 error of the quadratic regression is 66.230919.

## 思考

通过这次实验，对于回归分析的了解更加深刻了，但是有一个遗憾是没有实现三阶的回归，我想可能是自己能力还有欠缺，而且对算法的理解还不算到位。以后要继续学习思考，这些问题也都需要向同学老师请教。