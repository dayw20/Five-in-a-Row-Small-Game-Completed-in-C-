#include<winsock.h>		/*����winsockͷ�ļ�*/
#pragma comment(lib,"ws2_32.lib")
#include<stdio.h> 
#include <graphics.h>
#include<string.h>
#include<bits/stdc++.h>

using namespace std;

#define MAXN 1000

FILE *fp;

struct Node
{
	char name[100];

	int mark;

}three[3];

void choose();

void explation();

void scoring(int n);

void select(); //ѡ������ģʽ 

int visb[MAXN][MAXN];//��¼����

int visw[MAXN][MAXN];//��¼����

int bwin;//��Ǻ����ʤ

int wwin;//��ǰ����ӻ�ʤ

int step;  //��¼���� 

int steppc;  //��¼�˻�����

int flag;   //�жϽ����˻������˶�ս 

int flag2;//�˳�ģʽ

int px, py;

int player;

static int MAN = 1;

static int COM = -1;

int CD=0; 

char IP[100];

mouse_msg msg = { 0 };

int zqy[2];

struct point

{

	int x;

	int y;

};



int board[MAXN][MAXN];//1�Ǻ��壬-1�ǰ��壬0����ʾû��



void CreateMenus()//���˵�

{




	wwin = 0;

	bwin = 0;

	memset(visb, 0, sizeof(visb));

	memset(visw, 0, sizeof(visw));

	flag = 0;

	flag2 = 0;//�˳�ģʽ



	initgraph(1000, 600, 0);

	//	setcolor(EGERGB(0x0, 0xFF, 0x0));//������ɫ

	  //  setbkmode(TRANSPARENT);//�������͸����

	//	setfont(100, 60, "����");

	//	outtextxy(200, 0, "��������Ϸ");

	setcolor(EGERGB(228, 228, 228));

	setfont(60, 30, "����");

	outtextxy(420, 150, "�˻���ս");

	setcolor(EGERGB(228, 228, 228));

	setfont(60, 30, "����");

	outtextxy(420, 240, "���˶�ս");

	setcolor(EGERGB(228, 228, 228));

	setfont(60, 30, "����");

	outtextxy(420, 330, "��Ϸ����");

	setcolor(EGERGB(228, 228, 228));

	setfont(60, 30, "����");

	outtextxy(420, 420, "�˳���Ϸ");

	setcolor(EGERGB(228, 228, 228));

	setbkmode(TRANSPARENT);

	setfont(35, 14, "����");

	//  outtextxy(710,500,"Author: Farmer Three");




}





int jud()//�����ж�

{

	for (int i = 60; i <= 480; i++)

	{

		for (int j = 60; j <= 480; j++)

		{

			//�жϺ���

			if (visb[i][j] && visb[i + 30][j] && visb[i + 60][j] && visb[i - 30][j] && visb[i - 60][j]) return 1;//�����ʤ

			else if (visb[i][j] && visb[i][j + 30] && visb[i][j + 60] && visb[i][j - 30] && visb[i][j - 60]) return 1;//�����ʤ

			else if (visb[i][j] && visb[i + 30][j + 30] && visb[i + 60][j + 60] && visb[i - 30][j - 30] && visb[i - 60][j - 60]) return 1;//б��Ϊ1

			else if (visb[i][j] && visb[i - 30][j + 30] && visb[i - 60][j + 60] && visb[i + 30][j - 30] && visb[i + 60][j - 60]) return 1;//б��Ϊ-1

			//�жϰ���

			if (visw[i][j] && visw[i + 30][j] && visw[i + 60][j] && visw[i - 30][j] && visw[i - 60][j]) return 2;//�����ʤ

			else if (visw[i][j] && visw[i][j + 30] && visw[i][j + 60] && visw[i][j - 30] && visw[i][j - 60]) return 2;//�����ʤ

			else if (visw[i][j] && visw[i + 30][j + 30] && visw[i + 60][j + 60] && visw[i - 30][j - 30] && visw[i - 60][j - 60]) return 2;//б��Ϊ1

			else if (visw[i][j] && visw[i - 30][j + 30] && visw[i - 60][j + 60] && visw[i + 30][j - 30] && visw[i + 60][j - 60]) return 2;//б��Ϊ-1

		}

	}

}



int judpc()//�˻��ж�

{

	for (int i = 60; i <= 480; i += 30)

	{

		for (int j = 60; j <= 480; j += 30)

		{

			//�жϺ���

			if (board[i][j] == 1 && board[i + 30][j] == 1 && board[i + 60][j] == 1 && board[i - 30][j] == 1 && board[i - 60][j] == 1) return 1;//�����ʤ

			else if (board[i][j] == 1 && board[i][j + 30] == 1 && board[i][j + 60] == 1 && board[i][j - 30] == 1 && board[i][j - 60] == 1) return 1;//�����ʤ

			else if (board[i][j] == 1 && board[i + 30][j + 30] == 1 && board[i + 60][j + 60] == 1 && board[i - 30][j - 30] == 1 && board[i - 60][j - 60] == 1) return 1;//б��Ϊ1

			else if (board[i][j] == 1 && board[i - 30][j + 30] == 1 && board[i - 60][j + 60] == 1 && board[i + 30][j - 30] == 1 && board[i + 60][j - 60] == 1) return 1;//б��Ϊ-1

			//�жϰ�����

			if (board[i][j] == -1 && board[i + 30][j] == -1 && board[i + 60][j] == -1 && board[i - 30][j] == -1 && board[i - 60][j] == -1) return 2;//�����ʤ

			else if (board[i][j] == -1 && board[i][j + 30] == -1 && board[i][j + 60] == -1 && board[i][j - 30] == -1 && board[i][j - 60] == -1) return 2;//�����ʤ

			else if (board[i][j] == -1 && board[i + 30][j + 30] == -1 && board[i + 60][j + 60] == -1 && board[i - 30][j - 30] == -1 && board[i - 60][j - 60] == -1) return 2;//б��Ϊ1

			else if (board[i][j] == -1 && board[i - 30][j + 30] == -1 && board[i - 60][j + 60] == -1 && board[i + 30][j - 30] == -1 && board[i + 60][j - 60] == -1) return 2;//б��Ϊ-1

		}

	}

}



void CreatePCBoard()//�˻�����

{

	setbkcolor(EGERGB(173, 92, 45));//���ñ�����ɫ

	setcolor(BLACK);

	for (int i = 60; i < 510; i += 30)

	{

		line(i, 60, i, 480);

	}

	for (int j = 60; j < 510; j += 30)

	{

		line(60, j, 480, j);

	}

	setcolor(EGERGB(0xFF, 0x0, 0x0));

	setbkmode(TRANSPARENT);

	setfont(40, 15, "����");

	outtextxy(750, 100, "PVP");

	setfillcolor(EGERGB(0xFF, 0x0, 0x0));

	setcolor(EGERGB(0xFF, 0xFF, 0x0));

	xyprintf(650, 40, "��ǰ��������0��");

	//P1��Ϣ

	setcolor(EGERGB(255, 255, 255));

	setfont(40, 15, "����");

	xyprintf(700, 150, "PC(��):0");

	//P2��Ϣ

	setcolor(EGERGB(0, 0, 0));

	setfont(40, 15, "����");

	xyprintf(700, 200, "Player(��):0");



	setfillcolor(EGERGB(0xFF, 0x0, 0x0));

	bar(700, 400, 850, 450);

	setcolor(EGERGB(0x0, 0xFF, 0x0));

	outtextxy(750, 400, "�˳�");

}



