void *receive_messages(void *arg) {
    int client_socket = *((int *)arg);
    free(arg);
 
    char buffer[MAX_MSG_LEN+MAX_USERNAME_LEN+1];
    char *message;
    char *username;
    while (1) {
        // Receive message from server
        memset(buffer,0,sizeof(buffer));
        int bytes_received = recv(client_socket,buffer,sizeof(buffer),0);
//      int bytes_received = recv(client_socket,message,sizeof(message),0);
        if (bytes_received <= 0) {
            perror("Error receiving message from server");
            close(client_socket);
            exit(EXIT_FAILURE);
        }
 
        buffer[bytes_received]='\0';
 
        username = strtok(buffer,"|");
        message = strtok(NULL,"|");
        printf("[%s]: %s\n",username, message);
    }
 
    return NULL;
}
