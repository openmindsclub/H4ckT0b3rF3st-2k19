#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#define EXIT() exit(EXIT_FAILURE);

List* list_init(){
    List* l = malloc(sizeof(*l));
    Element* elem = malloc(sizeof(*elem));
    if (!l || !elem)
      EXIT();
    (elem->val).i=0;
    elem->next=NULL;
    elem->prec=NULL;
    l->first=elem;
    l->size=1;
    return l;
}


void list_add_int(List* l , int val){
    Element* elem = malloc(sizeof(*elem));
    if (!l || !elem)
      EXIT();
    elem->type=INT_VAL;
    (elem->val).i=val;
    elem->next = l->first;
    elem->prec = NULL;
    if (l->first)
      l->first->prec=elem;
    l->first = elem;
    (l->size)++;
}

void list_add_float(List* l , float val){
    Element* elem = malloc(sizeof(*elem));
    if (!l || !elem)
      EXIT();
    elem->type=FLOAT_VAL;
    (elem->val).f=val;
    elem->next = l->first;
    elem->prec = NULL;
    if (l->first)
      l->first->prec=elem;
    l->first = elem;
    (l->size)++;
}

void list_add_char(List* l , char val){
    Element* elem = malloc(sizeof(*elem));
    if (!l || !elem)
      EXIT();
    elem->type=CHAR_VAL;
    (elem->val).c=val;
    elem->next = l->first;
    elem->prec = NULL;
    if (l->first)
      l->first->prec=elem;
    l->first = elem;
    (l->size)++;
}

void list_print(List* l){
    Element *elem = malloc(sizeof(*elem));
    if (!l || !elem) EXIT();
    elem = l->first;
	  printf("[");
    while (elem && l->size>0) {
        switch(elem->type){
          case INT_VAL:
            printf("%d",(elem->val).i);
          break;
          case FLOAT_VAL:
            printf("%f",(elem->val).f);
          break;
          case CHAR_VAL:
            printf("\'%c\'",(elem->val).c);
          break;
        }
        if (elem->next!=NULL) printf(" , ");
        elem = elem->next;
    }
	  printf("]\n");
}