void CreatePVPboard()//��������

{

	setbkcolor(EGERGB(173, 92, 45));//���ñ�����ɫ

	setcolor(BLACK);







	for (int i = 60; i < 510; i += 30)

	{

		line(i, 60, i, 480);

	}

	for (int j = 60; j < 510; j += 30)

	{

		line(60, j, 480, j);

	}
















	setcolor(EGERGB(0xFF, 0x0, 0x0));

	setbkmode(TRANSPARENT);

	setfont(40, 15, "����");

	outtextxy(750, 100, "PVP");

	setfillcolor(EGERGB(0xFF, 0x0, 0x0));

	setcolor(EGERGB(0xFF, 0xFF, 0x0));

	xyprintf(650, 40, "��ǰ��������0��");

	//P1��Ϣ

	setcolor(EGERGB(255, 255, 255));

	setfont(40, 15, "����");

	xyprintf(700, 150, "P1(��):0");

	//P2��Ϣ

	setcolor(EGERGB(0, 0, 0));

	setfont(40, 15, "����");

	xyprintf(700, 200, "P2(��):0");



	setfillcolor(EGERGB(0xFF, 0x0, 0x0));

	bar(700, 400, 850, 450);

	setcolor(EGERGB(0x0, 0xFF, 0x0));

	outtextxy(750, 400, "�˳�");

}



void PVPshow()//��ʾ��ǰ����״��

{

	setbkcolor(EGERGB(173, 92, 45));//���ñ�����ɫ

	setcolor(BLACK);



	PIMAGE img[2];

	img[0] = newimage();
	img[1] = newimage();
	getimage(img[0], "drawing\\hei.png");
	getimage(img[1], "drawing\\bai.png");





	for (int i = 60; i < 510; i += 30)

	{

		line(i, 60, i, 480);

	}

	for (int j = 60; j < 510; j += 30)

	{

		line(60, j, 480, j);

	}



	for (int i = 60; i <= 480; i += 30)

	{

		for (int j = 60; j <= 480; j += 30)

		{

			if (visw[i][j])

			{
				putimage(i - 15, j - 15, img[1]);
			}

			if (visb[i][j])

			{
				putimage(i - 15, j - 15, img[0]);
			}

		}

	}

	setcolor(EGERGB(0xFF, 0xFF, 0x0));



	setbkmode(TRANSPARENT);

	setfont(40, 15, "����");

	xyprintf(650, 40, "��ǰ��������%d��", step - 1);



	setcolor(EGERGB(0xFF, 0x0, 0x0));

	setbkmode(TRANSPARENT);

	setfont(40, 15, "����");

	outtextxy(750, 100, "PVP");



	//p1:

	setcolor(EGERGB(255, 255, 255));

	setfont(40, 15, "����");

	xyprintf(700, 150, "P1(��):%d", (step - 1) / 2 + (step - 1) % 2);


	//p2

	setcolor(EGERGB(0, 0, 0));

	setfont(40, 15, "����");

	xyprintf(700, 200, "P2(��):%d", (step - 1) / 2);



	setfillcolor(EGERGB(0xFF, 0x0, 0x0));

	bar(700, 400, 850, 450);

	setcolor(EGERGB(0x0, 0xFF, 0x0));

	outtextxy(750, 400, "�˳�");

	if (bwin)

	{

		setcolor(EGERGB(0, 0, 0));

		setbkmode(TRANSPARENT);

		setfont(20, 10, "����");

		outtextxy(630, 350, "�����ʤ������·��ص����˵�");

	}

	else if (wwin)

	{

		setcolor(EGERGB(255, 255, 255));

		setbkmode(TRANSPARENT);

		setfont(20, 10, "����");

		outtextxy(650, 350, "�����ʤ,����·��˳����ص����˵�");

	}

}

void PVEshow()//��ʾ��ǰ�˻�����״��

{

	PIMAGE img[2];

	img[0] = newimage();
	img[1] = newimage();
	getimage(img[0], "drawing\\hei.png");
	getimage(img[1], "drawing\\bai.png");



	setbkcolor(EGERGB(173, 92, 45));//���ñ�����ɫ

	setcolor(BLACK);

	for (int i = 60; i < 510; i += 30)

	{

		line(i, 60, i, 480);

	}

	for (int j = 60; j < 510; j += 30)

	{

		line(60, j, 480, j);

	}



	for (int i = 60; i <= 480; i++)

	{

		for (int j = 60; j <= 480; j++)

		{

			if (board[i][j] == -1)

			{


				putimage(i - 15, j - 15, img[1]);
			}

			if (board[i][j] == 1)

			{

				putimage(i - 15, j - 15, img[0]);
			}

		}

	}

	setcolor(EGERGB(0xFF, 0xFF, 0x0));



	setbkmode(TRANSPARENT);

	setfont(40, 15, "����");

	xyprintf(650, 40, "��ǰ��������%d��", step + steppc);



	setcolor(EGERGB(0xFF, 0x0, 0x0));

	setbkmode(TRANSPARENT);

	setfont(40, 15, "����");

	outtextxy(750, 100, "PVP");



	//p1:

	setcolor(EGERGB(255, 255, 255));

	setfont(40, 15, "����");

	xyprintf(700, 150, "PC(��):%d", steppc);



	//p2

	setcolor(EGERGB(0, 0, 0));

	setfont(40, 15, "����");

	xyprintf(700, 200, "Player(��):%d", step);



	setfillcolor(EGERGB(0xFF, 0x0, 0x0));

	bar(700, 400, 850, 450);

	setcolor(EGERGB(0x0, 0xFF, 0x0));

	outtextxy(750, 400, "�˳�");







	setfillcolor(EGERGB(0xFF, 0x0, 0x0));

	bar(700, 280, 850, 330);

	setcolor(EGERGB(0x0, 0xFF, 0x0));

	outtextxy(715, 280, "����һ��");










	if (bwin)

	{

		setcolor(EGERGB(0, 0, 0));

		setbkmode(TRANSPARENT);

		setfont(20, 10, "����");

		outtextxy(630, 350, "���(��)��ʤ������·��ص����˵�");

		if (CD)
		{

			setfillcolor(EGERGB(0xFF, 0x0, 0x0));

			bar(700, 500, 850, 550);

			setfont(40, 15, "����");

			setcolor(EGERGB(0x0, 0xFF, 0x0));

			outtextxy(710, 500, "��¼����");

		}

	}

	else if (wwin)

	{

		setcolor(EGERGB(255, 255, 255));

		setbkmode(TRANSPARENT);

		setfont(20, 10, "����");

		outtextxy(650, 350, "����(��)��ʤ,����·��˳����ص����˵�");

	}

}

