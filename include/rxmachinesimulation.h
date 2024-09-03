#ifndef EXAM_SIMULATION_H
#define EXAM_SIMULATION_H

#include "genericqueue.h"

// Definição da estrutura ExamSimulation
typedef struct exam_simulation ExamSimulation;

// Funções públicas da simulação de exames

ExamSimulation *es_create();

void es_destoyer(ExamSimulation *es);

void es_do_exam_callback(void *context, void *patient_queue, int current_time);

void es_run(Dispatcher *dispatcher, ExamSimulation *es, int current_time);

void es_set_patient_queue(ExamSimulation *es, GenericQueue *patient_queue);

#endif // EXAM_SIMULATION_H
