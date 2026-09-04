#define _GNU_SOURCE
#include <stdio.h> // contém a função printf()
#include <sys/socket.h> // contém as funções socket() e connect()
#include <arpa/inet.h> // contém as funções de IP e portas, como htons()
#include <unistd.h> // contém as funções close() e getopt()
#include <string.h> // contém as funções memset() e strtok()
#include <stdlib.h> // contém a função atoi()
#include <netdb.h> // contém a função getaddrinfo()

#define MAX_PORTAS 100


int testar_porta(struct sockaddr_in *alvo, int porta) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    alvo->sin_port = htons(porta);

    int resultado = connect(sock, (struct sockaddr *) alvo, sizeof(struct sockaddr_in));

    close(sock);

    return resultado;
}


int resolve_dns(char *dominio, struct addrinfo **resultado) {
    struct addrinfo hints; // define hints para a função getaddrinfo()

    memset(&hints, 0, sizeof(hints)); // limpa toda a memoria da sockaddr_in

    // setar parâmetros pra hints
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    return getaddrinfo(dominio, NULL, &hints, resultado); // faz a busca de dns. status é o status da busca, o resultado vai estar em resustado no formato de uma lista encadeada
}


int main(int argc, char *argv[]) {

//---------------VARIÁVEIS----------------//
    int output;
    int i;
    int status;
    int opcao;
    int qtd_portas = 0;
    int mode = 0;
    int portas_especificas[MAX_PORTAS];
    unsigned int porta_inicial = 1;
    unsigned int porta_final = 1024;

    char *ip;
    char *pedaco;

    struct addrinfo *resultado;
    struct sockaddr_in *alvo;

//----------------------------------------//
    
    while ((opcao = getopt(argc, argv, "u:p:r:a")) != -1) {
        if (opcao == '?') {
        // Se o usuário digitou uma flag que não existe (ex: -x)
            printf("Uso: %s <-u alvo> [-p porta] [-r ini-fim] [-a]\n", argv[0]);

            return 1;
        }

        switch (opcao) {
            case 'u':
                ip = optarg;

                break;

            case 'a':
                porta_inicial = 1;
                porta_final = 65535;

                mode = 0;

                break;

            case 'r':
                sscanf(optarg, "%d-%d", &porta_inicial, &porta_final);

                mode = 0;

                break;

            case 'p':
                pedaco = strtok(optarg, ",");

                while (pedaco != NULL) {
                    if (qtd_portas > MAX_PORTAS) {
                        printf("Número limite de portas excedido");

                        break;
                    }

                    portas_especificas[qtd_portas] = atoi(pedaco);

                    qtd_portas++;

                    pedaco = strtok(NULL, ",");
                }

                mode = 1;

                break;
            
        }
    }
    resolve_dns(ip, &resultado);

    alvo = (struct sockaddr_in *) resultado->ai_addr; // typecast para o campo 

    printf("-----------------------------\n");
    printf("| %-9s| %-15s|\n", "PORTA", "ESTADO");
    printf("-----------------------------\n");

    if (mode == 0) {
        for (porta_inicial; porta_inicial < porta_final; porta_inicial++) {
            output = testar_porta(alvo, porta_inicial);

            if (output == 0) {
                printf("|%9d | %14s |\n", porta_inicial, "ABERTA");
            }
        }
    }

    else if (mode == 1) {
        for (i = 0; i < qtd_portas; i++) {
            output = testar_porta(alvo, portas_especificas[i]);

            if (output == 0) {
                printf("|%9d | %14s |\n", portas_especificas[i], "ABERTA");
            }
        }
    }

    printf("-----------------------------\n");

    freeaddrinfo(resultado);

    return 0;
}