'''
/******************************************************************************/  
/* Nome: Christian M. T. Takagi             No. USP: 7136971                  */  
/* Disciplina: MAC323                       Prof. Andre Fujita                */  
/* Exercicio Programa 2                     Arquivo: README.md                */  
/******************************************************************************/
'''


1. Introdução
================================================================================

Esse exercício programa trata de operações com grafos.

Foi usado como referência o material criado pelo Prof. Paulo Feofiloff, que 
se encontra em http://www.ime.usp.br/~pf/algoritmos_em_grafos/


2. Estrutura de Dados
================================================================================

De acordo com o enunciado, o grafo orientado é representado como um vetor no 
qual os vértices são os índices do vetor e os arcos são representados por uma 
lista encadeada para cada vetor.  

Para maiores detalhes sobre cada estrutura, leia os comentários no código fonte.

Devido a falta de esclarecimentos, assumo que a contagem de vértices começa a 
partir do vértice de número 0 e que se há um vértice não mencionado no arquivo
de entrada, mas algum outro de ordem posterior o for, considero que esse vertice
existe e que possui grau 0.  
Adoto também que o grau de um vértice é a união de seu grau de entrada e saída e
que um grafo orientado é chamado de digrafo.


3. Compilando
================================================================================

Para compilar, rode o Makefile que acompanha o projeto, com o make:  

    make
	
Observe que foram criados dois executáveis. O ep2db contém os links simbólicos
para se usar no gdb.  

Para limpar os arquivos temporários criados pelo make, execute:  

    make clean
  
4. O Programa
================================================================================

Para executar o programa digite:  

    ./ep2 arquivo_de_entrada.txt
	
Onde 'arquivo_de_entrada.txt' contém as informações do digrafo, de acordo com a 
formatação do enunciado.  

O programa irá, então, criar a representação por lista de adjacência do digrafo
e imprimir as informações pedidas.  

Após a impressão das informações do digrafo, o programa irá entrar em um modo
interativo, no qual o usuário deve inserir dois números e o programa irá
calcular a distancia do primeiro ao segundo e o caminho feito, se existir.
Segue a mensagem de instruções do modo interativo.

	==== Modo interativo ====
	== Encontrando um caminho de s a t ==");
	Para imprimir o caminho do vertice s ao vertice t, digite um numero 
	correspondente a s e outro para t. Tecle Enter.
	Para imprimir essa mensagem novamente digite algum numero negativos e outro 
	qualquer e tecle Enter.
	Qualquer outra entrada encerrara o programa.

Na realidade você também pode digitar cada valor separadamente seguido de um
Enter.


5. Dificuldades
================================================================================

A maior dificuldade foi do cálculo do grau de cada vértice. A solução foi 
calcular cada acréscimo durante a criação do digrafo.
Bem simples e provavelmente a solução mais óbvia para as outras pessoas, porém 
eu estava focado em fazer uma função isolada para seu cálculo.