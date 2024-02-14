#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    // Create a child process
    pid_t child_pid = fork();

    if (child_pid == -1) {
        // Error handling if fork fails
        perror("Error creating child process");
        return 1;
    }

    if (child_pid == 0) {
        // Code executed by the child process
        printf("Child process PID: %d\n", getpid());
    } else {
        // Code executed by the parent process
        printf("Parent process PID: %d\n", getpid());
        printf("Child process PID: %d\n", child_pid);
    }

    return 0;
}

