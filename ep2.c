/******************************************************************************/
/* Nome: Christian M. T. Takagi             No. USP: 7136971                  */
/* Disciplina: MAC323                       Prof.  Andre Fujita               */
/* Exercicio Programa 2                     Arquivo: ep2.c                    */
/******************************************************************************/

/* O código a seguir utiliza a 'biblioteca" disponibilizada pelo Professor */
/* Paulo Feofiloff. Quando algum código for alterado, nos comentários será */
/* dito qual foi a mudança, se pertinente. */

#include<stdio.h>
#include<stdlib.h>


/* A lista de adjacência de um vértice v é composta por nós do tipo node. */
/* Cada nó da lista corresponde a um arco e contém um vizinho w de v e o */
/* endereço do nó seguinte da lista. Um link é um ponteiro para um node. */
typedef struct node {
    int w;
    struct node *next;
} *link;


/* Vértices de digrafos são representados por objetos do tipo Vertex. */
/* Cada vértice contém informações sobre seu grau de entrada (indeg) e */
/* sobre seu grau de saída (outdeg). */
typedef struct vertex {
    int indeg;
    int outdeg;
    link arcs;
} Vertex;


/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A estrutura digraph representa um  */
/* digrafo. O campo adj é um ponteiro para o vetor de listas de adjacência, o */
/* campo V contém o número de vértices e o campo A contém o número de arcos. */
/* O vetor dist armazena as distancias entre um vertice e os demais e o vetor */
/* parent armazena os pais de um dado vertice. Ambos sao manipulados pela */
/* função DIGRAPHdist() e suas informacoes são impressas por imprimeCaminho() */
struct digraph {
    int V;
    int A;
    Vertex *adj;
    int *dist;
    int *parent;
};

/* Um objeto do tipo Digraph contém o endereço de um digraph. */
typedef struct digraph *Digraph;


