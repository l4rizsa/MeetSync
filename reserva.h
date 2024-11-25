/**
 * MeetSync - Sistema para reserva de salas de reunião
 *
 * Este programa gerencia reservas de salas, permitindo que os usuários registrem,
 * visualizem e cancelem reservas. O usuário também pode visualizar os detalhes das diferentes capacidades e
 * configurações de cada sala. Além disso, o sistema verifica conflitos
 * de horários entre reservas e valida datas e horários fornecidos.
 *
 * Funções:
 * Inicializar, registrar reserva, mostrar reserva, listar reservas, cancelar reserva, validar data, validar horário de
 * início, validar horário de término, checar conflito inicial, checar conflito final e visualizar salas.
 *
 * @since nov 2024
 * @author Larissa
 */

#define MAX 100

typedef struct Reserva{
    int id;
    char nome[51];
    int dia, mes, ano;
    int hi, mi;
    int hf, mf;
}reserva;

extern reserva;

typedef reserva *p_reserva;

extern p_reserva v[MAX];

/**
 * Função inicializar - Configura os dados iniciais do sistema de reservas
 */
void inicializar();

/**
 * Função registrarReserva - Registra uma nova reserva no sistema
 */
void registrarReserva();

/**
 * Função mostrarReserva - Exibe uma reserva específica
 * @param pos posição da reserva na lista
 */
void mostrarReserva(int pos);

/**
 * Função listarReservas - Lista todas as reservas registradas no sistema
 */
void listarReservas();

/**
 * Função cancelarReserva - Cancela uma reserva com base na posição informada
 * @param pos posição da reserva a ser cancelada
 * @param t ponteiro para o total de reservas registradas, atualizado após o cancelamento
 */
void cancelarReserva(int pos, int *t);

/**
 * Função validarData - Verifica se uma data informada é válida
 * @param d dia da data
 * @param m mês da data
 * @param a ano da data
 * @return 1 se a data for válida, 0 caso contrário
 */
int validarData(int d, int m, int a);

/**
 * Função validarHoraInicio - Verifica se o horário de início é válido
 * @param hi hora inicial
 * @param mi minutos iniciais
 * @return 1 se o horário for válido, 0 caso contrário
 */
int validarHoraInicio(int hi, int mi);

/**
 * Função validarHoraTermino - Verifica se o horário de término é válido em relação ao horário de início
 * @param hf hora final
 * @param mf minutos finais
 * @param hi hora inicial
 * @param mi minutos iniciais
 * @return 1 se o horário for válido, 0 caso contrário
 */
int validarHoraTermino(int hf, int mf, int hi, int mi);

/**
 * Função checarConflitoI - Verifica se o horário de início de uma reserva não conflita com reservas existentes
 * @param hi hora inicial
 * @param mi minutos iniciais
 * @param pos posição da reserva atual
 * @param t total de reservas registradas
 * @return 1 se não houver conflito, 0 caso contrário
 */
int checarConflitoI(int hi, int mi, int pos, int t);

/**
 * Função checarConflitoF - Verifica se o horário de término de uma reserva não conflita com reservas existentes
 * @param hf hora final
 * @param mf minutos finais
 * @param pos posição da reserva atual
 * @param t total de reservas registradas
 * @param hi hora inicial
 * @param mi minutos iniciais
 * @return 1 se não houver conflito, 0 caso contrário
 */
int checarConflitoF(int hf, int mf, int pos, int t, int hi, int mi);

/**
 * Função visualizarSalas - Exibe as informações detalhadas sobre as salas disponíveis
 */
void visualizarSalas();