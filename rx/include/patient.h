#ifndef PATIENT_H_INCLUDED
#define PATIENT_H_INCLUDED

#include "genericqueue.h"

typedef struct patient Patient;

Patient *patient_create();

void patient_destroyer(Patient *patient);

const void patient_save(Patient *patient, const char *file_name, const char *str);

const char *patient_generation_random_name();

int patient_generation_id(GenericQueue *q);

const char *patient_format_to_string(const Patient *patient);

const int patient_get_id(Patient *patient);

const char *patient_get_name(Patient *patient);

const int patient_get_timestamp(Patient *patient);

void patient_set_id(Patient *patient, const int id);

void patient_set_name(Patient *patient, const char *name);

void patient_set_timestamp(Patient *patient, const int timestamp);

#endif // PATIENT_H_INCLUDED
