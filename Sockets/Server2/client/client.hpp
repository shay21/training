#pragma once

#define PORT     8080 
#define MAXLINE 1024 

class Client {
    public:
        Client(int interval);
        ~Client();
        
        void StartClient();
        
    private:
        void handleServer();
        void connectServer();
        static int _sockfd;
        static struct sockaddr_in _servaddr;
        int _interval; //amount of messages per minute
};