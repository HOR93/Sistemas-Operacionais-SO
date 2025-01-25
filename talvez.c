#include <stdio.h>

#define QUANTUM 2 // valor fixo do quantum estabelecido

int main(){
  int Data[100], duracao[100], tempo[100], N_Processos;  // variaveis responsaveis pela inicialização do simulador
  int Fila_Processos[100], proximo_a_executar = 0, proximo_a_adicionar = 0;// Fila de processos prontos e variaveis dos futuros processos
  int tmax = 0, t = 0, tarefa_em_execucao = -1, tempo_em_execucao = 0, contador_trocas = 0; // variaveis do loop principal
  int Tempo_TOTAL= t, Tempo_TOTAL_retorno = 0; // variaveis com relação as medias.

  // Entrada do simulador
  do {
    printf("Quantos Processos ? "); // entrada com condição se não tiver um valor aceitavel
    scanf("%d", &N_Processos);
    if (N_Processos <=0){
      printf("Digite um valora aceitavel\n");
    }
  }while (N_Processos <= 0);

  for (int i=0; i<N_Processos; i++){
    printf("Data de criacao e Duracao: ", i+1); // cada processo recebe sua data de criação e duração
    scanf("%d %d", &Data[i], &duracao[i]);
  }

  //inicialização do simulador
  for (int i=0; i<N_Processos; i++){ // array tempo vai receber a duração do processo e finaliza calculando o tempo maximo
    tempo[i] = duracao[i];
    if (Data[i] + duracao[i] > tmax){
      tmax = Data[i] + duracao[i];
    }
  }

  //cabecalho
  printf("\nCabeçalho de execucao"); // cabeçalho do simulador que preenche pra cada Processo do usuario
  printf("\ntempo   ");           // para ficar no formato desejado no trabalho
  switch (N_Processos) {
    case 0:
        printf("(Nenhum processo)\n");
        break;
    default:
        for (int i = 0; i< N_Processos; i++) {
            printf("p%d  ", i + 1);
        }
        printf("\n");
        break;
  }

  //while determina se enquanto ainda tem um processo com tempo, rodando ou na fila
  while (t < tmax || tarefa_em_execucao != -1 || proximo_a_executar < proximo_a_adicionar){
    if(tarefa_em_execucao != -1){ // se ainda tem processo no momento
      if (tempo[tarefa_em_execucao] == 0){ // se o processo terminou
        tarefa_em_execucao = -1; // libera o simulador para novo processo
        tempo_em_execucao = 0; // zera o tempo dele
      } else if (tempo_em_execucao == QUANTUM) { // se o processo atingiu o limite do quantum
        Fila_Processos[proximo_a_adicionar++] = tarefa_em_execucao;
        tarefa_em_execucao = -1; // libera o simulador para novo processo
        tempo_em_execucao = 0;  // zera o tempo dele
        contador_trocas++; // incrementa para um novo processo
      }
    }

    for (int i = 0; i<N_Processos; i++){ // aqui ele verifica se tem algum novo processo sendo criado no tempo atual
      if (Data[i]==t){ // se a data de criação do processo bate com o t atual
        Fila_Processos[proximo_a_adicionar++] = i; // então coloca ele na fila
      }
    }

    if (tarefa_em_execucao == -1 && proximo_a_executar < proximo_a_adicionar){ // condição pra ver se tem algum processo ou se ainda tem algum na fila  
      tarefa_em_execucao = Fila_Processos[proximo_a_executar++]; // tira o proximo da fila e bota ele como atual
      tempo_em_execucao = 0;  // zero o tempo do novo processo
    }

    //Imprimir o estado dos processos no simulador
    printf("%2d- %2d  ", t, t + 1); // espaçamento para ficar adequado no terminal
    for (int i = 0; i< N_Processos; i++) {
        int estado_atual;


        if ( tempo[i] == 0 && Data[i] <= t) {
            estado_atual = 0; // se a processo terminou
        } else if (Data[i] > t) {
            estado_atual = 1; // se o processo ainda não entrou como atual
        } else if (i == tarefa_em_execucao) {
            estado_atual = 2; // se ainda ta acontecendo
        } else {
            estado_atual = 3; // se ainda ta na fila
        }

        switch (estado_atual) {
            case 0:
                printf("    "); // Tarefa já terminou
                break;
            case 1:
                printf("--  "); // Tarefa ainda não chegou
                break;
            case 2:
                printf("##  "); // Tarefa está rodando
                break;
            default:
                printf("    ");
                break;
        }
    }
    printf("\n");

    t++; 
    if (tarefa_em_execucao != -1) { // se tiver um processo rodando..
        tempo[tarefa_em_execucao]--; // decremento o tempo que resta do processo atual que esta em execução
        tempo_em_execucao++; // aqui ele finaliza incrementando o processo que ta rodando no quantum
    }
  }

  for (int i = 0; i< N_Processos; i++) {
      Tempo_TOTAL_retorno += Tempo_TOTAL - Data[i]; // soma o tempo total de retorno dos processos - tempo de criação de cada processo
  }

    int Media_Retorno= Tempo_TOTAL_retorno / N_Processos;

    printf("\nTempo medio de retorno no simulador: %d\n", Media_Retorno);
    printf("Numero total de trocas: %d\n", contador_trocas);  

    return 0;
}
