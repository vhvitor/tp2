#ifndef EVENTMANAGER_H_INCLUDED
#define EVENTMANAGER_H_INCLUDED

typedef struct event_manager EventManager;

EventManager *em_create();

void em_destroyer(EventManager *em);

void em_run_simulation();

#endif // EVENTMANAGER_H_INCLUDED
