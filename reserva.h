//
// Created by Larissa on 11/11/2024.
//

#define MAX 30

typedef struct Reserva{
    int id;
    char nome[71];
    int dia, mes, ano;
    int hi, mi;
    int hf, mf;
}reserva;

extern reserva;

typedef reserva *p_reserva;

extern p_reserva v[MAX];


void inicializar();


void registrarReserva();


void mostrarReserva(int pos);


void listarReservas();


void cancelarReserva(int pos, int *t);


int validarData(int d, int m, int a);


int validarHoraInicio(int hi, int mi);


int validarHoraTermino(int hf, int mf, int hi, int mi);


int checarConflitoI(int hi, int mi, int pos, int t);


int checarConflitoF(int hf, int mf, int pos, int t, int hi, int mi);

void carregarReservas();