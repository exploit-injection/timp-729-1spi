#include <stdio.h>
int main()
{
double x;
long int n,i, count;
i = 0;
count = 0;
if(scanf("%ld",&n)==1)
{
    for (i=0; i<n;i++)
    {
        if (scanf("%lf",&x)==1)
        {
            if(x>0)
            count++;
        }
        else if (scanf("%lf",&x)!=1)
        {
            printf("Неверный ввод чисел!");
        }
    }
    printf("%ld", count);
}
else 
{
    printf("Неверный ввод чисел!");
}
return 0;
}


