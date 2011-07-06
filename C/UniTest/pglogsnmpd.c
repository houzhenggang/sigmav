#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <sys/stat.h>
#include <errno.h>

/*#define DEBUG*/

#define FILENAME_LEN 256
#define CONTENT_LEN 1024
#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024*(EVENT_SIZE + 16))

int main (int argc, char const* argv[])
{
    int length,i=0;
    int fd;
    int wd;

    int ifd;

    char buffer[BUF_LEN];
    char * dirpath="/opt/PostgreSQL/9.0/data/pg_log";

    DIR * dir;
    struct dirent * pdir;

    time_t newest = 0;
    char   newestFile[FILENAME_LEN];
    struct stat  fileStat;
    off_t  newestFileSize;
    char   newContentBuf[CONTENT_LEN];

    //Init inotify
    fd=inotify_init();

#ifdef DEBUG/*{{{*/
    printf("Init inotify ....\n");
#endif/*}}}*/

    if(fd < 0)
    {
        perror("inotify_init error!");
        exit(1);
    }

    if((dir=opendir(dirpath)) == NULL)
    {
        perror("Open dir error!");
        exit(1);
    }

    if(chdir(dirpath) == -1)
    {
        perror("change dir error!");
        exit(1);
    }

    while((pdir=readdir(dir)) != NULL)
    {
        if(strcmp(pdir->d_name,".")==0||strcmp(pdir->d_name,"..")==0||pdir->d_type==DT_DIR)
        {
            continue;
        }

        if((ifd=open(pdir->d_name,O_RDONLY)) == -1)
        {
            perror("Open file error! 0");
            continue;
        }
        if(fstat(ifd,&fileStat) == -1)
        {
            perror("Get file stat error!");
            continue;
        }

        close(ifd);

        if(fileStat.st_mtime > newest)
        {
            newest=fileStat.st_mtime;
            strcpy(newestFile,pdir->d_name);
            newestFileSize=fileStat.st_size;
        }
    }
#ifdef DEBUG/*{{{*/
    printf("newest file time:%ld\n",newest);
    printf("newest file name:%s\n",newestFile);
    printf("newest file size:%d\n",newestFileSize);
#endif/*}}}*/
    wd=inotify_add_watch(fd,dirpath
                         /*"/opt/PostgreSQL/9.0/data/pg_log"*/
                         ,IN_MODIFY|IN_CREATE|IN_DELETE);
#ifdef DEBUG/*{{{*/
    printf("Watching dir: %s\n",dirpath);
#endif/*}}}*/


    while(1)
    {

        i=0; //counter

        length=read(fd,buffer,BUF_LEN);

#ifdef DEBUG/*{{{*/
        printf("-----------\nlength read:%d\n",length);
#endif/*}}}*/

        if (length < 0)
        {
            perror("read error!");
            continue;
        }

        while(i<length)
        {
            struct inotify_event *event = (struct inotify_event *)  &buffer[i];
            if(event->len)
            {
                if(event->mask & IN_CREATE)
                {
                    /*if(event->mask & IN_ISDIR)*//*{{{*/
                    /*{*/
                    /*printf("Dir %s is created\n",event->name);*/
                    /*}*/
                    /*else*//*}}}*/
                    if(!(event->mask & IN_ISDIR))
                    {
#ifdef DEBUG/*{{{*/
                        printf("created log file:%s\n",event->name);
#endif/*}}}*/
                        if((ifd=open(event->name,O_RDONLY)) == -1)
                        {
                            perror("Open new file error");
                            continue;
                        }
                        if(fstat(ifd,&fileStat) == -1)
                        {
                            perror("Get file stat error!");
                            continue;
                        }
                        close(ifd);
#ifdef DEBUG/*{{{*/
                        printf("closed log\n");
#endif/*}}}*/
                        if(fileStat.st_mtime > newest)
                        {
                            newest=fileStat.st_mtime;
#ifdef DEBUG/*{{{*/
                            printf("newest file time:%ld\n",newest);
#endif/*}}}*/
                            strcpy(newestFile,event->name);
#ifdef DEBUG/*{{{*/
                            printf("newest file name:%s\n",newestFile);
#endif/*}}}*/
                            newestFileSize=fileStat.st_size;
#ifdef DEBUG/*{{{*/
                            printf("newest file size:%d\n",newestFileSize);
#endif/*}}}*/
                        }
                    }
                }
                else if(event->mask & IN_MODIFY)
                {
                    /*if(event->mask & IN_ISDIR)*//*{{{*/
                    /*{*/
                    /*printf("Dir %s is modified\n",event->name);*/
                    /*}*/
                    /*else*//*}}}*/
                    if(!(event->mask & IN_ISDIR))
                    {
#ifdef DEBUG/*{{{*/
                        printf("modified log file :%s\n",event->name);
#endif/*}}}*/
                        if((ifd=open(event->name,O_RDONLY)) == -1)
                        {
                            perror("Open modified file error");
                            continue;
                        }
                        if(fstat(ifd,&fileStat) == -1)
                        {
                            perror("Get file stat error!");
                            continue;
                        }

                        if(strcmp(event->name,newestFile)!=0)
                        {
#ifdef DEBUG/*{{{*/
                            printf(">>%s\n<<%s\n",event->name,newestFile);
                            printf("modified new file!\n");
#endif/*}}}*/
                            close(ifd);

#ifdef DEBUG/*{{{*/
                            printf("closed log\n");
#endif/*}}}*/
                            if(fileStat.st_mtime > newest)
                            {
                                newest=fileStat.st_mtime;
#ifdef DEBUG/*{{{*/
                                printf("newest file time:%ld\n",newest);
#endif/*}}}*/
                                strcpy(newestFile,event->name);
#ifdef DEBUG/*{{{*/
                                printf("newest file name:%s\n",newestFile);
#endif/*}}}*/
                                newestFileSize=fileStat.st_size;
#ifdef DEBUG/*{{{*/
                                printf("newest file size:%d\n",newestFileSize);
#endif/*}}}*/
                            }
                        }
                        else
                        {

                            off_t newContentSize = fileStat.st_size - newestFileSize;
#ifdef DEBUG/*{{{*/
                            printf("new content size :%d\n",newContentSize);
                            printf("last fileSize:%d\n",newestFileSize);
                            printf("new  fileSize:%d\n",fileStat.st_size);
#endif/*}}}*/
                            if(lseek(ifd,-newContentSize,SEEK_END) == -1)
                            {
                                perror("Lseek error!");
                                continue;
                            }
                            if(read(ifd,&newContentBuf,newContentSize) == -1)
                            {
                                perror("Read error!");
                                continue;
                            }
                            if(lseek(ifd,0,SEEK_END) == -1)
                            {
                                perror("Lseek error!");
                                continue;
                            }
                            close(ifd);

                            newestFileSize = fileStat.st_size;
                            newest = fileStat.st_mtime;

                            printf("===================================\n");
                            newContentBuf[newContentSize]='\0';
                            printf(newContentBuf);

                            //Do your stuff here
                            //with newContentBuf

                        }
                    }
                }
                /*else if(event->mask & IN_DELETE)*//*{{{*/
                /*{*/
                /*if(event->mask & IN_ISDIR)*/
                /*{*/
                /*printf("Dir %s is deleted\n",event->name);*/
                /*}*/
                /*else*/
                /*{*/
                /*printf("File %s is deleted\n",event->name);*/
                /*}*/
                /*}*//*}}}*/
            }//if event>len
            i +=EVENT_SIZE + event->len;
        }//while i<length
    } //while 1

    inotify_rm_watch(fd,wd);
    close(fd);

    exit(0);
}

