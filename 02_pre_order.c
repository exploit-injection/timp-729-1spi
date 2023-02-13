#include <stdio.h>
#include <stdlib.h>

typedef struct node { 
    int value; 
    struct node *left; 
    struct node *right; 
    struct node *parent; 
} node;

typedef struct tree 
{ 
    int count; 
    struct node *head;
} tree;



void init(tree *t)
{
    t->head = NULL;
    t->count = 0;
}

int insert(tree *t, int value)
{
    if(t->head == NULL) 
    {
        t->head = (node*)malloc(sizeof(node)); 
        t->head->parent = NULL; 
        t->head->left = NULL; 
        t->head->right = NULL; 
        t->head->value = value; 
        t->count++; 
        return 0; 
    }

    node *temp = t->head; 
    while(temp->value != value) 
    {
        if(value > temp->value) 
        {
            if(temp->right != NULL) 
            {
                temp = temp->right; 
            }
            else 
            {
                temp->right = (node*)malloc(sizeof(node)); 
                temp->right->value = value; 
                temp->right->parent = temp; 
                temp->right->right = NULL; 
                temp->right->left = NULL; 
                t->count++; 
                return 0; 
            }
        }
        else 
        {
            if(temp->left != NULL) 
            { temp = temp->left; 
            }
            else 
            {
                temp->left = (node*)malloc(sizeof(node)); 
                temp->left->value = value; 
                temp->left->parent = temp; 
                temp->left->right = NULL; 
                temp->left->left = NULL; 
                t->count++; 
                return 0; 
            }
        }
    }
    return 1; //значение уже существует
}

// Для вывода нужен прямой обход, а значит нужен стек
// Двусвязный список
typedef struct node_list { 
    node *value; 
    struct node_list *next; 
    struct node_list *prev; 
} node_list;

typedef struct list { 
    struct node_list *head; 
    struct node_list *tail; 
} list;

void init_list(list *l)
{
    l->head = NULL;
    l->tail = NULL;
}

int push_front(list *l, node *value) //вставить в начало
{
    node_list *temp = (node_list*)malloc(sizeof(node_list)); 
    temp->value = value; 
    temp->next = l->head; //устанавливаем указатель следующего элемента на тот, что раньше был головным
    temp->prev = NULL; //устанавливаем указатель предыдущего элемента на NULL (никакой элемент не предшествует)
    if (l->head)
        l->head->prev = temp;
    l->head = temp; //делаем созданный элемент головным
    if (l->tail == NULL)
        l->tail = temp;
    return 0; 
}

node_list* pop_first(list *l) //вернуть последнее значение списка
{
    node_list *temp = l->head; //начинаем с начала списка
    if (temp == NULL) 
        return NULL; 
    if (temp->next != NULL) 
        temp->next->prev = NULL; //обновляем предыдущий элемент у следующего
    l->head = temp->next; //обновляем начало списка
    return temp; //возвращаем первый элемент
}

//Прямой обход с использованием стека
void pre_order(tree *t) 
{
    list *l = NULL; //создание очереди
    l = (list*)malloc(sizeof(list)); 
    init_list(l); //инициализирую
    node *temp; //создание хранилища текущего узла дерева
    push_front(l, t->head); //вставляем корень дерева в стек
    while(l->head != NULL) //пока список не пуст
    {
        node_list* temp_list = pop_first(l); //забираем первое значение в списке
        temp = temp_list->value; //сохраняем узел от него
        free(temp_list); //очищаем память от записи списка
        while(temp != NULL) //пока текущий узел не будет пуст
        {
            printf("%d ", temp->value); //выводим значение узла
            if(temp->right) //если есть правый потомок
                push_front(l, temp->right); //то вставляем его в стек
            temp = temp->left;  //переходим в левому потомку
        }
    }
}
int main() {
    tree *t = NULL;
    t = (tree*)malloc(sizeof(tree));
    init(t);
    int a;
    for (int i = 0; i < 7; i++)
    {
        scanf("%d",&a);
        insert(t, a);
    }
    pre_order(t);
    return 0;
}