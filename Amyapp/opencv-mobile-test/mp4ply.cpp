#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <unistd.h> // sleep()
#include <linux/fb.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static int fd_fb;
static struct fb_var_screeninfo var; /* Current var */
static int xres, yres;
static int screen_size;
static unsigned char *fb_base;


int main()
{
    // 打开LCD
    fd_fb = open("/dev/fb0", O_RDWR);
    if (fd_fb < 0)
    {
        printf("can't open /dev/fb0\n");
        return -1;
    }

    if (ioctl(fd_fb, FBIOGET_VSCREENINFO, &var))
    {
        printf("can't get var\n");
        return -1;
    }

    xres = var.xres;
    yres = var.yres;
    screen_size = var.xres * var.yres * var.bits_per_pixel / 8;
    fb_base = (unsigned char *)mmap(NULL, screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_fb, 0);
    // 判断是映射成功
    if (fb_base == MAP_FAILED)
    {
        printf("mmap failed\n");
        return -1;
    }

    int fb_vidieo = open("videoplayback.mp4" , O_RDWR);

    // 打开视频文件
    cv::VideoCapture cap;
    cap.open(fb_vidieo);
    // 判断是否打开视频文件
    

    if (!cap.isOpened())
    {
        printf("can't open videoplayback.mp4\n");
        return -1;
    }

    cv::Mat frame;
    while (1)
    {
        cap >> frame;
        if (frame.empty())
        {
            printf("frame is empty\n");
            break;
        }
        // 读取图片并调整大小
        cv::resize(frame, frame, cv::Size(var.xres, var.yres));
        cv::Mat fb_image;
        cv::cvtColor(frame, fb_image, cv::COLOR_BGR2BGR565);

        // 将图像数据写入帧缓冲
        memcpy(fb_base, fb_image.data, screen_size);

    }


    // 关闭LCD
    munmap(fb_base, screen_size);
    close(fd_fb);
    // 打印结束
    printf("end\n");


    return 0;



}