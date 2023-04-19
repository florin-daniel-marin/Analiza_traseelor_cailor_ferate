#ifndef QUEUE_H
#define QUEUE_H
#include "structures.h"

int queue_empty(queue_t *queue);
int queue_length(queue_t *queue);
queue_t *queue_create(int SIZE_CHUNK);
queue_node_t *queue_node_create(char *string, int val, int index, char *ruta);
void queue_push(queue_t *queue, char *string, int val, char *ruta);
void queue_print(queue_t *queue);
void queue_pop(queue_t *queue);
int queue_front(queue_t *queue);
int queue_back(queue_t *queue);
int queue_get_index (queue_t *queue, char *string);
char * queue_get_string (queue_t *queue, int index);
#endif