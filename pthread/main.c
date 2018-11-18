#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <sys/prctl.h>

void* worker_fun(void *arg)
{
    printf("I'm worker thread(%d)\n", *(int*)arg);
    printf("My thread id: %lu\n", pthread_self());
    prctl(PR_SET_NAME, "Fucking", NULL, NULL, NULL);
    sleep(10);
    
    return NULL;
}

int main(int argc, char** argv)
{
    pid_t pid = -1;
    pid_t tid1 = -1;
    pthread_t tid;
    int ret = -1;
    int arg = 2;
  
    pid = getpid();
    tid1 = syscall(SYS_gettid);
    printf("pid: %d, tid1: %d\n", pid, tid1);
    ret = pthread_create(&tid, NULL, worker_fun, &arg);
    if (ret != 0) {
	printf("Create thread failed\n");
        exit(-1);
    }

    pthread_join(tid, NULL);
    printf("pid: %d tid: %lu\n", pid, tid);

    getchar();

    return 0;
}
