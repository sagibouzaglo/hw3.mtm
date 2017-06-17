//
//  list_mtm1.c
//  hw3
//
//  Created by sagi bouzaglo on 27/05/2017.
//  Copyright © 2017 sagi bouzaglo. All rights reserved.
//

#include "list_mtm1.h"
#include <stdio.h>
#include <stdlib.h>

#define NULL_CHECK(ptr,ret) if (ptr == NULL){\
                                    return ret;\
                                }

typedef struct node{
    ListElement listElement;
    struct node* next;
} *Node;

struct list_t{
    Node head;
    Node iterator;
    Node tail;
    int size;
    FreeListElement freeElement;
    CopyListElement copyElement;
};

List listCreate(CopyListElement copyElement, FreeListElement freeElement){
    if ((!copyElement) || (!freeElement)){
        return NULL;
    }
    List list =malloc(sizeof(*list));
    NULL_CHECK(list, NULL);
    Node node= malloc(sizeof(*node));
    if (node==NULL){
        freeElement(list);
        return NULL;
    }
    
    list->copyElement = copyElement;
    list->freeElement = freeElement;
    list->head = list->tail = list->iterator = node;
    list->size=0;
    return list;
}

List listCopy(List list){
    int first=0;
    List newList = malloc(sizeof(*newList));
    NULL_CHECK(newList, NULL);
    newList->copyElement=list->copyElement;
    newList->freeElement=list->freeElement;
    Node tmpIterator = list->iterator;
    list->iterator=listGetFirst(list);
    LIST_FOREACH(Node, iterator, list){
        Node node = malloc(sizeof(*node));
        if (node == NULL){
            listDestroy(newList);
            return NULL;
        }
        if (first==0){
            ++first;
            list->head=node;
        }
        node=list->copyElement(list->iterator);
        newList->iterator=node;
        list->size++;
    }
    newList->tail=newList->iterator;
    list->iterator=tmpIterator;
    return newList;
}

int listGetSize(List list){
    NULL_CHECK(list, -1);
    return (list->size);
}

ListElement listGetFirst(List list){
    NULL_CHECK(list, NULL);
    list->iterator=list->head;
    return list->head;
}

ListElement listGetNext(List list){
    NULL_CHECK(list, NULL);
    list->iterator=list->iterator->next;
    return list->iterator;
}

ListElement listGetCurrent(List list){
    NULL_CHECK(list, NULL);
    NULL_CHECK(list->iterator, NULL);
    return list->iterator;
}

ListResult listInsertFirst(List list, ListElement element){
    NULL_CHECK(list, LIST_NULL_ARGUMENT);
    Node node = malloc(sizeof(*node));
    NULL_CHECK(node, LIST_OUT_OF_MEMORY);
    node=list->copyElement(element);
    node->next=list->head;
    list->head=node;
    list->size++;
    return LIST_SUCCESS;
}

ListResult listInsertLast(List list, ListElement element){
    NULL_CHECK(list, LIST_NULL_ARGUMENT);
    Node node = malloc(sizeof(*node));
    NULL_CHECK(node, LIST_OUT_OF_MEMORY);
    node=list->copyElement(element);
    list->tail=node;
    list->size++;
    return LIST_SUCCESS;
}

ListResult listInsertBeforeCurrent(List list, ListElement element){
    NULL_CHECK(list, LIST_NULL_ARGUMENT);
    NULL_CHECK(list->iterator, LIST_INVALID_CURRENT);
    Node tmp = list->iterator;
    Node node = malloc(sizeof(*node));
    NULL_CHECK(node, LIST_OUT_OF_MEMORY);
    LIST_FOREACH(Node, iterator, list){
        if (list->iterator == tmp){
            node=list->copyElement(element);
            node->next=list->iterator->next;
            list->iterator->next=node;
            list->size++;
            return LIST_SUCCESS;
        }
    }
    return LIST_SUCCESS;
}

ListResult listInsertAfterCurrent(List list, ListElement element){
    NULL_CHECK(list, LIST_NULL_ARGUMENT);
    NULL_CHECK(list->iterator, LIST_INVALID_CURRENT);
    Node node = malloc(sizeof(*node));
    NULL_CHECK(node, LIST_OUT_OF_MEMORY);
    node = list->copyElement(element);
    node->next=list->iterator->next;
    list->iterator->next=node;
    list->size++;
    return LIST_SUCCESS;
}

ListResult listRemoveCurrent(List list){
    NULL_CHECK(list, LIST_NULL_ARGUMENT);
    NULL_CHECK(list->iterator, LIST_INVALID_CURRENT);
    Node tmp = list->iterator;
    LIST_FOREACH(Node, iterator, list){
        if (list->iterator->next == tmp){
            list->iterator = tmp->next;
            list->freeElement(tmp);
            list->size--;
            return LIST_SUCCESS;
        }
    }
    return LIST_SUCCESS;
}

/**
 * Sorts the list according to the given function.
 *
 * For example, the following code will sort a list of integers according to
 * their distance from 0.
 * @code
 * int closerTo(ListElement num1, ListElement num2, ListSortKey value) {
 *   int distance1 = abs(*(int*)num1 - *(int*)value);
 *   int distance2 = abs(*(int*)num2 - *(int*)value);
 *   return distance1 - distance2;
 * }
 *
 * void sortInts(List listOfInts) {
 *   int key = 0;
 *   listSort(listOfInts, closerTo, &key);
 * }
 * @endcode
 *
 * @param list the target list to sort
 * @param compareElement A comparison function as defined in the type
 * CompareListElements. This function should return an integer indicating the
 * relation between two elements in the list
 *
 * @return
 * LIST_OUT_OF_MEMORY if a memory allocation failed, the list will be intact
 * in this case.
 */
ListResult listSort(List list, CompareListElements compareElement){
     NULL_CHECK(list, LIST_NULL_ARGUMENT);
     NULL_CHECK(compareElement, LIST_NULL_ARGUMENT);
    
    return LIST_SUCCESS;
}

List listFilter(List list, FilterListElement filterElement, ListFilterKey key){
    List newList = malloc(sizeof(*newList));
    int first=0;
    NULL_CHECK(newList, NULL);
    newList->copyElement=list->copyElement;
    newList->freeElement=list->freeElement;
    Node tmpIterator = list->iterator;
    list->iterator=listGetFirst(list);
    LIST_FOREACH(Node, iterator, list){
        if (filterElement(list->iterator,key)){
            Node node = malloc(sizeof(*node));
            if (first==0){
                ++first;
                list->head=node;
            }
            NULL_CHECK(node, NULL);
            node=list->copyElement(list->iterator);
            list->size++;
        }
    }
    list->tail=list->iterator;
    list->iterator=tmpIterator;
    return newList;
}


ListResult listClear(List list){
    NULL_CHECK(list, LIST_NULL_ARGUMENT);
    list->iterator=listGetFirst(list);
    LIST_FOREACH(Node, iterator, list){
        list->freeElement(list->iterator);
    }
    return LIST_SUCCESS;
}


void listDestroy(List list){
    if(list==NULL){
        return;
    }
    listClear(list);
    free(list);
}