void inter1()//�������˶�ս

{

	int k = 0;

	int b1, b2, b3, i, j;

	int a[10];

	int net[2];

	net[0] = 0;

	net[1] = 0;

	bwin = 0;

	wwin = 0;

	CreatePVPboard();

	step = 1;//������ʼ��

	/*-----------------------------------------*/
	/*------------�������---------------------*/
	/*-----------------------------------------*/
	char Sendbuf[100];		/*�������ݵĻ�����*/
	char Sendbuf1[100];		/*�������ݵĻ�����*/
	char Receivebuf[100];	/*�������ݵĻ�����*/
	int SendLen;			/*�������ݵĳ���*/
	int	ReceiveLen;			/*�������ݵĳ���*/
	int Length;				/*��ʾSOCKADDR�Ĵ�С*/

	SOCKET socket_server;	/*����������׽���*/
	SOCKET socket_receive;  /*�������������׽���*/

	SOCKADDR_IN Server_add;	/*��������ַ��Ϣ�ṹ*/
	SOCKADDR_IN Client_add;	/*�ͻ��˵�ַ��Ϣ�ṹ*/

	WORD wVersionRequested;	/*�֣�word����unsigned short*/
	WSADATA wsaData;		/*��汾��Ϣ�ṹ*/
	int error;				/*��ʾ����*/

	/*-----------------------------------------*/
	/*------------��ʼ���׽��ֿ�---------------*/
	/*-----------------------------------------*/
	/*����汾���͡��������ֽ���ϳ�һ���֣�ǰ���ǵ��ֽڣ������Ǹ��ֽ�*/
	wVersionRequested = MAKEWORD(2, 2);
	/*�����׽��ֿ⣬��ʼ��Ws2_32.dll��̬���ӿ�*/
	error = WSAStartup(wVersionRequested, &wsaData);
	if (error != 0)
	{
		outtextxy(500, 400, "�����׽���ʧ�ܣ�");
		//	return 0;	/*�������*/
	}
	/*�ж�������صİ汾���Ƿ����Ҫ��*/
	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();	/*�����ϣ��ر��׽��ֿ�*/
	//	return 0;		/*�������*/
	}

	/*-----------------------------------------*/
	/*------------�������ӵ�ַ-----------------*/
	/*-----------------------------------------*/
	Server_add.sin_family = AF_INET;/*��ַ���壬���ڱ�����AF_INET��ע��ֻ�����������������ֽ�˳��*/
	Server_add.sin_addr.S_un.S_addr = htonl(INADDR_ANY);/*������ַ*/
	Server_add.sin_port = htons(8888);/*�˿ں�*/

	/*------------�����׽���-------------------*/
	/*AF_INET��ʾָ����ַ�壬SOCK_STREAM��ʾ��ʽ�׽���TCP���ض��ĵ�ַ������ص�Э�顣*/
	socket_server = socket(AF_INET, SOCK_STREAM, 0);

	/*-----------------------------------------*/
	/*---���׽��ֵ����ص�ĳ����ַ�Ͷ˿���----*/
	/*-----------------------------------------*/
			/*socket_serverΪ�׽��֣�(SOCKADDR*)&Server_addΪ��������ַ*/
	if (bind(socket_server, (SOCKADDR*)&Server_add, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		outtextxy(500, 400, "��ʧ��\n");
	}

	/*-----------------------------------------*/
	/*------------�����׽���Ϊ����״̬---------*/
	/*-----------------------------------------*/
		/*����״̬��Ϊ������׼�������ȴ�����ĿΪ5*/
	if (listen(socket_server, 5) < 0)
	{
		outtextxy(500, 400, "����ʧ��\n");
	}

	/*-----------------------------------------*/
	/*------------��������---------------------*/
	/*-----------------------------------------*/
	Length = sizeof(SOCKADDR);
	/*���ܿͻ��˵ķ�������,�ȴ��ͻ��˷���connect����*/
	socket_receive = accept(socket_server, (SOCKADDR*)&Client_add, &Length);
	if (socket_receive == SOCKET_ERROR)
	{
		outtextxy(500, 400, "��������ʧ��");
	}

	/*-----------------------------------------*/
	/*--------------��������-------------------*/
	/*-----------------------------------------*/



	int Flag = 0;

	int jb = 0;













	for (; is_run(); )

	{





		msg = getmouse();

		//�߽�����
		if (jb > 0 && (int)msg.is_left() && (int)msg.x >= ((int)msg.x - (int)msg.x % 30) - 14 && (int)msg.x <= ((int)msg.x - (int)msg.x % 30) + 14 && (int)msg.y >= ((int)msg.y - (int)msg.y % 30) - 14 && (int)msg.y <= ((int)msg.y - (int)msg.y % 30) + 14 && visw[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] == 0 && visb[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] == 0 && msg.x >= 50 && msg.x <= 485 && msg.y >= 55 && msg.y <= 485)
		{

			step++;//ÿ��һ��������+1

			k++;

			Flag = 1;


			visw[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] = 1;//ż���°���;


			if (jud() == 1) bwin = 1;

			else if (jud() == 2) wwin = 1;


			cleardevice();

			PVPshow();

			//   if(bwin||wwin) break;



		}


		if (jb == 0 || (k % 2 == 0 && k != 0 && Flag == 1))
		{

			jb++;

			if (k % 2 == 0 && k != 0 && Flag == 1)
			{


				Flag = 0;

				net[0] = (int)msg.x - (int)msg.x % 30;

				net[1] = (int)msg.y - (int)msg.y % 30;

				memset(Sendbuf, 0x00, sizeof(char) * 100);
				memset(Sendbuf1, 0x00, sizeof(char) * 100);



				sprintf(Sendbuf, "%d", net[0]);
				sprintf(Sendbuf1, "%d", net[1]);
				strcat(Sendbuf, ",");
				strcat(Sendbuf, Sendbuf1);


				SendLen = send(socket_receive, Sendbuf, 100, 0);
				//��������
				if (SendLen < 0)
				{
			//		outtextxy(600, 400, "����ʧ��!\n");
				}
			}
			if (bwin || wwin)
			{
				closesocket(socket_receive);	/*�ͷſͻ��˵��׽�����Դ*/
				closesocket(socket_server);/*�ͷ��׽�����Դ*/
				WSACleanup();/*�رն�̬���ӿ�*/
				break;
			}

			//--------------�������ݹ���---------------
			ReceiveLen = recv(socket_receive, Receivebuf, 100, 0);	//��������
			if (ReceiveLen < 0)
			{
				outtextxy(600, 400, "�Է����˳�");
				closesocket(socket_receive);	/*�ͷſͻ��˵��׽�����Դ*/
				closesocket(socket_server);/*�ͷ��׽�����Դ*/
				WSACleanup();/*�رն�̬���ӿ�*/
				break;
			}
			else
			{
				step++;
				for (i = 0; i < 10; i++)
				{
					a[i] = 5;

					//cleardevice();
					  //PVPshow();
				}

				for (i = 0; Receivebuf[i] != ','; i++)
				{

					a[i] = Receivebuf[i] - 48;

				}
				b3 = a[2]; b2 = a[1]; b1 = a[0];
				if (b3 != 5)
					net[0] = b1 * 100 + b2 * 10 + b3;
				else
					net[0] = b1 * 10 + b2;

				for (j = i + 1; Receivebuf[j] != '\0'; j++)
					a[j - 1] = Receivebuf[j] - 48;
				b3 = a[i + 2];
				b2 = a[i + 1];
				b1 = a[i];
				if (b3 != 5)
					net[1] = b1 * 100 + b2 * 10 + b3;
				else
					net[1] = b1 * 10 + b2;

				visb[net[0]][net[1]] = 1;



				if (jud() == 1) bwin = 1;

				else if (jud() == 2) wwin = 1;


				cleardevice();
				PVPshow();

				if (bwin || wwin)
				{
					closesocket(socket_receive);	/*�ͷſͻ��˵��׽�����Դ*/
					closesocket(socket_server);/*�ͷ��׽�����Դ*/
					WSACleanup();/*�رն�̬���ӿ�*/
					break;
				}

			}

		}

		if (k % 2 != 0 && k != 0)
			k++;






		if ((bwin || wwin) && (int)msg.is_down() && (int)msg.x >= 700 && msg.x <= 850 && msg.y >= 400 && msg.y <= 450)

		{

			cleardevice();

			CreateMenus();

			choose();

		}




	}

}



