#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/exampriorityqueue.h"
#include "../include/arrivalsimulation.h"
#include "../include/patient.h"
#include "../include/genericqueue.h"
#include "../include/dispatcher.h"
// Structure for exam simulation
struct exam_simulation {
    int num_patients_treated;  // Number of patients treated
    ExamPriorityQueue *epq;    // Exam priority queue
};

void es_run(Dispatcher *dispatcher, ExamSimulation *es, GenericQueue *patient_queue, int current_time){
/**
 * \brief Runs the exam simulation process by registering a callback and triggering an event.
 *
 * \details This function sets up the exam simulation by first registering a callback function (`es_do_exam_callback`)
 *          with the dispatcher for a specific event (`EVENT_XR_ALLOCATION`). It then triggers the event, passing the
 *          current state of the simulation, the patient queue, and the current time. This setup allows the simulation
 *          to process patient exams asynchronously based on the event system.
 *
 * \param dispatcher - Pointer to the Dispatcher instance responsible for handling events and callbacks.
 * \param es - Pointer to the ExamSimulation structure that contains the state and resources for the simulation.
 * \param patient_queue - Pointer to the GenericQueue containing the patients waiting for an exam.
 * \param current_time - The current time in the simulation, used to manage timing and scheduling.
 *
 * \return void
 */

    disp_register_callback(dispatcher,EVENT_XR_ALLOCATION,es,es_do_exam_callback);

    disp_trigger_event(dispatcher,EVENT_XR_ALLOCATION,es, patient_queue, current_time);



}

void es_do_exam_callback(void *context, void *patient_queue, int current_time) {
/**
     * \brief Simulates performing an exam for a patient removed from the patient queue.
     *
     * \param context - Pointer to the exam simulation (ExamSimulation)
     * \param patient_queue - Queue of patients waiting for an exam
     * \param current_time - The current time of the simulation
     */

    ExamSimulation *es = (ExamSimulation *)context;

    // Create the exam machines
    int *machines = create_machines();

    // Check if there are patients in the queue
    if (patient_queue) {
        // Check and occupy an available machine for the patient in the queue
        Exam *new_exam = verify_and_ocupate(machines, patient_queue);

       // If a new exam is created
        if (new_exam) {
            // Convert the exam condition to a string and save it to the exam database
            char *condition = exam_format_to_string(new_exam);
            exam_save(new_exam, "exam_db.txt", condition);

            // Determine the priority type based on the exam condition
            PriorityType priority_type = exam_get_priority_type(new_exam);

             // Enqueue the exam in the priority queue
            epq_enqueue(es->epq, priority_type,new_exam);

             // Increment the number of patients treated
            es->num_patients_treated++;
        }
    }

}



// Function to create a new exam simulation
ExamSimulation *es_create(GenericQueue *patient_queue) {
/**
 * \brief Creates a new instance of an ExamSimulation.
 *
 * \details This function allocates memory for a new `ExamSimulation` structure and initializes it. It sets the
 *          number of patients treated to 0 and creates a new `ExamPriorityQueue` for managing the prioritization
 *          of exams. If memory allocation or queue creation fails, appropriate error messages are printed, and
 *          the function returns `NULL`. Otherwise, it returns a pointer to the newly created `ExamSimulation`
 *          instance.
 *
 * \param patient_queue - Pointer to the GenericQueue containing patients waiting for an exam. This parameter is
 *                        provided for potential use in the initialization but is not used directly in this function.
 *
 * \return Pointer to the newly created ExamSimulation structure. Returns `NULL` if memory allocation or queue
 *         creation fails.
 */

    ExamSimulation *es = (ExamSimulation*)malloc(sizeof(ExamSimulation));
    if (!es) {
        fprintf(stderr, "Error: Exam simulation allocation failure\n");
        return NULL;
    }

    es->num_patients_treated = 0;
    es->epq = epq_create();
    if (!es->epq) {
        fprintf(stderr, "Error: queue creation failure\n");
        free(es);
        return NULL;
    }

    return es;
}




static int *create_machines() {
/**
 * @brief Creates a list of X-Machines.
 * @return Pointer to an array of pointers to Rx (X-Machines).
 */
    int machines[5] = {0}; // Array of 5 machines, all initially available (0)
    return machines;
}



