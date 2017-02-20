#Ta Hoang Hai Nam
#USTH BI6-110
#include <stdio.h>
#include <unistd.h>
int main() 
{
	printf("Main before fork()\n");
	int pid_1 = fork();

	if (pid_1 == 0) {
		printf("I am child after fork(), launching ps -ef\n");
		char *args[]= { "ps", "-ef" , NULL};
		execvp("ps", args);
		printf("Finished launching ps -ef\n");
	}

	else printf("I am parent after fork(), child is %d\n", pid_1);
	
	
	int pid_2 = fork();	
	if (pid_2 == 0) {
		printf("I am child after fork(), launching free -h\n");
		char *args[]= { "free", "-h" , NULL};
		execvp("free", args);
		printf("Finished launching free -h\n");
	}

	else printf("I am parent after fork(), child is %d\n", pid_2);
	return 0;
}
