#ifndef REPORT_H_INCLUDED
#define REPORT_H_INCLUDED

typedef struct report Report;

// Builds a report's structure
// Constrói uma estrutura de report
Report *report_create();

// Destroys a report's structure
// Destrói uma estrutura report
void report_destroyer(Report *report);

// Saves the report in the database
// Grava o report no banco de dados
void report_save(Report *report, const char *file_name, const char *str);

const char *report_format_to_string(Report *report);


// GETTERS

// Gets the report's id
// Obtém o id do report
int report_get_id(Report *report);

// Gets the report's condition
// Obtém a condição do report
int report_get_condition(Report *report);

// Gets the report's timestamp
// Obtém o timestamp do report
int report_get_timestamp(Report *report);

// Gets the exam id associated with the report
// Obtém o id do exame associado ao report
const int report_get_exam_id(Report *report);


// SETTERS

// Sets the report's id
// define o id do report
void report_set_id(Report *report, int id);

// Sets the report's condition
// Define a condição do report
void report_set_condition(Report *report, int condition);

// Sets the report's timestamp
// define o timestamp do report
void report_set_timestamp(Report *report, int timestamp);

#endif // REPORT_H_INCLUDED
