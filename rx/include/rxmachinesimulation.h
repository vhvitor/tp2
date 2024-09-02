#ifndef EXAM_SIMULATION_H
#define EXAM_SIMULATION_H

#include "../include/exampriorityqueue.h"
#include "../include/arrivalsimulation.h"
#include "../include/patient.h"
#include "../include/genericqueue.h"
#include "../include/dispatcher.h"

// Definição da estrutura ExamSimulation
typedef struct exam_simulation ExamSimulation;

// Funções públicas da simulação de exames

/**
 * @brief Cria uma nova simulação de exames.
 *
 * @param patient_queue - Fila de pacientes aguardando exame.
 * @return Ponteiro para a simulação de exames criada.
 */
ExamSimulation *es_create(GenericQueue *patient_queue);

/**
 * @brief Inicia a simulação de exames.
 *
 * @param dispatcher - Ponteiro para o dispatcher de eventos.
 * @param es - Ponteiro para a simulação de exames.
 * @param patient_queue - Fila de pacientes aguardando exame.
 * @param current_time - O tempo atual da simulação.
 */
void es_run(Dispatcher *dispatcher, ExamSimulation *es, GenericQueue *patient_queue, int current_time);

/**
 * @brief Callback que simula a realização de um exame.
 *
 * @param context - Ponteiro para a simulação de exames (ExamSimulation).
 * @param patient_queue - Fila de pacientes aguardando exame.
 * @param current_time - O tempo atual da simulação.
 */
void es_do_exam_callback(void *context, void *patient_queue, int current_time);

// Funções internas (estáticas) - apenas disponíveis no arquivo de implementação

/**
 * @brief Cria uma lista de máquinas X para exames.
 *
 * @return Ponteiro para o array de máquinas X.
 */
static int *create_machines();

/**
 * @brief Verifica e ocupa uma máquina X disponível para o paciente dado.
 *
 * @param machines_list - Ponteiro para o array de máquinas X.
 * @param patient_queue - Fila de pacientes aguardando exame.
 * @param current_time - O tempo atual da simulação.
 * @return Ponteiro para o exame criado, ou NULL se não houver máquinas disponíveis.
 */
Exam *_verify_and_ocupate(int *machines_list, GenericQueue *patient_queue, int current_time);

/**
 * @brief Gera um diagnóstico aleatório baseado em AI.
 *
 * @return Diagnóstico gerado pela AI.
 */
static int diagnostic_by_ai();

/**
 * @brief Realiza um exame usando o diagnóstico de AI e marca a máquina como disponível.
 *
 * @param machine - Máquina X que realiza o exame.
 * @param patient - Ponteiro para o paciente que precisa do exame.
 * @param current_time - O tempo atual da simulação.
 * @return Ponteiro para o exame criado.
 */
Exam *_do_exam_with_AI(int machine, Patient *patient, int current_time);
/**
*
* @brief Destroy structure for exam simulation
* @param ExamSimulation structure
*
*
*
*
*/
void destroyer_struct_exam_simulation(ExamSimulation *es);


/**
*
* @brief Returns exam priority queue from ExamSimulation instance
* @param ExamSimulation structure
*
*
*
*
*/

ExamPriorityQueue *priority_queue_exams(ExamSimulation *es);

#endif // EXAM_SIMULATION_H
