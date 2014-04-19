/******************************************************************************/
/* Nome: Christian M. T. Takagi    No. USP: 7136971                           */
/* Disciplina: MAC323    Profº Andre Fujita EP:2    Arquivo: README.md        */
/* EP:2    Arquivo: README.md                                                 */
/******************************************************************************/

/* O código a seguir utiliza a 'biblioteca' disponibilizada pelo Professor */
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
struct digraph {
   int V;
   int A;
   Vertex *adj;
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


/* Para cada vertice v do grafo G, imprime todos os vertices adjacentes a v */
void DIGRAPHshow(Digraph G) {
    int i;
    link p;
    printf( "G->V: %d\tG->A: %d\n", G->V, G->A);
    printf( "G->adj:\n");
    for (i = 0; i < G->V; i ++) {
        printf( "V: %d | indeg: %d | outdeg: %d | arcs:", 
                i, G->adj[i].indeg, G->adj[i].outdeg);
        for (p = G->adj[i].arcs; p != NULL; p = p->next) {
            printf( "  %d", p->w);
        }
        printf("\n");
    }
}


/* Imprime as instrucoes de uso do modo interativo. */
void showHelp() {
    printf( "==== Modo interativo ====\n== Encontrando um caminho de s a t ==");
    printf( "Para imprimir o caminho de s a t, digite o numero correspondente");
    printf( "a s e tecle \nEnter. Repita para t.\n Para sair do programa");
    printf( " digite qualquer letra e tecle Enter.\n");
    printf( "Para imprimir essa mensagem novamente digite dois numeros");
    printf( " negativos e tecle Enter\n");
}


/* MAIN */
int main( int argc, char *argv[]) {
    FILE *fi;
    int c, x, in, out, max, i;
    Digraph G;
    Vertex *new = NULL;

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
    max = x = G->V;
    while ((c = fscanf( fi, "%d %d", &in, &out)) > 0) {
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
    new = realloc( G->adj, G->V * ( sizeof (Vertex)));
    G->adj = new;
    DIGRAPHshow( G);

    showHelp();
    while ((c = scanf( "%d %d", &in, &out)) == 2) {
        if (in < 0 || out < 0)
            exit(0);
        printf("BETA\n");
    }
    return 0;
}
