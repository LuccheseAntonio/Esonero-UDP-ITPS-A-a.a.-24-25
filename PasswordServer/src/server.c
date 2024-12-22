#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "compatibility.h" // Include for compatibility
#include "protocol.h"
#include "password_utils.h"

#define BUFFER_SIZE 256

int main() {
	setbuf(stdout, NULL);
	if (init_sockets() != 0) {
	    fprintf(stderr, "Failed to initialize sockets.\n");
	    exit(EXIT_FAILURE);
	}

    int server_sock;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    char response[PASSWORD_MAX_LENGTH + 1];
    socklen_t client_len = sizeof(client_addr);

    srand((unsigned int)time(NULL));

    server_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_sock < 0) {
        perror("Socket creation failed");
        cleanup_sockets();
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVER_PORT);

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        CLOSE_SOCKET(server_sock);
        cleanup_sockets();
        exit(EXIT_FAILURE);
    }

    printf("Server is running on port %d...\n", SERVER_PORT);

    while (1) {
        ssize_t recv_len = recvfrom(server_sock, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr *)&client_addr, &client_len);
        if (recv_len < 0) {
            perror("Receive failed");
            continue;
        }

        buffer[recv_len] = '\0';
        printf("New request from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        char command = buffer[0];
        size_t length = atoi(buffer + 2);

        if (length < PASSWORD_MIN_LENGTH || length > PASSWORD_MAX_LENGTH) {
            snprintf(response, sizeof(response), "Error: Invalid length");
        } else {
            switch (command) {
                case CMD_NUMERIC:
                    generate_numeric(response, length);
                    break;
                case CMD_ALPHA:
                    generate_alpha(response, length);
                    break;
                case CMD_MIXED:
                    generate_mixed(response, length);
                    break;
                case CMD_SECURE:
                    generate_secure(response, length);
                    break;
                case CMD_UNAMBIGUOUS:
                    generate_unambiguous(response, length);
                    break;
                default:
                    snprintf(response, sizeof(response), "Error: Invalid command");
            }
        }

        sendto(server_sock, response, strlen(response), 0, (struct sockaddr *)&client_addr, client_len);
    }

    CLOSE_SOCKET(server_sock);
    cleanup_sockets();
    return 0;
}

