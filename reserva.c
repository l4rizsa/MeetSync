#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "reserva.h"


int total = 0;

void inicializar(){
    printf("||||    ||||  ||||||||||  ||||||||||  ||||||||||  ||||||||||  ||      ||  ||      ||  ||||||||||\n");
    printf("|| ||  || ||  ||          ||              ||      ||            ||  ||    ||||    ||  ||\n");
    printf("||   ||   ||  ||||||||||  ||||||||||      ||      ||||||||||      ||      ||  ||  ||  ||\n");
    printf("||        ||  ||          ||              ||              ||      ||      ||    ||||  ||\n");
    printf("||        ||  ||||||||||  ||||||||||      ||      ||||||||||      ||      ||      ||  ||||||||||\n\n");
    for (int i = 0; i < MAX; ++i) {
        v[i] = NULL;
    }
    FILE *p_arq = fopen("D:\\Linguagem de Programacao\\MeetSync\\salas.txt", "r");
    if (p_arq == NULL) {
        printf("Erro ao abrir arquivo para leitura");
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
    printf("Registros no momento:  %d \n", total);
    fseek(p_arq, 0, SEEK_SET);
};

void registrarReserva(){
    char dados[200];
    int pos = total;
    v[pos] = (p_reserva) malloc(sizeof(struct Reserva));

    printf("        R E G I S T R A R   R E S E R V A\n\n");

    do {
        fflush(stdin);
        printf("  > ID da Sala:\n");
        scanf("%d", &v[pos]->id);

        /*if(v[pos]->id == -999){
            v[pos]->id = -1;
            v[pos]->nome[0] = '\0';
            v[pos]->dia = -1;
            v[pos]->mes = -1;
            v[pos]->ano = -1;
            v[pos]->hi = -1;
            v[pos]->mi = -1;
            v[pos]->hf = -1;
            v[pos]->mf = -1;
            printf("      (!) Reserva Cancelada!\n\n");
            return;
        }*/
    }while(v[pos]->id < 1);

    do {
        fflush(stdin);
        printf("  > Reservante:\n");
        scanf(" %[^\n]s", v[pos]->nome);

    }while(v[pos]->nome[0] == '\0');

    do {
        fflush(stdin);
        printf("  > Data(DD/MM/AAAA):\n");
        scanf("%d/%d/%d", &v[pos]->dia, &v[pos]->mes, &v[pos]->ano);

        if(validarData(v[pos]->dia, v[pos]->mes, v[pos]->ano) != 1){
            printf("      /!\\ Data Invalida! Tente Novamente\n");
        }

    }while(validarData(v[pos]->dia, v[pos]->mes, v[pos]->ano) == 0);

    do {
        fflush(stdin);
        printf("  > Horario de Inicio(HH:MM):\n");
        scanf("%d:%d", &v[pos]->hi, &v[pos]->mi);

        if (validarHoraInicio(v[pos]->hi, v[pos]->mi) != 1) {
            printf("      /!\\ Hora Invalida! Tente Novamente.\n\n");
        }

        if (checarConflitoI(v[pos]->hi, v[pos]->mi, pos, total-1) != 1) {
            printf("      /!\\ Hora Indisponivel! Tente Novamente.\n\n");
        }

    } while (validarHoraInicio(v[pos]->hi, v[pos]->mi) == 0
             || checarConflitoI(v[pos]->hi, v[pos]->mi, pos, total) == 0);

    do {
        fflush(stdin);
        printf("  > Horario de Termino(HH:MM):\n");
        scanf("%d:%d", &v[pos]->hf, &v[pos]->mf);
        fflush(stdin);

        if (validarHoraTermino(v[pos]->hf, v[pos]->mf, v[pos]->hi, v[pos]->mi) != 1) {
            printf("      /!\\ Hora Invalida! Tente Novamente.\n\n");
        }

        if (checarConflitoF(v[pos]->hf, v[pos]->mf,pos, total,v[pos]->hi, v[pos]->mi) != 1) {
            printf("      /!\\ Hora Indisponivel! Tente Novamente.\n\n");
        }

    } while(validarHoraTermino(v[pos]->hf, v[pos]->mf, v[pos]->hi, v[pos]->mi) == 0
            || checarConflitoF(v[pos]->hf, v[pos]->mf, pos, total, v[pos]->hi, v[pos]->mi) == 0);

    /*sprintf(dados, "%d %s %d/%d/%d %d:%d %d:%d", v[pos]->id, v[pos]->nome, v[pos]->dia,
            v[pos]->mes, v[pos]->ano, v[pos]->hi, v[pos]->mi, v[pos]->hf, v[pos]->mf);*/

    FILE *p_arq = fopen("D:\\Linguagem de Programacao\\MeetSync\\salas.txt", "a");
    if (p_arq == NULL) {
        printf("Erro ao abrir arquivo para escrita!\n");
        return;
    }

    fprintf(p_arq, "%d;%-70s;%d/%d/%d;%d:%d;%d:%d\n", v[pos]->id, v[pos]->nome, v[pos]->dia, v[pos]->mes,
            v[pos]->ano, v[pos]->hi, v[pos]->mi, v[pos]->hf, v[pos]->mf);

    fclose(p_arq);

    pos++;
    total = pos;
    printf("\n    +* Reserva Registrada com Sucesso! *+\n      - Numero da Reserva: %.3d -\n", pos);
};

void mostrarReserva(int pos){
    //  FILE *p_arq = fopen("C:\\TRAB\\NOVO\\salas.txt", "r");
    //  if (p_arq == NULL) {
    //      printf("Erro ao abrir arquivo para leitura");
    //      return;
    //  }
    //  if(pos == 0) fseek(p_arq, 0, SEEK_SET);

    //  fscanf(p_arq, "%d;%70s;%d/%d/%d;%d:%d;%d:%d\n", &v[pos]->id, v[pos]->nome, &v[pos]->dia, &v[pos]->mes,
    //         &v[pos]->ano, &v[pos]->hi, &v[pos]->mi, &v[pos]->hf, &v[pos]->mf);

    // fclose(p_arq);

    if(pos > total-1 || pos < 0){
        printf("\n      /!\\ Reserva Inexistente!\n\n");
    }else{

        printf("\n              RESERVA No. %.3d\n\n", pos);
        printf("ID DA SALA:         %d\n", v[pos]->id);
        printf("RESERVANTE:         %s\n", v[pos]->nome);
        printf("DATA:               %d/%d/%d\n", v[pos]->dia, v[pos]->mes, v[pos]->ano);
        printf("HORARIO DE INICIO:  %d:%.2d\n", v[pos]->hi, v[pos]->mi);
        printf("HORARIO DE TERMINO: %d:%.2d\n", v[pos]->hf, v[pos]->mf);
        printf("\n");
    }
};

void listarReservas(){
    printf("\n        R E S E R V A S\n\n");
    for (int i = 0; i < MAX; ++i) {
        if (v[i] == NULL) return;
        mostrarReserva(i);
    }
};

void cancelarReserva(int pos, int *t){
    *t = total;
    int sn = 0;
    if(pos < 0 || pos >= *t){
        printf("\n      /!\\ Reserva Inexistente!\n\n");
        return;
    }
    printf("\n    (?) Deseja cancelar a reserva numero %.3d?\n      > 1 - SIM | 0 - NAO\n", pos);
    scanf("%d", &sn);
    if(sn == 1) {
        v[pos] = NULL;


        FILE *p_arq = fopen("D:\\Linguagem de Programacao\\MeetSync\\salas.txt", "w");
        fseek(p_arq, 0, SEEK_SET);

        if (p_arq == NULL) {
            printf("Erro ao abrir arquivo para escrita!\n");
            return;
        }
        for (int i = 0; i < total; ++i) {
            if(v[i] == NULL) continue;
            fprintf(p_arq, "%d;%-70s;%d/%d/%d;%d:%d;%d:%d\n", v[i]->id, v[i]->nome, v[i]->dia, v[i]->mes,
                    v[i]->ano, v[i]->hi, v[i]->mi, v[i]->hf, v[i]->mf);


        }
        fclose(p_arq);
        total--;
        printf("\nReserva cancelada\n\n");
    } else {
        printf("\nReserva mantida\n\n");
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
        else{
            if(d > 0 && d <= 28) return 1;
        }
    }
    return 0;
};

int validarHoraInicio(int hi, int mi){
    if((hi >= 6 && hi <= 22) && (mi >= 0 && mi <= 59)) return 1;
    return 0;
};

int validarHoraTermino(int hf, int mf, int hi, int mi){
    if(!(hf >= 6 && hf <= 23) && (mf >= 0 && mf <= 59)) return 0;
    if(hf > hi) return 1;
    if(hf == hi){
        if((mf - mi) >= 20) return 1;
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

void salvar(char d){

}

void carregarReservas() {
    FILE *p_arq = fopen("D:\\Linguagem de Programacao\\MeetSync\\salas.txt", "r");
    if (p_arq == NULL) {
        perror("Erro ao abrir arquivo para leitura");
        return;
    }



    while (fscanf(p_arq, "%d %s %d/%d/%d %d:%d %d:%d\n",
                  &v[total]->id,
                  v[total]->nome,
                  &v[total]->dia, &v[total]->mes, &v[total]->ano,
                  &v[total]->hi, &v[total]->mi,
                  &v[total]->hf, &v[total]->mf) != EOF) {
        v[total] = (p_reserva) malloc(sizeof(struct Reserva));
        total++;
    }

    fclose(p_arq);
}


