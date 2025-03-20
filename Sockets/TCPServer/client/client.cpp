#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 7215
#define MAXLINE 1024

int main()
{
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0;i< 100;i++)
    {
        std::cout << "Enter message: ";
        std::cin.getline(buffer, MAXLINE);
        send(sockfd, buffer, strlen(buffer), 0);
        std::cout << "Message sent" << std::endl;
        recv(sockfd, buffer, MAXLINE, 0);
        std::cout << "Message received: " << buffer << std::endl;
    }
    
    

    close(sockfd);
    return 0;
}