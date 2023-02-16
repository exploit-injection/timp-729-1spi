#include <stdio.h>
#include <math.h>
int main()
{
double i,x,z,k,l,n;
z=0;
if(scanf("%lf",&n)==1)
{
    for (i=1; i<=n;i++)
    {
        if (scanf("%lf",&x)==1)
        {
            k = pow(x,3);
            l = pow(-1.0,i+1);
            z += l*k;
        }
        else if (scanf("%lf",&x)!=1)
        {
            printf("Неверный ввод чисел!");
        }
    }
    printf("%lf", z);
}
else 
{
    printf("Неверный ввод чисел!");
}
return 0;
}