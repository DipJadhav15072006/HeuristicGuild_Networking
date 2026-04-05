#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA ws;
    SOCKET clientSocket;
    sockaddr_in server;

    if (WSAStartup(MAKEWORD(2,2), &ws) != 0) {
        cout << "WSAStartup failed\n";
        return 1;
    }


    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        cout << "Socket creation failed\n";
        return 1;
    }
    cout<<"1. Client socket has been created successfully....."<<endl;
   
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost

    if (connect(clientSocket, (struct sockaddr*)&server, sizeof(server)) < 0) {
        cout << "Connection failed\n";
        return 1;
    }

    cout << "3.Conneced...\n";

    cout<<"Enter the messge you want to send to server:";

    string message;
    cin>>message;

    send(clientSocket, message.c_str(), message.length(), 0);


    cout << "Message sent to server\n";

    
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}