#include <stdio.h>
#include "reserva.h"
#include <malloc.h>

p_reserva v[MAX];
extern int total;

int main(void) {
    inicializar();
    /**FILE *p_arq = fopen("D:\\Linguagem de Programacao\\MeetSync\\salas.txt", "r");
    if (p_arq == NULL) {
        perror("Erro ao abrir arquivo para leitura");
        return 1;
    }

    v[total] = (p_reserva) malloc(sizeof(struct Reserva));
    if (v[total] == NULL) {
        perror("Erro ao alocar memória");
        exit(1);
    }

    fscanf(p_arq, "%d %71s %d/%d/%d %d:%d %d:%d\n",
                   &v[total]->id, v[total]->nome,
                   &v[total]->dia, &v[total]->mes, &v[total]->ano,
                   &v[total]->hi, &v[total]->mi,
                   &v[total]->hf, &v[total]->mf);*/


    //

    int posicao = 0;
    int *p_total = &total;

    int pd = 0, opcao = 0, sn = 0;

    do {

        printf("\n    0 - VISUALIZAR SALAS\n");
        printf("    1 - REGISTRAR RESERVA\n");
        printf("    2 - LISTAR RESERVAS\n");
        printf("    3 - MOSTRAR RESERVA ESPECIFICA\n");
        printf("    4 - CANCELAR RESERVA\n");
        printf("    9 - SAIR\n");
        printf("        > O que deseja fazer?\n\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                printf("            * Tempo Minimo Para Reserva: 20 Minutos\n");
                printf("                      [ HORARIO DE FUNCIONAMENTO: 6:00 - 23:00 ]\n\n");
                printf("               ID      LOCAL       CAPACIDADE        DETALHES\n");
                printf("           +---------------------------------------------------------------+  \n");
                printf("               01      Bloco A     40 Pessoas        Mesas Redondas\n");
                printf("               02      Bloco A     40 Pessoas        Mesa Central\n");
                printf("               03      Bloco A     20 Pessoas        Mesa em ""U""\n");
                printf("               04      Bloco A     20 Pessoas        Mesa em ""T""\n");
                printf("               05      Bloco A     20 Pessoas        Auditorio\n");
                printf("               06      Bloco A     20 Pessoas        Espaco Colaborativo\n");
                printf("               07      Bloco A     20 Pessoas        Estilo Lounge\n");
                printf("               08      Bloco A     20 Pessoas        Estilo Sala de Aula\n");

                printf("\n");
                break;
            case 1:
                registrarReserva();

                break;
            case 2:
                listarReservas();
                break;
            case 3:
                printf("  > Numero da reserva: ");
                scanf("%d", &pd);
                mostrarReserva(pd);
                break;
            case 4:
                printf("  > Numero da reserva a ser cancelada: ");
                scanf("%d", &pd);
                cancelarReserva(pd, p_total);
                break;
            case 9:
                printf("    Fim do Programa");
                break;
            default:
                printf("    /!\\ Opcao Invalida!\n");
                break;
        }

    } while (opcao != 9);

    //fclose(p_arq);

    return 0;
}