int inter2()//�������˶�ս

{
	int jb = 1;

	int k = 0;

	int b1, b2, b3, i, j;

	int a[10];

	int net[2];

	net[0] = 0;

	net[1] = 0;

	bwin = 0;

	wwin = 0;

	CreatePVPboard();

	/*-----------------------------------------*/
/*------------�������---------------------*/
/*-----------------------------------------*/
	char Sendbuf[100];				/*�������ݵĻ�����*/
	char Receivebuf[100];			/*�������ݵĻ�����*/
	int	SendLen;					/*�������ݵĳ���*/
	int	ReceiveLen;					/*�������ݵĳ���*/
	char Receivebuf1[100];			/*�������ݵĻ�����*/
	char Sendbuf1[100];				/*�������ݵĻ�����*/

	SOCKET socket_send;				/*�����׽���*/

	SOCKADDR_IN Server_add;			/*��������ַ��Ϣ�ṹ*/

	WORD wVersionRequested;			/*�֣�word����unsigned short*/
	WSADATA wsaData;				/*��汾��Ϣ�ṹ*/
	int error;						/*��ʾ����*/

	/*-----------------------------------------*/
	/*------------��ʼ���׽��ֿ�---------------*/
	/*-----------------------------------------*/
				/*����汾���͡��������ֽ���ϳ�һ���֣�ǰ���ǵ��ֽڣ������Ǹ��ֽ�*/
	wVersionRequested = MAKEWORD(2, 2);
	/*�����׽��ֿ⣬��ʼ��Ws2_32.dll��̬���ӿ�*/
	error = WSAStartup(wVersionRequested, &wsaData);
	if (error != 0)
	{
		outtextxy(500, 400, "�����׽���ʧ�ܣ�");
		//	return 0;					/*�������*/
	}
	/*�ж�������صİ汾���Ƿ����Ҫ��*/
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();				/*�����ϣ��ر��׽��ֿ�*/
		//return 0;					/*�������*/
	}

	/*-----------------------------------------*/
	/*------------���÷�������ַ---------------*/
	/*-----------------------------------------*/
	Server_add.sin_family = AF_INET;/*��ַ���壬���ڱ�����AF_INET��ע��ֻ�����������������ֽ�˳��*/
	/*�������ĵ�ַ����һ�����ʮ���Ʊ�ʾΪIP��ַ��inet_ntoa�ǽ���ַת���ַ���*/
	Server_add.sin_addr.S_un.S_addr = inet_addr(IP);
	Server_add.sin_port = htons(8888);/*�˿ں�*/

	/*-----------------------------------------*/
	/*-------------�������ӷ�����--------------*/
	/*-----------------------------------------*/
	/*�ͻ��˴����׽��֣����ǲ���Ҫ�󶨵ģ�ֻ��Ҫ�ͷ��������������ӾͿ����ˣ�*/
	/*socket_sendr��ʾ�����׽��֣�Server_add�������ĵ�ַ�ṹ*/
	socket_send = socket(AF_INET, SOCK_STREAM, 0);

	/*-----------------------------------------*/
	/*-------------�����������ӵ��׽���--------*/
	/*-----------------------------------------*/
	/*AF_INET��ʾָ����ַ�壬SOCK_STREAM��ʾ��ʽ�׽���TCP���ض��ĵ�ַ������ص�Э�顣*/
	if (connect(socket_send, (SOCKADDR*)&Server_add, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		jb = 0;

		outtextxy(500, 400, "����ʧ��!");
	}
	else
	{
		outtextxy(500, 400, "���ӳɹ�!");
	}


	int Flag = 0;


	step = 1;//������ʼ��

	for (; is_run();)

	{





		msg = getmouse();

		//�߽�����
		if ((int)msg.is_left() && (int)msg.x >= ((int)msg.x - (int)msg.x % 30) - 14 && (int)msg.x <= ((int)msg.x - (int)msg.x % 30) + 14 && (int)msg.y >= ((int)msg.y - (int)msg.y % 30) - 14 && (int)msg.y <= ((int)msg.y - (int)msg.y % 30) + 14 && visw[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] == 0 && visb[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] == 0 && msg.x >= 50 && msg.x <= 485 && msg.y >= 55 && msg.y <= 485 && jb)
		{

			step++;//ÿ��һ��������+1


			k++;

			Flag = 1;

			visb[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] = 1;//�����º���//ȡ����Ϊ�˾�ȷ����

			if (jud() == 1) bwin = 1;

			else if (jud() == 2) wwin = 1;

			cleardevice();

			PVPshow();

			//    if(bwin||wwin) break;  

		}


		if (k % 2 == 0 && k != 0 && Flag == 1)
		{


			Flag = 0;
			net[0] = (int)msg.x - (int)msg.x % 30;

			net[1] = (int)msg.y - (int)msg.y % 30;

			memset(Sendbuf, 0x00, sizeof(char) * 100);
			memset(Sendbuf1, 0x00, sizeof(char) * 100);



			sprintf(Sendbuf, "%d", net[0]);
			sprintf(Sendbuf1, "%d", net[1]);
			strcat(Sendbuf, ",");
			strcat(Sendbuf, Sendbuf1);


			SendLen = send(socket_send, Sendbuf, 100, 0);

			if (SendLen < 0)
			{
			//	outtextxy(500, 400, "����ʧ��!");
			}
			if (bwin || wwin) break;

			//--------------�������ݹ���---------------
			ReceiveLen = recv(socket_send, Receivebuf, 100, 0);	//��������
			if (ReceiveLen < 0)
			{
						outtextxy(500,400,"�Է����˳�");
						closesocket(socket_send);/*�ͷ��׽�����Դ*/
						WSACleanup();/*�رն�̬���ӿ�*/
						
						break;
			}
			else
			{
				step++;
				for (i = 0; i < 10; i++)

					a[i] = 5;



				for (i = 0; Receivebuf[i] != ','; i++)
				{

					a[i] = Receivebuf[i] - 48;

				}
				b3 = a[2]; b2 = a[1]; b1 = a[0];
				if (b3 != 5)
					net[0] = b1 * 100 + b2 * 10 + b3;
				else
					net[0] = b1 * 10 + b2;

				for (j = i + 1; Receivebuf[j] != '\0'; j++)
					a[j - 1] = Receivebuf[j] - 48;
				b3 = a[i + 2];
				b2 = a[i + 1];
				b1 = a[i];
				if (b3 != 5)
					net[1] = b1 * 100 + b2 * 10 + b3;
				else
					net[1] = b1 * 10 + b2;

				visw[net[0]][net[1]] = 1;



				if (jud() == 1) bwin = 1;

				else if (jud() == 2) wwin = 1;

				cleardevice();

				PVPshow();

				if (bwin || wwin)
				{
					WSACleanup();/*�رն�̬���ӿ�*/

					break;
				}
			}

		}


		if (k % 2 != 0 && k != 0)
			k++;

		if ((bwin || wwin || jb == 0) && (int)msg.is_down() && (int)msg.x >= 700 && msg.x <= 850 && msg.y >= 400 && msg.y <= 450)

		{

			cleardevice();

			CreateMenus();

			choose();

		}






	}

}


