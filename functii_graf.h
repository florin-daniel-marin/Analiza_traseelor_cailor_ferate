#ifndef FUNCTII_GRAF_H
#define FUNCTII_GRAF_H
#include "structures.h"

graf *graf_create (int n);

void graf_matrix_add(graf *g, int lat, int col, int val);

void graf_display (graf *p, char path[]);

void graf_matrix_create(queue_t *queue, graf *g, char *tip);

void graf_neorientat_edges (graf *q);

void graf_orientat_edges (graf *q);

int graf_min_matrix (graf *q);

int graf_max_matrix (graf *q);

void graf_display_val (queue_t *queue, graf *g, int val, char path[]);

void graf_all_costs (graf *g, char path[]);

void graf_path_two_nodes (graf *graf, int src, int dest, char path[]);

void graf_path_two_nodes_recursiv(graf *graf, FILE *f, int j, int dest, bool inclus[], int path[], int path_index);
#endif