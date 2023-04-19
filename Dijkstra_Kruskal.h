#ifndef DIJKSTRA_KRUSKAL_H
#define DIJKSTRA_KRUSKAL_H
#include "structures.h"

#define nrm 600

void dijkstra(queue_t *queue, graf *graf, int src, int if_display, char path[], int *distanta_max, int *dest);
void dijkstra_print_path(queue_t *queue, FILE *f, int parent[], int nod_start, int j);
int dijkstra_print_solution(queue_t *queue, graf *graf, FILE *f, int dist[], int src, int parent[]);
void dijkstra_max_path(graf *graf, int src, int *distanta_max, int *dest);
void kruskalMST(graf *g, graf *mst, char txt_path[], char txt_path_2[]);
int find_nod_start(int i, int nod_parinte[]);
int union_fct(int i, int j, int nod_parinte[]);

#endif