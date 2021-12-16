#include "pipe_networking.h"


int main() {

	int to_client;
	int from_client;

	while(1) {
		from_client = server_setup( &to_client );
		
		int f;
		f = fork();

		if(f) {
			//server
		} else {
			//subserver
			to_client = server_connect( from_client );
			char s[BUFFER_SIZE];
			int r = 0;
			while(r = read(from_client, s, sizeof(s))) {
				// printf("%d\n", r);
				// printf("%s\n", s);
				s[strlen(s)-1] = '\0';
				strcat(s, "<3");
				s[strlen(s)] = '\0';
				//printf("%s\n", s);
				write(to_client, s, strlen(s)+1);
				for(int i = 0; i < BUFFER_SIZE; i++) s[i] = '\0';
			}
		}
	}
}
