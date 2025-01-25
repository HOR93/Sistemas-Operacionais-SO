#include <stdio.h>

#define QUANTUM 2 // valor fixo do quantum estabelecido

int main() {
    int Data[100], duracao[100], tempo[100], N_Processos;  // variaveis responsaveis pela inicialização do simulador
    int Fila_Processos[100], Inicio_Fila = 0, Final_Fila = 0;// Fila de processos prontos e Ponteiros para controlar a fila
    int tmax = 0, t = 0, tarefa_rodando = -1, tempo_rodando = 0, contexto_trocas = 0;

    // 1. Entrada
    do {
        printf("Quantos processos? "); // entrada com condição se não tiver um valor aceitavel
        scanf("%d", &N_Processos);
        if (N_Processos <= 0) {
            printf("Digite um valora aceitavel\n");
        }
    } while (N_Processos <= 0);

    for (int i = 0; i < N_Processos; i++) {
        printf("Data de criacao e Duracao: ", i + 1); // cada processo recebe sua data de criação e duração
        scanf("%d %d", &Data[i], &duracao[i]);
    }

    // 2. Inicialização
    for (int i = 0; i < N_Processos; i++) { // array tempo vai receber a duração do processo e finaliza calculando o tempo maximo
        tempo[i] = duracao[i];
        if (Data[i] + duracao[i] > tmax) {
            tmax = Data[i] + duracao[i];
        }
    }

    // 3. Cabeçalho do Diagrama
    printf("Cabeçalho do Diagrama"); // cabeçalho do simulador que preenche pra cada Processo do usuario
    printf("\ntempo   ");           // para ficar no formato desejado no trabalho
    switch (N_Processos) {
        case 0:
            printf("(Nenhum processo)\n");
            break;
        default:
            for (int i = 0; i < N_Processos; i++) {
                printf("P%d  ", i + 1);
            }
            printf("\n");
            break;
    }

    // 4. while determina se enquanto ainda tem um processo com tempo, rodando ou na fila 
    while (t < tmax || tarefa_rodando != -1 || Inicio_Fila < Final_Fila) {
        if (tarefa_rodando != -1) { // se ainda tem processo no momento
            if (tempo[tarefa_rodando] == 0) { // se o processo terminou
                tarefa_rodando = -1; // libera o simulador para novo processo
                tempo_rodando = 0;   // zera o tempo dele          
            } else if (tempo_rodando == QUANTUM) { // se o processo atingiu o limite do quantum
                Fila_Processos[Final_Fila++] = tarefa_rodando;
                tarefa_rodando = -1; // libera o simulador para novo processo
                tempo_rodando = 0;  // zera o tempo dele
                contexto_trocas++;  // incrementa para um novo processo
            }
        }

        for (int i = 0; i < N_Processos; i++) { // aqui olha se tem algum novo processo sendo criado no tempo atual do simulador
            if (Data[i] == t) {  // se ele coincide com t
                Fila_Processos[Final_Fila++] = i; // enão coloca ele no final da fila
            }
        }

        if (tarefa_rodando == -1 && Inicio_Fila < Final_Fila) { // condição pra ver se tem algum processo ou se ainda tem algum na fila  
            tarefa_rodando = Fila_Processos[Inicio_Fila++]; // tira o proximo da fila e bota ele como atual
            tempo_rodando = 0; // zero o tempo do novo processo
        }

        // 5. Imprime o estado
        printf("%2d- %2d  ", t, t + 1);
        for (int i = 0; i < N_Processos; i++) {
            int estado;

            // Determina o estado do processo usando if-else
            if (tempo[i] == 0 && Data[i] <= t) {
                estado = 0; // se a processo terminou
            } else if (Data[i] > t) {
                estado = 1; // se o processo ainda não entrou como atual
            } else if (i == tarefa_rodando) {
                estado = 2; // se ainda ta acontecendo
            } else {
                estado = 3; // se ainda ta na fila
            }

            // Usa switch para imprimir o estado do processo
            switch (estado) {
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
                    printf("    "); // Tarefa está na fila
                    break;
            }
        }
        printf("\n");

        t++;
        if (tarefa_rodando != -1) { 
            tempo[tarefa_rodando]--; // decremento o tempo atual que resta do processo
            tempo_rodando++;
        }
    }
    //6 
    int tempoTotalExecucao = t; // Tempo total da simulação
    int tempoTotalRetorno = 0;

    for (int i = 0; i < N_Processos; i++) {
        tempoTotalRetorno += tempoTotalExecucao - Data[i];
    }

    // Cálculo do tempo médio de retorno usando inteiros
    int tempoMedioRetornoInteiro = tempoTotalRetorno / N_Processos;

    printf("\nTempo médio de retorno (aproximado): %d segundos\n", tempoMedioRetornoInteiro);
    printf("Número total de trocas de contexto: %d\n", contexto_trocas);

    return 0;
}

