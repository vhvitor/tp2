#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/arrivalsimulation.h"
#include "../include/patient.h"
#include "../include/genericqueue.h"
#include "../include/dispatcher.h"

#define ARRIVAL_PROBABILITY 0.2

// Structure for arrival simulation
// Estrutura para a simulação de chegada
struct arrival_simulation {
    int num_patients_treated;
    GenericQueue *patient_queue;
};

// Signatures of private functions
// Assinaturas das funções privadas
static int _as_patient_arrived();
static void _as_process_arrival(ArrivalSimulation *as, int current_time);
static Patient _as_register_patient(Patient *patient, int id_patient, char *name_patient, int timestamp_patient);



// Public functions // Funções públicas


ArrivalSimulation *as_create() {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */

    // Allocates memory for a arrival simulation structure
    // Aloca memória para uma estrutura de simulação de chegada
    ArrivalSimulation *as = (ArrivalSimulation *) calloc(1, sizeof(ArrivalSimulation));

    // Checks if the allocation successful
    // Verifica se a alocação foi bem sucedida
    if (!as) {
        fprintf(stderr, "Error: arrival simulation allocation failure/n");
        return NULL;
    }

    return as;
}

void as_destroyer(ArrivalSimulation *as) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    if (as) {
        free(as);
    }
}



void as_patient_arrival_callback(void *context, int current_time) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Casting for Arrival Simulation type
    ArrivalSimulation *as = (ArrivalSimulation *) context;

    if (_as_patient_arrived()) {
        _as_process_arrival(as, current_time);
        as->num_patients_treated++;
    } else return;
}

void as_run(ArrivalSimulation *as, int current_time) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Registers the event in the dispatcher
    // Registra o evento no disparador
    disp_register_callback(dispatcher, EVENT_PATIENT_ARRIVAL, (void *) as_patient_arrival_callback);

    // Trigger the dispatcher
    // Aciona o disparador
    disp_trigger_event(dispatcher, EVENT_PATIENT_ARRIVAL, (void *) patient_queue, current_time);
}


// GETTERS

const int as_get_num_patients_treated(ArrivalSimulation *as) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    return as->num_patients_treated;
}

void as_set_queue(ArrivalSimulation *as, GenericQueue *patient_queue) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Checks if the queue exist
    // Verifica se a fila existe
    if (!patient_queue) {
        fprintf(stderr, "In function 'as_set_queue' \nError: the patient queue cannot be null \n");
    }

    as->patient_queue = patient_queue;
}



// Private Functions // Funções privadas


int _as_patient_arrived() {
    return ((rand() / (double) RAND_MAX) < ARRIVAL_PROBABILITY);
}

void _as_process_arrival(ArrivalSimulation *as, int current_time) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Builds the patient's object
    // Constrói o objeto paciente
    Patient *new_patient = patient_create();

    // Checks success in creating the patient object
    // Verifica o sucesso na criação do objeto paciente
    if (!new_patient) {
        fprintf(stderr, "Error: patient object creation failure \n");
        return;
    }

    // Generates a patient's id
    // Gera um id de paciente
    const int id_patient = patient_generation_id(patient_queue);

    // Generates a random patient' name
    // Gera um nome de paciente aleatório
    const char *name_patient = patient_generation_random_name();

    new_patient = _as_register_patient(new_patient, id_patient, current_time);

    // Insert the patient at the end of the queue
    // Insere o paciente no final da fila
    gq_enqueue(as->patient_queue, (void *) new_patient);

    // Format the patient object to string
    // Formata o objeto paciente para string
    const char *formatted_patient = patient_format_to_string(new_patient);

    // Saves the patient to the database
    // Salva o paciente no banco de dados
    patient_save(new_patient, "db_patient.txt", formatted_patient);
}

static Patient _as_register_patient(Patient *patient, int id_patient, char *name_patient, int timestamp_patient) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Sets the patient's id
    // Define o id do paciente
    patient_set_id(patient, patient_id);

    // Sets the patient's name
    // Define o nome do paciente
    patient_set_name(patient, name_patient);

    // Sets the patient's timestamp
    // Define o timestamp do paciente
    patient_set_timestamp(patient, timestamp_patient);

    return patient;
}