void pvp()//���˶�ս

{

	bwin = 0;

	wwin = 0;

	CreatePVPboard();

	step = 1;//������ʼ��

	for (; is_run(); )

	{





		msg = getmouse();

		//�߽�����
		if ((int)msg.is_left() && (int)msg.x >= ((int)msg.x - (int)msg.x % 30) - 14 && (int)msg.x <= ((int)msg.x - (int)msg.x % 30) + 14 && (int)msg.y >= ((int)msg.y - (int)msg.y % 30) - 14 && (int)msg.y <= ((int)msg.y - (int)msg.y % 30) + 14 && visw[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] == 0 && visb[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] == 0 && msg.x >= 50 && msg.x <= 485 && msg.y >= 55 && msg.y <= 485)
		{

			step++;//ÿ��һ��������+1

			if ((step) & 1)

			{

				visb[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] = 1;//�����º���//ȡ����Ϊ�˾�ȷ����
			}

			if ((step) % 2 == 0)

			{

				visw[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] = 1;//ż���°���;

			}

			if (jud() == 1) bwin = 1;

			else if (jud() == 2) wwin = 1;


			cleardevice();

			PVPshow();

			if (bwin || wwin) break;





		}


		if ((int)msg.is_down() && (int)msg.x >= 700 && msg.x <= 850 && msg.y >= 400 && msg.y <= 450)

		{

			cleardevice();

			CreateMenus();

			choose();

		}






	}

}





void pcposition() //�˹�����������ж� 

{



	for (int i = 60; i <= 480; i += 30)

	{

		for (int j = 60; j <= 480; j += 30)

		{



			if (board[i][j] == 1 && board[i + 30][j] == 1)
			{
				if (board[i - 30][j] == 0)
				{
					px = i - 30;
					py = j;
				}
				else
					if (board[i + 60][j] == 0)
					{
						px = i + 60;
						py = j;
					}
			}
			else if (board[i][j] == 1 && board[i][j + 30] == 1)
			{
				if (board[i][j - 30] == 0)
				{
					px = i;
					py = j - 30;
				}
				else if (board[i][j + 60] == 0)
				{
					px = i;
					py = j + 60;
				}
			}
			else
				if (board[i][j] == 1 && board[i + 30][j + 30] == 1)
				{
					if (board[i - 30][j - 30] == 0)
					{
						px = i - 30;
						py = j - 30;
					}
					else
						if (board[i + 60][j + 60] == 0)
						{
							px = i + 60;
							py = j + 60;
						}
				}
				else
					if (board[i][j] == 1 && board[i - 30][j + 30] == 1)
					{
						if (board[i - 60][j + 60] == 0)
						{
							px = i - 60;
							py = j + 60;
						}
						else
							if (board[i + 30][j - 30] == 0)
							{
								px = i + 30;
								py = j - 30;
							}

					}


		}
	}



	if (step == 1)
	{
		srand((int)time(NULL));

		px = rand() % 480 + 60;

		py = rand() % 480 + 60;

		while (px % 30 != 0 || py % 30 != 0 || board[px][py] == 1 || board[px][py] == -1)
		{
			px = rand() % 480 + 60;

			py = rand() % 480 + 60;

		}
	}











	int dx, dy;
	/*
		srand((int)time(NULL));

		px=rand()%480+60;

		py=rand()%480+60;

		while(board[px-px%30][py-py%30]==1||board[px-px%30][py-py%30]==-1)

		{

			px=rand()%421+60;

			py=rand()%421+60;

		}  */

}

int qiju[480][480][8][2];

int oldp[480][480];

int newp[480][480];

int a1[1000][1000];

int a2[1000][1000];

int win;







int caculate(int oldp[480][480], int qiuju[480][480][8][2])//�������

{

	int k;

	int cnt;

	int tx, ty;

	int dirx[8] = { 0,30,30,30,0,-30,-30,-30 };//�˸�����

	int diry[8] = { 30,30,0,-30,-30,-30,0,30 };//�˸�����

	for (int i = 60; i <= 480; i += 30)

	{

		for (int j = 60; j <= 480; j += 30)

		{

			if (oldp[i][j] == 0)//�˴�Ϊ��

			{

				for (int k = 0; k < 8; k++)

				{

					tx = i;

					ty = j;

					cnt = 0;

					for (int t = 0; t < 5; t++)

					{

						tx += dirx[k];

						ty += diry[k];

						if (tx < 60 || tx>480 || ty < 60 || ty>480)

						{

							break;

						}

						if (oldp[tx][ty] == 1)//����

						{

							cnt++;

						}

						else break;

					}

					qiju[i][j][k][0] = cnt;

					//����

					cnt = 0;

					tx = i;

					ty = j;

					for (int t = 0; t < 5; t++)

					{

						tx += dirx[k];

						ty += diry[k];

						if (tx < 60 || tx>480 || ty < 60 || ty>480)

						{

							break;

						}

						if (oldp[tx][ty] == -1)

						{

							cnt++;

						}

						else break;

					}

					qiju[i][j][k][1] = cnt;

				}

			}

		}

	}

}



int naiveline()

