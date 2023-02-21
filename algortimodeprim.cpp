#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

/*Discente: Joice Jesus Disciplina: Grafos Data:16/02/2023. #Entre lagrimas, sofrimento, raiva e pesquisas salvaram-se todos.
Este programa controi um grafo usando lista de adjacencias de forma dinamica, e atravez do algoritmo de prim um algoritmo guloso e nesse caso feita de forma
simples nos da a A.G.M. Árvore Geradora Minima.
Refêrencias: Canal:Programação Descomplicada, https://www.ime.usp.br/~pf/algoritmos_para_grafos/, Material de Aula etc.
*/

struct grafo{
    int ponderado;//se o grafo é ponderado ou não.
    int NumerodeVertices;//numero de vertices que o grafo possui.
    int GrauMaximo;//grau máximo que o grafo possui.
    int **arestas;//guarda as conexões.(uma matriz alocada dinamicamente),linhas(guarda os vertices)e as colunas(guarda a quantidade de conexões que o vertice possui).
    float **pesos;//guarda o peso de cada aresta.
    int *grau;//vetor que guarda o grau de cada vertice.esse vetor vai até o valor armazenado na variavel grau_max(grau maximo do grafo).
};

/*nomeio a minha estrutura como do tipo Grafo.(minha estrutura grafo é do tipo Grafo agora).
e sendo um ponteiro para não presizar declarar tantos ponteiros ao longo do código.*/
typedef struct grafo *Grafo;

