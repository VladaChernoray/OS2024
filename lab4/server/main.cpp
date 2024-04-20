#include <winsock2.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

void swap(int* arr, int idx1, int idx2) {
    int tmp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = tmp;
}

int getPivotPos(int* arr, int start, int end) {
    int mid = start + (end - start) / 2;
    int a = arr[start], b = arr[mid], c = arr[end];
    if (a < b) {
        if (b < c) return mid;
        return (a < c) ? end : start;
    } else {
        if (a < c) return start;
        return (b < c) ? end : mid;
    }
}

int partition(int* arr, int start, int end) {
    int pivotPos = getPivotPos(arr, start, end);
    int pivot = arr[pivotPos];
    swap(arr, pivotPos, end);
    int i = start;
    for (int j = start; j < end; j++) {
        if (arr[j] < pivot) {
            swap(arr, i, j);
            i++;
        }
    }
    swap(arr, i, end);
    return i;
}

void quicksort(int* arr, int start, int end) {
    if (start < end) {
        int pi = partition(arr, start, end);
        quicksort(arr, start, pi - 1);
        quicksort(arr, pi + 1, end);
    }
}

int main() {
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        std::cout << "WSAStartup failed with error: " << WSAGetLastError() << std::endl;
        return 1;
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;

    SOCKET sListen = socket(AF_INET, SOCK_STREAM, 0);
    if (sListen == INVALID_SOCKET) {
        std::cout << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    if (bind(sListen, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        std::cout << "Bind failed with error: " << WSAGetLastError() << std::endl;
        closesocket(sListen);
        WSACleanup();
        return 1;
    }

    if (listen(sListen, SOMAXCONN) == SOCKET_ERROR) {
        std::cout << "Listen failed with error: " << WSAGetLastError() << std::endl;
        closesocket(sListen);
        WSACleanup();
        return 1;
    }

    while (true) {
        SOCKET newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
        if (newConnection == INVALID_SOCKET) {
            std::cout << "Accept failed with error: " << WSAGetLastError() << std::endl;
            closesocket(sListen);
            WSACleanup();
            return 1;
        }

        std::cout << "Client connected" << std::endl;
        int N = 1000;
        int receivedArray[N];

        if (recv(newConnection, (char*)receivedArray, sizeof(receivedArray), 0) <= 0) {
            std::cout << "Failed to receive data or connection closed by client: " << WSAGetLastError() << std::endl;
            closesocket(newConnection);
            continue; 
        }

        std::cout << "Data received. Sorting now...\n";
        quicksort(receivedArray, 0, N - 1);

        std::cout << "Data sorted. Sending back...\n";
        if (send(newConnection, (char*)receivedArray, sizeof(receivedArray), 0) == SOCKET_ERROR) {
            std::cout << "Failed to send sorted data: " << WSAGetLastError() << std::endl;
        } else {
            std::cout << "Sorted data sent back to client successfully!" << std::endl;
        }

        closesocket(newConnection);
    }

    closesocket(sListen);
    WSACleanup();
    return 0;
}
