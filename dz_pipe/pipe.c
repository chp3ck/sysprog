#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BYTES_NUMBER 128

int dataInput(char* dataPtr){
        printf("Input data:\n\r>>");
        scanf(" %127[^\n]s", dataPtr);
        return 0;
}

int main() {
	char* dataParentPtr=malloc(BYTES_NUMBER*sizeof(char));
	dataInput(dataParentPtr);
	char* dataBufPtr=malloc(BYTES_NUMBER*sizeof(char));
	int  p1[2], p2[2];
	pipe(p1);
	pipe(p2);
	if(fork() == 0){
		close(p1[1]);
		close(p2[0]);
		read(p1[0], dataBufPtr, BYTES_NUMBER*sizeof(dataBufPtr));
		write(p2[1], dataBufPtr, BYTES_NUMBER*sizeof(dataBufPtr));
		exit(0);
	}else{
		close(p1[0]);
		close(p2[1]);
		printf("Parent write to first pipe ---> %s\n\r", dataParentPtr);
		write(p1[1], dataParentPtr, BYTES_NUMBER*sizeof(dataParentPtr));
		read(p2[0], dataBufPtr, BYTES_NUMBER*sizeof(dataBufPtr));
		printf("Parent read from second pipe: <--- %s\n\r", dataBufPtr);
	}
	return 0;
}
