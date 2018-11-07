#include "common.h"
#include "message.h"

int sock;
struct sockaddr_in servaddr;

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
    if (servsock == -1) error("could not connect to server", -1);

    p_message_header msg = receive_header(servsock);
    printf("code: %d, size: %lu\n", msg->msgcode, msg->plsize);

    close(sock);

    return 0;
}
