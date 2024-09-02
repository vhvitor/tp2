#include <stdio.h>
#include <stdlib.h>

#include "../include/eventmanager.h"
#include "../include/arrivalsimulation.h"
#include "../include/dispatcher.h"

#define MAX_TIME 1000

struct event_manager{
    ArrivalSimulation *as;
    Dispatcher *dispatcher;
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
    EventManager *em = (EventManager *) malloc(sizeof(EventManager));

    // Checks if the allocation successfull
    // Verifica se a alocação foi bem sucedida
    if (!em) {
        fprintf(stderr, "Error: event manager allocation failure");
    }

    // Builds the arrival simulation
    // Constrói a simulação de chegada
    em->as = as_create();

    // Builds the dispatcher
    // Constrói o disparador
    em->dispatcher = disp_create();

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


    GenericQueue *patient_queue = gq_create();

    EventManager *em = em_create();

    if (em) {
        for (int i = 0; i < MAX_TIME; i++) {
            as_run(em->dispatcher, em->as, patient_queue, i);
        }
    }

    em_destroyer(em);
}

// PRIVATE FUNCTIONS // FUNÇÕES PRIVADAS
