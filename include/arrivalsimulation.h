#ifndef ARRIVALSIMULATION_H_INCLUDED
#define ARRIVALSIMULATION_H_INCLUDED

#include "genericqueue.h"

// Structure for hospital ArrivalSimulation
// Estrutura para a simulação do hospital
typedef struct arrival_simulation ArrivalSimulation;

// Builds a ArrivalSimulation of arrival
// Constrói a simulação de chegada
ArrivalSimulation *as_create();

// Destroys the ArrivalSimulation
// Destrói a simulação
void as_destroyer(ArrivalSimulation *as);

// Callback function for dispatcher
// Função callback para dispatcher
void as_patient_arrival_callback(void *context, int current_time);

// Runs arrival simulation event
// Roda o evento de simulação de chegada
void as_run(ArrivalSimulation *as, int current_time);

// Gets number of patients treated
// Obtém o número de pacientes atendidos
int as_get_num_patients_treated(ArrivalSimulation *as);

void as_set_queue(ArrivalSimulation *as, GenericQueue *patient_queue);

#endif // ARRIVALSIMULATION_H_INCLUDED
