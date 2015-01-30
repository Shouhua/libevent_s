#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/inotify.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>

#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024 * (EVENT_SIZE + 16))

typedef struct EVENTMASK{
    int flag;
    char *name;
}event_mask; 

int main(void)
{
    event_mask event_masks[] = {
        {IN_ACCESS        , "IN_ACCESS"}        ,  
        {IN_ATTRIB        , "IN_ATTRIB"}        ,  
        {IN_CLOSE_WRITE   , "IN_CLOSE_WRITE"}   ,  
        {IN_CLOSE_NOWRITE , "IN_CLOSE_NOWRITE"} ,  
        {IN_CREATE        , "IN_CREATE"}        ,  
        {IN_DELETE        , "IN_DELETE"}        ,  
        {IN_DELETE_SELF   , "IN_DELETE_SELF"}   ,  
        {IN_MODIFY        , "IN_MODIFY"}        ,  
        {IN_MOVE_SELF     , "IN_MOVE_SELF"}     ,  
        {IN_MOVED_FROM    , "IN_MOVED_FROM"}    ,  
        {IN_MOVED_TO      , "IN_MOVED_TO"}      ,  
        {IN_OPEN          , "IN_OPEN"}          ,  

        {IN_DONT_FOLLOW   , "IN_DONT_FOLLOW"}   ,  
        {IN_EXCL_UNLINK   , "IN_EXCL_UNLINK"}   ,  
        {IN_MASK_ADD      , "IN_MASK_ADD"}      ,  
        {IN_ONESHOT       , "IN_ONESHOT"}       ,  
        {IN_ONLYDIR       , "IN_ONLYDIR"}       ,  

        {IN_IGNORED       , "IN_IGNORED"}       ,  
        {IN_ISDIR         , "IN_ISDIR"}         ,  
        {IN_Q_OVERFLOW    , "IN_Q_OVERFLOW"}    ,  
        {IN_UNMOUNT       , "IN_UNMOUNT"}       ,  

    };

    int i;
    int wd;
    int fd;
    int length;
    char buffer[BUF_LEN];

    int fd_max;
    int done = 0;
    int result;

    fd = inotify_init();
    if(fd < 0)
    {
        perror("inotify_init error");
        exit(EXIT_FAILURE);
    }
    wd = inotify_add_watch(fd, "/home/shouhua/test", IN_ALL_EVENTS);
    fd_set read_sets;
    while(!done)
    {
        printf("in while loop...");
        FD_ZERO(&read_sets);
        FD_SET(fd, &read_sets);

        result = select(fd+1, &read_sets, NULL, NULL, NULL);
        printf("result = %d\n", result);
        if(result == -1)      //经典错误, 如果将括号里的表达式改为result = -1将永远执行if里面的内容!!!
        {
            if(errno == EINTR)
                continue;
            else
            {
                done = 1;
                perror("select error");
                exit(EXIT_FAILURE);
            }
        }
        if(FD_ISSET(fd, &read_sets))
        {
            printf("we are now do the directory event...\n");
            length = read(fd, buffer, BUF_LEN);
            printf("read length = %d\n", length);
            i = 0;
            while(i<length)
            {
                struct inotify_event *event = (struct inotify_event *)&buffer[i];
                int index;
                for(index=0; index<(sizeof(event_masks)/sizeof(event_mask)); index++)
                {
                    if(event->mask & event_masks[index].flag)
                        printf("%s:%s(name)\n", event_masks[index].name, event->name);
                }
                i = i + EVENT_SIZE + event->len;
                printf("i=%d\n", i);
            }
        }        
    }
    inotify_rm_watch(fd, wd);
    close(fd);
    exit(0);    
}