{

	for (int i = 60; i <= 480; i += 30)

	{

		for (int j = 60; j <= 480; j += 30)

		{

			if (board[i][j] == 0)

			{

				int win = 0;

				for (int k = 0; k < 4; k++)

				{

					if (qiju[i][j][k][0] + qiju[i][j][k + 4][0] >= 4)

					{

						win += 10000;

					}

					else if (qiju[i][j][k][0] + qiju[i][j][k + 4][0] == 3)

					{

						win += 1000;

					}

					else if (qiju[i][j][k][0] + qiju[i][j][k + 4][0] == 2)

					{

						win += 100;

					}

					else if (qiju[i][j][k][0] + qiju[i][j][k + 4][0] == 1)

					{

						win += 10;

					}

				}

				a1[i][j] = win;//����

				win = 0;

				for (int k = 0; k < 4; k++)

				{

					if (qiju[i][j][k][1] + qiju[i][j][k + 4][1] >= 4)

					{

						win += 10000;

					}

					else if (qiju[i][j][k][1] + qiju[i][j][k + 4][1] == 3)

					{

						win += 1000;

					}

					else if (qiju[i][j][k][1] + qiju[i][j][k + 4][1] == 2)

					{

						win += 100;

					}

					else if (qiju[i][j][k][1] + qiju[i][j][k + 4][1] == 1)

					{

						win += 10;

					}

				}

				a2[i][j] = win;//������

			}

		}

	}

}



void AIprotect()//������AI

{

	int x, y;

	int k = 0;

	int x1 = 270, y1 = 270;

	int x2 = 270, y2 = 270;



	for (int i = 60; i <= 480; i += 30)

	{

		for (int j = 60; j <= 480; j += 30)

		{

			oldp[i][j] = board[i][j];

			newp[i][j] = board[i][j];

		}

	}

	memset(qiju, 0, sizeof(qiju));

	memset(a1, 0, sizeof(a1));

	memset(a2, 0, sizeof(a2));

	caculate(oldp, qiju);

	naiveline();

	for (int i = 60; i <= 480; i += 30)

	{

		for (int j = 60; j <= 480; j += 30)

		{

			if (a2[x2][y2] < a2[i][j])

			{

				x2 = i;

				y2 = j;

			}

		}

	}

	for (int i = 60; i <= 480; i += 30)

	{

		for (int j = 60; j <= 480; j += 30)

		{

			if (a1[x1][y1] < a1[i][j])

			{

				x1 = i;

				y1 = j;

			}

		}

	}

	if (a2[x2][y2] > a1[x1][y1])

	{

		px = x2;

		py = y2;

	}

	else

	{

		px = x1;

		py = y1;

	}

}







void pveeasy()//�˹�����

{

	int zqy[2];

	zqy[0] = zqy[1] = 0;

	memset(board, 0, sizeof(board));//�������

	int flag3 = 0;

	int k = 0;

	bwin = 0;

	wwin = 0;

	CreatePCBoard();

	step = 0;

	steppc = 0;

	AIprotect();

	flag3 = 0;

	steppc++;

	board[px - px % 30][py - py % 30] = -1;

	cleardevice();

	PVEshow();

	for (; is_run();)

	{

		msg = getmouse();

		if ((int)msg.is_left() && (int)msg.x >= ((int)msg.x - (int)msg.x % 30) - 14 && (int)msg.x <= ((int)msg.x - (int)msg.x % 30) + 14 && (int)msg.y >= ((int)msg.y - (int)msg.y % 30) - 14 && (int)msg.y <= ((int)msg.y - (int)msg.y % 30) + 14 && board[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] == 0 && msg.x >= 50 && msg.x <= 485 && msg.y >= 55 && msg.y <= 485)
		{
			k = 1;

			flag3 = 1;

			step++;

			board[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] = 1;//�����º���//ȡ����Ϊ�˾�ȷ����

			zqy[0] = (int)msg.x - (int)msg.x % 30;

			zqy[1] = (int)msg.y - (int)msg.y % 30;

			cleardevice();

			PVEshow();

			if (judpc() == 1)

			{

				bwin = 1;

				break;

			}

		}


		if ((int)msg.is_down() && (int)msg.x >= 700 && msg.x <= 850 && msg.y >= 400 && msg.y <= 450)     //��Ϸ�˳� 

		{

			cleardevice();

			CreateMenus();

			choose();
		}


		if (flag3)

		{

			pcposition();

			flag3 = 0;

			steppc++;

			board[px][py] = -1;

			cleardevice();

			PVEshow();

			if (judpc() == 2)

			{

				wwin = 1;

				break;

			}

		}

		if ((int)msg.is_down() && (int)msg.x >= 700 && msg.x <= 850 && msg.y >= 280 && msg.y <= 330 && step > 0 && k)     //���幦�� k�ж��Ƿ�ֻ�ܻ���һ�����������������������ϲ� 
		{
			k = 0;

			step--;         //�˲����˻�һ�� 

			steppc--;          //PC�����˻�һ�� 

			board[px][py] = 0;      //�˻���Ӧ��������� 

			board[zqy[0]][zqy[1]] = 0;          //����Ӧ��������� 

			cleardevice();

			PVEshow();

		}

	}

	cleardevice();

	PVEshow();

}







void pve()//�е��Ѷ�

{
	int zqy[2];

	zqy[0] = zqy[1] = 0;

	memset(board, 0, sizeof(board));//�������

	int flag3 = 0;

	int k = 0;

	bwin = 0;

	wwin = 0;

	CreatePCBoard();

	step = 0;

	steppc = 0;

	AIprotect();

	flag3 = 0;

	steppc++;

	board[px - px % 30][py - py % 30] = -1;

	cleardevice();

	PVEshow();

	for (; is_run();)

	{

		msg = getmouse();
		//���������Լ�����λ���ж� 
		if ((int)msg.is_left() && (int)msg.x >= ((int)msg.x - (int)msg.x % 30) - 14 && (int)msg.x <= ((int)msg.x - (int)msg.x % 30) + 14 && (int)msg.y >= ((int)msg.y - (int)msg.y % 30) - 14 && (int)msg.y <= ((int)msg.y - (int)msg.y % 30) + 14 && board[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] == 0 && msg.x >= 50 && msg.x <= 485 && msg.y >= 55 && msg.y <= 485)
		{

			k = 1;

			flag3 = 1;

			step++;

			board[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] = 1;//�����º���//ȡ����Ϊ�˾�ȷ����

			zqy[0] = (int)msg.x - (int)msg.x % 30;

			zqy[1] = (int)msg.y - (int)msg.y % 30;

			cleardevice();

			PVEshow();

			if (judpc() == 1)

			{

				bwin = 1;

				if ((int)msg.is_down() && (int)msg.x >= 700 && msg.x <= 850 && msg.y >= 400 && msg.y <= 450)     //��Ϸ�˳� 

				{

					cleardevice();

					CreateMenus();

					choose();

				}



			}

		}

		if ((int)msg.is_down() && (int)msg.x >= 700 && msg.x <= 850 && msg.y >= 500 && msg.y <= 550 && bwin)
		{

			cleardevice();

			scoring(step);

		}





		if ((int)msg.is_down() && (int)msg.x >= 700 && msg.x <= 850 && msg.y >= 400 && msg.y <= 450)         //��Ϸ�˳� 

		{

			cleardevice();

			CreateMenus();

			choose();

		}










		if (flag3)

		{

			AIprotect();

			flag3 = 0;

			steppc++;

			board[px - px % 30][py - py % 30] = -1;

			cleardevice();

			PVEshow();

			if (judpc() == 2)

			{

				wwin = 1;

				break;

			}

		}

		if ((int)msg.is_down() && (int)msg.x >= 700 && msg.x <= 850 && msg.y >= 280 && msg.y <= 330 && step > 0 && k)     //���幦�� k�ж��Ƿ�ֻ�ܻ���һ���������������������� 
		{
			k = 0;

			step--;         //�˲����˻�һ�� 

			steppc--;          //PC�����˻�һ�� 

			board[px - px % 30][py - py % 30] = 0;      //����Ӧ��������� 

			board[zqy[0]][zqy[1]] = 0;          //����Ӧ��������� 

			cleardevice();

			PVEshow();

		}



	}



	cleardevice();

	PVEshow();

}