Exam *_verify_and_ocupate(int *machines_list, GenericQueue *patient_queue,int current_time) {
/**
 * @brief Verify and occupy an available X-Machine for the given patient.
 *
 * @param machines_list - Pointer to the array of X-Machines
 * @param patient_queue - Queue of patients waiting for an exam
 * @param current_time - Current time of the simulation
 * @return Pointer to the created Exam if a machine is available, NULL otherwise
 */

    Patient *patient = (Patient*)gq_dequeue(patient_queue);
    if (machines_list && patient) {
        for (int i = 0; i < 5; i++) {
            if (machines_list[i] == 0) {
                Exam *new_exam = _do_exam_with_AI(i+1,patient,current_time);
                machines_list[i] = 1;
                return new_exam;
            }
        }

        patient_destroyer(patient);

        printf("\nThere is no X-MACHINE avaible, please wait.");
    }
    return NULL;
}


ExamPriorityQueue *priority_queue_exams(ExamSimulation *es){

/**
 * \brief Retrieves the ExamPriorityQueue from an ExamSimulation instance.
 *
 * \details This function checks if the provided `ExamSimulation` pointer and its associated `ExamPriorityQueue`
 *          are valid. If both are valid, it returns the pointer to the `ExamPriorityQueue`. If either the
 *          `ExamSimulation` pointer or its `ExamPriorityQueue` is `NULL`, the function returns `NULL`.
 *
 * \param es - Pointer to the ExamSimulation instance from which the ExamPriorityQueue is to be retrieved.
 *
 * \return Pointer to the ExamPriorityQueue associated with the given ExamSimulation. Returns `NULL` if the
 *         `ExamSimulation` pointer or its `ExamPriorityQueue` is invalid.
 */

    // Check if the ExamSimulation pointer is valid
    if(es) {
        // Check if the ExamPriorityQueue pointer within the ExamSimulation is valid
        if(es->epq) {
            // Return the ExamPriorityQueue pointer if both checks pass
            return es->epq;
        }
        // Return NULL if the ExamPriorityQueue is NULL
        return NULL;
    }
    // Return NULL if the ExamSimulation pointer is NULL
    return NULL;
}


static int diagnostic_by_ai() {
/**
 * @brief Generate a random diagnostic based on AI
 * @details This function creates a diagnostic based on probability. The probabilities for each diagnostic are as follows:
 * - "Normal Health": 30%
 * - "Bronchitis": 20%
 * - "Pneumonia": 10%
 * - "COVID": 10%
 * - "Pulmonary Embolism": 5%
 * - "Pleural Effusion": 5%
 * - "Pulmonary Fibrosis": 5%
 * - "Tuberculosis": 5%
 * - "Lung Cancer": 10%
 * The thresholds array defines cumulative probability thresholds to determine the diagnostic.
 * @return Pointer to a string representing the diagnostic
 */



    static const int thresholds[] = {30, 50, 60, 70, 75, 80, 85, 90, 100};

    int geradorP = rand() % 100 + 1;

    for (int i = 0; i < 9; i++) {
        if (geradorP <= thresholds[i]) {
            return i;
        }
    }
    return 8;
}

Exam *_do_exam_with_AI(int machine,Patient *patient,int current_time) {
/**
 * \brief Perform an exam using the AI diagnostic and mark the machine as available.
 * \details This function simulates performing an exam on a patient using an AI-generated diagnostic.
 *          It assigns a unique exam ID, generates a diagnostic based on AI, and marks the X-Machine as available after the exam is completed.
 *          The exam is conducted with a simulated delay to mimic real-world processing time.
 *
 * \param machine - Number of the X-Machine performing the exam. It should be a valid number of a machine in use.
 * \param patient - Pointer to the patient undergoing the exam.
 * \param current_time - Current time of the simulation
 *
 * \return Pointer to the created Exam. If the machine is valid and the exam is successfully created,
 *         a pointer to the new Exam is returned. If the machine is invalid, the function returns NULL.
 */

        int exam_id = rand() % 1000;
        printf("\nExam started for (ID): %d", patient_get_id(patient));

    Exam *new_exam = exam_create(); // Create a new Exam structure
    int ai_diagnostic = diagnostic_by_ai(); // Generate a diagnostic based on AI
    exam_set_id(new_exam, exam_id); // Set the exam ID
    exam_set_patient_id(new_exam, patient_get_id(patient)); // Set the patient ID
    exam_set_condition(new_exam, ai_diagnostic); // Set the exam condition
    exam_set_time(new_exam, current_time); // Set the exam time

        printf("\nExam finished for (ID): %d", patient_get_id(patient));


        while(current_time<current_time+10){
        // waiting...
        current_time++;
        }

        return new_exam; // Return the created Exam


}

void destroyer_struct_exam_simulation(ExamSimulation *es){
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

    epq_destroyer(es->epq);
    free(es);



}

