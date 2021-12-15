#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client
  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.
  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
    int from_client = 0;

    mkfifo(WKP, 0644);

    from_client = open("mario", O_RDONLY);
    printf("[server] Opened WKP\n");
    char s[HANDSHAKE_BUFFER_SIZE];
    read(from_client, s, HANDSHAKE_BUFFER_SIZE);
    printf("[server] Received ACK: %s\n", s);
    remove(WKP);

    *to_client = open(s, O_WRONLY);
    write(*to_client, "hello", 5);
    char r[HANDSHAKE_BUFFER_SIZE];
    read(from_client, r, HANDSHAKE_BUFFER_SIZE);
    printf("[server] Received Message: %s\n", r);
    remove(ACK);
    printf("Removed pipes\n");
    return from_client;
}


/*=========================
  client_handshake
  args: int * to_server
  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.
  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
    int from_server = 0;
    
    mkfifo(ACK, 0644);
    *to_server = open(WKP, O_WRONLY);
    printf("[client] Connected to WKP\n");
    write(*to_server, ACK, HANDSHAKE_BUFFER_SIZE);
    from_server = open(ACK, O_RDONLY);
    char s[100];
    read(from_server, s, HANDSHAKE_BUFFER_SIZE);
    printf("[client] Message: %s\n", s);
    s[0]++;
    write(*to_server, s, HANDSHAKE_BUFFER_SIZE);
    //printf("Wrote again\n");

    return from_server;
}
