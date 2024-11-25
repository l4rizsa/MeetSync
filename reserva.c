#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "reserva.h"


int total = 0;

void inicializar(){
    printf("\n\n                     ||||    ||||  ||||||||||  ||||||||||  ||||||||||  ||||||||||  ||      ||  ||      ||  ||||||||||\n");
    printf("                     || ||  || ||  ||          ||              ||      ||            ||  ||    ||||    ||  ||\n");
    printf("                     ||   ||   ||  ||||||||||  ||||||||||      ||      ||||||||||      ||      ||  ||  ||  ||\n");
    printf("                     ||        ||  ||          ||              ||              ||      ||      ||    ||||  ||\n");
    printf("                     ||        ||  ||||||||||  ||||||||||      ||      ||||||||||      ||      ||      ||  ||||||||||");
    for (int i = 0; i < MAX; ++i) {
        v[i] = NULL;
    }
    FILE *p_arq = fopen("D:\\Linguagem de Programacao\\MeetSync\\salas.txt", "r");
    if (p_arq == NULL) {
        printf("\n                                        (!) Erro ao abrir arquivo para leitura!\n");
        return;
    }
    fseek(p_arq, 0, SEEK_SET);
    char ch;
    while ((ch = fgetc(p_arq)) != EOF) {
        if (ch == '\n') {
            total++;
        }
    }
    fseek(p_arq, 0, SEEK_SET);
    for (int pos = 0; pos < total; pos++) {
        v[pos] = malloc(sizeof(struct Reserva));
        fscanf(p_arq, "%d;%[^\n;];%d/%d/%d;%d:%d;%d:%d\n", &v[pos]->id, v[pos]->nome, &v[pos]->dia, &v[pos]->mes,
               &v[pos]->ano, &v[pos]->hi, &v[pos]->mi, &v[pos]->hf, &v[pos]->mf);
    }
    fseek(p_arq, 0, SEEK_SET);
};

void registrarReserva(){
    int pos = total;
    v[pos] = (p_reserva) malloc(sizeof(struct Reserva));

    printf("\n\n              R E G I S T R A R   R E S E R V A\n");
    printf("* Tempo Minimo Para Reserva: 20 Minutos\n\n");

    do {
        fflush(stdin);
        printf("  > ID da Sala:\n");
        scanf("%d", &v[pos]->id);
    }while(v[pos]->id < 1 || v[pos]->id >15);

    do {
        fflush(stdin);
        printf("\n  > Reservante:\n");
        scanf(" %[^\n]s", v[pos]->nome);

    }while(v[pos]->nome[0] == '\0');

    do {
        fflush(stdin);
        printf("\n  > Data(DD/MM/AAAA):\n");
        scanf("%d/%d/%d", &v[pos]->dia, &v[pos]->mes, &v[pos]->ano);

        if(validarData(v[pos]->dia, v[pos]->mes, v[pos]->ano) != 1){
            printf("    +-------------------------------------+\n");
            printf("    | (!) Data Invalida! Tente Novamente. |\n");
            printf("    +-------------------------------------+\n\n");
        }
    }while(validarData(v[pos]->dia, v[pos]->mes, v[pos]->ano) == 0);

    do {
        fflush(stdin);
        printf("\n  > Horario de Inicio(HH:MM):\n");
        scanf("%d:%d", &v[pos]->hi, &v[pos]->mi);

        if (validarHoraInicio(v[pos]->hi, v[pos]->mi) != 1) {
            printf("    +-------------------------------------+\n");
            printf("    | (!) Hora Invalida! Tente Novamente. |\n");
            printf("    +-------------------------------------+\n\n");
        }

        if (checarConflitoI(v[pos]->hi, v[pos]->mi, pos, total) != 1) {
            printf("        +---------------------------+\n");
            printf("        | (!) Horario Indisponivel! |\n");
            printf("        +---------------------------+\n\n");
        }

    } while (validarHoraInicio(v[pos]->hi, v[pos]->mi) == 0
             || checarConflitoI(v[pos]->hi, v[pos]->mi, pos, total) == 0);

    do {
        fflush(stdin);
        printf("\n  > Horario de Termino(HH:MM):\n");
        scanf("%d:%d", &v[pos]->hf, &v[pos]->mf);
        fflush(stdin);

        if (validarHoraTermino(v[pos]->hf, v[pos]->mf, v[pos]->hi, v[pos]->mi) != 1) {
            printf("    +-------------------------------------+\n");
            printf("    | (!) Data Invalida! Tente Novamente. |\n");
            printf("    +-------------------------------------+\n\n");
        }

        if (checarConflitoF(v[pos]->hf, v[pos]->mf,pos, total,v[pos]->hi, v[pos]->mi) != 1) {
            printf("        +---------------------------+\n");
            printf("        | (!) Horario Indisponivel! |\n");
            printf("        +---------------------------+\n\n");
        }

    } while(validarHoraTermino(v[pos]->hf, v[pos]->mf, v[pos]->hi, v[pos]->mi) == 0
            || checarConflitoF(v[pos]->hf, v[pos]->mf, pos, total, v[pos]->hi, v[pos]->mi) == 0);

    FILE *p_arq = fopen("D:\\Linguagem de Programacao\\MeetSync\\salas.txt", "a");
    if (p_arq == NULL) {
        printf("\n                                        (!) Erro ao abrir arquivo para escrita!\n");
        return;
    }

    fprintf(p_arq, "%d;%-50s;%d/%d/%d;%d:%d;%d:%d\n", v[pos]->id, v[pos]->nome, v[pos]->dia, v[pos]->mes,
            v[pos]->ano, v[pos]->hi, v[pos]->mi, v[pos]->hf, v[pos]->mf);

    fclose(p_arq);

    pos++;
    total = pos;

    printf("\n     +-------------------------------------+\n");
    printf("     | * Reserva Registrada com Sucesso! * |\n");
    printf("     +-------------------------------------+\n");
    printf("     |        Numero da Reserva: %.3d       |\n", pos-1);
    printf("     +-------------------------------------+");
};

