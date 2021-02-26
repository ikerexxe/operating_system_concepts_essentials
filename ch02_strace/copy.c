#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> 

#define MAX 1024

int main(void)
{
	char src[32];
	char dst[32];
	int fd;
	char buf[MAX];
	ssize_t size;
	
	printf("Insert source file name: ");
	scanf("%s", src);
	printf("Insert destination file name: ");
	scanf("%s", dst);
	
	fd = open(src, O_RDONLY);
	if(fd == -1) {
	    printf("Error opening %s\n", src);
	    return -1;
    }
	size = read(fd, buf, MAX);
	if(size == -1) {
	    printf("Error reading %s\n", src);
	    return -1;
    }
	close(fd);
	
	fd = open(dst, O_WRONLY|O_CREAT);
	if(fd == -1) {
	    printf("Error opening %s\n", dst);
	    return -1;
    }
	size = write(fd, buf, size);
	if(size == -1) {
	    printf("Error writing %s\n", dst);
	    return -1;
    }
	close(fd);
	
	return 0;
}
