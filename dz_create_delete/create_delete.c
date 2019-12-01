#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
	if (argc == 3){
		FILE *f;
		if(strcmp(argv[1],"-c") == 0){
			if(access(argv[2],F_OK) != -1){
				printf("File exists!!!\n\r");
			}else{
				f=fopen(argv[2],"a+");
				printf("Succesful. File %s was created\n\r",argv[2]);
				fclose(f);
			}
		}else if(strcmp(argv[1],"-d") == 0){
			if(remove(argv[2])){
				printf("File not exists!!!\n\r");
			}else{
				printf("Succesful. File %s was deleted\n\r",argv[2]);
			}
		}else{
			printf("Invalid input parameters!!!\n\r ");
		}
	}else{
		printf("Invalid number of input paremeters!!!Valid number 3, your number %d\n\r",argc);
	}
		return 0;
}
