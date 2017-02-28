#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
	int which = PRIO_PROCESS;
	id_t pid;
	int priority;
	int ret;

	if (!(argv[1] && argv[2]))
	{
		printf("Correct input is - nice.exe <processId> <processPriority - from -15 to 15>\n");
		exit(EXIT_FAILURE);
	}

	pid = atoi(argv[1]);
        priority = atoi(argv[2]);

	if (priority > 15 || priority < -15)
	{
		printf("processPriority - from -15 to 15\n");
		exit(EXIT_FAILURE);
	}		

        printf("pid = %d priority = %d\n", pid, priority);
        ret = setpriority(which, pid, priority);
	
	if(ret==-1) 
	{
	    printf("%s\n", strerror(errno));
	}

	exit(EXIT_SUCCESS);
}
