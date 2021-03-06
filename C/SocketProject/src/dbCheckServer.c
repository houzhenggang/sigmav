#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket
#include <stdio.h>        // for printf
#include <stdlib.h>        // for exit
#include <string.h>        // for bzero

#define CHECK_SERVER_PORT    6666
#define LENGTH_OF_LISTEN_QUEUE 20
#define BUFFER_SIZE 1024
#define CHECK_FOLDER    "~/TestFolder"
#define MAX_NAME_LEN 256

int main(int argc, char **argv)
{
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(CHECK_SERVER_PORT);

    int server_socket = socket(AF_INET,SOCK_STREAM,0);
    if( server_socket < 0)
    {
        printf("Create Socket Failed!");
        exit(1);
    }

    if( bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)))
    {
        printf("Server Bind Port : %d Failed!", CHECK_SERVER_PORT);
        exit(1);
    }

    if ( listen(server_socket, LENGTH_OF_LISTEN_QUEUE) )
    {
        printf("Server Listen Failed!");
        exit(1);
    }

    while (1)
    {
        struct sockaddr_in client_addr;
        socklen_t length = sizeof(client_addr);

        int new_server_socket = accept(server_socket,(struct sockaddr*)&client_addr,&length);
        if ( new_server_socket < 0)
        {
            break;
        }

        char buffer[BUFFER_SIZE];
        bzero(buffer, BUFFER_SIZE);
        strcpy(buffer,"Init");
        send(new_server_socket,buffer,BUFFER_SIZE,0);

        while(1)
        {
            bzero(buffer,BUFFER_SIZE);
            length = recv(new_server_socket,buffer,BUFFER_SIZE,0);
            if (length < 0)
            {
                printf("Server Recieve Data Failed!\n");
                break;
            }
            if(strcmp(buffer,"Check") != 0)
            {
                printf("Not checking ...\n");
                break;
            }
            else
            {
                //Check Folder
                struct stat statbuf;
                struct dirent *dirp;
                DIR           *dp;
                if (lstat(CHECK_FOLDER,&statbuf) < 0)
                {
                    printf("CHECK_FOLDER stat error\n");
                    break;
                }
                if (S_ISDIR(statbuf.st_mode) == 0)
                {
                    printf("CHECK_FOLDER is not a directory\n");
                    break;
                }

                if((dp = opendir(CHECK_FOLDER)) != NULL)
                {
                    printf("opendir error!\n");
                    break;
                }

                while( (dirp = readdir(dp)) != NULL )
                {
                    int goodList=0;
                    if (chdir(CHECK_FOLDER) < 0)
                    {
                        printf("Chdir to CHECK_FOLDER error\n");
                        break;
                    }

                    if(strcmp(dirp->d_name,".") == 0 || strcmp(dirp->d_name,"..") == 0)
                    {
                        continue;
                    }
                    if (lstat(dirp->d_name,&statbuf) < 0)
                    {
                        printf("%s stat error\n",dirp->d_name);
                        break;
                    }
                    if (S_ISDIR(statbuf.st_mode) == 0)
                    {
                        continue;
                    }

                    if(chdir(dirp->d_name) < 0)
                    {
                        printf("chdir to %s error\n",dirp->d_name);
                        continue;
                    }
                    int logFd;
                    if(logFd = open(dirp->d_name,O_RDONLY) < 0)
                    {
                        printf("open file %s error\n",dirp->d_name);
                        continue;
                    }

                    char listedName[MAX_NAME_LEN];
                    int  listedSize;

                    while(fscanf(logFd,"%s %d",listedName,&listedSize) != EOF)
                    {
                        if(lstat(listedName,&statbuf) <0)
                        {
                            printf("listed file %s stat error!\n",listedName);
                            goodList=1;
                            break;
                        }

                        if(statbuf.st_size != listedSize)
                        {
                            printf("listed file %s file size mismatch\n",listedName);
                            goodList=1;
                            break;
                        }
                    }

                    if(goodList == 1)
                    {
                        bzero(buffer,BUFFER_SIZE);
                        strcpy(buffer,"Error");
                        send(new_server_socket,buffer,BUFFER_SIZE,0);
                        bzero(buffer,BUFFER_SIZE);
                        strcpy(buffer,"Error list:");
                        strcpy(buffer,dirp->d_name);
                        send(new_server_socket,buffer,BUFFER_SIZE,0);
                        goodList = 0;
                    }
                    else
                    {
                        bzero(buffer,BUFFER_SIZE);
                        strcpy(buffer,"Succeed");
                        send(new_server_socket,buffer,BUFFER_SIZE,0);
                        bzero(buffer,BUFFER_SIZE);
                        strcpy(buffer,dirp->d_name);
                        send(new_server_socket,buffer,BUFFER_SIZE,0);
                        if(lseek(logFd,0,SEEK_SET) == -1)
                        {
                            printf("lseek error!\n");
                            break;
                        }
                        bzero(buffer,BUFFER_SIZE);
                        while(fgets(buffer,BUFFER_SIZE,logFd) != NULL)
                        {
                            send(new_server_socket,buffer,BUFFER_SIZE,0);
                            bzero(buffer,BUFFER_SIZE);
                        }
                        strcpy(buffer,"EOF");
                        send(new_server_socket,buffer,BUFFER_SIZE,0);
                    }
                    close(logFd);
                }
                close(dp);
            }
        }
        close(new_server_socket);
        printf("Socket Disconnect\n");
    }
    close(server_socket);
    return 0;
}

