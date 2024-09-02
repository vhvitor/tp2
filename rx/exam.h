#ifndef EXAM_H_INCLUDED
#define EXAM_H_INCLUDED

#include <time.h>

typedef struct exam Exam;

Exam *exam_create();

void exam_destroyer(Exam *exam);

const int exam_get_id(Exam *exam);

const int exam_get_patient_id(Exam *exam);

const int exam_get_rx_id(Exam *exam);

const int exam_get_time(Exam *exam);

const int exam_get_condition(Exam *exam);

void exam_set_id(Exam *exam, int id);

void exam_set_patient_id(Exam *exam, int patient_id);

void exam_set_rx_id(Exam *exam, int rx_id);

void exam_set_condition(Exam *exam, int condition_ia);

void exam_set_time(Exam *exam, int time);

#endif // EXAM_H_INCLUDED
