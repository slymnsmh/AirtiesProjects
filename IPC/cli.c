#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <arpa/inet.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

#define SUNUCUPORT 3001
#define SUNUCUIP "127.0.0.1"
#define MAX_LENTGH 1024

int main() {
	char *input = malloc(MAX_LENTGH);

	int sockfd;
	struct sockaddr_in serverAddr;
	char str[MAX_LENTGH];
	int recvByte, sendByte, structSize;

	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (-1 == sockfd) {
		perror(RED "Socket" RESET);
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SUNUCUPORT);
	serverAddr.sin_addr.s_addr = inet_addr(SUNUCUIP);
	memset(&(serverAddr.sin_zero), '\0', 8);

	if (-1 == connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr))) {
		perror(RED "Connect" RESET);
	}

	int runCount = 0;

    while (1) {
		if (++runCount == 1) {
			system("clear");
		}
		
		printf(GREEN "ssd-cli$ " RESET);

		fgets(input, MAX_LENTGH, stdin);
		if (strcmp(input, "\0") != 0) {
			input[strlen(input)-1] = '\0';
		}

		if (strcmp(input, "clear") == 0) {
			system("clear");
			continue;
		} else if (strcmp(input, "ifconfig") == 0) {
			system("ifconfig");
			continue;
		}

		sendByte = write(sockfd, input, strlen(input));
		if (-1 == sendByte) {
			perror(RED "Write" RESET);
		}

		bzero(str, MAX_LENTGH);
		recvByte = read(sockfd, &str, MAX_LENTGH);
		if (-1 == recvByte) {
			perror(RED "Read" RESET);
		} else if (0 == recvByte) {
			printf(RED "Connection closed!" RESET);
		}
		
		if (strcmp(str, " ") == 0) {
			printf(RED "Empty response!\n\t" RESET "(" YELLOW "Possible cause: " RESET "Inappropriate command is entered)" );
		}

		printf("%s\n", str);

		if (strcmp(input, "quit") == 0) {
			exit(1);
		}
    }

	close(sockfd);
}