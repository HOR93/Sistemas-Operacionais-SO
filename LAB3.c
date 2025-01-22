#include <stdlib.h>
#include <stdio.h>

int main() {
   int N_Processos;
   int Quantum = 2;
   int Data[5][2], Duracao[5][2];

   printf("Quantos processos ? ");
   scanf("%d", &N_Processos);

   for(int i=0; i<N_Processos; i++){
      printf("Data de criacao e Duracao em segundos: ");
      scanf("%d %d", &Data[i][0], &Duracao[i][0]);
      

   };

   return 0;
}
