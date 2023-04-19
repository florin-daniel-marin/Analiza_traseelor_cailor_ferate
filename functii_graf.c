#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "functii_graf.h"
#include "queue.h"

graf *graf_create (int n)
{
	int i;
	graf *p = malloc(sizeof(graf));
	if (p == NULL)
	exit (1);
	
	p->muchii = 0;
	p->varf = n;
	
	p->matrice_adiacenta = malloc(n * sizeof (int*));
	
	for (i = 0; i < n; i++)
		p->matrice_adiacenta[i] = calloc (n, sizeof(int));

	if (p->matrice_adiacenta == NULL)
		exit(1);
	
	return p;
}

void graf_matrix_add(graf *g, int lat, int col, int val)
{
	g->matrice_adiacenta[lat][col] = val;
}

//pe primul si pe ultimul rand se pune cate un numar: src si dst au un singur vecin
//pe restul 2, ->next si ->prev

void graf_matrix_create(queue_t *queue, graf *g, char *tip)
{
	queue_node_t *q = queue->head;

	int val = 0;
	q = queue->head;

	while (q->next != NULL)// se merge rand cu rand
	{
		if (q->next->string != NULL) //prima statie index = 0 => primul rand
		{
			//pentru grafurile simple, val = 1---------------
			if (q->next->val - q->val < 0){val = 0;} //din coada, daca e prima val dintr o ruta, pe matricea de adiacenta se va pune 0, else diferenta dintre cele 2 statii
				else {val = 1;}
			
			if (strcmp(tip,"ns") == 0){ //neorientat simplu
				graf_matrix_add(g, q->index, q->next->index, val);
				graf_matrix_add(g, q->next->index, q->index, val);
			}
			if (strcmp(tip,"os") == 0) //orientat simplu
				graf_matrix_add(g, q->index, q->next->index, val);

			//pentru grafurile cu cost, val = q->next->val - q->val---------------
			if (q->next->val - q->val < 0){val = 0;} //din coada, daca e prima val dintro ruta, pe matricea de adiacentase va pune 0, else diferenta dintre cele 2 statii
				else {val = q->next->val - q->val;}
			
			if (strcmp(tip,"nc") == 0){ //neorientat + cost
				graf_matrix_add(g, q->index, q->next->index, val);
				graf_matrix_add(g, q->next->index, q->index, val);
			}
			if (strcmp(tip,"oc") == 0)  // orientat + cost
				graf_matrix_add(g, q->index, q->next->index, val);
		}
	q = q-> next;
	}
}

void graf_orientat_edges (graf *q)
{
	int sum = 0;
	int i, j;

	for (j = 0; j < q->varf; j++)
		for (i = 1 + j; i < q->varf; i++){
			if (q->matrice_adiacenta[j][i] != 0)
				sum++;
		}
	
	q->muchii = sum;
}

void graf_neorientat_edges (graf *q)
{
	int sum = 0;
	int i, j;

	for (j = 0; j < q->varf; j++)
		for (i = 0; i < q->varf; i++){
			if (q->matrice_adiacenta[j][i] != 0)
				sum++;
		}

	q->muchii = sum;
}

int graf_min_matrix (graf *q)
{
	int min = 9999;
	int k = 0;
	int i, j;

	for (j = 0; j < q->varf; j++)
		for (i = 0; i < q->varf; i++){
			if (q->matrice_adiacenta[j][i] < min && q->matrice_adiacenta[j][i] != 0)
				min = q->matrice_adiacenta[j][i];
		}
	return min;
}

int graf_max_matrix (graf *q)
{
	int max = INT_MIN;
	int k = 0;
	int i, j;

	for (j = 0; j < q->varf; j++)
		for (i = 0; i < q->varf; i++){
			if (q->matrice_adiacenta[j][i] > max)
				max = q->matrice_adiacenta[j][i];
		}
	return max;
}

void graf_display_val (queue_t *queue, graf *g, int val, char path[])
{
	int i, j, k = 0;
	FILE *f;
	queue_node_t *q = queue->head;
	queue_node_t *r = queue->head;

	if((f = fopen(path, "wt")) == NULL)
		exit(1);

	while (q != NULL){
		if (q->next != NULL)
			if ((q->next->val - q->val) == val){
				fprintf(f, "%s -> %s: %d km pe ruta %s cu index statii: %d %d", q->string, q->next->string, (q->next->val - q->val), q->ruta, q->index, q->next->index);
				fprintf(f, "\n");
			}
		q = q->next;
	}

	fclose(f);
}

void graf_all_costs (graf *g, char path[])
{
	int i, j;
	int sum = 0, k = 0;
	FILE *f;
	
	if((f = fopen(path, "wt")) == NULL)
		exit(1);


	for (j = 0; j < g->varf; j++){
		for (i = 0 + k; i < g->varf; i++){
			sum = sum + g->matrice_adiacenta[j][i];	
		}
		k++;
	}
	fprintf(f, "%d", sum);
	fclose(f);
}

void graf_display (graf *q, char path[])
{
	int i, j;
	FILE *f;
	
	if((f = fopen(path, "wt")) == NULL)
		exit(1);

	for(i = 0; i < q->varf; i++)
	{
		for (j = 0; j < q->varf; j++){
			if (q->matrice_adiacenta[i][j] == 9999)
				q->matrice_adiacenta[i][j] = 0;
			fprintf(f, "%d,", q->matrice_adiacenta[i][j]);
		}
		fprintf(f, "\n");
	}

	fclose(f);		
}

void graf_path_two_nodes (graf *graf, int src, int dest, char txt_path[])
{
	int i, j;
	FILE *f;
	
	if((f = fopen(txt_path, "wt")) == NULL)
		exit(1);

    int *path; 
	path = malloc (graf->varf * sizeof(int));
    bool *inclus;
	inclus = malloc (graf->varf * sizeof(bool));
    int path_index = 0;

    for (int i = 0; i < graf->varf; i++)
    {
        inclus[i] = false;
    }
  
	graf_path_two_nodes_recursiv(graf, f, src, dest, inclus, path, path_index);
	printf("%d", path_index);
	fclose(f);
}

void graf_path_two_nodes_recursiv(graf *graf, FILE* f, int src, int dest, bool *inclus, int *path, int path_index)
{

	int i, k = 0;
	inclus[src] = true;
	path[path_index] = src;
	path_index = path_index + 1;

	if (src == dest)
	{
		for (i = 0; i < path_index; i++)
			fprintf(f, "%d ", path[i]);
		fprintf(f, "\n");
		//return;
	}
	else
	{
		for (i = 0; i < graf->varf; i++)
		{
			if(!inclus[i] && graf->matrice_adiacenta[src][i] != 0)
				graf_path_two_nodes_recursiv(graf, f, i, dest, inclus, path, path_index);
		}
	}
	path_index = path_index - 1;
	inclus[src] = false;
}
