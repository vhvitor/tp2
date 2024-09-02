#include <stdlib.h>

#include "../include/dispatcher.h"


struct dispatcher {
    EventCallback callbacks[EVENT_TYPE_SIZE];           // Enum array of event callbacks
};

Dispatcher *disp_create() {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */

    // Allocates memory for a dispatcher structure
    // Alloca memória para uma estrutura disparador
    Dispatcher *dispatcher = (Dispatcher *) calloc(1, sizeof(Dispatcher));

    // Checks if the allocation successful
    // Verifica se a alocação foi bem sucedida
    if (!dispatcher) {
        fprintf(stderr, "Error: arrival simulation allocation failure/n");
        return NULL;
    }

    return dispatcher;
}

void disp_destroyer(Dispatcher *dispatcher) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */

    if (dispatcher) {
        free(dispatcher);
    }
}

void disp_register_callback(Dispatcher *dispatcher, EventType type, EventCallback callback) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */

    if (type < EVENT_TYPE_SIZE) {
        dispatcher->callbacks[type] = callback;
    }
}

void disp_trigger_event(Dispatcher *dispatcher, EventType type, void *context, void *gqueue, int current_time) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    if (type < EVENT_TYPE_SIZE && dispatcher->callbacks[type]) {
        dispatcher->callbacks[type](context, gqueue, current_time);
    }
}
