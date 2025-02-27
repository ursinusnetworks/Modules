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
#include "message.h"

#define BUFLEN 1024

int main(int argc, char** argv) {
    // Step 1: Get address information for a host
    struct addrinfo hints;
    struct addrinfo* node;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC; // Use either IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // Use TCP
    int ret = getaddrinfo("127.0.0.1", "60000", &hints, &node);
    if (ret != 0) {
        fprintf(stderr, "Error number %i getting address info\n", ret);
        freeaddrinfo(node);
        exit(ret);
    }
    int sockfd = -1;
    // Step 1b: Try all possible connection types in the link list
    // it gives me until I find one that works
    while (node != NULL) {
        printf("ai_family = %i, ai_socktype=%i, ", node->ai_family, node->ai_socktype);
        // IPv6 128 bits (16 bytes, 32 hex, grouped by 8 hex digits)
        char ip[40];
        if (node->ai_family == AF_INET) {
            struct sockaddr_in* ipdata = (struct sockaddr_in*)node->ai_addr;
            inet_ntop(node->ai_family, &ipdata->sin_addr, ip, 40);
            printf("IP = %s\n", ip);
        }
        else if (node->ai_family == AF_INET6) {
            struct sockaddr_in6* ipdata = (struct sockaddr_in6*)node->ai_addr;
            inet_ntop(node->ai_family, &ipdata->sin6_addr, ip, 40);
            printf("IP = %s\n", ip);
        }
        sockfd = socket(node->ai_family, node->ai_socktype, node->ai_protocol);
        if (sockfd != -1) {
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
    // Step 2: Setup stream on socket and connect
    ret = connect(sockfd, node->ai_addr, node->ai_addrlen);
    freeaddrinfo(node);
    if (ret == -1) {
        fprintf(stderr, "Error number %i connecting to socket\n", errno);
        exit(errno);
    }
    // Step 3: Send message
    char* name = "Chris";
    char* message = "I'm running something else!\r\n\r\n";
    uint16_t lenName = strlen(name);
    uint32_t lenMessage = strlen(message);
    struct Header header;
    header.lenName = htons(lenName);
    header.lenMessage = htonl(lenMessage);
    header.magicNum = 174;

    int bytesSent = send(sockfd, &header, sizeof(struct Header), 0);
    printf("Sent over %i bytes for header\n", bytesSent);
    bytesSent = send(sockfd, name, lenName, 0);
    printf("Sent over %i bytes for name\n", bytesSent);
    bytesSent = send(sockfd, message, lenMessage, 0);
    printf("Sent over %i bytes for message\n", bytesSent);

    close(sockfd);
}