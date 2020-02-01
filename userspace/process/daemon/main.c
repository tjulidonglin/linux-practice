#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char**argv)
{
    pid_t pid = 0;

    pid = fork();
    if (pid > 0) {
	    printf("Father will exit\n");
        exit(0); 
    } else if(0 == pid) {
	    printf("This is first son\n");
        // 1. 改变工作路径，从而保证当前路径涉及的文件系统可以被正常卸载 
        chdir("/");
        // 2. 更新umask值
        umask(0);
        // 3. 调用setsid函数脱离控制终端
        setsid();
        // 4. open/dev/console设备可能导致进程重新获得控制终端，因此再次fork一次
        pid = fork();
        if (pid > 0) {
            printf("This is first son(exit)\n");
            exit(0);
        } else if(0 == pid) { // grandson process
            int fd = -1;

            fd = open("/dev/null", O_RDWR);
            if (fd < 0) {
                printf("Open /dev/null failed\n");
                exit(-1);
            }
	        dup2(0, fd); 
	        dup2(1, fd); 
	        dup2(2, fd); 
            close(0);
            close(1);
            close(2);
            while (1) {
                sleep(1);
            }
        } else {
            goto out; 
        }
    } else {
		goto out; 
    }

out:
    printf("fork failed\n");
    exit(-1);
}
