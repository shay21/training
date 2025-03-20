#include "client.hpp"
#include <iostream>
int main() { 
    int interval = 60;
    std::cout << "Enter messages per minute: ";
    std::cin >> interval;
    Client client = Client(interval);
    client.StartClient();
    
}