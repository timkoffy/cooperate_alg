#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Элемент списка
typedef struct element
{
    void *data;
    struct element *next;
} Element;

// Список
typedef struct
{
    Element *first;
} List;
// Создание нового элемента
Element *createElement(void *data, int size_el)
{
    if (data == NULL || size_el <= 0)
        return NULL;

    Element *el = (Element *)malloc(sizeof(Element));
    if (!el)
        return NULL;

    el->data = data;
    el->next = NULL;
    return el;
}

int addFirst(List *l, void *data, int size_el)
{
    if (!l)
        return 0;

    Element *el = createElement(data, size_el);
    if (!el)
        return 0;

    el->next = l->first;
    l->first = el;
    return 1;
}

// Добавление в конец
int addLast(List *l, void *d, int size_el)
{
    if (!l)
        return 0;

    Element *el = createElement(d, size_el);
    if (!el)
        return 0;

    if (l->first == NULL)
    {
        l->first = el;
    }
    else
    {
        Element *current = l->first;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = el;
    }
    return 1;
}

void *getElem(List *l, int index)
{
    if (!l || index < 0)
        return NULL;

    Element *current = l->first;
    int i = 0;
    while (current != NULL && i < index)
    {
        current = current->next;
        i++;
    }

    if (current == NULL)
        return NULL;
    

    return current->data;
}

// Длина списка
int lenSingleLink(List *l)
{
    if (!l)
        return 0;
    int len = 0;
    Element *current = l->first;
    while (current)
    {
        len++;
        current = current->next;
    }
    return len;
}

// Вставка элемента на позицию index (0 – в начало, len – в конец)
int insertAdd(List *l, int index, void *d, int size_el)
{
    if (!l || index < 0)
        return 0;

    int len = lenSingleLink(l);
    if (index > len)
        return 0; // индекс вне диапазона

    if (index == 0)
    {
        addFirst(l, d, size_el);
        return 1;
    }
    else if (index == len)
    {
        addLast(l, d, size_el);
        return 1;
    }
    else
    {
        // Ищем элемент, после которого будем вставлять (индекс index-1)
        Element *prev = l->first;
        for (int i = 0; i < index - 1; i++)
        {
            prev = prev->next;
        }

        Element *el = createElement(d, size_el);
        if (!el)
            return 0;

        el->next = prev->next;
        prev->next = el;
    }
    return 1;
}

// Замена данных в первом найденном элементе, у которого данные совпадают с oldData (побайтовое сравнение)
int changeElem(List *l, void *newData, int index)
{
    if (!l || !newData || index <= 0)
        return 0;

    int i = 0;
    Element *current = l->first;
    while (current)
    {
        // Сравниваем содержимое, если размер совпадает
        if (i == index)
        {
            current->data = newData;
            return 1;
        }
        current = current->next;
    }
}

// Удаление элемента по индексу
int delElement(List *l, int index)
{
    if (!l || index < 0 || index > lenSingleLink(l) - 1)
        return 0;
    if (l->first == NULL)
        return 0; // пустой список

    if (index == 0)
    {
        Element *tmp = l->first;
        l->first = tmp->next;
        free(tmp);
        return 1;
    }

    Element *prev = l->first;
    int i = 0;
    while (prev->next != NULL && i < index - 1)
    {
        prev = prev->next;
        i++;
    }

    Element *to_delete = prev->next;
    prev->next = to_delete->next;
    free(to_delete);
    return 1;
}


// Объединение двух списков (l2 присоединяется к концу l1, l2 становится пустым)
void unificationList(List *l1, List *l2)
{
    if (!l1 || !l2)
        return;

    if (l1->first == NULL)
    {
        l1->first = l2->first;
    }
    else
    {
        Element *last = l1->first;
        while (last->next != NULL)
        {
            last = last->next;
        }
        last->next = l2->first;
    }
    l2->first = NULL; // предотвращаем двойное освобождение
}

// Полное освобождение списка
void freeList(List *l)
{
    if (!l)
        return;
    Element *current = l->first;
    while (current)
    {
        Element *next = current->next;
        free(current);
        current = next;
    }
    l->first = NULL;
}

// ----------------------------------------------
// Пример использования (main)
int main()
{
    List *l = (List *)calloc(1, sizeof(List));
    if (!l)
        return 1;

    // Добавляем целое число
    int a = 12;
    addFirst(l, &a, sizeof(a));

    // Добавляем строку
    char str[] = "Hello";
    addLast(l, str, sizeof(str));

    // Получаем первый элемент (индекс 0)

    int p = *(int*)getElem(l, 0);
    printf("Первый элемент (int): %d\n", p);


    // Получаем второй элемент (индекс 1)
    char *el1 = (char*)getElem(l, 1);
    printf("Второй элемент (string): %s\n", el1);

    // Освобождаем список
    freeList(l);
    free(l);
    return 0;
}