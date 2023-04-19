#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"


/**
 * TASK 1.
 *
 * Creeaza o coada vida.
 *
 * Functia nu primeste niciun parametru.
 * Ea doar aloca spatiu de memorie pentru o coada cu tipul 'queue_t' si
 * returneaza un pointer catre spatiul alocat.
 */
queue_t *queue_create(int SIZE_CHUNK)
{
	queue_t *queue = NULL;

	/* TODO: TASK 1: Alocare memorie pentru o coada vida. Initializare campuri. */
	queue = malloc (SIZE_CHUNK* sizeof(queue_t));

	queue->head = NULL;
	queue->tail = NULL;
	queue->index_max = 0;
	queue->length = 0;
	return queue;
}

/**
 * TASK 2, a)
 *
 * Creeaza un nod nou pentru lista inlantuita.
 *
 * Functia primeste o valoare de tip intreg, aloca dinamic spatiu pentru
 * un nod nou din lista inlantuita, il initializeaza si returneaza
 * un pointer catre acest nod.
 */
queue_node_t *queue_node_create(char *string, int val, int index, char *ruta)
{
	queue_node_t *node = NULL;

	/* TODO: TASK 2, a): Alocare si initializare nod. */
	node = malloc (sizeof(queue_node_t));
	node->string = malloc ((strlen(string)+1)*sizeof(char));
	node->ruta = malloc ((strlen(ruta)+1)*sizeof(char));

	strcpy(node->string, string);
	node->val = val;
	node->index = index;
	strcpy(node->ruta, ruta);
	node->next = NULL;
	node->prev = NULL;
	return node;
}

/**
 * TASK 2, b).
 *
 * Adauga un element nou in coada.
 *
 * Functia primeste ca parametrii un pointer catre coada in care se va adauga
 * un element nou cu valoarea 'val'.
 */
void queue_push(queue_t *queue, char *string, int val, char *ruta)
{
	queue_node_t *node = NULL;
	queue_node_t *q = queue->head;
	int ok = 1;
	
	if (queue_empty(queue) == 0) //daca coada exista
	{	
		do{	
		ok = 1;
		if(strcmp(q->string, string) == 0){ //testez daca statia mai exista in coada
			node = queue_node_create(string, val, q->index, ruta);//dc statia exista, indexului nodului nou ii atribui acelasi index ca si cel vechi, statia este aceasi=> acelasi index
			ok = 0;
			//q = queue->head;
			break;
		}
		q = q->next;
		}while(q != NULL && ok != 0);
	
		if (ok != 0){ //toate elementele, in afara de primul, cand sunt create prima data
			node = queue_node_create(string, val, queue->index_max, ruta);
			queue->index_max = queue->index_max + 1; //formez un index nou pentru statie
		}

		queue->tail->next = node;
		node->prev = queue->tail;
		queue->tail = node;
	}
	else{ //daca in coada nu se afla niciun element, se creaza capul listei
		node = queue_node_create(string, val, queue->index_max, ruta);
		queue->index_max = queue->index_max + 1; //formez un index nou pentru statie
		queue->head = queue->tail = node;
	}
	queue->length = queue->length + 1;
}

/**
 * TASK 3.
 *
 * Afiseaza la stdout (consola) continutul cozii, impreuna cu lungimea ei.
 *
 * Functia primeste ca parametrii un pointer catre coada care trebuie afisata.
 */
void queue_print(queue_t *queue)
{
	queue_node_t *p = queue->head;
	/* TODO: Parcurgere si afisare. */
	while (p != NULL)
	{
		printf ("%s.   \t%d.\t%d.\n",p->string,p->val,p->index);
		p = p->next;
	}
}

/**
 * TASK 4.
 *
 * Scoate un element din coada.
 *
 * Functia primeste ca parametrii un pointer catre coada din care trebuie
 * scos un element.
 *
 * Functia returneaza valoarea retinuta de catre nod.
 */
void queue_pop(queue_t *queue)
{

	/* TODO: Identificare nod de tipul 'queue_node_t' ce trebuie scos. */
	if(queue_empty(queue))
		exit;
	/* TODO: Copiere valoare. Stergere nod.*/
	queue_node_t *p = queue->head;
	queue->head = queue->head->next;
	queue->length = queue->length - 1;
	free(p);

}

/**
 * TASK 5 a)
 *
 * Functia returneaza valoarea primului element din coada, fara sa il stearga.
 *
 * Functia primeste ca parametru un pointer catre coada din care trebuie
 * intors elementul.
 *
 * In caz ca (virgula) coada e vida, se intoarce valoarea constantei INT_MIN.
 * Ea este definita in biblioteca limits.h
 */
int queue_front(queue_t *queue)
{
	int val = 0;

	/* TODO */
	if (queue_empty(queue) == 0)
		val = queue->head->val;
	else
		val = INT_MIN;
	return val;
}

/**
 * TASK 5 b)
 *
 * Functia returneaza valoarea ultimului element din coada, fara sa il stearga.
 *
 * Functia primeste ca parametru un pointer catre coada din care trebuie
 * intors elementul.
 *
 * In caz ca (virgula) coada e vida, se intoarce valoarea constantei INT_MIN.
 * Ea este definita in biblioteca limits.h
 */
int queue_back(queue_t *queue)
{
	int val = 0;

	/* TODO */
	if (queue_empty(queue) == 0)
		val = queue->tail->val;
	else
		val = INT_MIN;
	return val;
}

/**
 * TASK 5 c)
 *
 * Functia returneaza 1 daca coada este vida, 0 in caz contrar.
 *
 * Functia primeste ca parametru un pointer catre coada.
 */
int queue_empty(queue_t *queue)
{
	/* TODO */
	if (queue_length(queue) == 0)
	{
		return 1;
	}
	return 0;
}

/**
 * TASK 5 d)
 *
 * Functia returneaza dimensiunea cozii.
 *
 * Functia primeste ca parametru un pointer catre coada.
 */
int queue_length(queue_t *queue)
{
	return queue->length;
	/* TODO */

	return 0;
}

int queue_get_index (queue_t *queue, char *string)
{
	if(string == NULL)
		exit;
	
	queue_node_t *q = queue->head;
	while (q != NULL)
	{
		if (strcmp(q->string, string) == 0)
			return q->index;
		q = q->next;
	}
}

char * queue_get_string (queue_t *queue, int index)
{
	queue_node_t *q = queue->head;
	while (q != NULL)
	{
		if (q->index == index)
			return q->string;
		q = q->next;
	}
}