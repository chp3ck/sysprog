#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include <unistd.h>
#include <wait.h>

int main( ) {
	int pipes[2];
	char buff[128];
	if(pipe(pipes) == 0){
		if(fork() == 0){
			close(pipes[0]);
			char* msg_1 = "child sends first message...\n\r";
			write(pipes[1], msg_1, strlen(msg_1) + 1);
			char* msg_2 = {"child sends second message...\n\r"};
			write(pipes[1], msg_2, strlen(msg_2) + 1);
		}
	}else{
		close(pipes[1]);
		read(pipes[0], buff, 128);
		printf("Parent receives message: %s", buff);
		read(pipes[0], buff, 128);
		printf("Parent receives 2nd message : %s", buff);
		wait(NULL);
	}
}
