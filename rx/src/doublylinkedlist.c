#include <stdio.h>
#include <stdlib.h>

#include "../include/doublylinkedlist.h"


struct _g_node {
    void *data;
    struct _g_node *next;
    struct _g_node *previous;
};

struct _doubly_linked_list {
    GNode *nose;
    GNode *tail;
    int size;
};


// private function prototypes
// protótipos de funções privadas
static GNode *_gn_create(void *data);
static void _ll_reset(DoublyLinkedListG *l);
static GNode *_ll_search(const DoublyLinkedListG *l, void *data);
static void _ll_remove_mid(DoublyLinkedListG *l, GNode *p);



// PUBLIC FUNCTIONS // FUNÇÕES PÚBICAS


DoublyLinkedListG *ll_create() {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    DoublyLinkedListG *l = (DoublyLinkedListG *) calloc(1, sizeof(DoublyLinkedListG));

    if (!l) {
        fprintf(stderr, "Error: failed to allocate memory for the list.\n");
        return NULL;
    }

    return l;
}

void ll_destroyer(DoublyLinkedListG **l_ref) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */

    if (l_ref == NULL || *l_ref == NULL)
        return;

    DoublyLinkedListG *l = *l_ref;

    GNode *p = l->nose;
    GNode *aux = NULL;

    while (p != NULL) {
        aux = p;

        p = p->next;
        free(aux->data);
        free(aux);
    }

    free(l);
    *l_ref = NULL;
}

int ll_get_size(const DoublyLinkedListG *l) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    return l->size;
}

int ll_is_empty(const DoublyLinkedListG *l) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    return ll_get_size(l) == 0;
}

void ll_insert_nose(DoublyLinkedListG *l, void *data) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    GNode *p = _gn_create(data);

    p->next = l->nose;

    if (!ll_is_empty(l)) {
        l->nose->previous = p;
    } else l->tail = p;

    l->nose = p;
    l->size++;
}

void ll_insert_tail(DoublyLinkedListG *l, void *data) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    GNode *p = _gn_create(data);

    // Checks if the list is empty and inserts a new node in the tail
    // Verifica se a lista está vazia e insere um novo nó na cauda
    if (ll_is_empty(l)) {
        ll_insert_nose(l, data);
    } else {
        p->previous = l->tail;

        l->tail->next = p;
        l->tail = p;

        l->size++;
    }
}

int ll_is_in(const DoublyLinkedListG *l, void *data) {
   return _ll_search(l, data) != NULL;
}

void ll_remove_nose(DoublyLinkedListG *l) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */

     if (ll_is_empty(l)) {
        fprintf(stderr, "Error: list is empty \n");
        return;
     }

    GNode *p = l->nose;

    if (ll_get_size(l) == 1) {
         _ll_reset(l);
         free(p);
     }

    l->nose = p->next;
    l->nose->previous = NULL;
    l->size--;

    free(p);
}

void ll_remove_tail(DoublyLinkedListG *l) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */

     if (ll_is_empty(l)) {
        fprintf(stderr, "Error: list is empty \n");
        return;
     }

    GNode *p = l->tail;

    l->tail = p->previous;
    l->tail->next = NULL;
    l->size--;

    free(p);
}

void ll_remove(DoublyLinkedListG *l, void *data) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */

    // Searches the element at the list and assigns it to node position
    // Busca o elemento na lista e o atribui ao nó position
    GNode *position = _ll_search(l, data);

    // Checks if the element exists and if the list size is greater than 1
    // Verifica se o elemento existe e se o tamanho da lista é maior que 1
    if (position != NULL) {

        // Checks if the element is at the begin and removes it
        // Verifica se o elemento está no início da lista e o remove
        if (l->nose == position) {
            ll_remove_nose(l);
        }

        // Checks if the element is at the tail or in the middle and removes it
        // Verifica se o elemento está na cauda da lista ou no meio e o remove
        if (l->tail == position) {
            ll_remove_tail(l);
        } else { // The element is at the middle...
            _ll_remove_mid(l, position);
        }
    } else {
        _ll_reset(l);

        free(position);
    }
}

void *ll_get_nose(const DoublyLinkedListG *l) {
    if (!l || ll_is_empty(l)) {
        fprintf(stderr, "Error in 'll_get_nose()' \n");
        fprintf(stderr, "List is empty \n");
        return NULL;
    }

    return l->nose->data;
}

void *ll_get_tail(const DoublyLinkedListG *l) {
    if (!l || ll_is_empty(l)){
        fprintf(stderr, "Error in 'll_get_tail()' \n");
        fprintf(stderr, "List is empty \n");

        return NULL;
    }

    return l->tail->data;
}

void ll_print(const DoublyLinkedListG *l, PrintFunction callback) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    GNode *p = l->nose;

    while (p != NULL) {
        callback(p->data);

        p = p->next;
    }
}

// PRIVATE FUNCTIONS // FUNÇÕES PRIVADAS

static GNode *_gn_create(void *data){
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    GNode *p = (GNode *) calloc(1, sizeof(GNode));

    p->data = data;
    return p;
}

static void _ll_reset(DoublyLinkedListG *l) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    l->nose = NULL;
    l->tail = NULL;
    l->size = 0;
}

static GNode *_ll_search(const DoublyLinkedListG *l, void *data) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    GNode *p = l->nose;

    while ((p != NULL) && (p->data != data))
      p = p->next;

    return p; // Return the found node or NULL if not found.
}

static void _ll_remove_mid(DoublyLinkedListG *l, GNode *p) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */

    p->previous->next = p->next;
    p->next->previous = p->previous;
    l->size--;

    free(p);
}
