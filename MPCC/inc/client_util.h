#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
 
#define SERVER_IP "127.0.0.5"
#define SERVER_PORT 11111
#define MAX_USERNAME_LEN 20
#define MAX_PASSWORD_LEN 20
#define MAX_MSG_LEN 256
