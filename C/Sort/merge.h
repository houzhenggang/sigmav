/*�������򷨺��� 2010-03-14*/
#include <malloc.h>
#include <limits.h>
//��������
int merge(int begin,int middle,int end,int num[])
{
    int dstCounter=begin;
    int leftLength=middle-begin+1;
    int rightLength=end-middle;
    int * leftArray=(int *)malloc(sizeof(int)*(leftLength+1));
    int * rightArray=(int *)malloc(sizeof(int)*(rightLength+1));
    int leftCounter=leftLength;
    int rightCounter=rightLength;
    leftArray[leftCounter--]=INT_MAX;
    rightArray[rightCounter--]=INT_MAX;
    for(;leftCounter>=0;leftCounter--)
    {
        leftArray[leftCounter]=num[begin+leftCounter];
    }
    for(;rightCounter>=0;rightCounter--)
    {
        rightArray[rightCounter]=num[middle+1+rightCounter];
    }
    int i=0,j=0;
    for(;dstCounter<=end;dstCounter++)
    {
        if(leftArray[i]<rightArray[j])
        {
            num[dstCounter]=leftArray[i++];
        }
        else
        {
            num[dstCounter]=rightArray[j++];
        }
    }
    return 0;
}

//��Χ���������㷨�������������ʼλ�ý��иöε�����
int mergeSortRange(int begin,int end,int num[])
{
    //����ʼλ�������λ�ò�һ��ʱ�������ų���Ԫ�����⣩
    if(begin<end)
    {
        //��ȡ�е�
        int middle=(begin+end)/2;
        //�������
        mergeSortRange(begin,middle,num);
        //�Ҳ�����
        mergeSortRange(middle+1,end,num);
        //�ź�������ҽ��й�������
        merge(begin,middle,end,num);
    }
    return 0;
}

//���㷨
int mergeSort(int number,int num[])
{
    //ת��Ϊ��Χ���������㷨
    mergeSortRange(0,number-1,num);
    return 0;
}
