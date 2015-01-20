/*
This file is aim to test how to write a daemon process in linux, there are one question here:
    In ubuntu, when i run the process and use "ps -eo uid,pid,ppid,pgid,sid,tty,cmd" to check 
if the process meet the rule, everthing is ok but its ppid is "init --user", i'm confused about 
that, hope anyone can answer it.

we must implement rules as follows:
umask(0);
fork() and parent process must exit(0); --this is make child process is not a leader process in 
    process group and this will be used in next step.
setsid(); -- this is to make sure that our process is take away from controlling terminal totally.
chdir("/"); --make sure we're not be unmounted
close(fd); -- like last step

Author: Shouhua Peng
Date: 1/20/2015
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <signal.h>
#include <syslog.h>

void daemonize()
{
    int i, fd0, fd1, fd2;
    pid_t pid;
    struct rlimit rl;
    struct sigaction sa;
    
    umask(0);
    
    if(getrlimit(RLIMIT_NOFILE, &rl) < 0)  
    {
        fprintf(stderr, "getrlimit failed!\n");
        exit(EXIT_FAILURE);
    }
    
    if((pid = fork()) < 0)
    {
        fprintf(stderr, "fork failed!\n");
        exit(EXIT_FAILURE);
    }
    else if(pid != 0)
        exit(0); 
    
    setsid();

    if((pid = fork()) < 0)
    {
        exit(EXIT_FAILURE);
    }
    else if(pid != 0)
        exit(0);
     
    if(chdir("/") < 0)
        exit(EXIT_FAILURE);

    if(rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for(i=0; i<rl.rlim_max; i++)
        close(i);

    fd0 = open("/dev/null", O_RDWR);    
    fd1 = dup(0);
    fd2 = dup(0);
    
    syslog(LOG_INFO, "new a daemmon success!!!");
    
}

int main()
{
    daemonize();    
    sleep(100000);
}
