#ifndef DOUBLYLINKEDLIST_H_INCLUDED
#define DOUBLYLINKEDLIST_H_INCLUDED

typedef struct _g_node GNode;
typedef struct _doubly_linked_list DoublyLinkedListG;

// Defines callback function for print
typedef void(*PrintFunction)(void *data);

DoublyLinkedListG *ll_create();

void ll_destroyer(DoublyLinkedListG **l_ref);

int ll_get_size(const DoublyLinkedListG *l);

int ll_is_empty(const DoublyLinkedListG *l);

void ll_insert_nose(DoublyLinkedListG *l, void *data);

void ll_insert_tail(DoublyLinkedListG *l, void *data);

int ll_is_in(const DoublyLinkedListG *l, void *data);

void ll_remove_nose(DoublyLinkedListG *l);

void ll_remove_tail(DoublyLinkedListG *l);

void ll_remove(DoublyLinkedListG *l, void *data);

void *ll_get_nose(const DoublyLinkedListG *l);

void *ll_get_tail(const DoublyLinkedListG *l);

void ll_print(const DoublyLinkedListG *l, PrintFunction callback);

#endif // DOUBLYDoublyLinkedListG_H_INCLUDED
