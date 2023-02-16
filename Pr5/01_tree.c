#include <stdio.h>
#include <stdlib.h>


// Структура для хранения узла дерева.
typedef struct node 
{
	int value;
	struct node *left;
	struct node *right;
	struct node *parent;
} node;


// Структура для хранения дерева.
// Хранит ссылку на корень дерева и количество элементов в дереве
typedef struct tree 
{
	int count;
	struct node *root;
} tree;


// Инициализация дерева
void init(tree* t) 
{
    t = malloc(sizeof(tree));
    t->root = NULL;
    t->count = 0;
};

// Удалить все элементы из дерева
void clean_tree(node* tmp) 
{
    if (tmp->right) 
    {
        clean_tree(tmp->right);
    }
    if (tmp->left) 
    {
        clean_tree(tmp->left);
    }
    tmp->right = NULL;
    tmp->parent = NULL;
    tmp->left = NULL;
    free(tmp);
};

void clean(tree* t) 
{
        clean_tree(t->root);
        t->count=0;
        t->root = NULL;
    return;
}
//поиск значения в дереве
node* find_node(node* tmp, int value) {
    if (tmp->value == value)
        return tmp;
    else {
        if (value < tmp->value) {
            if (tmp->left != NULL)
                return(find_node(tmp->left, value));
            else
                return NULL;
        }
        else {
            if (tmp->right != NULL)
                return(find_node(tmp->right, value));
            else
                return NULL;
        }
    }
}

node* findInfo(tree* t, int value) {
    node *tmp = find_node(t->root, value);
    return tmp;
}
// Поиск элемента по значению. Вернуть NULL если элемент не найден
node* find(tree* t, int value) {
    return (find_node(t->root, value));
};

node* create(node* parent, int value) {
	node* tmp = malloc(sizeof(node));
    tmp->left = tmp->right = NULL;
    tmp->value = value;
    tmp->parent = parent;
}
// Вставка значения в дерево:
// 0 - вставка выполнена успешно
// 1 - элемент существует
// 2 - не удалось выделить память для нового элемента
int insert(tree* t, int value) {
	node *tmp = NULL;

	// Если корень дерева пуст
    if (t->root == NULL) {
        t->root = create(tmp, value);
		t->count++;
        return 0;
    }

    tmp = t->root;
    while (tmp) {
		// Если значение меньше корневого
        if (value > tmp->value) {
            if (tmp->right) {
                tmp = tmp->right;
                continue;
            } else {
                tmp->right = create(tmp, value);
				t->count++;
                return 0;
            }
		// Если значение больше корневого
        } else if (value < tmp->value) {
            if (tmp->left) {
                tmp = tmp->left;
                continue;
            } else {
                tmp->left = create(tmp, value);
				t->count++;
                return 0;
            }
        } else if (value == tmp->value)
			return 1;
		else {
            return 2;
        }
    }
};
// Минимальный элемент дерева
node *min(node *root)
{
    node *tmp = root;
    while (tmp -> left != NULL)
        tmp = tmp -> left;
    return tmp;
}

// Максимальный элемент дерева
node *max(node *root)
{
    node *tmp = root;
    while (tmp -> right != NULL)
        tmp = tmp -> right;
    return tmp;
}

// Удалить элемент из дерева:
// 0 - удаление прошло успешно
// 1 - нет элемента с указанным значением
int remove_node(tree* t, int value) {
    // Поиск удаляемого узла по ключу
    node *l = NULL, *m = NULL;
    l = find_node(t->root, value);
    if (l == NULL)
        return 1;
// Если у вершины нет поддерева
    if ((l -> left == NULL) && (l -> right == NULL))
    {
        if (l != t->root) {
            m = l -> parent;
            if (l == m -> right)
                m -> right = NULL;
            else m -> left = NULL;
            free(l);
        }
        else {
            t->root = NULL;
        }
        t->count--;
        return 0;
    }
// Если у вершины поддерево справа
    if ((l -> left == NULL) && (l -> right != NULL))
    {
        if (l!=t->root) {
            m = l -> parent;
            if (l == m -> right) 
                m -> right = l -> right;
            else 
                m -> left = l -> right;
        }
        else {
            t->root = l->right;
        }
        free(l);
        t->count--;    
        return 0;
    }
// Если у вершины поддерево слева
    if ((l -> left != NULL) && (l -> right == NULL))
    {
        if (l!=t->root) {
            m = l -> parent;
            if (l == m -> right) m -> right = l -> left;
            else m -> left = l -> left;
        }
        else {
            t->root = l->left;
        }
        free(l);
        t->count--;
        return 0;
    }
// Если у вершины оба поддерева
    if ((l -> left != NULL) && (l -> right != NULL))
    {
        if (l == t->root) {
            m = min(l->right);
            if (m == l->right) {
                m->left = l->left;
                t->root = m;
                t->count--;
                free(l);
                return 0;
            } 
            if (m == m->parent->right) 
                m->parent->right = NULL;
            else m->parent->left = NULL;
            if (m->right == NULL) {
                l -> value = m -> value;
                t->count--;
                free(m);
            }
            else if (m->right != NULL) {
                l -> value = m -> value;
                m->parent->left = m->right;
                t->count--;
                free(m);
            }
        }
        else {
            m = min(l->right);
            if (m == l->right) {
                m->left = l->left;
                if (l == l->parent->right) 
                    l->parent->right = m;
                else l->parent->left = m;
                t->count--;
                free(l);
                return 0;
            } 
            if (m == m->parent->right) 
                m->parent->right = m->right;
            else m->parent->left = NULL;
            l->value = m->value;
            t->count--;
            free(m);
        }
    }
    return 0;
};

