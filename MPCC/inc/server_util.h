#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
 
#define MAX_CLIENTS 10
#define MAX_USERNAME_LEN 20
#define MAX_PASSWORD_LEN 20
#define REGISTRATION_FILE "registration.txt"
#define MAX_MSG_LEN 256
#define ENCRYPTION_KEY 0x0F // Encryption key (change this value for better encryption)
 
struct Client {
    int socket;
    char username[MAX_USERNAME_LEN];
};
 
struct Client clients[MAX_CLIENTS];
int num_clients = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
