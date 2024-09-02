#include <stdio.h>
#include <stdlib.h>

#include "../include/exampriorityqueue.h"
#include "../include/genericqueue.h"
#include "../include/exam.h"

#define NUMBER_PRIORITY_QUEUES 6

struct exam_priority_queue {
    GenericQueue *priority_queues[NUMBER_PRIORITY_QUEUES];
    Exam *current_exam;
};


// OPERATIONS // OPERAÇÕES

ExamPriorityQueue *epq_create() {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Allocates memory for an exam priority queue structure
    // Aloca memória para uma estrutura fila de prioridades de exames
    ExamPriorityQueue *epq = (ExamPriorityQueue *) calloc(1, sizeof(ExamPriorityQueue));

    // Checks if the allocation successfull
    // Verifica se a alocação foi bem sucedida
    if (!epq) {
        fprintf(stderr, "In function 'epq_create' \nError: exam priority queue allocation failure\n");
        return NULL;
    }

    // Initializes the priority queues
    // Starta as filas de prioridades
    for (int i = 0; i < NUMBER_PRIORITY_QUEUES; i++) {
        epq->priority_queues[i] = gq_create();

        if (!epq->priority_queues[i]) {
            fprintf(stderr, "In function 'epq_create' \nError: priority queue %d allocation failure\n", i);

            // If the creation fails, destroys the previously created queues
            // Se a criação falhar, destrói as filas criadas anteriormente
            for (int j = 0; j < i; j++) {
                gq_destroyer((void *) epq->priority_queues[j]);
            }

            free(epq);
            return NULL;
        }
    }

    return epq;
}

void epq_destroyer(ExamPriorityQueue *epq) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    if (!epq) {
        fprintf(stderr, "In function 'epq_destroyer' \nExam priority queue is null\n");
        return;
    }

    // Destroys the priority queues
    // Destrói as filas de prioridades
    for (int i = 0; i < NUMBER_PRIORITY_QUEUES; i++) {
        gq_destroyer((void *) epq->priority_queues[i]);
    }

    // Free memory of the exam priority queue
    // Libera memória para a fila de prioridades de exames
    free(epq);
}

int epq_is_empty(const ExamPriorityQueue *epq, PriorityType type) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    if (epq == NULL) {
        fprintf(stderr, "In function 'epq_is_empty' \nError: ExamPriorityQueue pointer is NULL.\n");
        return 0; // Or handle the error as appropriate
    }

    // Validate type if there's a range for PriorityType
    // Validar tipo se houver um intervalo para PriorityType
    if (type < 0 || type >= NUMBER_PRIORITY_QUEUES) {
        fprintf(stderr, "In function 'epq_is_empty' \nError: Invalid PriorityType value.\n");
        return 0;
    }

    return gq_is_empty(epq->priority_queues[type]);
}

void epq_enqueue(ExamPriorityQueue *epq, PriorityType type, Exam *exam) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Checks if exam priority queue exist
    // Verifica se a fila de prioridades dos exames existe
    if (!epq) {
        fprintf(stderr, "In function 'epq_enqueue' \nError: exam priority queue cannot be null.\n");
        return;
    }

    if (type < 0 || type >= NUMBER_PRIORITY_QUEUES) {
        fprintf(stderr, "In function 'epq_enqueue' \nError: invalid priority type.\n");
        return;
    }

    if (!exam) {
        fprintf(stderr, "In function 'epq_enqueue' \nError: exam cannot be null.\n");
        return;
    }

    // Adds the exam to the specified priority queue
    // Add o exame à fila de prioridades especificada
    gq_enqueue(epq->priority_queues[type], (void *) exam);
}

Exam *epq_dequeue(ExamPriorityQueue *epq) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */



    // Checks if exam priority queue exist
    // Verifica se a fila de prioridades dos exames existe
    if (!epq ) {
        fprintf(stderr, "In function 'epq_dequeue' \nError: exam priority queue cannot be null \n");
        return NULL;
    }

    // Scans the queues from highest to lowest priority
    // Varre as filas de maior para menor prioridade
    for (int i = (NUMBER_PRIORITY_QUEUES - 1); i >= 0; i--) {

        // If the queue isn't empty, dequeue
        // Se a fila não estiver vazia, remove
        if (!gq_is_empty(epq->priority_queues[i])) {
            Exam *removed_exam = (Exam *) gq_peek(epq->priority_queues[i]);           // Gets MAX PRIORITY exam

            gq_dequeue(epq->priority_queues[i]);

            return removed_exam;
        }
    }

    fprintf(stderr, "In function 'epq_dequeue' \nWarning: The queue is empty!");
    return NULL;
}


// GETTERS

int epq_get_size_by_priority(const ExamPriorityQueue *epq, PriorityType type) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    if (!epq) {
        fprintf(stderr, "In function 'epq_get_size_by_priority' \nError: exam priority queue cannot be null \n");
        return -1;
    }

    // Checks if exam priority queue exist
    // Verifica se a fila de prioridades dos exames existe
    if (type < 0 || type >= NUMBER_PRIORITY_QUEUES) {
        fprintf(stderr, "In function 'epq_get_size_by_priority' \nError: exam priority queue cannot be null \n");
        return -1;
    }

    return gq_get_size(epq->priority_queues[type]);
}

int epq_get_size_total(const ExamPriorityQueue *epq) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Checks if exam priority queue exist
    // Verifica se a fila de prioridades dos exames existe
    if (!epq ) {
        fprintf(stderr, "In function 'epq_get_size_total' \nError: exam priority queue cannot be null \n");
        return -1;
    }

    int size_total = 0;

    // Gets the individual size of the queues and assigns the sum to the total_size variable
    // Obtém o tamanho individual das filas e atribui a soma à variável total_size
    for (int i = 0; i < NUMBER_PRIORITY_QUEUES; i++) {
        size_total += gq_get_size(epq->priority_queues[i]);
    }

    return size_total;
}

