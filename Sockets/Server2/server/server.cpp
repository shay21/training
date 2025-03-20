#include "server.hpp"
#include <iostream>
#include <string.h>
#include <thread>
#include <unistd.h>
std::unordered_map<int, std::pair<sockaddr_in, std::thread>> Server::_clients;
int Server::_sockfd;
struct sockaddr_in Server::_servaddr;
Server::Server()
{
    
    int sockfd;
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
    int optval = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }
    memset(&_servaddr, 0, sizeof(_servaddr)); 
        
    _servaddr.sin_family    = AF_INET; 
    _servaddr.sin_addr.s_addr = INADDR_ANY; 
    _servaddr.sin_port = htons(PORT); 
        
    if ( bind(sockfd, (const struct sockaddr *)&_servaddr,  
            sizeof(_servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    }
    _sockfd = sockfd;
    std::cout << "Server Created\n";
}

void Server::StartServer()
{
    int sockfd = _sockfd;
    if ((listen(sockfd, 5)) != 0) { 
        std::cerr << "Listen failed...\n"; 
        exit(0); 
    } 
    else
        std::cout << "Server listening..\n"; 

    while (true) {
        acceptClient();
    }
}
void Server::acceptClient()
{
    sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);
    int connfd = accept(_sockfd, (struct sockaddr *)&cliaddr, &len);
    if (connfd < 0) {
        std::cerr << "server acccept failed...\n";
        exit(0);
    }
    else
    {
        
        std::cout << "New client: " << inet_ntoa(cliaddr.sin_addr) << "," << ntohs(cliaddr.sin_port) << std::endl;
    }
    _clients[connfd] = std::make_pair(cliaddr, std::thread(handleClient, connfd));
    _clients[connfd].second.detach();
    std::cout << "Thread created\n";
}
void Server::handleClient(int sockfd)
{
    std::string address = std::string(inet_ntoa(_clients[sockfd].first.sin_addr)) + ": " + std::to_string(ntohs(_clients[sockfd].first.sin_port));
    char buff[MAXLINE] = { 0 };
    int byteRecv;

    while (true) {
        recv(sockfd, buff, sizeof(buff), 0);
        std::cout << "Client, " << address << ": " << buff << std::endl;
    }


}

Server::~Server()
{
    close(_sockfd);
}