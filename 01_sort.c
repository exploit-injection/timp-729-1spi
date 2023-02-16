#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <malloc.h> 
#include <time.h> 
FILE *f;

void change(int Arr[], int N, int i, int j, int *t)
{
    int V= Arr[i];
    Arr[i] = Arr[j]; //Перестановка элементов
    Arr[j] = V;
    if ((*t) != 0) fprintf(f, "\n");
    else
    (*t)++;
    for (int k = 0; k < N; k++)
    {
        if (k != 0)
        fprintf(f, " ");
        fprintf(f, "%d", Arr[k]);
    }

}
//Сортировка "Расческой"
void comb(int Arr[], int N)
{
int Space = N - 1, i, V, t=0;
while (Space >= 1)
{
    i = 0;
    while ((i + Space) < N)
{
if (Arr[i] > Arr[i + Space]) change(Arr, N, i, i+Space, &t);
i++;
}
Space = Space / 1.247; //фактор уменьшения
}
for (i = 0; i < (N - 1); i++) 
if (Arr[i] > Arr[i + 1])
change(Arr, N, i, i + 1, &t);
}
//Сортировка Шелла
int Shell(int Arr[], int N)
{
    int Space = N, i, j, k, v, t=0; 
    while (Space != 1)
    {
        if (Space % 2 == 1) Space++;
        Space = Space / 2; i = 0;
        j = i + Space;
        while (j < N)
        {
        k = i;
        while (Arr[k] > Arr[j])
        {
            change(Arr, N, i, j, t);
            k = k - Space;
            j = j - Space;
            if ((k < 0) || (j < 0))
            break;
        }
j = i + Space + 1;
i++;
}
}
return 1;
}
int main()
{
int *Arr = (int*)malloc(sizeof(int)), *CArr = (int*)malloc(sizeof(int)), N, i,
t = 0;
double k;
scanf("%lf", &k);
N = k;
Arr = (int*)realloc(Arr, N * sizeof(int));
CArr = (int*)realloc(CArr, N * sizeof(int));
for (i = 0; i < N; i++)
{
scanf("%lf", &k);
Arr[i] = k;
CArr[i] = k;
}
f = fopen("combsort.log", "w+");
fclose(f);
f = fopen("combsort.log", "w+");
comb(Arr, N);
fclose(f); t = 0;
f = fopen("shellsort.log", "w+");
fclose(f);
f = fopen("shellsort.log", "r+");
comb(CArr, N);
fclose(f);
for (int k = 0; k < N; k++)
{
if (k != 0) printf(" ");
printf("%d", Arr[k]);
}
return 0;
}
