#ifndef GENERICQUEUE_H_INCLUDED
#define GENERICQUEUE_H_INCLUDED

typedef struct _generic_queue GenericQueue;

GenericQueue *gq_create();

void gq_destroyer(GenericQueue **l_ref);

int gq_is_empty(const GenericQueue *q);

int gq_get_size(const GenericQueue*q);

void gq_enqueue(GenericQueue *q, void *data);

void *gq_peek(GenericQueue *q);

void *gq_peek_tail(GenericQueue *q);

void *gq_dequeue(GenericQueue *q);

#endif // GENERICQUEUE_H_INCLUDED
