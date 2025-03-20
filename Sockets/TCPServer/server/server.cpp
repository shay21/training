#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 7215
#define MAXLINE 1024

int main()
{
    int serverSocket;
    char buffer[MAXLINE] = {0};
    struct sockaddr_in servaddr, cliaddr;

    // Create socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // Bind socket to address
    if (bind(serverSocket, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    listen(serverSocket, 5);
    std::cout << "waiting to accept" << std::endl;

    int clientSocket = accept(serverSocket, (struct sockaddr *)&cliaddr, (socklen_t *)&cliaddr);
    if (clientSocket < 0)
    {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0;i< 100;i++)
    {
        
        recv(clientSocket, buffer, MAXLINE, 0);
        std::cout << "Message received: " << buffer << std::endl;
        std::cout << "Enter message: ";
        std::cin.getline(buffer, MAXLINE); //
        send(clientSocket, buffer, strlen(buffer), 0);
        
        std::cout << "Message sent" << std::endl;
    }

    close(clientSocket);
    close(serverSocket);

    return 0;
}