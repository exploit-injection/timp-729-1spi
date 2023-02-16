#include <stdio.h>
#include <stdlib.h>

typedef struct node { 
    int value; 
    struct node *left; 
    struct node *right; 
    struct node *parent; 
} node;

typedef struct tree { 
    int num; 
    struct node *head; 
} tree;


void init(tree *t){
    t->head = NULL;
    t->num = 0;
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
        t->num++; 
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
                t->num++; 
                return 0; 
            }
        }
        else 
        {
            if(temp->left != NULL) 
            {
                temp = temp->left; 
            }
            else 
            {
                temp->left = (node*)malloc(sizeof(node)); 
                temp->left->value = value; 
                temp->left->parent = temp; 
                temp->left->right = NULL; 
                temp->left->left = NULL; 
                t->num++; 
                return 0; 
            }
        }
    }
    return 1; //значение уже существует
}

//Вывод обратным обходом с помощью рекурсии
void post_order(node *temp) 
{
    if(temp == NULL) //если этого элемента не существует
        return;
    post_order(temp->left); //запускаем рекурсию для левого поддерева
    post_order(temp->right); //запускаем рекурсию для правого поддерева
    printf("%d ", temp->value); //выводим значение текущего элемента
}

int main() 
{
    tree *t = NULL;
    t = (tree*)malloc(sizeof(tree));
    init(t);
    int a;
    for (int i = 0; i < 7; i++)
    {
        scanf("%d",&a);
        insert(t, a);
    }
    post_order(t->head);
    return 0;
}
