/*
 * z1804759.cxx
 * 
 * Tim Dickens
 * CSCI 330
 * TCP file server
 * 
 * 	loops/waits/forks/execs for path received from client 
 * 	      opens direectory or file, sends back lines of file names or contents of file to client
 * 
 * 	processes extra credit date command INFO
 * 
 * 	command line arguments:
 * 		argv[1] port number to receive requests on
 * 
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string.h>
using namespace std;

void processClientRequest(int connSock) {
	int received, fd, readfd;
	char path[2048], buffer[2048], readbuffer[2048];
	char proc[5];
	char* cPath;
	char* dPath;
	// read a message from the client
	if ((received = read(connSock, path, sizeof(path))) < 0) {
		perror("receive");
		exit(EXIT_FAILURE);
	}
	cout << "Client request: " << path << endl;
	//tokenize request, check for GET or INFO
	for(int i = 0; path[i] != ' ' && path[i] != '\0'; i++){
		proc[i] = path[i];
	}
	cPath = path + 4;
		//check tokenized GET or INFO argument
	if( strcmp(proc, "GET" ) == 0){
		//check for valid pathname use '/'
		if( cPath[0] != '/' )
		{
			close(2);
			dup(connSock);
			cerr << "Error: File or directory not found\n";
			exit(EXIT_SUCCESS);
		}
		//check for file or directory
		int rs;
		struct stat Sbuffer;
		rs = stat(cPath, &Sbuffer);
		if(rs == - 1){
			close(2);
			dup(connSock);
			perror("stat");
			exit(EXIT_SUCCESS);
			}
		//check if path is a directory
		if( S_ISDIR(Sbuffer.st_mode) ){
			//open directory and check for errors
			DIR *dirp = opendir(cPath);
			if(dirp == 0){
				close(2);
				dup(connSock);
				cerr << "Cannot open file or directory";
				exit(EXIT_SUCCESS);
				}
			//check for index.html and open it if it exists
			dPath = cPath;
			strcat(dPath, "index.html");
			chmod( cPath, 00666);
			fd = open(dPath, O_RDONLY);
			if( fd != - 1){
               			 readfd = read(fd, readbuffer, 2048);
               			 if(readfd == - 1) {
                       			 //tell client error occured
                       			 close(2);
                       		 	dup(connSock);
                                 	perror("read");
                      		 	exit(EXIT_FAILURE);
				}
                if (write(connSock, readbuffer, strlen(readbuffer)) < 0) {
                                perror("write");
                                exit(EXIT_FAILURE);
                                 }
                        cout << "sent: " << readbuffer;
				}
			// read directory entries
			struct dirent *dirEntry;
			while ((dirEntry = readdir(dirp)) != NULL) {
				if( dirEntry->d_name[0] != '.'){
				strcpy(buffer, dirEntry->d_name);
				strcat(buffer, "\n");
				}
			if (write(connSock, buffer, strlen(buffer)) < 0) {
				perror("write");
				exit(EXIT_FAILURE);
				}
			cout << "sent: " << buffer;
				}
		closedir(dirp);
		}
		else {
		//read from file if it exists
		fd = open(cPath, O_RDONLY);
		if(fd == - 1){
			close(2);
			perror("open");
			exit(EXIT_FAILURE);
		}
		close(1);
		dup(connSock);
		int cat = system("cat $cPath");
		if(cat == - 1){
			close(2);
			perror("system");
			exit(EXIT_FAILURE);
			}
		}
	}
	else if( strcmp(proc, "INFO" ) == 0){
		close(1);
		dup(connSock);
		int sys2 = system("date");
		if(sys2 == - 1){
			close(2);
			perror("system");
			exit(EXIT_FAILURE);
		}
		}
	close(connSock);
	cout << "done with client request\n";
	exit(EXIT_SUCCESS);
}
        
int main(int argc, char *argv[]) {

	if (argc != 2) {
		cerr << "USAGE: z1804759.cxx port\n";
		exit(EXIT_FAILURE);
	}
	
	// Create the TCP socket 
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}	
	// create address structures
	struct sockaddr_in server_address;  // structure for address of server
	struct sockaddr_in client_address;  // structure for address of client
	unsigned int addrlen = sizeof(client_address);	

	// Construct the server sockaddr_in structure 
	memset(&server_address, 0, sizeof(server_address));   /* Clear struct */
	server_address.sin_family = AF_INET;                  /* Internet/IP */
	server_address.sin_addr.s_addr = INADDR_ANY;          /* Any IP address */
	server_address.sin_port = htons(atoi(argv[1]));       /* server port */

	// Bind the socket
	if (bind(sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
		perror("bind");
		exit(EXIT_FAILURE);
	}	
	
	// listen: make socket passive and set length of queue
	if (listen(sock, 64) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	
	cout << "File Server listening on port: " << argv[1] << endl;

	// Run until cancelled 
	while (true) {
		int connSock=accept(sock, (struct sockaddr *) &client_address, &addrlen);
		if (connSock < 0) {
			perror("accept");
			exit(EXIT_FAILURE);
		}
		// fork
		if (fork()) { 	    // parent process
			close(connSock);
		} else { 			// child process
			processClientRequest(connSock);
		}
	}	
	close(sock);
	return 0;
}

