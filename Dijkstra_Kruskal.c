#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "functii_graf.h"
#include "queue.h"
#include "Dijkstra_Kruskal.h"

//-------Functii Dijkstra----------------shortest path---------------------------------------------------------------------

void dijkstra(queue_t *queue, graf *graf, int nod_start, int if_display, char path[], int *distanta_max, int *dest)
{
	int i, j, dist_min, nod_urmator;
	if (if_display){
		FILE *f;
	
	if((f = fopen(path, "wt")) == NULL)
		exit(1);
	}

    int n = graf->varf; //numarul de noduri

    int nod_parinte[n]; //array de noduri parinte => practic TOT drumul intre noduri de la nod_start la dest !!
	int dist[n]; //array de distanta intre nod_parinte si nod_urmator
	int nod_vizitat[n]; //array care arata daca nodul k a fost vizitat sau nu
	int cost[n][n]; //matrice de adiacenta unde valoriile de 0 au fost trecute in int_max

	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			if(graf->matrice_adiacenta[i][j] == 0)
				cost[i][j]=9999;
			else
				cost[i][j]=graf->matrice_adiacenta[i][j];
  
	// INITIALIZARE
    for (i = 0; i < n; i++){
        nod_parinte[i] = nod_start; //nodul parinte al nodului curent
        dist[i] = cost[nod_start][i]; //distanta intre noduri: costul (timp, km, etc)
        nod_vizitat[i] = 0;
    }
    dist[nod_start] = 0;
	nod_vizitat[nod_start] = 1;

	int count = 1;
    while(count < n){
		//calc noul nod
		dist_min = 9999;

        //nodul nu e vizitat si costul de pana acum e mai mic decat dist_min => se trece la urmatorul nod
		for (i = 0; i < n; i++){
        	if ((!nod_vizitat[i]) && (dist[i] < dist_min)){
            	dist_min = dist[i]; 
				nod_urmator = i;
			}
			if (dist[i] == *distanta_max)
				*dest = i; //destinatia pentru distanta maxima
		}
        nod_vizitat[nod_urmator] = 1; //1 -> nodul urmator devine vizitat

        for (i = 0; i < n; i++)
            if (!nod_vizitat[i])
                if(dist_min + cost[nod_urmator][i] < dist[i]){
                    nod_parinte[i] = nod_urmator; //se trece la nodul urmator
					//printf("np:%d| dist:%d|, dist_max:%d| ", nod_urmator, dist[i], *distanta_max);
                    dist[i] = dist_min + cost[nod_urmator][i];
                    if (dist[i] > *distanta_max) //caut distanta maxima
                        *distanta_max = dist[i];
                }
		count++;
    }
	if (if_display){
		FILE *f;
		if((f = fopen(path, "wt")) == NULL)
			exit(1);
		dijkstra_print_solution(queue, graf, f, dist, nod_start, nod_parinte);
		fclose(f);
	}
}

int dijkstra_min_distance(graf *graf, int dist[], bool inclus[])
{
      
    // Initialize min value
    int min = INT_MAX, min_index;
  
    for (int v = 0; v < graf->varf; v++)
        if (inclus[v] == false && dist[v] < min)
            min = dist[v], min_index = v;
  
    return min_index;
}

void dijkstra_print_path(queue_t *queue, FILE *f, int nod_parinte[], int nod_start, int j)
{

    if (nod_start == j)
        return;
    dijkstra_print_path(queue, f, nod_parinte, nod_start, nod_parinte[j]);
    fprintf(f, "%s ", queue_get_string(queue, j));
}
  
int dijkstra_print_solution(queue_t *queue, graf *graf, FILE *f, int dist[], int nod_start, int nod_parinte[])
{
	
    for (int i = 0; i < graf->varf; i++){
		if (dist[i] == 9999)
			dist[i] = 0;
		if (i != nod_start){
			fprintf(f, "%d > %d-%d-%s ", nod_start, i, dist[i], queue_get_string(queue, nod_start));
			dijkstra_print_path(queue, f, nod_parinte, nod_start, i);
			fprintf(f, "\n");
    	}
	}
	
}

