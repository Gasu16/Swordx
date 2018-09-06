#include <stdio.h>
#include <stdlib.h>

// dichiaro una struct "node", la struttura di ogni singolo nodo della lista 
// tramite typedef, associo il nome "t_node" a "struct node"
typedef struct node
{
	// informazioni contenute nel nodo
	int data;

	// puntatore al nodo precedente
	struct node *prev;

	// puntatore al nodo successivo
	struct node *next;
} t_node;


// dichiaro una struct "dlist", la struttura della lista doppiamente linkata
// tramite typedef, associo il nome "t_dlist" a "struct dlist"
typedef struct dlist
{
	// tiene traccia di quanti nodi sono presenti all'interno della lista
	int count;

	// puntatore al primo nodo della lista
	struct node *header;

	// puntatore all'ultimo nodo della lista
	struct node *tailer;
} t_dlist;


// inizializza la lista
void init_list(t_dlist *list)
{
	// la lista inizialmente non contiene elementi
	list->count = 0;

	// sia la testa che la coda puntano inizialmente a NULL
	list->header = list->tailer = NULL;
}


// cancella la lista
void delete_list(t_dlist *list)
{
	t_node *n1, *n2;
	n1 = list->header;
	
	// scorro i nodi della lista e li cancello
	// tramite la funzione free() libero la memoria da essi occupata 
	while (n1 != NULL)
	{
		n2 = n1->next;
		free(n1);
		n1 = n2;
	}
}


// inserisce un nuovo nodo nella lista
void insert(t_dlist *list, int new_data)
{
	// creo il nuovo nodo e gli alloco uno spazio di memoria
	t_node *new_node;
	new_node = malloc(sizeof(t_node));

	// inizializzo il nuovo nodo e gli inserisco il nuovo dato
	new_node->data = new_data;
	new_node->next = NULL;
	
	// inserisco il nodo all'interno della lista: due casi possibili

	// CASO 1: la lista e' vuota (count e' 0)
	// il nuovo nodo fara' sia da header che da tailer
	if (list->count == 0)
	{
		new_node->prev = NULL;
		list->header = list->tailer = new_node;
	}
	// CASO 2: la lista contiene gia' almeno un elemento
	// aggancio il nuovo nodo alla fine della lista
	// dopo l'inserimento, il nuovo nodo sara' quindi il tailer della lista
	else
	{
		new_node->prev = list->tailer;
		list->tailer->next = new_node;
		list->tailer = new_node;
	}
	
	// aumento il contatore dei nodi della lista
	list->count++;
}


// cerca un'informazione all'interno della lista
// restituisce il nodo contenente quell'informazione
t_node * search(t_dlist *list, int value)
{
	t_node *tmp;
	tmp = list->header;

	// scorro la lista cercando value
	// ritorno l'indirizzo del primo nodo che contiene value
	// altrimenti continuo a scorrere la lista
	while (tmp != NULL)
	{
		if (tmp->data == value)
			return tmp;

		tmp = tmp->next;
	}

	// se non trovo nessun nodo contenente value, ritorno NULL
	return NULL;
}


// cancella un nodo dalla lista
void delete_node(t_dlist *list, t_node *n)
{
	// sgancio il nodo puntato da n dalla lista
	n->prev->next = n->next;
	if (n->next != NULL) // previene possibili Segmentation Fault
		n->next->prev = n->prev;
	

	// libero la memoria allocata
	free(n);
	list->count--;

	return;
}


// cancella tutti i nodi della lista contenenti un determinato valore
void delete_value(t_dlist *list, int value)
{
	t_node *tmp;
	
	while ((tmp = search(list, value)) != NULL)
		delete_node(list, tmp);

	return;	
}


// stampa tutti i dati che contengono i nodi della lista
void print_list(t_dlist *list)
{
	t_node *tmp;
	tmp = list->header;
	int i;

	for (i = 1; i <= list->count; i++)
	{
		printf("nodo %d: %d\n", i, tmp->data);
		tmp = tmp->next;
	}

	return;
}	


int main()
{
	printf("\nCreo e inizializzo la lista\n");
	t_dlist mylist;
	init_list(&mylist);
	
	printf("\nInserisco i seguenti valori all'interno della lista: 2, 2, 3, 3, 5, 5, 6, 7, 7, 7\n");
	insert(&mylist, 2);
	insert(&mylist, 2);
	insert(&mylist, 3);
	insert(&mylist, 3);
	insert(&mylist, 5);
	insert(&mylist, 5);
	insert(&mylist, 6);
	insert(&mylist, 7);
	insert(&mylist, 7);
	insert(&mylist, 7);

	printf("Stampo la lista:\n");
	print_list(&mylist);

	printf("\nCancello tutti i nodi che contengono il valore 5 dalla lista.\n");
	delete_value(&mylist, 5);

	printf("Stampo la lista:\n");
	print_list(&mylist);

	printf("Cancello la lista e chiudo.\n");
	delete_list(&mylist);

	return 0;
}
