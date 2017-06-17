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
    ListElement Element;
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
    list->copyElement = copyElement;
    list->freeElement = freeElement;
    list->head = list->tail = list->iterator = NULL;
    list->size=0;
    return list;
}

List listCopy(List list){
    NULL_CHECK(list, NULL);
    List newList = listCreate( list->copyElement, list->freeElement);
    NULL_CHECK(newList, NULL);
    Node tmpIterator = list->iterator;
    LIST_FOREACH(ListElement, current, list){
        if (listInsertLast(newList,current) != LIST_SUCCESS){
            listDestroy(newList);
            return NULL;
        }
    }
    list->iterator=tmpIterator;
    return newList;
}

int listGetSize(List list){
    NULL_CHECK(list, -1);
    return (list->size);
}

ListElement listGetFirst(List list){
    NULL_CHECK(list, NULL);
    NULL_CHECK(list->head, NULL);
    list->iterator=list->head;
    return list->iterator->Element;
}

ListElement listGetNext(List list){
    NULL_CHECK(list, NULL);
    NULL_CHECK(list->iterator, NULL);
    NULL_CHECK(list->iterator->next, NULL);
    list->iterator=list->iterator->next;
    return list->iterator->Element;
}

ListElement listGetCurrent(List list){
    NULL_CHECK(list, NULL);
    NULL_CHECK(list->iterator, NULL);
    return list->iterator->Element;
}

ListResult listInsertFirst(List list, ListElement element){
    NULL_CHECK(list, LIST_NULL_ARGUMENT);
    Node node = malloc(sizeof(*node));
    NULL_CHECK(node, LIST_OUT_OF_MEMORY);
    if (list->tail == NULL){
        list->tail=node;
    }
    node->Element=list->copyElement(element);
    node->next=list->head;
    list->head=node;
    list->size++;
    return LIST_SUCCESS;
}

ListResult listInsertLast(List list, ListElement element){
    NULL_CHECK(list, LIST_NULL_ARGUMENT);
    Node node = malloc(sizeof(*node));
    NULL_CHECK(node, LIST_OUT_OF_MEMORY);
    node->Element=list->copyElement(element);
    if (list->tail == NULL){
        list->head=node;
    }else{
        list->tail->next = node;
    }
    list->tail=node;
    node->next=NULL;
    list->size++;
    return LIST_SUCCESS;
}

ListResult listInsertBeforeCurrent(List list, ListElement element){
    NULL_CHECK(list, LIST_NULL_ARGUMENT);
    NULL_CHECK(list->iterator, LIST_INVALID_CURRENT);
    Node tmp = list->iterator;
    Node node = malloc(sizeof(*node));
    NULL_CHECK(node, LIST_OUT_OF_MEMORY);
    node->Element=list->copyElement(element);
    list->size++;
    if (tmp == list->head){
        list->head = node;
        node->next=tmp;
        return LIST_SUCCESS;
    } else {
        LIST_FOREACH(ListElement, current, list){
            if (list->iterator->next == tmp){
                node->next=tmp;
                list->iterator->next=node;
                list->iterator=tmp;
                return LIST_SUCCESS;
            }
        }
    }
    list->size--;
    list->freeElement(node->Element);
    free(node);
    return LIST_INVALID_CURRENT;
}

ListResult listInsertAfterCurrent(List list, ListElement element){
    NULL_CHECK(list, LIST_NULL_ARGUMENT);
    NULL_CHECK(list->iterator, LIST_INVALID_CURRENT);
    Node node = malloc(sizeof(*node));
    NULL_CHECK(node, LIST_OUT_OF_MEMORY);
    node->Element = list->copyElement(element);
    node->next=list->iterator->next;
    list->iterator->next=node;
    list->size++;
    return LIST_SUCCESS;
}

ListResult listRemoveCurrent(List list){
    NULL_CHECK(list, LIST_NULL_ARGUMENT);
    NULL_CHECK(list->iterator, LIST_INVALID_CURRENT);
    Node tmp = list->iterator;
    LIST_FOREACH(ListElement, current, list){
        if (list->iterator->next == tmp){
            list->iterator->next = tmp->next;
            list->freeElement(tmp->Element);
            list->size--;
            return LIST_SUCCESS;
        }
    }
    return LIST_SUCCESS;
}

ListResult listSort(List list, CompareListElements compareElement){
    NULL_CHECK(list, LIST_NULL_ARGUMENT);
    NULL_CHECK(compareElement, LIST_NULL_ARGUMENT);
    List sortedList = listCreate(list->copyElement, list->freeElement);
    LIST_FOREACH(ListElement, current, list){
        if(compareElement(listGetCurrent(sortedList), current)>0){
            LIST_FOREACH(ListElement, sorted_current, sortedList){
                if (compareElement(current,sorted_current)<0){
                    listInsertBeforeCurrent(sortedList, current);
                }else if (compareElement(current,sorted_current)==0){
                    listInsertAfterCurrent(sortedList, current);
                }
            }
        }
        
    }
    listClear(list);
    return LIST_SUCCESS;
}

List listFilter(List list, FilterListElement filterElement, ListFilterKey key){
    NULL_CHECK(list, NULL);
    List newList = listCreate( list->copyElement, list->freeElement);
    NULL_CHECK(newList, NULL);
    Node tmpIterator = list->iterator;
    LIST_FOREACH(ListElement, current, list){
        if (filterElement(current,key)){
            if (listInsertLast(newList,current) != LIST_SUCCESS){
                listDestroy(newList);
                return NULL;
            }
        }
    }
    list->iterator=tmpIterator;
    
    return newList;
}


ListResult listClear(List list){
    NULL_CHECK(list, LIST_NULL_ARGUMENT);
    LIST_FOREACH(ListElement, current, list){
        list->freeElement(current);
        free(list->iterator);
    }
    list->head=list->tail=list->iterator=NULL;
    list->size=0;
    return LIST_SUCCESS;
}


void listDestroy(List list){
    if(list==NULL){
        return;
    }
    listClear(list);
    free(list);
}
