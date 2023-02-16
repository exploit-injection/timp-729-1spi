#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int value;
    struct node *next;

}node;

typedef struct list
{
    node *head; //указатели на структуру
    node *tail;
} list;

//инициализация пустого списка
void init(list *l)
{
    l->head = NULL; // указатель на первый элемент
    l->tail = NULL; // указатель на конечный элемент
}
//удаление всех элементов из списка
void clean(list *l)
{
    node  *tmp = l->head;
    while(tmp)
    {
        node *tmpNode = tmp;
        tmp = tmp->next;
        free (tmpNode);
    }
    l->head = NULL;
    /*node *tmp1;
    node *tmp2;
    tmp1 = l->head;
    while(tmp1->next != NULL)
    {
        tmp2 = tmp1;
        tmp1 = tmp1->next;
        free(tmp2);
    }   
    free(tmp1);
    init(l);*/
}
//проверка на пустоту списка
int is_empty(list *l)
{
    if (l->head == NULL) return 0;
    else return 1;
}

int find(list *l, int value)
{
    bool data;
    data = false;
    
    for(node* l1 = l->head; l1; l1 = l1->next)
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

//вставка значения в конец списка, вернуть 0 если успешно
int push_back(list *l, int value)
{
    node *new_node = (node*)malloc(sizeof(node)); //создаем новый узел
    new_node->value = value; //присваиваем значение
    new_node->next = NULL; //присваиваем значение NULL
    if (l->head == NULL)
    {
        l->head=new_node;
    }
    else if (l->head->next == NULL)
    {
        l->head->next = new_node;
    }
    else
    {
        l->tail->next = new_node;
    }
        l->tail = new_node;
    return 0;

}

// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list* l, int value)
{
    node *new_node = (node*)malloc(sizeof(node)); //создаем новый узел
    new_node->value = value; //присваиваем значение
    if (l->head == NULL)
    {
        new_node->next = NULL; //присваиваем указателю new_node NULL
        l->tail = new_node; 
    }
else if (l->head->next == NULL) new_node->next = l->tail;
else new_node->next = l->head;
    l->head = new_node;
return 0;
}
//вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(list *l, int value, int data)
{
    int i = 0;
    node *tmp = l->head;
    while (tmp->next != NULL && i<value)
    {
        tmp=tmp->next;
        i++;
        if(tmp->next == NULL && i<value)
        {
            return -1;
        }
    }
    if(i!=value)
    {
        return 0;
    }
    else
    {
    node *l1;
    node *tmp2 = l->head;
    l1 = (node*)malloc(sizeof(node));
    l1->value = data;
    l1->next = NULL;
    for(i = 1; i < value; i++)
    {
        tmp2 = tmp2->next;
    }
    if (value <= 0)
    {
        return 0;
    }
    else
    {
        if (tmp2->next != NULL)
        {
            l1->next = tmp2->next;
        }
        tmp2->next = l1;
        return 0;
    }
    }
}

//удалить первый элемент из списка с указанным значением,
// вернуть 0 если успешно
int remove_node(list* l, int value)
{
      struct node* tmp1;
      struct node* tmp2;
      tmp1 = l->head;
      while (tmp1->value != value)
      {
              tmp2 = tmp1;
              tmp1 = tmp1->next;
              if (tmp1 == NULL)
              {
                  return -1;
              }
      }
      if (tmp1 == l->head) l->head = tmp1->next; //если удаляемый элемент первый
      else if (tmp1 == l->tail) //если удаляемый элемент последний
      {
              tmp2->next = NULL;
              l->tail = tmp2;
      }
      else tmp2->next = tmp1->next;
      free(tmp1);
      return 0;


}

//вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list* l)
{
    if (is_empty(l) == 1)
    {
        node* tmp;
        tmp = l->head;
        while (tmp->next != NULL)
        {
            printf("%d ", tmp->value);
            tmp = tmp->next;
        }
        printf("%d\n", l->tail->value);
    }

}
int main()
{
    int n, x, i, k1, k2, k3,j,x1;
    j = 0, x1 = 0;

    list a;
    node* b;
    init(&a);
    scanf("%d", &n);

    for (i = 1; i <= n; i = i+1)
    {
        if(n<0)
        {
            return 1;
        }
        scanf("%d", &x);
        push_back(&a, x);
    }

    print(&a);
    scanf("%d%d%d", &k1, &k2, &k3);
    printf("%d ", find(&a, k1));
    printf("%d ", find(&a, k2));
    printf("%d\n", find(&a, k3));
    if (is_empty(&a) == 1)
    {
        if (scanf("%d", &x) == 1)
        {
		    push_back(&a, x);
            print(&a);
	    }
	    else return -1;
    }
	else  return -1;
    if (is_empty(&a) == 1)
    {
        if (scanf("%d", &x) == 1)
        {
		    push_front(&a, x);
            print(&a);
	    }
	    else return -1;
    }
	else  return -1;
    scanf("%d%d", &j, &x1);
		    insert_after(&a, j, x1);
            print(&a);
    if (is_empty(&a) == 1)
    {
        if (scanf("%d", &x) == 1)
        {
		    remove_node(&a, x);
            print(&a);
	    }
	    else return -1;
    }
	else  return -1;

    return 0;
}