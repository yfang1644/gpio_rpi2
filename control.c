#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <linux/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define GPIOSET0 _IOW(123, 0, int *)
#define GPIOSET1 _IOW(123, 1, int *)
#define GPIOSET2 _IOW(123, 2, int *)

int main()
{
	int fd;
	int val;

	fd = open("/dev/xxxxx", O_RDWR);

	ioctl(fd, GPIOSET2, 1);
	for(;;) {
		val = (20 << 16) | 1;
		write(fd, &val, 4);
		sleep(1);
		val = (20 << 16);
		write(fd, &val, 4);
		sleep(1);
	}
}
