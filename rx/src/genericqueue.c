#include <stdio.h>
#include <stdlib.h>

#include "../include/genericqueue.h"
#include "../include/doublylinkedlist.h"

struct _generic_queue {
    DoublyLinkedListG *list;
};

GenericQueue *gq_create(){
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Allocates memory for the generic queue strucutre
    // Alloca memória para a estrutura fila genérica
    GenericQueue *q = (GenericQueue *) malloc(sizeof(GenericQueue));

    // Checks if the allocation successfull
    // Verifica se a alocação foi bem sucedida
    if (!q) {
        fprintf(stderr, "Error: failed to allocate memory for generic queue\n");
        return NULL;
    }

    // Builds the generic doubly linked list
    // Constróis a lista duplamente encadeada genérica
    q->list = ll_create();

    return q;
}

void gq_destroyer(GenericQueue **l_ref) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */

    if (!l_ref || !*l_ref) {
        fprintf(stderr, "Error: attempting to destroy a null queue.\n");
        return;
    }

    GenericQueue *q = *l_ref;

    ll_destroyer(&q->list);

    free(q);
    *l_ref = NULL;
}

int gq_is_empty(const GenericQueue *q) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    return ll_is_empty(q->list);
}

int gq_get_size(const GenericQueue*q) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    return ll_get_size(q->list);
}

void gq_enqueue(GenericQueue *q, void *data) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Delegates the responsability for enqueuing to the list
    // Delega à lista a responsabilidade de enfileirar
    ll_insert_tail(q->list, data);
}

void *gq_peek(GenericQueue *q) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Checks if the queue is empty
    // Verifica se a fila está vazia
    if (gq_is_empty(q)) {
        fprintf(stderr, "Error in 'gq_peek()' \n");
        fprintf(stderr, "The queue is empty! \n");
        return NULL;
    }

    return ll_get_nose(q->list);
}

void *gq_peek_tail(GenericQueue *q) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Checks if the queue is empty
    // Verifica se a fila está vazia
    if (gq_is_empty(q)) {
        fprintf(stderr, "Error in 'gq_peek_tail()' \n");
        fprintf(stderr, "The queue is empty! \n");
        return NULL;
    }

    return ll_get_tail(q->list);
}

void *gq_dequeue(GenericQueue *q) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Checks if the queue is empty
    // Verifica se a fila está vazia
    if (gq_is_empty(q)) {
        fprintf(stderr, "Error in 'gq_dequeue()' \n");
        fprintf(stderr, "The queue is empty!");
        return NULL;
    }

    // Gets the first object
    // Obtém o primeiro objeto
    void *nose = ll_get_nose(q->list);

    // Delegates the responsability for dequeuing to the list
    // Delega à lista a responsabilidade de desenfileirar
    ll_remove_nose(q->list);

    return nose;
}
