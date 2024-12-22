#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compatibility.h" // Include for compatibility
#include "protocol.h"

#define DEFAULT_SERVER "127.0.0.1"  // Default server address (localhost)
#define DEFAULT_PORT 12345          // Default Port

void print_help() {
    printf("Password Generator Help Menu\n");
    printf("Commands:\n");
    printf(" h        : show this help menu\n");
    printf(" n LENGTH : generate numeric password (digits only)\n");
    printf(" a LENGTH : generate alphabetic password (lowercase letters)\n");
    printf(" m LENGTH : generate mixed password (lowercase letters and numbers)\n");
    printf(" s LENGTH : generate secure password (uppercase, lowercase, numbers, symbols)\n");
    printf(" u LENGTH : generate unambiguous secure password (no similar-looking characters)\n");
    printf(" q        : quit application\n");
    printf("LENGTH must be between 6 and 32 characters\n");
}

int main(int argc, char *argv[]) {
	setbuf(stdout, NULL);
    if (init_sockets() != 0) {
        fprintf(stderr, "Failed to initialize sockets\n");
        exit(EXIT_FAILURE);
    }

    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[256];
    char server_ip[50];
    int server_port;

    if (argc < 2) {
        strcpy(server_ip, DEFAULT_SERVER);
        server_port = DEFAULT_PORT;
    } else {
        strcpy(server_ip, argv[1]);
        server_port = atoi(argv[2]);
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        cleanup_sockets();
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    while (1) {
        printf("Enter your request: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        if (strcmp(buffer, "h") == 0) {
            print_help();
            continue;
        }

        if (strcmp(buffer, "q") == 0) {
            printf("Exiting application...\n");
            break;
        }

        if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            perror("Error in sendto");
            break;
        }

        socklen_t server_len = sizeof(server_addr);
        int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&server_addr, &server_len);
        if (n < 0) {
            perror("Error in recvfrom");
            break;
        }

        buffer[n] = '\0';
        printf("Password generated: %s\n", buffer);
    }

    CLOSE_SOCKET(sockfd);
    cleanup_sockets();
    return 0;
}
