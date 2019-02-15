#include "common.h"
#include "message.h"
#include "game.h"
#include "msgcodes.h"

#define DEFAULT_PORT 10900
#define SERVER_PORT 10910

int sock;
struct sockaddr_in servaddr;
p_message msg;
char *client_name = "BeLuckyDaf";

int main(int argc, char** argv) {
    if (argc < 2) return 1;

    // create a socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    printf("socket descriptor: %d\n", sock);

    // initialize address
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(DEFAULT_PORT);

    // bind socket to port
    bind(sock, (struct sockaddr*)&addr, sizeof(addr));

    // define server address
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    servaddr.sin_port = htons(SERVER_PORT);

    // connect to server
    int conn = connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if (conn == -1) error("could not connect to server", -1);

    // ignore all messages not related to verifying connection
    while((msg = receive_message(sock))->header.msgcode != SMSG_VERIFY_CONNECTION);
    printf("code: %d, size: %lu\n", msg->header.msgcode, msg->header.plsize);
    msg = create_message(BMSG_POSITIVE, 0, NULL);
    send_message(sock, msg);

    msg = create_message(CMSG_SET_NAME, strlen(client_name), client_name);
    send_message(sock, msg);

    msg = create_message(CMSG_REQUEST_GAME, 0, NULL);
    send_message(sock, msg);

    int connected = 1;
    while(connected) {
        connected = 0;
    }

    // clean up
    close(sock);

    return 0;
}
