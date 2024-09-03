#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "../include/exampriorityqueue.h"
#include "../include/patient.h"
#include "../include/dispatcher.h"
#include "../include/rxmachinesimulation.h"
#include "../include/genericqueue.h"

#define XR_DURATION 10
#define NUMBER_MACHINES 6


typedef enum {
    QUEUE_ES_PATIENT,
    QUEUE_ES_XR_MACHINE,

    NUMBER_QUEUES_ES
}QUEUES_ES;



// Structure for exam simulation
struct exam_simulation {
    GenericQueue *queues[NUMBER_QUEUES_ES];
    ExamPriorityQueue *epq;    // Exam priority queue
};


static int _es_machines_is_empty(GenericQueue *machine_queue);
static int _es_machines_is_full(GenericQueue *machine_queue);
static const char *_es_diagnostic_by_ai();
static void _es__do_exam_with_AI(int *machine, Patient *patient, int current_time);



// OPERATIONS

ExamSimulation *es_create() {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */



    // Allocates memory for exam simulation structure
    ExamSimulation *es = (ExamSimulation*) calloc(1, sizeof(ExamSimulation));

    // Checks if the allocation successful
    // Verifica se a alocação foi bem sucedida
    if (!es) {
        fprintf(stderr, "In function 'es_create' \nError: Exam simulation allocation failure \n");
        return NULL;
    }

    // Builds the exam priority queue
    // Constrói a fila de prioridades de exames
    es->epq = epq_create();

    return es;
}

void es_destoyer(ExamSimulation *es){
    /**
     * \brief Frees the memory allocated for an ExamSimulation structure and its associated resources.
     *
     * \details This function deallocates the memory used by the ExamSimulation structure and its components.
     *          It is important to call this function when the ExamSimulation instance is no longer needed
     *          to avoid memory leaks. The function also frees the memory allocated for the ExamPriorityQueue
     *          within the ExamSimulation structure.
     *
     * \param es - Pointer to the ExamSimulation structure that needs to be destroyed.
     *
     * \return void
     */


    // Checks if es exist
    // Verifica se es existe
    if (!es) {
        fprintf(stderr, "In function 'es_destroyer' \nError: es cannot be null \n");
    }

    epq_destroyer(es->epq);
    free(es);
}

void es_do_exam_callback(void *context, void *queues_es, int current_time) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    ExamSimulation *es = (ExamSimulation *)context;

    _es__do_exam_with_AI(machines, patient, current_time);

}

void es_run(Dispatcher *dispatcher, ExamSimulation *es, int current_time){
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    disp_register_callback(dispatcher, EVENT_XR_ALLOCATION, es_do_exam_callback);

    disp_trigger_event(dispatcher, EVENT_XR_ALLOCATION, (void *) es, current_time);
}


// GETTERS

PriorityType get_priority_type(const char *condition) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    if (condition == NULL) {
        return -1; // Retorna um valor inválido se a string for NULL
    }

    // Converta a string para minúsculas para facilitar a comparação
    char lower_condition[100];
    for (int i = 0; condition[i]; i++) {
        lower_condition[i] = tolower(condition[i]);
    }
    lower_condition[strlen(condition)] = '\0';

    // Compare a string com os valores possíveis e retorne o enum correspondente
    if (strcmp(lower_condition, "normal") == 0) {
        return NORMAL;
    } else if (strcmp(lower_condition, "bronquite") == 0) {
        return BRONQUITE;
    } else if (strcmp(lower_condition, "pneumonia") == 0) {
        return PNEUMONIA;
    } else if (strcmp(lower_condition, "covid") == 0) {
        return COVID;
    } else if (strcmp(lower_condition, "embolia pulmonar") == 0) {
        return EMBOLIA_PULMONAR;
    } else if (strcmp(lower_condition, "derrame pleural") == 0) {
        return DERRAME_PLEURAL;
    } else if (strcmp(lower_condition, "fibrose pulmonar") == 0) {
        return FIBROSE_PULMONAR;
    } else if (strcmp(lower_condition, "tuberculose") == 0) {
        return TUBERCULOSE;
    } else if (strcmp(lower_condition, "cancer pulmão") == 0) {
        return CANCER_PULMAO;
    } else {
        return -1; // Retorna um valor inválido se a condição não for reconhecida
    }
}



// SETERS

void es_set_patient_queue(ExamSimulation *es, GenericQueue *queues_es) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Checks if es exist
    // Verifica se es existe
    if (!es) {
        fprintf(stderr, "In function 'es_set_patient_queue' \nError: es cannot be null \n");
        return;
    }

    // Checks if es exist
    // Verifica se es existe
    if (!queues_es) {
        fprintf(stderr, "In function 'es_set_patient_queue' \nError: queues_es cannot be null \n");
        return;
    }

    es->queues[QUEUE_ES_PATIENT] = queues_es;
}



// PRIVATE FUNCTIONS // FUNÇÕES PRIVADAS


static int _es_machines_is_empty(GenericQueue *machine_queue) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    return (gq_get_size(machine_queue) == 0);
}

static int _es_machines_is_full(GenericQueue *machine_queue) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    return (gq_get_size(machine_queue[QUEUE_ES_XR_MACHINE]) == 5);
}

static const char *_es_diagnostic_by_ai() {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */

    double probability = (rand() / (double) RAND_MAX);

    if (probability < 0.3) return "Normal";
    if (probability < 0.5) return "Bronquite";
    if (probability < 0.6) return "Pneumonia";
    if (probability < 0.7) return "COVID";
    if (probability < 0.75) return "Embolia Pulmonar";
    if (probability < 0.8) return "Derrame Pleural";
    if (probability < 0.85) return "Fibrose Pulmonar";
    if (probability < 0.9) return "Tuberculose";
    return "Câncer de Pulmão";
}

void _es__do_exam_with_AI(ExamSimulation *es, int current_time, int *) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    int machine_status[NUMBER_MACHINES] = {0};
    int machine_id;

    // Checks if the xr machines is full
    // Verifica se as maquinas rx estão cheias
    if (!_es_machines_is_full(es->queues[QUEUE_ES_XR_MACHINE])) {
        // Remove the first patient from the queue
        // Remove o primeiro paciente da fila
        Patient *current_patient = (Patient *) gq_dequeue(es->queues[QUEUE_ES_PATIENT]);



        // Sets the start of the exam
        // Define o início do exame
        patient_set_exam_time(current_patient, current_time);

        // Allocates the patient to a machine
        // Aloca o paciente na máquina
        gq_enqueue(es->queues[QUEUE_ES_XR_MACHINE], (void *) current_patient);

        if (gq_is_empty(es->queues[QUEUE_ES_XR_MACHINE])) {

        }

    }

    Patient *first_patient = (Patient *) gq_peek(es->queues[QUEUE_ES_XR_MACHINE]);

    // Performs the exam in 10 time units
    // Realiza o exame em 10 unidades de tempo
    if (current_time - patient_get_time_exam(first_patient) == 10) {
        if (_es_machines_is_empty(es->queues[QUEUE_ES_XR_MACHINE])) {

        }
        epq_enqueue(es->epq, )
    }
}
