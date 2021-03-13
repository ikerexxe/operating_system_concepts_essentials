/*
 * Exercise 3.19 on page 152
 */

#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid, pid1;

    /* fork a child process */
    pid = fork();

    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed");
        return 1;
    } else if (pid == 0) { /* child process */
        pid1 = getpid();
        printf("Child process, pid: %d\n", pid1);
    } else { /* parent process */
        pid1 = getpid();
        printf("Parent process, pid: %d\n", pid1);
        sleep(5); // 5 seconds to execute "ps -l" and see that the child is a zombie process
    }
    
    return 0;
}
