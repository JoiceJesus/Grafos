/*Discente: Joice Jesus   Data:  Disciplina: Grafos
Este programa representa um grafo, ele cria a estrutura do grafo em formato de lista de adjacencias, recebe, o conjunto vertes 
adjacentes e seu respectivo peso, e imprime;
*/
#include<stdio.h>
#include<stdlib.h>

#define true 1
#define false 0
#define UGraph Graph

struct adjacencia {
	int vertice;
	int peso;
	struct adjacencia *prox;
};

typedef struct adjacencia ADJACENCIA ;

struct vertice {
	/*Armazenamento dos Dados*/
	ADJACENCIA *cab;
};

typedef struct vertice VERTICE;

struct grafo {
	int vertices;
	int arestas;
	VERTICE *adj;
};

typedef struct grafo GRAFO;

GRAFO *cria_Grafo(int v) {
	GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
	g->vertices = v;
	g->arestas = 0;
	g->adj = (VERTICE *)malloc(v*sizeof(VERTICE));
	int i;
	for(i=0; i<v; i++)
	g->adj[i].cab = NULL;
	return(g);
}
ADJACENCIA *cria_Adjacencia(int v, int peso) {
	ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
	temp->vertice = v;
	temp->peso = peso;
	temp->prox = NULL;
	return(temp);
}
int cria_Aresta(GRAFO *gr, int vi, int vf, int p) {
	if(!gr)	return(false);
	if((vf < 0) || (vf >= gr->vertices))
	return(false);
	if((vi < 0) || (vi >= gr->vertices))
	return(false);
	ADJACENCIA *novo = cria_Adjacencia(vf,p);
	novo->prox = gr->adj[vi].cab;
	gr->adj[vi].cab = novo;
	gr->arestas++;
	return(true);
}
void imprime(GRAFO *gr) {
	printf("Vertices: %d. Arestas: %d.\n", gr->vertices,gr->arestas);
	int i;
	for(i=0; i<gr->vertices; i++) {
	printf("v%d:",i);
	ADJACENCIA *ad = gr->adj[i].cab;
	while(ad) {
	printf("v%d(%d)", ad->vertice,ad->peso);
	ad = ad->prox;
	}
	printf("\n");
	}
}


int main(void){
	
	
	
	GRAFO *gr = cria_Grafo(4);//numero de vertices do grafo
	cria_Aresta(gr,0,1,2);//cria arestas e o peso
	cria_Aresta(gr,1,0,2);
	
	cria_Aresta(gr,0,2,4);
	cria_Aresta(gr,2,0,4);
	
	cria_Aresta(gr,3,2,1);
	cria_Aresta(gr,2,3,1);
	
	cria_Aresta(gr,3,1,6);
	cria_Aresta(gr,1,3,6);
	imprime(gr);
	
	
	return 0;
}
