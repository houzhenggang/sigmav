/* ����read��writeϵͳ���ôӱ�׼�������û������벢�������������׼��� */
/* ���û����������Ctrl+Z��ʾ���������ʱ�������˳� */

# include <unistd.h>
# include <stdio.h>

# define MAX_BUF_LEN 256

int main()
{
    /* ������� */
    char buff[MAX_BUF_LEN];

    /* code in below area */
    int ret;
    while((ret=read(STDIN_FILENO,buff,sizeof(buff)))>0)
    {
        ret=read(STDIN_FILENO,buff,sizeof(buff));
       // printf("%d\n",STDIN_FILENO);
       // printf("%d\n",STDOUT_FILENO);
       // printf("%d\n",ret);
        write(STDOUT_FILENO,buff,ret);
    }
    /* code in above area */

    return 0;
}
