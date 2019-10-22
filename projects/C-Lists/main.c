#include "list.h"

int main(){
	List* l = list_init();
	list_add_int(l,1337);
	list_add_float(l,5.9);
	list_add_char(l,'R');
	list_print(l);
	return 0;
}
