#include <stdio.h>
#include <math.h>
int main()
{
    double x,y,z;
    if((scanf("%lf",&x) ==1) && (scanf("%lf",&y)==1))
    {
        z = pow(x,y);
        printf("%lf",z);

    }
    else
    {
        printf("Неправильный ввод чисел!");
 
    }
    return 0;
}