//função que cria o grafo, recebe o numero de vertices, o grau maximo que os vertices podem ter e se é ponderado ou não.
Grafo cria_Grafo(int NumerodeVertices, int GrauMaximo, int ponderado){
	int i;
    Grafo gr; // crio um novo ponteiro do tipo da minha estrutura intitualda com Grafo.
    gr = (Grafo) malloc(sizeof(struct grafo));//aloco espaço na memoria para meu ponteiro.
    if(gr != NULL){//testo se não ouve erro na alocação de memoria.
        gr->NumerodeVertices = NumerodeVertices;//guardo o numero de vertices
        gr->GrauMaximo = GrauMaximo;//guardo o numero  de arestas
        /*faço uma verificação logica só por garantia de que a variavel eh_ponderado receba o valor correto,
		para caso seja ponderado assuma o valor 1 e caso contrario assuma o valor 0.*/
		if(ponderado != 0){
		gr->ponderado = 1;
		}else{
		gr->ponderado = 0;	
		}
    	gr->grau = (int*) calloc(NumerodeVertices,sizeof(int));/*cria o vetor de graus, alocando espaço e zerando o valor dos vertices a principio
    	em resumo crio um vetor 1xn[| 0 | 0 | 0 |...n]*/    
        gr->arestas = (int**) malloc(NumerodeVertices * sizeof(int*));//crio a matriz de arestas, aloco espaço na memoria do tamanho do numero ve vertices.
        for(i=0; i<NumerodeVertices; i++)//para cada vertice eu crio o grau maximo que ele pode ter.
        gr->arestas[i] = (int*) malloc(GrauMaximo * sizeof(int));
        if(gr->ponderado){/*caso o grafo seja ponderado cria-se um vetor recebe o vertice e adiciona na coluna correspondente o 
		o peso ponderado = 1; nxm n=0 e m=0 = peso 10, n=1 m=1 peso 2, n=3 e m=4 peso 11 ..... */
        gr->pesos = (float**) malloc(NumerodeVertices * sizeof(float*));
        for(i=0; i<NumerodeVertices; i++)
        gr->pesos[i] = (float*) malloc(GrauMaximo * sizeof(float));
        }
    }
    	return gr;//retorno o grafo.
}
int insereAresta(Grafo gr, int origem, int destino, int orientado, float peso){
    if(gr == NULL)//verifica se o grafo é valido, se não retorno 0.
    return 0;
    if(origem < 0 || origem >= gr->NumerodeVertices)//verifica se a origem possui vertices validos, que seja maior que 0 e menor ou igual ao numero de vertices.caso não retorna  0.
    return 0;
    if(destino < 0 || destino >= gr->NumerodeVertices)//verifica se o destino possui vertices validos, que seja maior que 0 e menor ou igual ao numero de vertices.caso não retorna  0..
    return 0;
	//se a origem e destino existem ai adiciona na lista destino. aresta x grau= vertice destino.
    gr->arestas[origem][gr->grau[origem]] = destino;
    if(gr->ponderado)//caso seja ponderado faz a mesma coisa para o peso.
    gr->pesos[origem][gr->grau[origem]] = peso;
    gr->grau[origem]++;//soma mais uma para correr a lista e preenche-la.
    if(orientado == 0)//caso o seja orientado. ele precisa direcionar a aresta em direção inversa nesse caso destino->origem.
    insereAresta(gr,destino,origem,1,peso);
    return 1;//retorna 1 para mostrar e ocorreu tudo bem com a função.
}
void imprime_Grafo(Grafo gr){
	int i, j;
	    
	if(gr == NULL){
    return;
	}else{
    for(i=0; i < gr->NumerodeVertices; i++){
        printf("|   %d: ", i);
    for(j=0; j < gr->grau[i]; j++){
    if(gr->ponderado){
    	printf(" |   %d(%.2f), ", gr->arestas[i][j], gr->pesos[i][j]);
    }else{
    	printf("|   %d, ", gr->arestas[i][j]);
    }
	}
        printf("\n");
	}
	}
}
void prim(Grafo gr,int origem, int *pai){
	int i, j, destino,primeiro, NV = gr->NumerodeVertices;
	double menorPeso;
	//no começo os vertices não vão ter pai.
	for(i=0;i<NV;i++)
		pai[i] = -1;
		pai[origem] = origem;
	//procurando novos vertices	
	while(1){
		primeiro = 1;//seto 1 como peso da 1° aresta só para inicializar.
	for(i=0;i<NV;i++){//procuro todos os verteces
	if(pai[i]!=-1){//se achei um vertece ja visitado
	for(j=0;j<gr->grau[i];j++){//percorro os vizinhos do vertece vizitado.
	if(pai[gr->arestas[i][j]]==-1){//caso encontre o vertie vizinho não visitado. se for igul a -1 é porque não tem pai, então saremos para ser a raiz/pai da arvore .
	if(primeiro){
		//procuro pela aresta com menor peso.
		menorPeso = gr->pesos[i][j];
		origem = i;
		destino = gr->arestas[i][j];
		primeiro = 0;//primeiro passa a ser zero porque ja encontramos pelomenos um vertice.
	}else{//caso encontre mais um vertece, verifico se o peso da aresta é menor do que o ja encontrado. caso seja então menor peso passa a ser esse, e 
	if(menorPeso>gr->pesos[i][j]){
		menorPeso = gr->pesos[i][j];
		origem = i;
		destino = gr->arestas[i][j];//mudamos a origem e destino para os adjacentes dessa nova aresta.
	}
	}
	}
	}
	}
	}
	if(primeiro==1){//verifico se é o primeiro caso seja é porque não encontramos nada.então finalizamos a busca.
	break;
	}else{
	pai[destino]=origem;//caso encontre coloco no pai[destino] o peso q encontrei na busca do menor peso acima.
	}
	}
}
int main(void){
    int orientado = 0;
    Grafo gr = cria_Grafo(6, 6, 1);
    setlocale(LC_ALL, "Portuguese");
    
    printf("---------------------------------------------\n");
   	printf("         Grafos: Algoritmo de Prim \n");
   	printf("---------------------------------------------\n");
    printf("O algoritmo foi publicado por Robert C. Prim\nem 1957 e por E. W. Dijkstra pouco depois.\n\nPROBLEMA:Encontrar uma MST (árvore geradora\nde custo mínimo)de um grafo não-dirigido com\ncustos nas arestas.\n");
    
   	system("color D7");
   	printf("---------------------------------------------\n");
   	printf("|Vertice|   	   Aresta(Pesos) \n");
   	printf("---------------------------------------------\n");
    insereAresta(gr, 0, 1, orientado, 6);
    insereAresta(gr, 0, 2, orientado, 1);
    insereAresta(gr, 0, 3, orientado, 5);
    insereAresta(gr, 1, 2, orientado, 2);
    insereAresta(gr, 1, 4, orientado, 5);
    insereAresta(gr, 2, 3, orientado, 2);
    insereAresta(gr, 2, 4, orientado, 6);
    insereAresta(gr, 2, 5, orientado, 4);
    insereAresta(gr, 3, 5, orientado, 4);
    insereAresta(gr, 4, 5, orientado, 3);

    imprime_Grafo(gr);
    
    int i, j, pai[6];
	float soma=0.0;
	printf("---------------------------------------------\n");
    printf("|Aresta Escolhida| Vertice |  Peso  |  Soma \n");
    printf("---------------------------------------------\n");
	prim(gr,0,pai);
    for(i=0;i<6;i++){
    for(j=0; j < gr->grau[i]; j++){
    if(pai[i]==gr->arestas[i][j])
    printf("|       %d:       |     %d   |   %.2f |  %.2f \n",pai[i],i,gr->pesos[i][j],soma=soma+gr->pesos[i][j]);
	}	
	
}

    system("pause");
    
    return 0;
}

