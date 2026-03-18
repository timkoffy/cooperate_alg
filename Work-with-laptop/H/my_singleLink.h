#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

namespace singleLinked
{
    typedef struct element
    {
        void *data;
        struct element *next;
    } Element;


    typedef struct
    {
        Element *first;
    } List;

    Element *createElement(void *data)
    {
        if (data == NULL)
            return NULL;

        Element *el = (Element *)malloc(sizeof(Element));
        if (!el)
            return NULL;

        el->data = data;
        el->next = NULL;
        return el;
    }

    int addFirst(List *l, void *data)
    {
        if (!l)
            return 0;

        Element *el = createElement(data);
        if (!el)
            return 0;

        el->next = l->first;
        l->first = el;
        return 1;
    }

    int addLast(List *l, void *d)
    {
        if (!l)
            return 0;

        Element *el = createElement(d);
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

    int insertAdd(List *l, int index, void *d)
    {
        if (!l || index < 0)
            return 0;

        int len = lenSingleLink(l);
        if (index > len)
            return 0; 

        if (index == 0)
        {
            addFirst(l, d);
            return 1;
        }
        else if (index == len)
        {
            addLast(l, d);
            return 1;
        }
        else
        {
            Element *prev = l->first;
            for (int i = 0; i < index - 1; i++)
            {
                prev = prev->next;
            }

            Element *el = createElement(d);
            if (!el)
                return 0;

            el->next = prev->next;
            prev->next = el;
        }
        return 1;
    }

    
    int changeElem(List *l, void *newData, int index)
    {
        if (!l || !newData || index <= 0)
            return 0;

        int i = 0;
        Element *current = l->first;
        while (current)
        {
            if (i == index)
            {
                current->data = newData;
                return 1;
            }
            current = current->next;
        }
    }


    int delElement(List *l, int index)
    {
        if (!l || index < 0 || index > lenSingleLink(l) - 1)
            return 0;
        if (l->first == NULL)
            return 0;
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
        l2->first = NULL; 
    }


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

}
