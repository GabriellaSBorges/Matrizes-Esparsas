# Matrizes Esparsas

Biblioteca para trabalhar com matrizes esparsas (maior parte dos valores são iguais a zero), a fim de economizar memória e tempo de operação.
No entanto, é mais eficiente para a manipulação de poucas matrizes, visto que são alocadas separadamente.


## ➕ Operações principais

    - Criar uma matriz;
    - Destruir uma matriz;
    - Atribuir ou alterar valores de uma célula;
    - Ler o valor de uma célula;
    - Somar duas matrizes;
    - Multiplicar uma matriz por um escalar;
    - Multiplicar duas matrizes;
    - Multiplicar duas matrizes ponto a ponto;
    - Trocar duas linhas;
    - Trocar duas colunas;
    - Retornar uma submatriz;
    - Transpor uma matriz;
    - Realizar a convolução de uma matriz;
    - Salvar uma matriz esparsa em um arquivo binário;
    - Ler uma matriz esparsa de um arquivo binário;
    - Mostrar uma matriz na tela em formato esparso;
    - Mostrar uma matriz na tela em formato denso;

## ⚠ Operações principais

Na biblioteca, foram criadas algumas "flags" com o intuito facilitar o entendimento do programa e generalizar algumas funções para serem usadas com linhas e colunas.

`list_type` Tipo de lista  

    - linha 'l'
    - coluna 'c'

`node_type` Tipo de node 

    - actual 'a' -> node de uma posição específica
    - prev 'p' -> node anterior à uma posição específica
    - next 'n' -> node posterior à uma posição específica

`position_type` Tipo de posição do node 

    - linha 'l'
    - coluna 'c'

_**Exemplo:**_ Se queremos achar o node anterior a um índice em uma linha, usamos a função: 

.
    `Node *list_find_node(List *row, int index, char node_type, char list_type, char position_type)`

Nesse caso:

    list_type = 'l' 
    node_type = 'p'
    position_type = 'c' 

Ou seja, a linha será iterada, mas a posição que será comparada ao index desejado é a coluna!