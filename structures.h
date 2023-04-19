#ifndef STRUCTURES_H
#define STRUCTURES_H
/**
 * Structura de mai jos NU reprezinta o coada, ea reprezinta doar un element
 * dintr-o coada implementat ca o lista inlantuita.
 */
typedef struct a{
	/* Valoarea retinuta de catre nod. */
	char *string;
	int val;
	int index;
	char *ruta;
	/* Pointer catre urmatorul element de tip nod. */
	struct a *next;
	struct a *prev;
} queue_node_t;

typedef struct {
	/* Capul listei inlantuite. */
	queue_node_t *head;
	/* Coada listei inlantuite. */
	queue_node_t *tail;

	/* Dimensiunea cozii. */
	unsigned int length;
	unsigned int index_max;
} queue_t;

typedef struct graf
{
	int varf;
	int muchii;
	int **matrice_adiacenta;
}graf;

#endif