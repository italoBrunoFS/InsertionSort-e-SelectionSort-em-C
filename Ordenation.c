#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void InsertionSort(int* arr, int tamanho){
    int pivo = 0;
    int j = 0;
    for(int i = 1 ; i <= tamanho - 1; i++){
        pivo = arr[i];
        j = i - 1;
        while(j >= 0 && arr[j] > pivo){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = pivo;
    }
}

void SelectionSort(int* arr, int t){
    for(int i = 0; i < t - 2; i++){
        int i_min = i;
        for(int j = i + 1; j <= t - 1; j++){
            if(arr[j] < arr[i_min]){
                i_min = j;
            }
        }
        if(arr[i] != arr[i_min]){
            int temp = arr[i];
            arr[i] = arr[i_min];
            arr[i_min] = temp;
        }
    }
}


int main(int argc, char* argv[]){
    if(argc < 2){
        perror("Nome do arquivo nao foi digitado!\n");
        exit(EXIT_FAILURE);
    }

    const char* nome_arquivo = argv[1];
    clock_t inicio, fim;
    double tempo_exec1, tempo_exec2;

    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo\n");
        exit(EXIT_FAILURE);
    }

    int contador = 0, temp;

    while(fscanf(arquivo, "%d", &temp) == 1){
        contador++;
    }

   int* array1 = (int*) malloc(contador * sizeof(int));
   int* array2 = (int*) malloc(contador * sizeof(int));
   if(!array1 || !array2){
    perror("Erro ao alocar memória\n");
    fclose(arquivo);
    exit(EXIT_FAILURE);
   }

   rewind(arquivo);
   int i = 0;

   while(fscanf(arquivo, "%d", &array1[i]) == 1){
       i++;
   }

   rewind(arquivo);
   i = 0;

   while(fscanf(arquivo, "%d", &array2[i]) == 1){
       i++;
   }

   fclose(arquivo);

   inicio = clock();
   InsertionSort(array1, contador);
   fim = clock();
   tempo_exec1 = (double)(fim - inicio)/CLOCKS_PER_SEC;

   inicio = clock();
   SelectionSort(array2, contador);
   fim = clock();
   tempo_exec2 = (double)(fim - inicio)/CLOCKS_PER_SEC;

   FILE *arquivo_ordenado[2]; 
   arquivo_ordenado[0] = fopen("Arquivo_InsertionSort.txt", "w");
   if (!arquivo_ordenado[0]) {
        perror("Erro ao abrir o arquivo para escrita\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < contador; i++){
        fprintf(arquivo_ordenado[0], "%d", array1[i]);
        fprintf(arquivo_ordenado[0], "\n");
    }

   fclose(arquivo_ordenado[0]);

   arquivo_ordenado[1] = fopen("Arquivo_SelectionSort.txt", "w");
   if (!arquivo_ordenado[1]) {
        perror("Erro ao abrir o arquivo para escrita\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < contador; i++){
        fprintf(arquivo_ordenado[1], "%d", array2[i]);
        fprintf(arquivo_ordenado[1], "\n");
    }

   fclose(arquivo_ordenado[1]);

   printf("Tempo de execucao:\n");
   printf("InsertionSort: %.5lf segundos\n", tempo_exec1);
   printf("SelectionSort: %.5lf segundos\n", tempo_exec2);
   if(tempo_exec1 < tempo_exec2){
    printf("O algoritmo InsertionSort foi mais rapido.\n");
   }else if(tempo_exec1 > tempo_exec2){
    printf("O algoritmo SelectionSort foi mais rapido. \n");
   }else{
    printf("Os dois levaram o mesmo tempo para executar.\n");
   }
   free(array1);
   free(array2);
}