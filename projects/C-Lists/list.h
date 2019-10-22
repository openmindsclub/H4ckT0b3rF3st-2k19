#ifndef DEF_LIST
#define DEF_LIST

enum {
    INT_VAL , FLOAT_VAL , CHAR_VAL
};

typedef struct Element Element;
struct Element {
    union {
	char c;
	int i;
	float f;
    } val;
    int type;
    Element *next; // Pointer to the next element
    Element *prec; // Pointer to the precedent element
};

typedef struct List List;
struct List {
    Element *first;     // Pointer to the first element
    int size;   // Size of the list
};

List* list_init();
void list_add_int(List* l,int val);
void list_add_float(List* l , float val);
void list_add_char(List* l,char val);
void list_print(List* l);

#endif
