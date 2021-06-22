/*  Autora: Laura Ferreira Rocha
    Data: 03/12/2020
*/

#include <stdio.h>
#define TAMANHO 12

void escreveMatriz(int **matriz);
void leMatriz(int **matriz);
int diagonais(int *);
int linhaColuna(int *);
int subMatrizes(int *);

int main(){
    int S[TAMANHO][TAMANHO];

    leMatriz(S);

    printf("Solulcao de Sudoku analisada:\n\n");
    escreveMatriz(S);

    //verificacao da solucao do Sudoku X
    if((diagonais(&S[0][0]) == 0) && (linhaColuna(&S[0][0]) == 0) && (subMatrizes(&S[0][0]) == 0)){
        printf("\nEsta eh uma solucao de Sudoku X 12\n");
    }

    return 0;
}

//leitura da matriz
void leMatriz(int **matriz){

    int l, c;
    FILE *sudoku = fopen("sudokux.txt", "r");
    
    if(sudoku == NULL)
        printf("Erro na abertura do arquivo\n\n");
    else{
        for(l = 0; l < TAMANHO; l++)
            for(c = 0; c < TAMANHO; c++)
                fscanf(sudoku, "%d", &matriz[l][c]);
        fclose(sudoku);
    }
}

//printa matriz
void escreveMatriz(int **matriz){
    
    int l, c;
    
    for(l = 0; l < TAMANHO; l++){
        for(c = 0; c < TAMANHO; c++)
            printf("%d ", matriz[l][c]);
        printf("\n");
    }
}

//verificacao de repeticoes nas diagonais
int diagonais(int *s){
    int i, j, m = 11, n;

    for(i = 0; i < TAMANHO; i++){
        n = 11;
        for(j = 0; j < TAMANHO; j++){
            if((i != j) && (*(s+TAMANHO*i+i) == *(s+TAMANHO*j+j))){
                printf("\nEsta nao eh uma solucao de Sudoku X\n");
                return 1;
            }
            if((i != j) && (m != n) && (*(s+TAMANHO*i+m) == *(s+TAMANHO*j+n))){
                printf("\nEsta nao eh uma solucao de Sudoku X\n");
                return 1;
            }
            n--;
        }
        m--;
    }
    return 0;
}

//verificacao de repeticao nas linhas e colunas
int linhaColuna(int *m){
    int l, c, i;

    for(l = 0; l < TAMANHO; l++){
        for(c = 0; c < TAMANHO; c++){
            for(i = 0; i < TAMANHO; i++){
                //identificando repeticao na mesma coluna
                if((c != i) && (*(m+TAMANHO*l+c) == *(m+TAMANHO*l+i))){
                    printf("\nEsta nao eh uma solucao de Sudoku X\n");
                    return 1;
                }
                //identificando repeticao na mesma linha
                if((l != i) && (*(m+TAMANHO*l+c) == *(m+TAMANHO*i+c))){
                    printf("\nEsta nao eh uma solucao de Sudoku X\n");
                    return 1;
                }
            }
        }
    }
    return 0;
}

//verificacao de repeticao nas submatrizes
int subMatrizes(int *p){
    int l, c, m, n, sequencia[13], i;

    for(l = 0; l <= 9; l += 3){
        for(c = 0; c <= 8; c += 4){

            for(i = 0; i < 13; i++)
                sequencia[i] = 0;

            for(m = l; m <= l+2; m++){
                for(n = c; n <= c+3; n++){
                    i = *(p+TAMANHO*m+n);
                    sequencia[i] = sequencia[i] + 1;

                    if(sequencia[i] == 2){
                        printf("\nEsta nao eh uma solucao de Sudoku X\n");
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
