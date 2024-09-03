#include <stdio.h>
#include <stdlib.h>

#include "../include/exam.h"
#include "../include/filehandler.h"
#include "../include/report.h"



struct report {
    int id;
    int condition;
    int timestamp;
    Exam *current_exam;
};



// OPERATIONS // OPERAÇÕES

Report *report_create() {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Allocates memory for an report structure
    // Aloca memória para uma estrutura report
    Report *report = (Report *) calloc(1, sizeof(Report));

    // Checks if the allocation successfull
    // Verifica se a alocação foi bem sucedida
    if (!report) {
        fprintf(stderr, "In function 'report_create' \nError: report allocation failure\n");
        return NULL;
    }

    return report;
}

void report_destroyer(Report *report) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Checks if the report exist
    // Verifica se o report existe
    if (!report) {
        fprintf(stderr, "In function 'report_destroyer' \nWarning: Report is null\n");
        return;
    }

    // Sets current_exam to null
    // Define current_exam como null
    report->current_exam = NULL;

    // Free memory of the exam priority queue
    // Libera memória para a fila de prioridades de exames
    free(report);
}

// MODIFICAR PARA RECEBER A CONDITION
const char *report_format_to_string(Report *report) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Static buffer to store the formatted report
    // Buffer estático para armazenar o report formatado
    static char formated_report[256];


    int exam_id = report_get_exam_id(report);
    char *exam_condition = exam_get_condition_code(report->current_exam);

    // Format the report object to string
    // Formata o objeto report para string
    snprintf(formated_report, sizeof(formated_report), "ID: %d\n Exam ID: %d\n Condition: %s\n Time stamp: %d", report->id, exam_id, exam_condition, report->timestamp);

    return formated_report;
}

void report_save(Report *report, const char *file_name, const char *str) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Builds the file handler
    // Constrói o manipulador de arquivos
    FileHandler *fh = fh_create(file_name);

    fh_write(fh, str);
    fh_destroyer(fh);
}


// GETTERS

int report_get_id(Report *report) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Checks if the report exist
    // Verifica se o report existe
    if (!report) {
        fprintf(stderr, "In function 'report_get_id' \nError: report cannot be null \n");
    }

    return report->id;
}

int report_get_condition(Report *report) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Checks if the report exist
    // Verifica se o report existe
    if (!report) {
        fprintf(stderr, "In function 'report_set_id' \nError: report cannot be null \n");
    }

    return report->condition;
}

int report_get_timestamp(Report *report) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Checks if the report exist
    // Verifica se o report existe
    if (!report) {
        fprintf(stderr, "In function 'report_set_id' \nError: report cannot be null \n");
    }

    return report->timestamp;
}

int report_get_exam_id(Report *report) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Checks if the report exist
    // Verifica se o report existe
    if (!report) {
        fprintf(stderr, "In function 'report_set_id' \nError: report cannot be null \n");
    }

    return exam_get_id(report->current_exam); // VERIFICAR NECESSIDADE DE ALTERAÇÃO
}


// SETTERS

void report_set_id(Report *report, int id) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Checks if the report exist
    // Verifica se o report existe
    if (!report) {
        fprintf(stderr, "In function 'report_set_id' \nError: report cannot be null \n");
    }

    report->id = id;
}

void report_set_condition(Report *report, int condition) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Checks if the report exist
    // Verifica se o report existe
    if (!report) {
        fprintf(stderr, "In function 'report_set_condition' \nError: report cannot be null \n");
    }

    report->condition = condition;
}

void report_set_timestamp(Report *report, int timestamp) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Checks if the report exist
    // Verifica se o report existe
    if (!report) {
        fprintf(stderr, "In function 'report_set_timestamp' \nError: report cannot be null \n");
    }

    report->timestamp = timestamp;
}