void mostrarReserva(int pos){
    FILE *p_arq = fopen("D:\\Linguagem de Programacao\\MeetSync\\salas.txt", "r");
    if (p_arq == NULL) {
        printf("\n                                        (!) Erro ao abrir arquivo para leitura!\n");
        return;
    }
    fseek(p_arq, 0, SEEK_SET);
    for (int pos = 0; pos < total; pos++) {
        v[pos] = malloc(sizeof(struct Reserva));
        fscanf(p_arq, "%d;%[^\n;];%d/%d/%d;%d:%d;%d:%d\n", &v[pos]->id, v[pos]->nome, &v[pos]->dia, &v[pos]->mes,
               &v[pos]->ano, &v[pos]->hi, &v[pos]->mi, &v[pos]->hf, &v[pos]->mf);
    }

    if(pos > total-1 || pos < 0){
        return;
    }else{
        printf("\n                                           +--------------------------------------------------------+\n");
        printf("                                           |                    RESERVA No. %.3d                     |\n", pos);
        printf("                                           +---------------------+----------------------------------+\n");
        printf("                                           |  ID DA SALA:        |  %.2d                              |\n", v[pos]->id);
        printf("                                           |  RESERVANTE:        |  %.30s  |\n", v[pos]->nome);
        printf("                                           |  DATA:              |  %.2d/%.2d/%.4d                      |\n", v[pos]->dia, v[pos]->mes, v[pos]->ano);
        printf("                                           |  HORARIO DE INICIO  |  %.2d:%.2d                           |\n", v[pos]->hi, v[pos]->mi);
        printf("                                           |  HORARIO DE TERMINO |  %.2d:%.2d                           |\n", v[pos]->hf, v[pos]->mf);
        printf("                                           +---------------------+----------------------------------+\n\n");
    }
};

