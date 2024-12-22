#ifndef COMPATIBILITY_H
#define COMPATIBILITY_H

#ifdef _WIN32
    // Windows-specific includes
    #include <winsock2.h>
    #include <ws2tcpip.h>
    typedef int socklen_t;
    #define CLOSE_SOCKET closesocket
#else
    // UNIX-like systems (macOS, Linux)
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    typedef int SOCKET;
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define CLOSE_SOCKET close
#endif

/**
 * Initialize network libraries (required for Windows only).
 * @return 0 if all went well, a non-0 error if there were problems.
 */
static inline int init_sockets() {
#ifdef _WIN32
    WSADATA wsaData;
    return WSAStartup(MAKEWORD(2, 2), &wsaData);
#else
    return 0; // No initialization needed for UNIX-like systems
#endif
}

/**
 * Cleans up network libraries (required for Windows only).
 */
static inline void cleanup_sockets() {
#ifdef _WIN32
    WSACleanup();
#endif
}

#endif // COMPATIBILITY_H