// Удалить минимальный элемент из поддерева, корнем которого является n
// Вернуть значение удаленного элемента
int remove_min(node* n) {
	while (n->left) {
        n = n->left;
    }
	int value = n->value;
	n->parent->left = NULL;
	free(n);
    return value;
};

// Выполнить правое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно 
int rotate_right(tree* t, node* n) {
    if (!n -> left)
        return 1;
    node *p = n -> parent;
    node *x = n -> left;
    n -> left = x -> right;
    x -> right = n;
    if (p) {
        if (n == p -> right)
            p -> right = x;
        else if (n == p -> right)
            p -> left = x;
    }
    if(n -> left)
        n -> left -> parent = n;
    n -> parent = x;
    x -> parent = p;
    if(n == t -> root) 
        t -> root = x;
    return 0;
}

// Выполнить левое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно
int rotate_left(tree* t, node* n) {
    if (!n -> right)
        return 1;
    node *p = n -> parent;
    node *x = n -> right;
    n -> right = x -> left;
    x -> left = n;
    if (p) {
        if (n == p -> left)
            p -> left = x;
        else if (n == p -> right)
            p -> right = x;
    }
    if (n -> right)
        n -> right -> parent = n;
    n -> parent = x;
    x -> parent = p;
    if(n == t -> root)
        t -> root = x;
    return 0;
}

// поиск высоты дерева
int deep(node *n) {
    int right = 0, left = 0;
    if (n -> right)
        right = deep(n -> right);
    if (n -> left)
        left = deep(n -> left);
    if (right > left)
        return (right + 1);
    return (left + 1);
}


// Вывести все значения из поддерева, корнем которого является n
// по уровням начиная с корня.
// Каждый уровень выводится на своей строке. 
// Элементы в строке разделяются пробелом. Если элемента нет, заменить на _. 
// Если дерево пусто, вывести -
void print(node* n) {
    if (!n) {
        printf("-\n");
        return;
    }
    node* height = n;
    node *Temp= n;
    int levels = 0, count_levels, count_elements, dir_indicator, y;
    int *comb;
    levels = deep(height); // нахождение глубины дерева
    comb = malloc(sizeof(int)); // выделение динам. памяти

    for (count_levels = 0; count_levels < levels; count_levels++) { // идем до последнего уровня

        if (count_levels != 0) {
            comb = realloc(comb, count_levels* sizeof(int));
            for (count_elements = 0; count_elements < count_levels; count_elements++)
            comb[count_elements] = 0; // присвоение значений счетчикам уровня
        }
    count_elements = 1;
    y = count_levels; // определение степени вложенности

    // наращивание количества элементов в
    // зависимости от уровня
    while (y != 0) {
        count_elements = count_elements * 2;
        y--;
    }

    while (count_elements != 0) {
        dir_indicator = 0;
        Temp = n;

        for (dir_indicator = 0; dir_indicator < count_levels; dir_indicator++) {

            if (comb[dir_indicator] == 0) { // определяем, в какую сторону идти, если 0 - то влево, иначе вправо
                if ((Temp -> left) != NULL)
                    Temp = Temp -> left;
                else {
                    dir_indicator = -1;
                    break;
                }
            }

            else {
                if ((Temp -> right) != NULL)
                Temp = Temp -> right;
                else {
                    dir_indicator = -1;
                    break;
                }
            }
        }

        if (count_levels != 0) {
        y = count_levels-1;
        comb[y]++;

        while (1) {

            if (comb[y] == 2) {
                comb[y] = 0;
                y--;
                if (y < 0)
                    break;
                else
                comb[y]++;
            }
            else
                break;
        }
    }

        if (dir_indicator == -1)
            printf("_");
        else
            printf("%d", Temp -> value);
        count_elements--;
        if (count_elements != 0)
            printf(" ");
    }
        printf("\n");
    }
    return;
}

// Вывести все значения дерева t, аналогично функции print
void print_tree(tree* t) {
    if (t -> root == NULL) {
        printf("-\n");
        return;
    }
    else {
        print(t -> root);
    }
    return;
}

int main() {
	tree* t = malloc(sizeof(tree));
    int i, x;
    init(t);
    for (i = 0; i < 4; i++)
    {
        scanf("%d", &x);
        insert(t, x);
    }
    print_tree(t);
    printf("\n");
    for (i = 0; i < 3; i++)
    {
        scanf("%d", &x);
        insert(t, x);
    }
    print_tree(t);
    printf("\n");
    node* temp;
    for (i = 0; i < 2; i++)
    {
        scanf("%d", &x);
        temp = findInfo(t, x);
        if (temp) {
            if (temp->parent)
                printf("%d ", temp->parent->value);
            else
                printf("_ ");
            if (temp->left)
                printf("%d ", temp->left->value);
            else
                printf("_ ");
            if (temp->right)
                printf("%d", temp->right->value);
            else
                printf("_");
            printf("\n\n");
        }
        else 
            printf("-\n\n");
    }
    scanf("%d", &x);
    remove_node(t, x);
    print_tree(t);
    printf("\n");
    if (t->count!=0) {
        while(1) {
            x = rotate_left(t, t->root);
            if (x==1)
                break;
        }
    }
    print_tree(t);
    printf("\n");
    if (t->count!=0) {
        while(1) {
            x = rotate_right(t, t->root);
            if (x==1)
                break;
        }
    }
    print_tree(t);
    printf("\n");
    printf("%d\n\n", t->count);
    if (t->root != NULL)
        clean(t);
    print_tree(t);
    return 0;
};
