#include <winsock2.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>
#include <iomanip> 

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

void generate_array(int *array, int size) {
    srand((unsigned)time(NULL)); 
    for (int i = 0; i < size; i++) {
        array[i] = rand() % size; 
    }
}

int main() {
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        std::cout << "WSAStartup error: " << WSAGetLastError() << std::endl;
        return 1;
    }

    SOCKADDR_IN addr;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;

    SOCKET Connection = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
        std::cout << "Error: Failed to connect to server" << std::endl;
        return 1;
    }
    std::cout << "Connected!" << std::endl;

    int N = 1000;
    int randomArray[N];
    generate_array(randomArray, N);

    std::cout << "Array being sent to the server:" << std::endl;
    for (int i = 0; i < N; i++) {
        std::cout << randomArray[i] << " ";
        if (i % 10 == 9) std::cout << std::endl;
    }
    std::cout << std::endl;

    std::vector<double> times;
    times.reserve(100);
    
    for (int iteration = 0; iteration < 100; iteration++) {
        auto start_time = std::chrono::high_resolution_clock::now();
         
        if (send(Connection, (char*)randomArray, sizeof(randomArray), 0) == SOCKET_ERROR) {
            std::cout << "Failed to send data: " << WSAGetLastError() << std::endl;
            continue;  
        }
        std::cout << "Data sent!\n";

        int receivedSortedArray[N];
        if (recv(Connection, (char*)receivedSortedArray, sizeof(receivedSortedArray), 0) <= 0) {
            std::cout << "Failed to receive data or connection closed by server: " << WSAGetLastError() << std::endl;
        } else {
            auto end_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed = end_time - start_time;
            times.push_back(elapsed.count());
            std::cout << "Sorted array received from the server:" << std::endl;

            for (int i = 0; i < N; i++) {
                std::cout << receivedSortedArray[i] << " ";
                if (i % 10 == 9) std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }

    std::cout << "All timing results (in milliseconds):\n";
    for (double t : times) {
        std::cout << std::fixed << std::setprecision(2) << t << " ms\n";
    }

    double total_time = 0;
    for (double t : times) {
        total_time += t;
    }
    double average_time = total_time / times.size();

    std::cout << "Average time taken: " << std::fixed << std::setprecision(2) << average_time << " ms" << std::endl;
    
    system("pause");
    
    closesocket(Connection);
    WSACleanup();
    return 0;
}