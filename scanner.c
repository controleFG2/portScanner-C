#define _GNU_SOURCE
#include <stdio.h> // contém a função printf()
#include <sys/socket.h> // contém as funções socket() e connect()
#include <arpa/inet.h> // contém as funções de IP e portas, como htons()
#include <unistd.h> // contém a função close()
#include <string.h> // contém a função memset()
#include <stdlib.h> // contém a função atoi()
#include <netdb.h> // contém a função getaddrinfo()


int testar_porta(struct sockaddr_in *alvo, int porta) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    alvo->sin_port = htons(porta);

    return 0;
}

int main(int argc, char *argv[]) {
    int output;
    int meu_socket = socket(AF_INET, SOCK_STREAM, 0); // crio um socket de rede
    int i;
    int status;
    char * ip = argv[1];
    int porta = atoi(argv[2]);

    struct addrinfo hints; // define hints para a função getaddrinfo()
    struct addrinfo *resultado;

    memset(&hints, 0, sizeof(hints)); // limpa toda a memoria da sockaddr_in

    // setar parâmetros pra hints
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(ip, NULL, &hints, &resultado); // faz a busca de dns. status é o status da busca, o resultado vai estar em resustado no formato de uma lista encadeada

    struct sockaddr_in *alvo = (struct sockaddr_in *) resultado->ai_addr; // typecast para o campo 
    alvo->sin_port = htons(porta);

    printf("%d\n", status);

    output = connect(meu_socket, resultado->ai_addr, resultado->ai_addrlen);
    
    if (output == 0) {
        printf("a porta está aberta: %d\n", output);
    }

    else {
        printf("a porta está fechada: %d\n", output);
    }

    printf("argc: %d\n", argc);
    for (i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    close(meu_socket);
    freeaddrinfo(resultado);

    return 0;
}