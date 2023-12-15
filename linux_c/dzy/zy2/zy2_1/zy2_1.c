/******************2_1_paomadeng.c*********/
 
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ioctl.h>
 
int main()
{
    int led_fd;
    if((led_fd=open("/dev/leds0",0))<0) 
    {
        if((led_fd=open("/dev/leds",0))<0)
        {
            printf("open device leds failed\n");
            return -1;
        }
    }
    ioctl(led_fd,0,0);
    ioctl(led_fd,0,1);
    ioctl(led_fd,0,2);
    ioctl(led_fd,0,3);
    while(1)
    {
        ioctl(led_fd,0,0);//led1灭
        ioctl(led_fd,1,2);//led3亮
        sleep(2);
        ioctl(led_fd,1,0);//led1亮
        ioctl(led_fd,0,2);//led3灭
        sleep(3);
        
    }
    close(led_fd);
    return 0;
}
 