void listarReservas(){
    FILE *p_arq = fopen("D:\\Linguagem de Programacao\\MeetSync\\salas.txt", "r");
    if (p_arq == NULL) {
        printf("\n                                        (!) Erro ao abrir arquivo para leitura!\n");
        return;
    }
    fseek(p_arq, 0, SEEK_SET);
    for (int pos = 0; pos < total; pos++) {
        v[pos] = malloc(sizeof(struct Reserva));
        fscanf(p_arq, "%d;%[^\n;];%d/%d/%d;%d:%d;%d:%d\n", &v[pos]->id, v[pos]->nome, &v[pos]->dia, &v[pos]->mes,
               &v[pos]->ano, &v[pos]->hi, &v[pos]->mi, &v[pos]->hf, &v[pos]->mf);
    }

    printf("\n                                                                 R E S E R V A S\n\n");
    for (int i = 0; i < MAX; ++i) {
        if (v[i] == NULL) return;
        mostrarReserva(i);
    }
};

void cancelarReserva(int pos, int *t){
    *t = total;
    int sn = 0;
    if(pos < 0 || pos >= *t){
        printf("\n                                                       +--------------------------+\n");
        printf("                                                       | (!) Reserva Inexistente! |\n");
        printf("                                                       +--------------------------+\n");
        return;
    }
    printf("\n                                           +--------------------------------------------------------+\n");
    printf("                                           |                    RESERVA No. %.3d                     |\n", pos);
    printf("                                           +---------------------+----------------------------------+\n");
    printf("                                           |  ID DA SALA         |  %.2d                              |\n", v[pos]->id);
    printf("                                           |  RESERVANTE         |  %.30s  |\n", v[pos]->nome);
    printf("                                           |  DATA               |  %.2d/%.2d/%.4d                      |\n", v[pos]->dia, v[pos]->mes, v[pos]->ano);
    printf("                                           |  HORARIO DE INICIO  |  %.2d:%.2d                           |\n", v[pos]->hi, v[pos]->mi);
    printf("                                           |  HORARIO DE TERMINO |  %.2d:%.2d                           |\n", v[pos]->hf, v[pos]->mf);
    printf("                                           +---------------------+----------------------------------+\n\n");
    printf("                                               +-----------------------------------------------+\n");
    printf("                                               |  (?) Deseja cancelar a reserva numero %.3d?    |\n", pos);
    printf("                                               +-----------------------------------------------+\n");
    printf("                                               |          > 1 - SIM    |    > 0 - NAO          |\n");
    printf("                                               +-----------------------------------------------+\n");
    scanf("%d", &sn);
    if(sn == 1) {
        v[pos] = NULL;


        FILE *p_arq = fopen("D:\\Linguagem de Programacao\\MeetSync\\salas.txt", "w");
        fseek(p_arq, 0, SEEK_SET);

        if (p_arq == NULL) {
            printf("\n                                        (!) Erro ao abrir arquivo para escrita!\n");
            return;
        }
        for (int i = 0; i < total; ++i) {
            if(v[i] == NULL) continue;
            fprintf(p_arq, "%d;%-50s;%d/%d/%d;%d:%d;%d:%d\n", v[i]->id, v[i]->nome, v[i]->dia, v[i]->mes,
                    v[i]->ano, v[i]->hi, v[i]->mi, v[i]->hf, v[i]->mf);
        }
        fclose(p_arq);
        total--;

        printf("\n                                                          +------------------------+\n");
        printf("                                                          | (!) Reserva Cancelada! |\n");
        printf("                                                          +------------------------+\n");
    } else {
        printf("\n                                                           +----------------------+\n");
        printf("                                                           | (!) Reserva Mantida! |\n");
        printf("                                                           +----------------------+\n");
    }

};

int validarData(int d, int m, int a){
    if(a >= 2024 && a <= 2050){
        if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12){
            if(d > 0 && d <= 31){
                return 1;
            }
        }
        if(m == 4 || m == 6 || m == 9 ||m ==11){
            if(d > 0 && d <= 30){
                return 1;
            }
        }
        if(m == 2 && ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0))){
            if(d > 0 && d <= 29) return 1;
        }
        else if(m == 2){
            if(d > 0 && d <= 28) return 1;
        }
    }
    return 0;
};

