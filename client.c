#include "headers.h"

int sock;
struct sockaddr_in servaddr;

void send_message(char* msg, size_t len) {
    sendto(sock, msg, len, 0, 
          (struct sockaddr*)&servaddr, sizeof(servaddr));
}

int main(int argc, char** argv) {
    if (argc < 3) return 1;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    printf("socket descriptor: %d\n", sock);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(atoi(argv[2]));

    bind(sock, (struct sockaddr*)&addr, sizeof(addr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    servaddr.sin_port = htons(10910);

    int servsock = connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr));

    close(sock);

    return 0;
}