#include "pipe_networking.h"


int main() {

	int to_server;
	int from_server;

	from_server = client_handshake( &to_server );

	char buffer[BUFFER_SIZE];
    while(fgets(buffer, sizeof(buffer), stdin)) {
		// printf("%s\n", buffer);
        write(to_server, buffer, sizeof(buffer));
        char s[BUFFER_SIZE];
        read(from_server, s, sizeof(s));
        
        printf("%s\n", s);
    }
}
