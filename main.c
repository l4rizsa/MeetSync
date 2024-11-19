#include <stdio.h>
#include "reserva.h"
#include <malloc.h>

p_reserva v[MAX];
extern int total;

int main(void) {
    inicializar();

    int posicao = 0;
    int *p_total = &total;

    int pd = 0, opcao = 0, sn = 0;

    do {
        printf("\n\n                   _____________________________________________________________________________________________________");
        printf("\n                                                   +-----------------------------------+\n");
        printf("                                                   |   0 - VISUALIZAR SALAS            |\n");
        printf("                                                   |   1 - REGISTRAR RESERVA           |\n");
        printf("                                                   |   2 - LISTAR RESERVAS             |\n");
        printf("                                                   |   3 - MOSTRAR RESERVA ESPECIFICA  |\n");
        printf("                                                   |   4 - CANCELAR RESERVA            |\n");
        printf("                                                   |   9 - SAIR                        |\n");
        printf("                                                   +-----------------------------------+\n");
        printf("                                                   |   > O que deseja fazer?           |\n");
        printf("                                                   +-----------------------------------+\n\n");
        printf("                   _____________________________________________________________________________________________________");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                visualizarSalas();
                break;
            case 1:
                registrarReserva();
                break;
            case 2:
                listarReservas();
                break;
            case 3:
                printf("                                                          > Numero da reserva: ");
                scanf("%d", &pd);
                if(pd < 0 || pd > total-1){
                    printf("\n                                                       +--------------------------+\n");
                    printf("                                                       | (!) Reserva Inexistente! |\n");
                    printf("                                                       +--------------------------+\n");
                } else mostrarReserva(pd);
                break;
            case 4:
                printf("                                                    > Numero da reserva a ser cancelada: ");
                scanf("%d", &pd);
                cancelarReserva(pd, p_total);
                break;
            case 9:
                printf("\n                                                               +-----------+\n");
                printf("                                                               | SAINDO... |\n");
                printf("                                                               +-----------+\n");
                break;
            default:
                printf("\n                                                         +---------------------+\n");
                printf("                                                         | (!) Opcao Invalida! |\n");
                printf("                                                         +---------------------+\n");
                break;
        }

    } while (opcao != 9);

    return 0;
}


