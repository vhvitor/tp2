#ifndef DISPATCHER_H_INCLUDED
#define DISPATCHER_H_INCLUDED

#include <stdio.h>

typedef enum {
    EVENT_PATIENT_ARRIVAL,
    EVENT_XR_ALLOCATION,

    EVENT_TYPE_SIZE
} EventType;

typedef void (*EventCallback)(void *context, void *gqueue, int current_time);

typedef struct dispatcher Dispatcher;

Dispatcher *disp_create();

void disp_destroyer(Dispatcher *dispatcher);

void disp_register_callback(Dispatcher *dispatcher, EventType type, EventCallback callback);

void disp_trigger_event(Dispatcher *dispatcher, EventType type, void *context, void *gqueue, int current_time);

#endif // DISPATCHER_H_INCLUDED
