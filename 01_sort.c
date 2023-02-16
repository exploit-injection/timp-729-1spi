#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <time.h>
FILE *f;

int heapUp(int Arr[], int Size, int *t)
{
int i, iS, j, r, l, RD, LD, v, N=Size;
iS = (Size / 2) - 1; //количество первых элементов, необходимых для "обработки"
while (Size != 0) //пока есть элементы в дереве
{
    i = iS;
    while (i != (-1))
    {
        j = i;
        while (1)
        {
            l = 2 * j + 1; // первый потомок корневого элемента
            r = 2 * j + 2; // ворой потомок корневого элемента
            if (l < Size)
            LD = Arr[l];
            else
            LD = -1001;
            if (r < Size)
            RD = Arr[r];
            else
            RD = -1001;
            if (RD > LD) //если значение второго потомка > первого
            {
                if (RD > Arr[j]) //если значение второго потомка > элемента для обработки
                {
                    v = Arr[j];
                    Arr[j] = Arr[r]; //меняются местами элементы-> больший элемент в начало
                    Arr[r] = v;
                    j = r;
                    if ((*t) != 0) fprintf(f, "\n");
                    else
                    (*t)++;
                    for (int k = 0; k < N; k++) //пошаговая запись изменения элементов в файл
                    {
                        if (k != 0)
                        fprintf(f, " ");
                        fprintf(f, "%d", Arr[k]);
                    }
                }
                else
                break;
            }
            else
            {
                if (LD > Arr[j]) //если значение первого потомка > значения элемента для обработки
                {
                    v = Arr[j];
                    Arr[j] = Arr[l]; //меняются местами элементы-> больший элемент в начало
                    Arr[l] = v;
                    j = l;
                    if ((*t) != 0) fprintf(f, "\n");
                    else
                    (*t)++;
                    for (int k = 0; k < N; k++) //пошаговая запись изменения элементов в файл
                    {
                        if (k != 0)
                        fprintf(f, " ");
                        fprintf(f, "%d", Arr[k]);
                    }
                }
                else
                break;
            }
        }
        i--;
    }
    Size--;
    if (Arr[0] > Arr[Size]) //если первый элемент больше последнего
    {
        v = Arr[0];
        Arr[0] = Arr[Size]; //элементы меняются местами
        Arr[Size] = v;
        if ((*t) != 0) fprintf(f, "\n");
        else
        (*t)++;
        for (int k = 0; k < N; k++) // пошаговая запись изменений элементов в файл
        {
            if (k != 0)
            fprintf(f, " ");
            fprintf(f, "%d", Arr[k]);
        }
    }
}
return 0;
}
int quickUp(int Arr[], int B, int E, int N, int *t)
{
int i = B, j = E, v = 0, el = Arr[(E + B) / 2], elN=(E+B)/2;
while (1)
{
    while (Arr[i] < el) i++; //пока первый элемент < опорного (усредненный элемент)
    while (Arr[j] > el) j--; //пока последний элемент > опорного 
    if (i < j)
    {
        v = Arr[i];
        Arr[i] = Arr[j]; //элементы меняются местами
        Arr[j] = v;
        if (i != elN) j--;
        else
        elN = j;
        if ((j + 1) != elN) i++;
        else
        elN = i;
        if ((*t) != 0)
        fprintf(f, "\n");
        else
        (*t)++;
for (int k = 0; k < N; k++) //пошаговая запись изменений элемента в файл
{
    if (k != 0)
    fprintf(f, " ");
    fprintf(f, "%d", Arr[k]);
}
}
else
break;
}
if ((i - B-1) > 0)
quickUp(Arr, B, i-1, N, t); //рекурсивное выполнение сортировки
if ((E - i-1) > 0) 
quickUp(Arr, i+1, E, N, t); return 0;
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
        f = fopen("quicksort.log", "w+");
        fclose(f);
        f = fopen("quicksort.log", "w+");
        quickUp(Arr, 0, N - 1, N, &t);
        fclose(f);
        t = 0;
        f = fopen("heapsort.log", "w+");
        fclose(f);
        f = fopen("heapsort.log", "r+");
        heapUp(CArr, N, &t);
        fclose(f);
        for (int k = 0; k < N; k++)
        {
            if (k != 0) printf(" ");
            printf("%d", Arr[k]);
        }
    return 0;
}