int validarHoraInicio(int hi, int mi){
    if((hi >= 6 && hi <= 21) && (mi >= 0 && mi <= 59)) return 1;
    return 0;
};

int validarHoraTermino(int hf, int mf, int hi, int mi){
    if(!(hf >= 6 && hf <= 22) || !(mf >= 0 && mf <= 59)) return 0;
    if(hf > hi) return 1;
    if(hf == hi){
        if((mf - mi) >= 19) return 1;
    }
    return 0;
};

int checarConflitoI(int hi, int mi, int pos, int t){
    for (int i = 0; i < t; ++i) {
        if(i == pos) continue;
        if(v[pos]->id == v[i]->id) {
            if (v[pos]->dia == v[i]->dia && v[pos]->mes == v[i]->mes && v[pos]->ano == v[i]->ano) {
                if (((hi > v[i]->hi) || (hi == v[i]->hi && mi >= v[i]->mi)) &&
                    (hi < v[i]->hf) || (hi == v[i]->hf && mi < v[i]->mf)) return 0;

                if(hi == v[i]->hi){
                    if((v[i]->mi - mi) < 20) return 0;
                }

                if(hi == ((v[i]->hi) - 1)){
                    if((60 - mi + v[i]->mi) < 20) return 0;
                }
            }
        }
    }
    return 1;
};

int checarConflitoF(int hf, int mf, int pos, int t, int hi, int mi){
    for (int i = 0; i < t; ++i) {
        if(i == pos) continue;
        if(v[pos]->id == v[i]->id) {
            if (v[pos]->dia == v[i]->dia && v[pos]->mes == v[i]->mes && v[pos]->ano == v[i]->ano) {
                if (((hf < v[i]->hf) || (hf == v[i]->hf && mf <= v[i]->mf)) &&
                    ((hf > v[i]->hi) || (hf == v[i]->hi && mf > v[i]->mi))) return 0;

                if ((hi < v[i]->hi || (hi == v[i]->hi && mi <= v[i]->mi)) &&
                    (hf > v[i]->hf || (hf == v[i]->hf && mf >= v[i]->mf))) return 0;
            }
        }
    }
    return 1;
};

void visualizarSalas(){
    printf("\n                                      +---------------------------------------------------------------+\n");
    printf("                                      |          [ HORARIO DE FUNCIONAMENTO: 6:00 - 23:00 ]           |\n");
    printf("                                      +---------------------------------------------------------------+\n");
    printf("                                      |   ID      LOCAL       CAPACIDADE        DETALHES              |\n");
    printf("                                      +---------------------------------------------------------------+\n");
    printf("                                      |   01      Bloco A     25 Pessoas        Mesas Redondas        |\n");
    printf("                                      |   02      Bloco A     20 Pessoas        Mesa Central          |\n");
    printf("                                      |   03      Bloco A     30 Pessoas        Mesa em \"U\"           |\n");
    printf("                                      |   04      Bloco A     15 Pessoas        Mesa em \"T\"           |\n");
    printf("                                      |   05      Bloco A     30 Pessoas        Auditorio             |\n");
    printf("                                      |   06      Bloco B     15 Pessoas        Espaco Colaborativo   |\n");
    printf("                                      |   07      Bloco B     10 Pessoas        Estilo Lounge         |\n");
    printf("                                      |   08      Bloco B     40 Pessoas        Estilo Sala de Aula   |\n");
    printf("                                      |   09      Bloco B     45 Pessoas        Auditorio             |\n");
    printf("                                      |   10      Bloco C     25 Pessoas        Mesas Redondas        |\n");
    printf("                                      |   11      Bloco C     10 Pessoas        Sala Privativa        |\n");
    printf("                                      |   12      Bloco C     12 Pessoas        Mesa Central          |\n");
    printf("                                      |   13      Bloco D     20 Pessoas        Estilo Workshop       |\n");
    printf("                                      |   14      Bloco D     50 Pessoas        Auditorio             |\n");
    printf("                                      |   15      Bloco E     15 Pessoas        Espaco Criativo       |\n");
    printf("                                      +---------------------------------------------------------------+\n");
}


