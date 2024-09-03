#ifndef EXAMPRIORITYQUEUE_H_INCLUDED
#define EXAMPRIORITYQUEUE_H_INCLUDED

#include "exam.h"
#include "genericqueue.h"

#define PRE_NORMAL 0.2
#define PRE_BRONQUITE 0.3



typedef struct exam_priority_queue ExamPriorityQueue;

ExamPriorityQueue *epq_create();

void epq_destroyer(ExamPriorityQueue *epq);

int epq_is_empty(const ExamPriorityQueue *epq, PriorityType type);

void epq_enqueue(ExamPriorityQueue *epq, PriorityType type, Exam *exam);

Exam *epq_dequeue(ExamPriorityQueue *epq);

int epq_get_size_by_priority(const ExamPriorityQueue *epq, PriorityType type);

int epq_get_size_total(const ExamPriorityQueue *epq);

#endif // EXAMPRIORITYQUEUE_H_INCLUDED
