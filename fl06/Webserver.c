#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <wiringPi.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define LED1	1
#define LED2	4
#define LED3	5
#define LED4	6

static void *clnt_connection(void *arg);
int sendData(int fd, FILE *fp, char *file_name);
void sendOk(FILE *fp);
void sendError(FILE *fp);

void ledControl(int gpio, int state)
{
	digitalWrite(gpio, state);
}

int main(int argc, char **argv)
{
	int serv_sock;
	pthread_t tid;
	struct sockaddr_in serv_addr, clnt_addr;
	socklen_t clnt_addr_size;

	if(argc != 2) {
		printf("usage : %s <PORT>\n", argv[0]);
		return -1;
	}
	
	wiringPiSetup();
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LED3, OUTPUT);
	pinMode(LED4, OUTPUT);
	
	serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(serv_sock < 0) {
		perror("socket");
		return -1;
	}
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));
	if(bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("bind");
		return -1;
	}

	if(listen(serv_sock, 10) < 0) {
		perror("listen");
		return -1;
	}

	while(1) {
		int clnt_sock;
		clnt_addr_size = sizeof(clnt_addr);
		clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
		printf("Client IP : %s:%d\n", inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));

		pthread_create(&tid, NULL, clnt_connection, (void *)&clnt_sock);
		pthread_detach(tid);
	}

	return 0;
}

void *clnt_connection(void *arg)
{
	int clnt_sock = *((int *)arg), clnt_fd;
	FILE *clnt_read, *clnt_write;
	
	char reg_line[BUFSIZ], reg_buf[BUFSIZ];
	char method[10];
	char file_name[256];
	
	clnt_read = fdopen(clnt_sock, "r");
	clnt_write = fdopen(dup(clnt_sock), "w");
	clnt_fd = clnt_sock;

	fgets(reg_line, BUFSIZ, clnt_read);
	fputs(reg_line, stdout);

	strcpy(method, strtok(reg_line, " /"));
	if(strcmp(method, "POST") == 0) {
		sendOk(clnt_write);
		fclose(clnt_read);
		fclose(clnt_write);
		return NULL;
	}
	else if(strcmp(method, "GET") != 0) {
		sendError(clnt_write);
		fclose(clnt_read);
		fclose(clnt_write);
		return NULL;
	}
	
	strcpy(file_name, strtok(NULL, " /"));
	printf("file_name : %s\n", file_name);
	if(strstr(file_name, "?") != NULL) {
		// LED 버튼을 누르고 submit을 했다면 "?x=x&x=x&x=x"같은 식으로 온다
		char	*check;
		char	opt[8];
		char	var[8];
		int		state = 0;
		int		num = 1;
		check = strstr(file_name, "?") + 1;
		while (strstr(check, "&") != NULL) {
			++num;
			check = strstr(check, "&") + 1;
		}
		strtok(file_name, "?");
		// 이후 led n번과 On/Off 분리하며 작업
		while (num--) {
			strcpy(opt, strtok(NULL, "="));
			strcpy(var, strtok(NULL, "&"));

			printf("%s=%s\n", opt, var);
			if (!strncmp(var, "On", 2))
				state = 1;
			else if (!strncmp(var, "Off", 3))
				state = 0;
			switch (opt[3]) {
			case '1':
				ledControl(LED1, state);
				break;
			
			case '2':
				ledControl(LED2, state);
				break;
			
			case '3':
				ledControl(LED3, state);
				break;
			
			case '4':
				ledControl(LED4, state);
				break;
			
			default:
				break;
			}
		}
	}
	
	// 웹 페이지
	do {
		fgets(reg_line, BUFSIZ, clnt_read);
		fputs(reg_line, stdout);
		strcpy(reg_buf, reg_line);
	} while(strncmp(reg_line, "\r\n", 2));
	
	sendData(clnt_fd, clnt_write, file_name);
	
	fclose(clnt_read);
	fclose(clnt_write);
	return NULL;
}

int sendData(int fd, FILE *fp, char *file_name)
{
	char protocol[] = "HTTP/1.1 200 OK\r\n";
	char server[] = "Server:Netscape-Enterprise\6.0\r\n";
	char cnt_type[] = "Content-Type:text/html\r\n";
	char end[] = "\r\n";
	char buf[BUFSIZ];
	int len;

	fputs(protocol, fp);
	fputs(server, fp);
	fputs(cnt_type, fp);
	fputs(end, fp);
	fflush(fp);

	fd = open(file_name, O_RDWR);
	do {
		len = read(fd, buf, BUFSIZ);
		fwrite(buf, len, sizeof(char), fp);
	} while(len == BUFSIZ);

	fflush(fp);
	close(fd);

	return 0;
}

void sendOk(FILE *fp)
{
	char protocol[] = "HTTP/1.1 200 OK\r\n";
	char server[] = "Server: Netscape-Enterprise/6.0\r\n\r\n";

	fputs(protocol, fp);
	fputs(server, fp);
	fflush(fp);
}

void sendError(FILE *fp)
{
	char protocol[] = "HTTP/1.1 200 OK\r\n";
	char server[] = "Server:Netscape-Enterprise\6.0\r\n";
	char cnt_len[] = "Content-Length:1024\r\n";
	char cnt_type[] = "Content-Type:text/html\r\n";
	char content1[] = "<html><head><title>BAD Connection</title></head>";
	char content2[] = "<body><font size=+5>BAD Request</font></body></html>";

	printf("send_error\n");
	fputs(protocol, fp);
	fputs(server, fp);
	fputs(cnt_len, fp);
	fputs(cnt_type, fp);
	fputs(content1, fp);
	fputs(content2, fp);

	fflush(fp);
}