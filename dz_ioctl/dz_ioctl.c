#include "chrdev/dz_chrdev.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>

int ioctl_set_msg(int loc_fd, char *loc_msg_ptr){

	int err_retn = 0;
	err_retn = ioctl(loc_fd, IOCTL_SET_MSG, loc_msg_ptr);

	if (err_retn < 0){
		printf("ioctl_set_msg err: %d\n\r", err_retn);
		exit(-1);
	}
}

int ioctl_get_msg(int loc_fd){

	int err_retn;
	char msg[IOCTL_MAX_SIZE];

	err_retn = ioctl(loc_fd, IOCTL_GET_MSG, msg);

	if (err_retn < 0) {
		printf("ioctl_get_msg err: %d\n\r", err_retn);
		exit(-1);
	}
	printf("%s\n\r", msg);
}

int menu_input(int* loc_cur_ptr){

	printf("Please enter:\n\r1 -> ioctl write\n\r2 ->  ioctl read\n\r3 -> exit\n\r");
	scanf("%1d", loc_cur_ptr);
	return 0;
}

int main(){

	int fd_device = 0;
	int in_menu = 1;
	int* cur_ptr = (int*)malloc(sizeof(int));
	char* msg_ptr = (char*)malloc(IOCTL_MAX_SIZE*sizeof(char));

	fd_device = open(DEVICE_FILE_NAME, 0);

	if (fd_device < 0){
		printf("Unable to open device file %s\n\r", DEVICE_FILE_NAME);
		exit(-1);
	}

	while(in_menu) {
		menu_input(cur_ptr);
		switch (*cur_ptr) {
			case 1:
				printf("Enter msg:\n\r-> ");
				scanf(" %127[^\n]s", msg_ptr);
				ioctl_set_msg(fd_device, msg_ptr);
				break;
			case 2:
				printf("Ur msg: --> ");
				ioctl_get_msg(fd_device);
				break;
			case 3:
				in_menu = 0;
				break;
			default:
				printf("Check cur_ptr condition, u in default branch...\n\r");
				break;
		}
	}
	close(fd_device);
}
