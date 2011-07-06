#include<stdio.h>
#include<math.h>

#define M 3
#define P 101.325  //ѹ����λKpa
#define A 0.001    //����
#define S 1        //����

double a[M][3],k[M],x[M];
double t0,t1,f=0,df=0;
double temp=0;
int i,j;
long n=0;

void intput()           //���뺯��
{
	for(i=0;i<M;i++)
	{
		printf("�������%d���Antoine��ʽ��A,B,Cֵ��\n",i);
		for(j=0;j<3;j++)
        {
			scanf("%lf",&a[i][j]);
        }
	}
	for(i=0;i<M;i++)
	{
		printf("�������%d���Ħ�����ʣ�\n",i);
		scanf("%lf",&x[i]);
	}
	printf("�������¶ȳ�ֵ��\n");
	scanf("%lf",&t1);
}

void newton()           //ţ�ٵ���������
{
	printf("ţ�ٵ�������\n");
	do
	{
		n++;
		t0=t1;
		for(i=0;i<M;i++)
        {
			k[i]=pow(10.0,(2.303*(a[i][0]-a[i][1]/(t0+a[i][2]))))/P;
        }
		for(i=0;i<M;i++)
		{
			temp=k[i]*x[i];
			f=f+temp;
		}
		f=f-1;
		for(i=0;i<M;i++)
		{
			temp=k[i]*x[i]*2.303*a[i][1]/(t0+a[i][2])/(t0+a[i][2]);
			df=df+temp;
		}
		t1=t0-f/df;
	}
	while(fabs(t1-t0)>A);
	printf("�����¶�Ϊ%.1f\n",t1);  //�¶�ȡһλС�����ɸ���
	printf("����������%ld",n);
}


void buchang()               //������or�Բ����
{
	printf("������:\n");
	double sum=0.0;
	do
	{
		n++;
		for(i=0;i<M;i++)
		{
			k[i]=pow(10.0,(2.303*(a[i][0]-a[i][1]/(t1+a[i][2]))))/P;
			sum+=k[i]*x[i];
		}
		if(sum-1>0)
			t1-=S;
		if(sum-1<0)
			t1+=S;

	}
	while(fabs(sum-1)>A);
	printf("�����¶ȣ�%.1f,ѭ��������%ld\n",t1,n);
}


void main()           //������
{
	intput();
	int z;
	printf("��ѡ����ⷽ����1��newton��������2����������3�����ַ���");
	scanf("%d",&z);
	if(z==1)
		newton();
	if(z==2)
		buchang();
	if(z==3)
	{
		newton();
		buchang();
	}
}
