#pragma once
#include <vector>
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <unordered_map>
#include <string>
#include <thread>
#define PORT     8080 
#define MAXLINE 1024 
class Server {
    public:
        Server();
        ~Server();
        
        void StartServer();
        
    private:
    static void handleClient(int connfd);
    void acceptClient();
    static std::unordered_map<int, std::pair<sockaddr_in, std::thread>> _clients;
    static int _sockfd;
    static struct sockaddr_in _servaddr;

};