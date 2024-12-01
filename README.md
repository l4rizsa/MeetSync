# Sistema de Reserva de Salas - MeetSync

  Este programa é um sistema para gerenciar reservas de salas, incluindo registro, visualização, listagem e cancelamento de reservas. Também valida horários e evita conflitos entre reservas.


## Funcionalidades

 - Exibir as salas disponíveis e suas características.
 - Registrar reservas com validação de datas e horários.
 - Listar todas as reservas feitas.
 - Visualizar detalhes de uma reserva específica.
 - Cancelar reservas existentes.


## Como Usar

1. Compile o programa utilizando um compilador C (CLion, por exemplo).
2. Execute o arquivo gerado e siga as instruções do menu.
3. Insira os dados necessários (id, nome, data, horários) conforme solicitado pelo programa.


## Estrutura do Código

### Funções Principais:
- inicializar(): Inicia sistema.
- registrarReserva(): Registra uma nova reserva.
- listarReservas(): Exibe todas as reservas registradas.
- mostrarReserva(): Exibe uma reserva específica.
- cancelarReserva(): Remove uma reserva específica.
- visualizarSalas(): Lista as salas disponíveis.

O código também inclui funções internas responsáveis por validações, como verificar se a data e os horários são válidos ou se existem conflitos entre reservas.

NOTA: Para mais detalhes sobre os parâmetros e a implementação de cada função, consulte os comentários diretamente no código.
