#include<stdio.h>

#define WMAX 20
#defind WMAXL 10
int main(void)
{
    int wordNum;
    int wordCount;
    int passLength;
    char words[WMAX][WMAXL];
    printf("�����뵥������\n");
    scanf("%d",&wordNum);
    wordCount=wordNum;
    printf("�����������������õ��ʣ�\n");
    for(;wordNum!=0;wordNum--)
    {
        printf("ʣ��%d��:",wordNum);
        scanf("%s",words[wordNum]);
    }
    printf("�����������������󳤶ȣ�")
    scnanf("%d",&passLength);

}
