#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/netlink.h>
#include <poll.h>
#include <sys/socket.h>

static void die(char *msg)
{
    write(2, msg, strlen(msg));
    exit(1);
}


int main(int argc, char** argv)
{
    struct sockaddr_nl nls;
    struct pollfd pfd;
    char buf[512] = {0};

    // Open hotplug event netlink socket
    memset(&nls, 0, sizeof(struct sockaddr_nl));
    nls.nl_family = AF_NETLINK;
    nls.nl_pid = getpid();
    nls.nl_groups = -1;

    pfd.events = POLLIN;
    pfd.fd = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);
    if (pfd.fd == -1)
        die("create socket failed\n");

    // Listen to netlink socket
    if (bind(pfd.fd, (struct sockaddr *)&nls, sizeof(struct sockaddr_nl)))
        die("Bind failed\n");

    while (-1 != poll(&pfd, 1, -1)) {
        int i;
        int len = 0;

        len = recv(pfd.fd, buf, sizeof(buf), MSG_DONTWAIT);
        if (-1 == len)
            die("recv failed\n");

        // Print the data to stdout
        i = 0;
        while (i < len) {
            printf("%s\n", buf + i);
            i += strlen(buf + i) + 1;
        }
    }

    die("poll\n");

    // Dear gcc: shut up
    exit(0);
}

