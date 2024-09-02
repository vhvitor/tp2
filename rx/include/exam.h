#ifndef EXAM_H
#define EXAM_H

#include "exampriorityqueue.h"

// STRUCT // STRUCTURE

typedef struct exam Exam;

// FUNCTION PROTOTYPES // FUNCTION PROTOTYPES


Exam *exam_create();


void exam_destroyer(Exam *exam);

// Getters // Access Functions


const int exam_get_id(Exam *exam);


const int exam_get_patient_id(Exam *exam);


const int exam_get_rx_id(Exam *exam);


const int exam_get_condition(Exam *exam);


const int exam_get_time(Exam *exam);

// Setters // Modification Functions


void exam_set_id(Exam *exam, int id);


void exam_set_patient_id(Exam *exam, int patient_id);


void exam_set_rx_id(Exam *exam, int rx_id);


void exam_set_condition(Exam *exam, int condition);


void exam_set_time(Exam *exam, int time);


void exam_save(Exam *exam, const char *file_name, const char *str);


PriorityType exam_get_priority_type(Exam *exam);


char* get_exam_condition_per_code(Exam *exam);


const char *exam_format_to_string(const Exam *exam);

#endif // EXAM_H
