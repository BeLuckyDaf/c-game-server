#include "headers.h"

int sock;
struct sockaddr_in servaddr;

void send_message(char* msg, size_t len) {
    sendto(sock, msg, len, 0, 
          (struct sockaddr*)&servaddr, sizeof(servaddr));
}

int main(int argc, char** argv) {
    if (argc < 2) return 1;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    printf("socket descriptor: %d\n", sock);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(atoi(argv[1]));

    bind(sock, (struct sockaddr*)&addr, sizeof(addr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(10900);

    char msg[100];

    sleep(3);

    struct timespec tm;
    tm.tv_sec = 0;
    tm.tv_nsec = 100000L;

    for (int i = 0; i < 10000; i++) {
        sprintf(msg, "%s ~> %d", argv[1], i);
        send_message(msg, sizeof(msg));
        //nanosleep(&tm, NULL);
    }

    close(sock);

    return 0;
}