//-------Functii Kruskal-----------minimum span tree-----------------------------------------------------------------------------

// Find set of vertex i
int find_nod_start(int i, int nod_parinte[])
{

	while (nod_parinte[i] != i)
        i = nod_parinte[i];
    return i;
}
 
// Does union of i and j. It returns
// false if i and j are already in same
// set.
int union_fct(int i, int j, int nod_parinte[])
{
	//if ((i = -1) && (j = -1))
	//	return 0;

	int a = find_nod_start(i, nod_parinte);
    int b = find_nod_start(j, nod_parinte);
	
	if (a != b){
		if (a > b)
			nod_parinte[b] = a;
		else
			nod_parinte[a] = b;	
		return 1;
		
	}
	nod_parinte[b] = a;
	return 0;
}
 
// Finds MST using Kruskal's algorithm
void kruskalMST(graf *g, graf*min_span_tree, char txt_path[], char txt_path_2[])
{
	int i, j, dist_min, a, b;
    int n = g->varf; //numarul de noduri

    //MINIMUM SPAN TREE
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			min_span_tree->matrice_adiacenta[i][j] == 0;

	int muchie_noua_nod_start;
	int muchie_noua_nod_end;
    int min_cost = 0; // Cost of min MST.
    int *nod_parinte; 
	nod_parinte = (int*) malloc((n)*sizeof(int));
	int dist[n]; //array de distanta intre nod_parinte si nod_urmator


    //initializare matrice de adiacenta
    int cost[n][n];
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			if(g->matrice_adiacenta[i][j] == 0)
				cost[i][j]=9999;
			else
				cost[i][j]=g->matrice_adiacenta[i][j];
	
	for (i = 0; i < n; i++){
        nod_parinte[i] = i;
    }

 
    // Calculeaza muchiile minimum span tree-ului rand pe rand, in mst_muchie
    int mst_muchie = 0;
	int k = 0;
	int stop = 0;
    while (mst_muchie < n - 1) {
    	//init
    	dist_min = 9999;
        muchie_noua_nod_start = -1;
        muchie_noua_nod_end = -1;

		//sorteaza muchiile in ordine crescatoare
		

        //caut muchia de cost minim din tot graful initial
        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++){
            	// doar daca nodul sursa pentru i si pentru j e diferit, adica subtree-ul nodului i nu e inclus in subtree-ul nodului j 
                if ((cost[i][j] < dist_min)){
                    dist_min = cost[i][j];
                    muchie_noua_nod_start = i; //muchie_noua_nod_start
                    muchie_noua_nod_end = j; //muchie_noua_nod_end
                }
            }
        }
		if ((muchie_noua_nod_start != -1) && (muchie_noua_nod_end != -1)){
			if((union_fct(muchie_noua_nod_start, muchie_noua_nod_end, nod_parinte) != 0) && (dist_min != 9999)){
				mst_muchie += 1;
				min_cost += dist_min;
				min_span_tree->matrice_adiacenta[muchie_noua_nod_start][muchie_noua_nod_end] = dist_min;
				min_span_tree->matrice_adiacenta[muchie_noua_nod_end][muchie_noua_nod_start] = dist_min;
			}
			cost[muchie_noua_nod_start][muchie_noua_nod_end] = 9999;
		} else {break;}
	}
	
    //show results
    //graf_display (min_span_tree, txt_path);

	FILE *f;
    if((f = fopen(txt_path_2, "wt")) == NULL)
		exit(1);
	fprintf(f, "Costul minim pentru mst: %d,", min_cost);
	fclose(f);	

	graf_path_two_nodes(min_span_tree, 1, 29, txt_path);
}