void createPC2()        //�˻���ս 

{

	PIMAGE img;
	img = newimage();
	getimage(img, "drawing\\three1.jpg");
	putimage(0, 0, img);



	int flag = 0;



	for (; is_run(); delay_fps(600))//������

	{

		setbkmode(TRANSPARENT);//�������͸����

		if (msg.x >= 30 && msg.x <= 250 && msg.y >= 110 && msg.y <= 200)
		{
			setcolor(EGERGB(255, 255, 0));

			setfont(60, 30, "����");

			outtextxy(35, 125, "�˹�����");

		}
		else
		{

			setcolor(EGERGB(42, 234, 207));

			setfont(60, 30, "����");

			outtextxy(35, 125, "�˹�����");

		}
		if (msg.x >= 30 && msg.x <= 250 && msg.y >= 270 && msg.y <= 360)
		{

			setcolor(EGERGB(255, 255, 0));

			setfont(60, 30, "����");

			outtextxy(35, 285, "�˹�����");
		}
		else
		{
			setcolor(EGERGB(42, 234, 207));

			setfont(60, 30, "����");

			outtextxy(35, 285, "�˹�����");


		}


		//��ȡ�����Ϣ�����������ȴ����ȴ�������ϢΪֹ

		//���Ƶأ��к�kbhit��������ĺ���MouseHit�����ڼ����û�������Ϣ

		while (mousemsg())

		{

			msg = getmouse();

		}



		//��ʽ�����Ϊ�ַ��������ں������

		//msg��flag������ο��ĵ�����mouse_msg_e, mouse_flag_e������

		if (msg.is_left() && msg.x >= 30 && msg.x <= 250 && msg.y >= 110 && msg.y <= 200)

		{

			cleardevice();

			flag = 1;

			break;

		}

		if (msg.is_left() && msg.x >= 30 && msg.x <= 250 && msg.y >= 270 && msg.y <= 360)

		{

			cleardevice();

			flag = 2;
			
			CD=1;

			break;

		}

	}

	if (flag == 1)

	{

		pveeasy();

	}

	else if (flag == 2)

	{

		pve();

	}



}





void choose()      //�������������Դ�ѡ����Ϸģʽ 

{
	PIMAGE img;
	img = newimage();
	getimage(img, "drawing\\three2.jpg");
	putimage(0, 0, img);




	for (; is_run(); delay_fps(600))//������

	{

		//��ȡ�����Ϣ�����������ȴ����ȴ�������ϢΪֹ

		//���Ƶأ��к�kbhit��������ĺ���MouseHit�����ڼ����û�������Ϣ

		while (mousemsg())

		{

			msg = getmouse();

		}


		//	setcolor(EGERGB(0x0, 0xFF, 0x0));//������ɫ

		//   setbkmode(TRANSPARENT);//�������͸����

		//	setfont(100, 60, "����");

		//	outtextxy(200, 0, "��������Ϸ");



		if (msg.x >= 400 && msg.x <= 660 && msg.y >= 150 && msg.y <= 220)
		{



			setcolor(EGERGB(255, 255, 0));

			setfont(60, 30, "����");

			outtextxy(420, 150, "�˻���ս");
		}
		else
		{
			setcolor(EGERGB(228, 228, 228));

			setfont(60, 30, "����");

			outtextxy(420, 150, "�˻���ս");

		}


		if (msg.x >= 400 && msg.x <= 660 && msg.y >= 240 && msg.y <= 310)
		{
			setcolor(EGERGB(255, 255, 0));

			setfont(60, 30, "����");

			outtextxy(420, 240, "���˶�ս");
		}
		else
		{
			setcolor(EGERGB(228, 228, 228));

			setfont(60, 30, "����");

			outtextxy(420, 240, "���˶�ս");
		}

		if (msg.x >= 400 && msg.x <= 660 && msg.y >= 330 && msg.y <= 400)
		{
			setcolor(EGERGB(255, 255, 0));

			setfont(60, 30, "����");

			outtextxy(420, 330, "��Ϸ����");
		}
		else
		{
			setcolor(EGERGB(228, 228, 228));

			setfont(60, 30, "����");

			outtextxy(420, 330, "��Ϸ����");
		}

		if (msg.x >= 400 && msg.x <= 660 && msg.y >= 420 && msg.y <= 490)
		{
			setcolor(EGERGB(255, 255, 0));

			setfont(60, 30, "����");

			outtextxy(420, 420, "�˳���Ϸ");
		}
		else
		{
			setcolor(EGERGB(228, 228, 228));

			setfont(60, 30, "����");

			outtextxy(420, 420, "�˳���Ϸ");
		}



		//Author

		setcolor(EGERGB(32, 229, 170));

		setbkmode(TRANSPARENT);

		setfont(35, 14, "����");

		// outtextxy(710,550,"Author: Farmer Three");








			 //��ʽ�����Ϊ�ַ��������ں������

			 //msg��flag������ο��ĵ�����mouse_msg_e, mouse_flag_e������

		if (msg.is_left() && msg.x >= 400 && msg.x <= 660 && msg.y <= 220 && msg.y >= 150)

		{

			cleardevice();  //�����Ļ��ͼ�λ����� 

			flag = 1;

			break;

		}

		if (msg.is_left() && msg.x >= 400 && msg.x <= 660 && msg.y >= 240 && msg.y <= 310)

		{

			cleardevice();    //�����Ļ��ͼ�λ����� 

			flag = 2;

			break;

		}

		if (msg.is_left() && msg.x >= 400 && msg.x <= 660 && msg.y >= 330 && msg.y <= 400)
		{
			cleardevice();    //�����Ļ��ͼ�λ����� 

			explation();


		}

		if (msg.is_left() && msg.x >= 400 && msg.x <= 660 && msg.y >= 420 && msg.y <= 490)
		{

			closegraph();

		}



	}

	if (flag == 1)//�����˻���ս

	{

		cleardevice();         //�����Ļ��ͼ�λ����� 

		createPC2();



	}

	//���˶Կ�

	else if (flag == 2)

	{

		select();

	}

}

