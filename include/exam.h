#ifndef EXAM_H_INCLUDED
#define EXAM_H_INCLUDED

#include <time.h>

typedef enum {
    NORMAL = 1,
    BRONQUITE = 2,
    PNEUMONIA = 3,
    COVID = 4,
    EMBOLIA_PULMONAR = 4,
    DERRAME_PLEURAL = 4,
    FIBROSE_PULMONAR = 5,
    TUBERCULOSE = 5,
    CANCER_PULMAO = 6
}PriorityType;


typedef struct exam Exam;

Exam *exam_create();

void exam_destroyer(Exam *exam);

const char *exam_format_to_string(Exam *exam);

int exam_generate_random_id();

const int exam_get_id(Exam *exam);

const int exam_get_patient_id(Exam *exam);

const int exam_get_rx_id(Exam *exam);

const int exam_get_time(Exam *exam);

const char *exam_get_condition(Exam *exam);

void exam_set_id(Exam *exam, int id);

void exam_set_patient_id(Exam *exam, int patient_id);

void exam_set_rx_id(Exam *exam, int rx_id);

void exam_set_condition(Exam *exam, char *condition_ia);

void exam_set_time(Exam *exam, int time);

#endif // EXAM_H_INCLUDED