/* A função DIGRAPHinit devolve (o endereço de) um novo digrafo com */
/* vértices 0 1 ... V-1 e nenhum arco. Edição: Portanto, seu grau é 0. */
Digraph DIGRAPHinit( int V) {
    int v;
    Digraph G = malloc( sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = malloc( V * sizeof (Vertex));
    for (v = 0; v < V; v++) {
        G->adj[v].arcs = NULL;
        G->adj[v].indeg = 0;
        G->adj[v].outdeg = 0;
    }
    return G;
}


/* A função NEWnode recebe um vértice w e o endereço next de um nó e devolve  */
/* o endereço a de um novo nó tal que a->w == w e a->next == next. */
link NEWnode( int w, link next) { 
    link a = malloc( sizeof (struct node));
    a->w = w; 
    a->next = next;
    return a;
}


/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHinsetA insere um */
/* arco v-w no digrafo G.  A função supõe que v e w são distintos, positivos, */
/* e menores que G->V. Se o digrafo já tem arco v-w, a função não faz nada. */
/* Edição: Quando um arco é adicionado, atualizamos a informação de seu grau. */
void DIGRAPHinsertA( Digraph G, int v, int w) { 
    link a;
    for (a = G->adj[v].arcs; a != NULL; a = a->next) 
        if (a->w == w) return;
    G->adj[v].arcs = NEWnode( w, G->adj[v].arcs);
    G->A++;
    G->adj[w].indeg ++;
    G->adj[v].outdeg ++;
}


/* Para cada vertice v do digrafo G, imprime todos os vertices adjacentes a v */
void DIGRAPHshow(Digraph G) {
    int i;
    link p;
    printf( "\nO grafo contem %d vertices e %d arestas\n", G->V, G->A);
    printf( "A tabela a seguir contem informacoes sobre cada vertice.\n\n");
    printf( "Vertice|grau de entrada|grau de saida|lista de adjacencias:");
    printf( "w1  w2  ...   wn\n");
    for (i = 0; i < G->V; i ++) {
        printf( "v: %d | entrada: %d | saida: %d |",
                i, G->adj[i].indeg, G->adj[i].outdeg);
        for (p = G->adj[i].arcs; p != NULL; p = p->next) {
            printf( "  %d", p->w);
        }
        printf("\n");
    }
    printf("\n");
}


/* Calcula a distância de um vértice s a cada um dos demais vértices do */
/* digrafo G. Para cada vértice v, a distância de s a v é depositada em */
/* G->dist[v]. Edição: Foi acrescentado o calculo do vetor parent, para */ 
/* registrar o caminho de s a t. */
void DIGRAPHdist( Digraph G, int s) {
    const int INFINITO = G->V;
    int v, w; 
    link a;
    int *fila, ini, fim;
    fila = malloc( G->V * sizeof (int));
    for (v = 0; v < G->V; v++)
        G->dist[v] = INFINITO;
    G->dist[s] = 0;
    fila[0] = s; ini = fim = 0;

    while (ini <= fim) {
        /* fila[ini..fim] é uma fila de vértices */
        v = fila[ini++]; 

        for (a = G->adj[v].arcs; a != NULL; a = a->next) {
            w = a->w;
            if (G->dist[w] == INFINITO) {
                G->dist[w] = G->dist[v] + 1;
                G->parent[w] = v;
                fila[++fim] = w;
            }
        }
    }
}


/* Editado: Imprime o caminho e a distâcia do vértice s ao t. */
void imprimeCaminho( Digraph G, int s, int t) {
    int w, topo = 0, *pilha;
	printf("Distancia de %d a %d: %d\n", s, t, G->dist[t]);
	printf("Caminho: ");
    pilha = malloc( G->V * sizeof (int));
    for (w = t; w != s; w = G->parent[w])
        pilha[topo++] = w;
    printf( "%d", s);
    while (topo > 0) 
        printf( "-%d", pilha[--topo]);
    printf( "\n");
}


/* Imprime as instrucoes de uso do modo interativo. */
void showHelp() {
    printf( "==== Modo interativo ====\n== Encontrando um caminho de s a t ==");
    printf( "\nPara imprimir o caminho do vertice s ao vertice t, digite um "); 
    printf( "numero correspondente a s e outro para t. Tecle Enter.\n");
    printf( "Para imprimir essa mensagem novamente digite algum numero ");
    printf( "negativos e outro \nqualquer e tecle Enter\n");
	printf( "Qualquer outra entrada encerrara o programa.\n");
}


/* Completa o digrafo G com as informações carregadas pelo arquivo file. */
void DIGRAPHconstruct( Digraph G, FILE *file) {
    int max, x, c, i, in, out;
    Vertex *new = NULL;
    max = x = 0; 
    while ((c = fscanf( file, "%d %d", &in, &out)) > 0) {
        if (in > out)
            x = in;
        else
            x = out;
        if (x > max)
            max = x;
        if (x >= G->V) {
            new = realloc( G->adj, 2 * x * ( sizeof (Vertex)));
            if (new == NULL) {
                free( G->adj);
                printf( "Erro ao realocar memoria\n");
                exit( 3);
            }
            else {
                G->adj = new;
                for (i = G->V; i < 2 * x; i++) {
                    G->adj[i].arcs = NULL;
                    G->adj[i].indeg = 0;
                    G->adj[i].outdeg = 0;
                }
                G->V = 2 * x;
            }
        }
        DIGRAPHinsertA( G, in, out);
    }
    if (G->V > max)
        G->V = max + 1;
    new = realloc( G->adj, G->V * sizeof (Vertex));
    G->adj = new;
    G->dist = malloc( G->V * sizeof (int));
    G->parent = malloc( G->V * sizeof (int));
    free( file);
}


/* MAIN */
int main( int argc, char *argv[]) {
    FILE *file;
    int c, in, out;
    Digraph G;

    G = DIGRAPHinit( 20);
    if (argc < 2) {
        printf( "Faltam argumentos: %s filename\n", argv[0]);
        exit( 1);
    }
    file = fopen( argv[1], "r");
    if (file == NULL) {
        printf( "Falha ao abrir o arquivo %s\n", argv[1]);
        exit( 2);
    }
    DIGRAPHconstruct( G, file);
    DIGRAPHshow( G);
    showHelp();
    while ((c = scanf( "%d %d", &in, &out)) == 2) {
        if (in < 0 || out < 0)
            showHelp();
        else if (in >= G->V || out >= G->V) 
            printf( "Os vertices nao podem ser maior que %d\n", G->V);
        else {
            DIGRAPHdist( G, in);
            if (G->dist[out] == G->V) 
                printf( "Nao existe caminho do vertice %d ao %d\n", in, out);
            else {
                imprimeCaminho( G, in, out);
            }
        }
    }
    return 0;
}
