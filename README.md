# INF1370 - Servidor em C

Este repositório contém a implementação de um servidor em C, projetado para atender múltiplos clientes simultaneamente através de threads. O servidor pode ser executado em segundo plano (background) e configurado via linha de comando, permitindo a definição de parâmetros como porta, log e diretório raiz.  

## Funcionalidades
- Suporte a múltiplos clientes com threads.
- Execução em background.
- Configuração flexível via argumentos de linha de comando.
- Registro de logs e estatísticas.

## Estrutura do Projeto
O projeto inclui arquivos para gerenciamento do servidor, manipulação de conexões e definição de variáveis globais.

## Ferramentas Utilizadas
- **Threads** para concorrência no atendimento a clientes.
- **Sockets** para comunicação entre cliente e servidor.
- **Semáforos** para controle de acesso a recursos compartilhados.
- **Manipulação de processos** para execução em background.
- **Registro de logs e estatísticas** para monitoramento do servidor.
