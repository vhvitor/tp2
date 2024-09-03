#include <stdio.h>
#include <stdlib.h>

#include "../include/eventmanager.h"
#include "../include/arrivalsimulation.h"
#include "../include/genericqueue.h"
#include "../include/xrmachine.h"

#define MAX_TIME 43200

typedef enum {
    QUEUE_EM_PATIENT,
    QUEUE_ER_XR_MACHINE,

    NUMBER_QUEUES_EM
}QUEUES_EM;

struct event_manager{
    ArrivalSimulation *as;
    ExamSimulation *es;
    GenericQueue *queues_em[NUMBER_QUEUES_EM];
    ExamPriorityQueue *epq;
};


EventManager *em_create() {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Allocates memory for an event manager structure
    // Aloca memória para uma estrutura gerenciador de eventos
    EventManager *em = (EventManager *) calloc(1, sizeof(EventManager));

    // Checks if the allocation successfull
    // Verifica se a alocação foi bem sucedida
    if (!em) {
        fprintf(stderr, "Error: event manager allocation failure");
    }

    // Builds the arrival simulation
    // Constrói a simulação de chegada
    em->as = as_create();

    // Initializes the queues_em
    // Starta as filas
    for (int i = 0; i < NUMBER_QUEUES_EM; i++) {
        em->queues_em[i] = gq_create();
    }

    return em;
}

void em_destroyer(EventManager *em) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    return;
}

void em_run_simulation() {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    EventManager *em = em_create();

    as_set_queue(em->as, em->queues_em[QUEUE_EM_PATIENT]);
    es_set_patient_queue(em->es, em->queues_em[QUEUE_EM_PATIENT]);

    if (em) {
        for (int i = 0; i < MAX_TIME; i++) {
            as_run(em->dispatcher, em->as, i);
        }
    }

    em_destroyer(em);
}

// PRIVATE FUNCTIONS // FUNÇÕES PRIVADAS
