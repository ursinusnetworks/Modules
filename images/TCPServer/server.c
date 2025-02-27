#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include "message.h"

#define BUFLEN 1024
#define BACKLOG 10


int counter = 0;

struct threadArgs {
    int sockfd;
    char* port;
    pthread_mutex_t* lock;
};

void* serviceClient(void* targs) {
    // Unpack information, then free
    struct threadArgs* targsUnpacked = (struct threadArgs*)targs;
    int sockfd = targsUnpacked->sockfd;
    pthread_mutex_t* lock = targsUnpacked->lock;
    free(targsUnpacked);

    pthread_mutex_lock(lock);
    printf("Servicing client %i\n", counter);
    counter++;
    pthread_mutex_unlock(lock); // Remember to unlock when you're finished!!
    

    struct Header header;
    recv(sockfd, &header, sizeof(struct Header), 0);
    header.lenName = ntohs(header.lenName);
    header.lenMessage = ntohl(header.lenMessage);
    
    printf("lenName = %i, lenMessage = %i, magicNum = %i\n", header.lenName, header.lenMessage, header.magicNum);

    char* name = (char*)malloc(header.lenName+1);
    recv(sockfd, name, header.lenName, 0);
    name[header.lenName] = '\0';
    printf("Name: %s\n", name);

    char* message = (char*)malloc(header.lenMessage+1);
    recv(sockfd, message, header.lenMessage, 0);
    message[header.lenMessage] = '\0';
    printf("Message: \"%s\"\n", message);

    free(message);
    free(name);
    close(sockfd);
    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    char* port = "60000";
    // Step 1: Get address information for a host
    struct addrinfo hints;
    struct addrinfo* node;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC; // Use either IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // Use TCP
    hints.ai_flags = AI_PASSIVE; // (New!!) Use my IP (Important!!!)
    int ret = getaddrinfo(NULL, port, &hints, &node);
    if (ret != 0) {
        fprintf(stderr, "Error number %i getting address info\n", ret);
        freeaddrinfo(node);
        exit(ret);
    }
    int sockfd = -1;
    // Step 1b: Try all possible connection types in the link list
    // it gives me until I find one that works
    while (node != NULL) {
        sockfd = socket(node->ai_family, node->ai_socktype, node->ai_protocol);
        if (sockfd != -1) {
            int yes = 1;
            if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
                fprintf(stderr, "Error setting %i reuse address\n", errno);
            }
            break;
        }
        else {
            node = node->ai_next;
        }
    }
    // Step 1b: Make sure we got a valid socket file descriptor
    // after going through all of the options
    printf("sockfd = %i\n", sockfd);
    if (sockfd == -1) {
        fprintf(stderr, "Error number %i opening socket\n", errno);
        freeaddrinfo(node);
        exit(errno);
    }
    // Step 2: Setup stream on socket for listening
    // Step 2a: Bind my IP address information to this socket
    ret = bind(sockfd, node->ai_addr, node->ai_addrlen);
    if (ret == -1) {
        fprintf(stderr, "Error number %i binding to socket\n", errno);
        freeaddrinfo(node);
        exit(errno);
    }
    // Step 2b: Mark socket for listening
    ret = listen(sockfd, BACKLOG);
    if (ret == -1) {
        fprintf(stderr, "Error number %i listening on socket\n", errno);
        freeaddrinfo(node);
        exit(errno);
    }

    // Step 3: Accept connection and communicate
    pthread_mutex_t lock;
    pthread_mutex_init(&lock, NULL);
    while (1) {
        struct sockaddr their_addr;
        socklen_t addrlen = sizeof(their_addr);
        // "Block" (wait) for incoming connection on listening socket sockfd
        int clientsockfd = accept(sockfd, &their_addr, &addrlen);
        if (clientsockfd != -1) {
            printf("Got new connection! ");
            char ip[40];
            if (node->ai_family == AF_INET) {
                struct sockaddr_in* ipdata = (struct sockaddr_in*)&their_addr;
                inet_ntop(node->ai_family, &ipdata->sin_addr, ip, 40);
                printf("IP address = %s\n", ip);
            }
            else if (node->ai_family == AF_INET6) {
                struct sockaddr_in6* ipdata = (struct sockaddr_in6*)&their_addr;
                inet_ntop(node->ai_family, &ipdata->sin6_addr, ip, 40);
                printf("IP address = %s\n", ip);
            }

            pthread_t thread;
            struct threadArgs* targs = (struct threadArgs*)malloc(sizeof(struct threadArgs));
            targs->sockfd = clientsockfd;
            targs->port = port;
            targs->lock = &lock;
            pthread_create(&thread, NULL, serviceClient, targs);
        }
    }
    // TODO: Code never reaches these!  Should do this on interrupt
    pthread_mutex_destroy(&lock);
    freeaddrinfo(node);
    close(sockfd);
}