void exitt()//�˳������˵�

{

	for (; is_run(); )

	{

		msg = getmouse();

		if ((int)msg.is_down() && (int)msg.x >= 700 && msg.x <= 850 && msg.y >= 400 && msg.y <= 450)

		{

			cleardevice();

			CreateMenus();

			choose();

		}

	}

}

void explation()
{

	PIMAGE img;
	img = newimage();
	getimage(img, "drawing\\three4.jpg");
	putimage(0, 0, img);

	outtextxy(0, 50, "1st");
	xyprintf(700, 50, "%10d", three[0].mark);
	outtextxy(300, 50, three[0].name);
	outtextxy(0, 150, "2nd");
	xyprintf(700, 150, "%10d", three[1].mark);
	outtextxy(300, 150, three[1].name);
	outtextxy(0, 250, "3rd");
	xyprintf(700, 250, "%10d", three[2].mark);
	outtextxy(300, 250, three[2].name);

	setfont(40, 15, "����");

	setcolor(EGERGB(0x0, 0xFF, 0x0));

	outtextxy(750, 400, "�˳�");


	for (; is_run(); )

	{


		msg = getmouse();




		if ((int)msg.is_down() && (int)msg.x >= 700 && msg.x <= 850 && msg.y >= 400 && msg.y <= 450)

		{

			cleardevice();

			CreateMenus();

			choose();

		}






	}


}


void scoring(int n)   //���û�Ӯ���˹����ܣ�����Լ�¼���а� 
{

	int score;

	char farmer[100];

	score = 12544 - n * n;

	PIMAGE img;

	img = newimage();

	getimage(img, "drawing\\three3.jpeg");

	putimage(0, 0, img);

	setcolor(EGERGB(25, 224, 114));

	setfont(40, 20, "����");




	// outtextxy(20,20,"������һ���ǳ�");

	inputbox_getline("������", "�㰮����ʲô������ʲô���س�ȷ�ϣ�", farmer, 100);   //����һ���Ի��� 
	int i, j;
	for (i = 0; i <= 2; i++)
	{
		if (score > three[i].mark)
		{
			for (j = 2; j >= i; j--)
			{
				if (i == j)
				{
					strcpy(three[i].name, farmer);
					three[i].mark = score;
					break;
				}
				else
				{
					strcpy(three[j].name, three[j - 1].name);
					three[j].mark = three[j - 1].mark;
				}
			}
			if (i == j)
				break;
		}

	}
	fp = fopen("rank.txt", "w+");

	for (i = 0; i < 3; i++)
	{
		if (three[i].mark != 0)
		{
			if (i != 0)
				fprintf(fp, "\n");
			fputs(three[i].name, fp);
			fprintf(fp, "\t");
			fprintf(fp, "%d", three[i].mark);
		}

	}

	fclose(fp);

	outtextxy(0, 50, "1st");
	xyprintf(700, 50, "%10d", three[0].mark);
	outtextxy(300, 50, three[0].name);
	outtextxy(0, 150, "2nd");
	xyprintf(700, 150, "%10d", three[1].mark);
	outtextxy(300, 150, three[1].name);
	outtextxy(0, 250, "3rd");
	xyprintf(700, 250, "%10d", three[2].mark);
	outtextxy(300, 250, three[2].name);












	setfont(80, 30, "����");

	setcolor(EGERGB(0x0, 0xFF, 0x0));

	outtextxy(750, 400, "�˳�");


	for (; is_run(); )

	{


		msg = getmouse();




		if ((int)msg.is_down() && (int)msg.x >= 700 && msg.x <= 850 && msg.y >= 400 && msg.y <= 450)

		{

			cleardevice();

			CreateMenus();

			choose();

		}



	}

}


void select()
{
	strcpy(IP, "0");

	char farmer[100];

	PIMAGE img;
	img = newimage();
	getimage(img, "drawing\\three5.jpg");
	putimage(0, 0, img);
	int h = 0;



	for (; is_run(); delay_fps(600))//������

	{

		setbkmode(TRANSPARENT);//�������͸����

		if (msg.x >= 30 && msg.x <= 250 && msg.y >= 110 && msg.y <= 200)
		{
			setcolor(EGERGB(255, 255, 0));

			setfont(60, 30, "����");

			outtextxy(35, 125, "���ض�ս");

		}
		else
		{

			setcolor(EGERGB(42, 234, 207));

			setfont(60, 30, "����");

			outtextxy(35, 125, "���ض�ս");

		}
		if (msg.x >= 30 && msg.x <= 250 && msg.y >= 270 && msg.y <= 360)
		{

			setcolor(EGERGB(255, 255, 0));

			setfont(60, 30, "����");

			outtextxy(35, 285, "������Ϸ");
		}
		else
		{
			setcolor(EGERGB(42, 234, 207));

			setfont(60, 30, "����");

			outtextxy(35, 285, "������Ϸ");
		}
		if (msg.x >= 30 && msg.x <= 250 && msg.y >= 430 && msg.y <= 520)
		{
			setcolor(EGERGB(255, 255, 0));

			setfont(60, 30, "����");

			outtextxy(35, 445, "������Ϸ");
		}
		else
		{
			setcolor(EGERGB(42, 234, 207));

			setfont(60, 30, "����");

			outtextxy(35, 445, "������Ϸ");
		}





		//��ȡ�����Ϣ�����������ȴ����ȴ�������ϢΪֹ

		//���Ƶأ��к�kbhit��������ĺ���MouseHit�����ڼ����û�������Ϣ

		while (mousemsg())

		{

			msg = getmouse();

		}



		//��ʽ�����Ϊ�ַ��������ں������

		//msg��flag������ο��ĵ�����mouse_msg_e, mouse_flag_e������

		if (msg.is_left() && msg.x >= 30 && msg.x <= 250 && msg.y >= 110 && msg.y <= 200)

		{

			cleardevice();

			h = 1;

			break;

		}

		if (msg.is_left() && msg.x >= 30 && msg.x <= 250 && msg.y >= 270 && msg.y <= 360)

		{

			cleardevice();

			h = 2;

			break;

		}
		if (msg.is_left() && msg.x >= 30 && msg.x <= 250 && msg.y >= 430 && msg.y <= 520)
		{
			cleardevice();
			h = 3;
			break;
		}

	}

	if (h == 1)
		pvp();
	else if (h == 2)
		inter1();
	else if (h == 3)
	{
		putimage(0, 0, img);

		inputbox_getline("������", "ip��ַ���س�ȷ�ϣ�", farmer, 100);   //����һ���Ի��� 

		strcpy(IP, farmer);

		cleardevice();

		inter2();

	}



}



int main()

{
	int i = 0;
	fp = fopen("rank.txt", "a+");
	while (!feof(fp))
	{
		fscanf(fp, "%s%d", three[i].name, &three[i].mark);
		i++;
	}
	fclose(fp);
	CreateMenus();//���˵�

	choose();//�˵���ѡ��

	exitt();

	getch();

	return 0;

}

