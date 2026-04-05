#include <iostream>
#include <string>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA ws;
    SOCKET server_socket, client_socket;
    sockaddr_in server, client;
    int c;
    char buffer[2000];

    if (WSAStartup(MAKEWORD(2, 2), &ws) != 0) {
        cout << "WSAStartup failed\n";
        return 1;
    }
    
    
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        cout << "Could not create socket\n";
        return 1;
    }
    cout<<"1.Socket has been created successfully....."<<endl;

    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    if (bind(server_socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        cout << "Bind failed. Error: " << WSAGetLastError() << endl;
        return 1;
    }
    cout<<"2.Successfully binded\n";

    listen(server_socket, 1);
    cout << "Waiting for incoming connections on port 8080...\n";

    c = sizeof(struct sockaddr_in);
    client_socket = accept(server_socket, (struct sockaddr*)&client, &c);
    if (client_socket == INVALID_SOCKET) {
        cout << "Accept failed\n";
        return 1;
    }
    cout << "3.Connection accepted........\n";

    string full_message = "";
    int bytes_received;

    while (true) {
        bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0'; // Manually null-terminate bytes
            full_message += buffer;

            if (full_message.find('\n') != string::npos || full_message.find('\r') != string::npos) {
                break;
            }
        } else {
            break; 
        }
    }

    cout << "Messege recieved:" << full_message << endl;

    
    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();

    return 0;
}
