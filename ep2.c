/******************************************************************************/
/* Nome: Christian M. T. Takagi    No. USP: 7136971                           */
/* Disciplina: MAC323    Profº Andre Fujita EP:2    Arquivo: README.md        */
/* EP:2    Arquivo: README.md                                                 */
/******************************************************************************/

/* O código a seguir utiliza a 'biblioteca' disponibilizada pelo Professor */
/* Paulo Feofiloff. Quando algum código for alterado, nos comentários será */
/* dito qual foi a mudança. */

#include<stdio.h>
#include<stdlib.h>


/* Vértices de digrafos são representados por objetos do tipo Vertex. */
#define Vertex int


typedef struct node {
    int w;
    struct node *next;
} *link;


/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A estrutura digraph representa um  */
/* digrafo. O campo adj é um ponteiro para o vetor de listas de adjacência, o */
/* campo V contém o número de vértices e o campo A contém o número de arcos. */
struct digraph {
   int V;
   int A;
   link *adj;
};

/* Um objeto do tipo Digraph contém o endereço de um digraph. */
typedef struct digraph *Digraph;

/* A função DIGRAPHinit devolve (o endereço de) um novo digrafo com */
/* vértices 0 1 ... V-1 e nenhum arco. */
Digraph DIGRAPHinit( int V) { 
    Vertex v;
    Digraph G = malloc( sizeof *G);
    G->V = V; 
    G->A = 0;
    G->adj = malloc( V * sizeof (link));
    for (v = 0; v < V; v++) 
        G->adj[v] = NULL;
    return G;
}


/* A função NEWnode recebe um vértice w e o endereço next de um nó e devolve  */
/* o endereço a de um novo nó tal que a->w == w e a->next == next. */
link NEWnode( Vertex w, link next) { 
    link a = malloc( sizeof (struct node));
    a->w = w; 
    a->next = next;     
    return a;                         
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHinsetA insere um */
/* arco v-w no digrafo G.  A função supõe que v e w são distintos, positivos, */
/* e menores que G->V. Se o digrafo já tem arco v-w, a função não faz nada. */
void DIGRAPHinsertA( Digraph G, Vertex v, Vertex w) { 
    link a;
    for (a = G->adj[v]; a != NULL; a = a->next) 
        if (a->w == w) return;
    G->adj[v] = NEWnode( w, G->adj[v]);
    G->A++;
}

/* Procura na lista G->adj[v] um arco w. Se encontrado, devolve o endereco do */
/* arco anterior. Caso contrario, devolve NULL  */
/*
void *DIGRAPHinsertA( Digraph G, Vertex v, Vertex w) {
    link ant = G->adj[v], *x;
    if (ant == NULL)
        x = ant->next;
    else {
        ant->next = NEWnode( w, ant);
        return;
    }
    while (x != NULL) {
        if (x->arc < a) {
            ant = x; x = x->next;
        }
        else if (x->w == a) {
            return;
        }
    }
    ant->next = NEWnode( w, x);
}
*/


/* Para cada vertice v do grafo G, imprime todos os vertices adjacentes a v */
void DIGRAPHshow(Digraph G) {
    int i;
    link p;
    for (i = 0; i < G->V; i ++) {
        for (p = G->adj[i]; p != NULL; p = p->next) {
            printf( "%d->%d\n", i, p->w);
        }
    }
}



/* MAIN */
int main( int argc, char *argv[]) {
    FILE *fi;
    int c, x, in, out, i;
    Digraph G;
    link *new = NULL;

    G = DIGRAPHinit( 3);

    if (argc < 2) {
        printf( "Faltam argumentos: %s filename\n", argv[0]);
        exit( 1);
    }

    fi = fopen( argv[1], "r");
    if (fi == NULL) {
        printf( "Falha ao abrir o arquivo %s\n", argv[1]);
        exit( 2);
    }
    while ((c = fscanf( fi, "%d %d", &in, &out)) > 0) {
        if (in > out)
            x = in;
        else
            x = out;

        if (x >= G->V) {
            new = realloc( G->adj, 2 * x * ( sizeof (link)));
            if (new == NULL) {
                free( G->adj);
                printf( "Erro ao realocar memoria\n");
                exit( 3);
            }
            else {
                G->adj = new;
                for (i = G->V; i < 2 * x; i++) {
                    G->adj[i] = NULL;
                }
                G->V = 2 * x;
            }
        }
        DIGRAPHinsertA( G, in, out);
    }
    DIGRAPHshow( G);
    return 0;
}
