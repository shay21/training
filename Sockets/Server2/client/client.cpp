#include "client.hpp"
#include <iostream>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <bits/this_thread_sleep.h>
#include <cmath>

int Client::_sockfd;
struct sockaddr_in Client::_servaddr;
Client::Client(int interval) : _interval(interval)
{
    int sockfd;
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
    _sockfd = sockfd;
    memset(&_servaddr, 0, sizeof(_servaddr)); 
    _servaddr.sin_family = AF_INET; 
    _servaddr.sin_port = htons(PORT); 
    _servaddr.sin_addr.s_addr = INADDR_ANY; 
}
void Client::StartClient()
{
    connectServer();
    handleServer();
}
void Client::connectServer()
{
    if (connect(_sockfd, (struct sockaddr *)&_servaddr, sizeof(_servaddr)) != 0) { 
        perror("connection with the server failed"); 
        exit(EXIT_FAILURE); 
    } 
    else
        std::cout << "connected to the server..\n"; 
}
void Client::handleServer()
{
    std::string message = "interval: " + std::to_string(_interval);
    char buff[MAXLINE]; 
    strcpy(buff, message.c_str());
    int n; 
    int final_interval = (int)std::round(60.0/_interval);
    while (true) {
        
        //std::cout << "Enter the string : ";
        //std::cin.getline(buff, MAXLINE);
        //send(_sockfd, buff, sizeof(buff), 0);
        send(_sockfd, buff, sizeof(buff), 0);
        std::this_thread::sleep_for(std::chrono::seconds(final_interval));
    }
}
Client::~Client()
{
    close(_sockfd);
}

