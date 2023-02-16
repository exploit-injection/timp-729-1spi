#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>


typedef struct node {
        int value;
    struct node *next;
    struct node *prev;

}node;

typedef struct list
{
    node *head;   //указатели на структуру
    node *tail;

} list;

// инициализация пустого списка
void init( list* l)
{
  l->head=NULL;
  l->tail=NULL;
}

// удалить все элементы из списка
void clean(list *l)
{
    node *tmp1;
    node *tmp2;
    tmp1 = l->head;
    while(tmp1->next != NULL)
    {
        tmp2 = tmp1;
        tmp1 = tmp1->next;
        free(tmp2);
    }
    free(tmp1);
    init(l);
}

// проверка на пустоту списка
int is_empty(list* l)
{
  if (l->head==NULL) return 0;
  else return 1;
}

int find(list *l, int value)
{
    bool data;
    data = false;
    
    for(node *l1 = l->head; l1; l1 = l1->next)
    {
     if(l1->value == value)
        {
            data = true;
            return 1;
      }
    }
    if(data == false)
    {
        return 0;
    }
}

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list*  l,int value)
{
node* l1 = (node*) malloc(sizeof(node));
l1->value = value;
l1->next = 0;
l1->prev = l->tail;
if (l->tail)
{
l->tail->next = l1;
}
l->tail = l1;

if (l->head == NULL)
{
l->head = l1;
}
return 0;
}

// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list* l, int value)
{
node *l1 = (node*) malloc(sizeof(node));
l1->value = value;
l1->next = l->head;
l1->prev = NULL;
if (l->head)
{
    l->head->prev = l1;
}
l->head = l1;

return 0;
}

// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(list *l, node *n,int value)
{
    node *tmp = (node*)malloc(sizeof(node)); 
	tmp->value = value;
	if (tmp != NULL && n != NULL)
    {
		if (n == l->tail) // если вставляется значение в конец списка
        {
            tmp->next = NULL;
            tmp->prev = l->tail;
            (l->tail)->next = tmp;
            l->tail = tmp;
            return 0;
        }
        else 
        {
            tmp->prev = n;
            tmp->next = n->next;
            (n->next)->prev = tmp;
            n->next = tmp;
            return 0;
        }
	}
	else
    {
		return 1; 
	}
    
}

// вставка значения перед указанным узлом, вернуть 0 если успешно
int insert_before(list *l, node* n, int value)
{
    node *tmp1 = (node*)malloc(sizeof(node)); 
	tmp1->value = value; 
	if (tmp1 != NULL && n != NULL)
    {
        if (n == l->head)
        {
            tmp1->next = l->head;
            tmp1->prev = NULL;
            (l->head)->prev = tmp1;
            l->head = tmp1;
            return 0;
        }
        else
        {
            tmp1->prev = n->prev;
            tmp1->next = n;
            (n->prev)->next = tmp1;
            n->prev = tmp1;
            return 0;
        }
    }
	else
    {
		return 1;
	}

}
// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно

int remove_first(list* l, int value)
{
    if (l->head != NULL)
    {
        node* tmp;
		tmp = l->head; 
		while (tmp != NULL && tmp->value != value)
        {
			tmp = tmp->next;
		}
		if (tmp != NULL)
        {
            if (tmp == l->head)
            {
                l->head = tmp->next; 
			    l->head->prev = NULL; 
			    free(tmp); 
			    return 0;
            }
            //если указатель на следующий элемент пустое значение
            if (tmp == l->tail)
            {
                l->tail = tmp->prev;
                l->tail->next = NULL;
                free(tmp);
                return 0;
            }
            (tmp->prev)->next = tmp->next;
            (tmp->next)->prev = tmp->prev;
            return 0;
        }
        else return -1;
    }
    else
    {
        return -1;
    }
}

// удалить последний элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_last(list* l, int value)
{
	if (l->head != NULL)
    {
        node* tmp;
		tmp = l->tail; 
		while (tmp != NULL && tmp->value != value)
        {
			tmp = tmp->prev;
		}
		if (tmp != NULL)
        {
            if (tmp == l->head)
            {
                l->head = tmp->next; 
			    l->head->prev = NULL; 
			    free(tmp); 
			    return 0;
            }
            //если указатель на следующий элемент пустое значение
            if (tmp == l->tail)
            {
                l->tail = tmp->prev;
                l->tail->next = NULL;
                free(tmp);
                return 0;
            }
            (tmp->prev)->next = tmp->next;
            (tmp->next)->prev = tmp->prev;
		    return 0;
        }
        else return -1;
    }
    else
    {
        return -1;
    }
}
// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list* l)
{
    for(node* l1 = l->head; l1; l1 = l1->next)
    {
        printf("%d ", l1->value);
        }
        printf("\n");
}

// вывести все значения из списка в обратном порядке через пробел,
// после окончания вывода перейти на новую строку
void print_invers(list* l)
{
     for(node* l1 = l->tail; l1; l1 = l1->prev)
     {
         printf("%d ", l1->value);
     }
     printf("\n");
      
}

int main()
{
    int n, x, i, k1, k2, k3,j,h;
    list a;
    node* b;
    node *dec = NULL;
    init(&a);
    scanf("%d", &n);
    for (i=1; i<=n; i=i+1)
    {
        scanf("%d", &x);
        push_back(&a, x);
    }
    print(&a);
    scanf("%d%d%d", &k1, &k2, &k3);
    printf("%d ", find(&a, k1));
    printf("%d ", find(&a, k2));
    printf("%d\n", find(&a, k3));
    scanf("%d", &x);
    push_back(&a, x);
    print_invers(&a);
    scanf("%d", &x);
    push_front(&a, x);
    print(&a);
	if (is_empty(&a) == 1)
    {
        if (scanf("%d %d", &j, &x) == 2)
        {
		    dec = (&a)->head;
		    if (dec != NULL && j > 0)
            {
                for(i=1; i<j; i++)
                {
                    dec = dec->next;
                }
			    insert_after(&a, dec, x);
                print_invers(&a);
		    }
	    }
	    else return -1;
    }
	else return -1;
	if (is_empty(&a) == 1)
    {
        if (scanf("%d %d", &h, &x) == 2)
        {
		    dec = (&a)->head;
		    if (dec != NULL && h > 0)
            {
                for(i=1; i<h; i++)
                {
                    dec = dec->next;
                }
			    insert_before(&a, dec, x);
                print(&a);
		    }
	    }
	    else return-1;
    }
	else return -1;
if (is_empty(&a) == 1)
    {
        if (scanf("%d", &x) == 1)
        {
		    remove_first(&a, x);
		    print_invers(&a);
	    }
	    else return -1;
    }
	else  return -1;
    if (is_empty(&a) == 1)
    {
        if (scanf("%d", &x) == 1)
        {
		    remove_last(&a, x);
		    print(&a);
	    }
	    else return -1;;
    }
	else return -1;
    return 0;
};
