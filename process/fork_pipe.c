#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int pipe_fd[2];

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    // Create a child process
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("Error creating child process");
        return 1;
    }

    if (child_pid == 0) {
        // Code executed by the child process
        close(pipe_fd[0]);  // Close the read end of the pipe in the child
        printf("Child process PID: %d\n", getpid());

        // Write the child process PID to the pipe
        write(pipe_fd[1], &child_pid, sizeof(child_pid));

        // Close the write end of the pipe in the child
        close(pipe_fd[1]);
    } else {
        // Code executed by the parent process
        close(pipe_fd[1]);  // Close the write end of the pipe in the parent
        printf("Parent process PID: %d\n", getpid());

        // Read the child process PID from the pipe
        read(pipe_fd[0], &child_pid, sizeof(child_pid));
        printf("Child process PID (received by parent): %d\n", child_pid);

        // Close the read end of the pipe in the parent
        close(pipe_fd[0]);
    }

    return 0;
}

