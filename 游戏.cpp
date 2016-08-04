#include<conio.h>
#include<graphics.h>
#include<string>
#include<iostream>
#pragma comment(lib,"Winmm.lib") //开启音频头文件
using namespace std;
void load(struct chess img[35]);                                                 //从硬盘加载图片
void printfallimage(struct chess img[], int a[10][9], int b[10][9]);               //打印所有图像函数
void chat();                                                                     //打印棋盘框架
void coordinate(struct chess img[35], int a[][9], int b[][9]);                     //给棋子赋坐标值
void mouse(struct chess img[35], MOUSEMSG A, int a[10][9], int b[10][9], int *m);    //鼠标移动函数
int  judge(struct chess img[], int x1, int y1, int x2, int y2, int a[][9], int b[][9]);//判断是否符合走棋规则
void name(struct chess img[35]);                                                 //命名函数
void judgechess(struct chess img[35], int a[][9], int b[][9], int x1, int y1, int x2, int y2, int *count); //判断该点是否有棋子    
void help();
int srtart();
void jieshao();
struct chess
{
	IMAGE picture;
	char name;
	int xx;
	int yy;
};
int main()
{
	int w, k;
	initgraph(730, 750);
	//initgraph(730, 750);
	while (true)
	{
		w = srtart();
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
		switch (w)
		{
		case 1:
		{
				  k = 1;
				  while (true)
				  {
					  setorigin(40, 50);
					  int a[10][9], b[10][9];
					  struct chess img[35];
					  int i, j;
					  int m[2], n[2];
					  for (i = 0; i<10; i++)
					  {
						  for (j = 0; j<9; j++)
						  {
							  a[i][j] = 70 * j + 10;
						  }
					  }
					  for (i = 0; i<10; i++)
					  {
						  for (j = 0; j<9; j++)
						  {
							  b[i][j] = 70 * i - 30;
						  }
					  }
					  name(img);                      //调用命名函数
					  int flag1;
					  int flag2 = -1, flag3 = 0;                 //判断每人每次只能走一步
					  coordinate(img, a, b);
					  chat();                          //调用表格函数
					  load(img);                       //从硬盘调用图片
					  printfallimage(img, a, b);         //打印棋子函数
					  MOUSEMSG A;
					  while (true)
					  {
						  FlushMouseMsgBuffer();
						  int mm[200], jj = 0, flagf;
						  while (1)
						  {
							  A = GetMouseMsg();
							  flagf = 0;
							  mouse(img, A, a, b, &mm[jj]);
							  if (A.uMsg == WM_LBUTTONDOWN)
							  {
								  if (jj != 0)
								  {
									  for (i = 0; i < 32; i++)
									  {
										  if (img[i].xx == mm[jj - 2] && img[i].yy == mm[jj - 1])
										  {
											  flagf = 1;
											  break;
										  }
									  }
									  if (mm[jj - 2] != mm[jj] || mm[jj - 1] != mm[jj + 1])
										  break;
									  if (flagf == 1)
										  jj += 2;
								  }
								  else
									  jj += 2;
							  }
						  }
						  m[0] = mm[jj - 2], m[1] = mm[jj - 1];
						  n[0] = mm[jj], n[1] = mm[jj + 1];
						  printf("%d %d 1\n", m[0], m[1]);
						  if ((m[0] == 9 && m[1] == 3) || flag3 == 1)       //退出
						  {
							  Sleep(500);
							  return 0;
						  }

						  printf("%d %d 2\n\n", n[0], n[1]);
						  flag1 = 0;
						  if (judge(img, m[0], m[1], n[0], n[1], a, b) == 1)
						  {
							  for (i = 0; i<32; i++)
							  {
								  if ((img[i].xx == a[m[1]][m[0]]) && (img[i].yy == b[m[1]][m[0]]))
								  {
									  if (i<16 && flag2<16 && flag2 >= 0)
									  {
										  settextstyle(20, 20, _T("隶书"));                //字体设置
										  outtextxy(510, 300, _T("黑方走棋！"));
										  goto found;
									  }
									  if (i>16 && flag2>16)
									  {
										  settextstyle(20, 20, _T("隶书"));                //字体设置
										  outtextxy(510, 300, _T("红方走棋！"));
										  goto found;
									  }
									  for (j = 0; j<32; j++)
									  {
										  if (img[j].xx == a[n[1]][n[0]] && img[j].yy == b[n[1]][n[0]])
										  {
											  if ((i <= 15 && j <= 15) || (i>15 && j>15))
												  goto found;                   // 防止吃自己的棋子
											  img[i].xx = a[n[1]][n[0]];
											  img[i].yy = b[n[1]][n[0]];
											  img[j].xx = 1000, img[j].yy = 1000;
											  flag1 = 1;
											  break;
										  }
									  }
									  if (flag1 == 0)
									  {
										  img[i].xx = a[n[1]][n[0]];
										  img[i].yy = b[n[1]][n[0]];
									  }
									  chat();
									  printfallimage(img, a, b);
									  mciSendString("close mymusic", NULL, 0, NULL);
									  mciSendString("open \"My Music\\5.mp3\" alias mymusic", NULL, 0, NULL); //打开音乐文件相对路径
									  mciSendString("play mymusic", NULL, 0, NULL);             //播放音乐文件
									  flag2 = i;
									  setcolor(RED);
									  if (img[0].xx == 1000)
									  {
										  settextstyle(20, 20, _T("隶书"));                //字体设置
										  outtextxy(510, 300, _T("黑方胜利"));
										  mciSendString("close mymusic", NULL, 0, NULL);
			                              mciSendString("open \"My Music\\2.wav\" alias mymusic", NULL, 0, NULL);     //打开音乐文件相对路径
		                                  mciSendString("play mymusic", NULL, 0, NULL);                               //播放音乐文件
										  flag3 = 0;
									  }
									  if (img[16].xx == 1000)
									  {
										  settextstyle(20, 20, _T("隶书"));                //字体设置
										  outtextxy(510, 300, _T("红方胜利"));
										  mciSendString("close mymusic", NULL, 0, NULL);
			                              mciSendString("open \"My Music\\2.wav\" alias mymusic", NULL, 0, NULL);     //打开音乐文件相对路径
		                                  mciSendString("play mymusic", NULL, 0, NULL);   
										  flag3 = 1;
									  }
								  found:
									  break;
								  }
							  }
						  }
					  }
				  }
		case 2:
			help();
			break;
		case 3:
			jieshao();
			break;
		case 0:
			return 0;
		}
		}
	}

}
//判断某点是否有棋子
void judgechess(struct chess img[35], int a[10][9], int b[10][9], int x1, int y1, int x2, int y2, int *count)
{
	int i, j;
	int m, n;
	(*count) = 0;
	count[1] = 0;
	if (x1 == x2)
	{
		m = y1;
		n = y2;
		if (n>m)
			swap(n, m);
		for (i = n + 1; i<m; i++)
		{
			for (j = 0; j<32; j++)
			{
				if (img[j].xx == a[i][x1] && img[j].yy == b[i][x1])
					count[0]++;
			}
		}
	}
	if (y1 == y2)
	{
		m = x2;
		n = x1;
		if (n>m)
			swap(n, m);
		for (i = n + 1; i<m; i++)
		{
			for (j = 0; j<32; j++)
			{
				if (img[j].xx == a[y1][i] && img[j].yy == b[y1][i])
					count[0]++;
			}
		}
	}
	for (j = 0; j<32; j++)
	{
		if (img[j].xx == a[y2][x2] && img[j].yy == b[y2][x2])
			count[1]++;
	}
}
//改变棋子位置函数
void  mouse(struct chess img[35], MOUSEMSG A, int a[10][9], int b[10][9], int *m)
{
	int x1, y1;
	x1 = A.x;
	y1 = A.y + 30;
	x1 = x1 / 70 - 1;
	y1 = y1 / 70 - 1;
	m[0] = x1, m[1] = y1;
}
int  judge(struct chess img[], int x1, int y1, int x2, int y2, int a[][9], int b[][9])
{
	int i, flag = 0, flag3;
	int k1;
	for (i = 0; i<32; i++)
	{
		if (img[i].xx == a[y1][x1] && img[i].yy == b[y1][x1])
		{
			k1 = i;
			flag = 1;
			break;
		}
	}
	if (flag == 0)
		return 0;
	switch (img[k1].name)
	{
	case 'k':                       //帅——————————
		if (k1 == 0)
		{
			if (x1 == 3 && y1 == 0)
			{
				if ((x2 == 4 && y2 == 0) || (x2 == 3 && y2 == 1))
					return 1;
			}
			else
			if (x1 == 4 && y1 == 0)
			{
				if ((x2 == 3 && y2 == 0) || (x2 == 5 && y2 == 0) || (x2 == 4 && y2 == 1))
					return 1;
			}
			else
			if (x1 == 5 && y1 == 0)
			{
				if ((x2 == 4 && y2 == 0) || (x2 == 5 && y2 == 1))
					return 1;
			}
			else
			if (x1 == 3 && y1 == 1)
			{
				if ((x2 == 3 && y2 == 0) || (x2 == 4 && y2 == 1) || (x2 == 3 && y2 == 2))
					return 1;
			}
			else if (x1 == 4 && y1 == 1)
			{
				if ((x2 == 3 && y2 == 1) || (x2 == 4 && y2 == 0) || (x2 == 5 && y2 == 1) || (x2 == 4 && y2 == 2))
					return 1;
			}
			else if (x1 == 5 && y1 == 1)
			{
				if ((x2 == 5 && y2 == 0) || (x2 == 5 && y2 == 2) || (x2 == 4 && y2 == 1))
					return 1;
			}
			else
			if (x1 == 3 && y1 == 2)
			{
				if ((x2 == 3 && y2 == 1) || (x2 == 4 && y2 == 2))
					return 1;
			}
			else
			if (x1 == 4 && y1 == 2)
			{
				if ((x2 == 3 && y2 == 2) || (x2 == 5 && y2 == 2) || (x2 == 4 && y2 == 1))
					return 1;
			}
			else
			if (x1 == 5 && y1 == 2)
			{
				if ((x2 == 5 && y2 == 1) || (x2 == 4 && y2 == 2))
					return 1;
			}
			else
				return 0;
		}
		if (k1 == 16)
		{
			if (x1 == 3 && y1 == 9)
			{
				if ((x2 == 4 && y2 == 9) || (x2 == 3 && y2 == 8))
					return 1;
			}
			else
			if (x1 == 4 && y1 == 9)
			{
				if ((x2 == 3 && y2 == 9) || (x2 == 5 && y2 == 9) || (x2 == 4 && y2 == 8))
					return 1;
			}
			else
			if (x1 == 5 && y1 == 9)
			{
				if ((x2 == 4 && y2 == 9) || (x2 == 5 && y2 == 8))
					return 1;
			}
			else
			if (x1 == 3 && y1 == 8)
			{
				if ((x2 == 3 && y2 == 9) || (x2 == 4 && y2 == 8) || (x2 == 3 && y2 == 7))
					return 1;
			}
			else if (x1 == 4 && y1 == 8)
			{
				if ((x2 == 3 && y2 == 8) || (x2 == 4 && y2 == 9) || (x2 == 5 && y2 == 8) || (x2 == 4 && y2 == 7))
					return 1;
			}
			else if (x1 == 5 && y1 == 8)
			{
				if ((x2 == 5 && y2 == 9) || (x2 == 5 && y2 == 7) || (x2 == 4 && y2 == 8))
					return 1;
			}
			else
			if (x1 == 3 && y1 == 7)
			{
				if ((x2 == 3 && y2 == 8) || (x2 == 4 && y2 == 7))
					return 1;
			}
			else
			if (x1 == 4 && y1 == 7)
			{
				if ((x2 == 3 && y2 == 7) || (x2 == 5 && y2 == 7) || (x2 == 4 && y2 == 8))
					return 1;
			}
			else
			if (x1 == 5 && y1 == 7)
			{
				if ((x2 == 5 && y2 == 8) || (x2 == 4 && y2 == 7))
					return 1;
			}
			else
				return 0;
		}
		break;
	case 'g':                       //士——————————
		if (k1 == 1 || k1 == 2)
		{
			if ((x1 == 3 && y1 == 0) || (x1 == 5 && y1 == 0) || (x1 == 3 && y1 == 2) || (x1 == 5 && y1 == 2))
			{
				if (x2 == 4 && y2 == 1)
					return 1;
				else
					return 0;
			}
			if (x1 == 4 && y1 == 1)
			{
				if ((x2 == 3 && y2 == 0) || (x2 == 5 && y2 == 0) || (x2 == 3 && y2 == 2) || (x2 == 5 && y2 == 2))
					return 1;
				else
					return 0;
			}
		}
		if (k1 == 17 || k1 == 18)
		{
			if ((x1 == 3 && y1 == 9) || (x1 == 5 && y1 == 9) || (x1 == 3 && y1 == 7) || (x1 == 5 && y1 == 7))
			{
				if (x2 == 4 && y2 == 8)
					return 1;
				else
					return 0;
			}
			if (x1 == 4 && y1 == 8)
			{
				if ((x2 == 3 && y2 == 9) || (x2 == 5 && y2 == 9) || (x2 == 3 && y2 == 7) || (x2 == 5 && y2 == 7))
					return 1;
				else
					return 0;
			}
			else
				return 0;
		}
		break;
	case 'e':                        //相————————
		flag3 = 0;
		for (i = 0; i<32; i++)
		{
			if ((img[i].xx == a[(y2 + y1) / 2][(x1 + x2) / 2]) && img[i].yy == b[(y1 + y2) / 2][(x1 + x2) / 2])
				flag3 = 1;
		}
		if (flag3 == 0)
		{
			if (k1 == 3 || k1 == 4)
			{
				if (y2<5)
				{
					if ((x2 == x1 + 2 && y2 == y1 + 2) || (x2 == x1 - 2 && y2 == y1 - 2) || (x2 == x1 + 2 && y2 == y1 - 2) || (x2 == x1 - 2 && y2 == y1 + 2))
						return 1;
					else
						return 0;
				}
			}

			else if (k1 == 19 || k1 == 20)
			{
				if (y2 >= 5)
				{
					if ((x2 == x1 + 2 && y2 == y1 + 2) || (x2 == x1 - 2 && y2 == y1 - 2) || (x2 == x1 + 2 && y2 == y1 - 2) || (x2 == x1 - 2 && y2 == y1 + 2))
						return 1;
					else
						return 0;
				}
			}
			else
				return 0;
		}
		else
			return 0;
		break;
	case 'h':                         //马————————
		int x3, y3;
		if ((x2 == x1 + 1 && y2 == y1 + 2) || (x2 == x1 + 2 && y2 == y1 + 1) || (x2 == x1 - 1 && y2 == y1 - 2) || (x2 == x1 - 2 && y2 == y1 - 1) || (x2 == x1 - 1 && y2 == y1 + 2) || (x2 == x1 + 2 && y2 == y1 - 1) || (x2 == x1 - 2 && y2 == y1 + 1) || (x2 == x1 + 1 && y2 == y1 - 2))
		{
			if (abs(x2 - x1) == 1)
			{
				if (y2 - y1 == 2)
				{
					x3 = x1;
					y3 = y1 + 1;
				}
				else
				{
					x3 = x1;
					y3 = y1 - 1;
				}
			}
			if (abs(y2 - y1) == 1)
			{
				if (x2 - x1 == 2)
				{
					x3 = x1 + 1;
					y3 = y1;
				}
				else
				{
					x3 = x1 - 1;
					y3 = y1;
				}

			}
			int ii;
			for (ii = 0; ii<32; ii++)
			{
				if (img[ii].xx == a[y3][x3] && img[ii].yy == b[y3][x3])
					return 0;
			}
			if (ii == 32)
				return 1;
		}
		else
			return 0; cout << x3 << endl << y3 << endl;
		break;
	case 'r':                        //车————————
		int Ccount[2];
		if (x1 == x2 || y1 == y2)
		{
			judgechess(img, a, b, x1, y1, x2, y2, &Ccount[0]);
			if (Ccount[0] == 0)
				return 1;
			else
				return 0;
		}
		else
			return 0;
		break;
	case 'c':
		int count[2];
		if (x1 == x2 || y1 == y2)           //炮————————
		{
			judgechess(img, a, b, x1, y1, x2, y2, count);
			if ((count[0] == 0 && count[1] == 0) || (count[0] == 1 && count[1] == 1))
				return 1;
			else
				return 0;
		}
		else
			return 0;
		break;
	case 'p':	                     //兵————————
		if (k1 <= 15)
		{
			if (y1<5 && y2 == y1 + 1 && x2 == x1)
				return 1;
			if (y1 >= 5 && ((y2 == y1 + 1 && x2 == x1) || (x2 == x1 + 1 && y2 == y1) || (x2 == x1 - 1 && y2 == y1)))
				return 1;
		}
		if (k1>15)
		{
			if (y1 >= 5 && y2 == y1 - 1 && x2 == x1)
				return 1;
			else
			if (y1<5 && ((y2 == y1&&x2 == x1 + 1) || (y2 == y1&&x2 == x1 - 1) || (x2 == x1&&y2 == y1 - 1)))
				return 1;
			else
				return 0;
		}
		break;
	default:
		break;
	}
}

//打印所有棋子函数
void printfallimage(struct chess img[35], int a[10][9], int b[10][9])
{
	putimage(img[0].xx, img[0].yy, &img[0].picture);                 //红帅
	putimage(img[1].xx, img[1].yy, &img[1].picture);                //红士
	putimage(img[2].xx, img[2].yy, &img[2].picture);                //红士
	putimage(img[3].xx, img[3].yy, &img[3].picture);                 //红相
	putimage(img[4].xx, img[4].yy, &img[4].picture);                 //红相
	putimage(img[5].xx, img[5].yy, &img[5].picture);                //红马
	putimage(img[6].xx, img[6].yy, &img[6].picture);                 //红马
	putimage(img[7].xx, img[7].yy, &img[7].picture);               //红车
	putimage(img[8].xx, img[8].yy, &img[8].picture);                 //红车
	putimage(img[9].xx, img[9].yy, &img[9].picture);                 //红炮
	putimage(img[10].xx, img[10].yy, &img[10].picture);                 //红炮

	putimage(img[11].xx, img[11].yy, &img[11].picture);                //红兵
	putimage(img[12].xx, img[12].yy, &img[12].picture);                 //红兵
	putimage(img[13].xx, img[13].yy, &img[13].picture);                 //红兵
	putimage(img[14].xx, img[14].yy, &img[14].picture);                 //红兵
	putimage(img[15].xx, img[15].yy, &img[15].picture);                 //红兵

	putimage(img[16].xx, img[16].yy, &img[16].picture);                 //黑帅
	putimage(img[17].xx, img[17].yy, &img[17].picture);          //黑士
	putimage(img[18].xx, img[18].yy, &img[18].picture);           //黑士
	putimage(img[19].xx, img[19].yy, &img[19].picture);          //黑相
	putimage(img[20].xx, img[20].yy, &img[20].picture);            //黑相
	putimage(img[21].xx, img[21].yy, &img[21].picture);            //黑马
	putimage(img[22].xx, img[22].yy, &img[22].picture);            //黑马
	putimage(img[23].xx, img[23].yy, &img[23].picture);            //黑车
	putimage(img[24].xx, img[24].yy, &img[24].picture);            //黑车

	putimage(img[25].xx, img[25].yy, &img[25].picture);            //黑炮
	putimage(img[26].xx, img[26].yy, &img[26].picture);            //黑炮

	putimage(img[27].xx, img[27].yy, &img[27].picture);           //黑兵
	putimage(img[28].xx, img[28].yy, &img[28].picture);           //黑兵
	putimage(img[29].xx, img[29].yy, &img[29].picture);            //黑兵
	putimage(img[30].xx, img[30].yy, &img[30].picture);            //黑兵
	putimage(img[31].xx, img[31].yy, &img[31].picture);            //黑兵
}
//初始化棋子坐标函数
void coordinate(struct chess img[35], int a[][9], int b[][9])
{
	img[0].xx = a[0][4], img[0].yy = b[0][4];    //红帅
	img[1].xx = a[0][3], img[1].yy = b[0][3];    //红士
	img[2].xx = a[0][5], img[2].yy = b[0][5];
	img[3].xx = a[0][2], img[3].yy = b[0][2];    //红相
	img[4].xx = a[0][6], img[4].yy = b[0][6];
	img[5].xx = a[0][1], img[5].yy = b[0][1];    //红马
	img[6].xx = a[0][7], img[6].yy = b[0][7];
	img[7].xx = a[0][0], img[7].yy = b[0][0];    //红车
	img[8].xx = a[0][8], img[8].yy = b[0][8];

	img[9].xx = a[2][1], img[9].yy = b[2][1];    //红炮
	img[10].xx = a[2][7], img[10].yy = b[2][7];

	img[11].xx = a[3][0], img[11].yy = b[3][0];  //红兵
	img[12].xx = a[3][2], img[12].yy = b[3][2];
	img[13].xx = a[3][4], img[13].yy = b[3][4];
	img[14].xx = a[3][6], img[14].yy = b[3][6];
	img[15].xx = a[3][8], img[15].yy = b[3][8];

	img[16].xx = a[9][4], img[16].yy = b[9][4];  //黑帅
	img[17].xx = a[9][3], img[17].yy = b[9][3];  //黑士
	img[18].xx = a[9][5], img[18].yy = b[9][5];
	img[19].xx = a[9][2], img[19].yy = b[9][2];  //黑相
	img[20].xx = a[9][6], img[20].yy = b[9][6];
	img[21].xx = a[9][1], img[21].yy = b[9][1];  //黑马
	img[22].xx = a[9][7], img[22].yy = b[9][7];
	img[23].xx = a[9][0], img[23].yy = b[9][0];  //黑车
	img[24].xx = a[9][8], img[24].yy = b[9][8];

	img[25].xx = a[7][1], img[25].yy = b[7][1];  //黑炮
	img[26].xx = a[7][7], img[26].yy = b[7][7];

	img[27].xx = a[6][0], img[27].yy = b[6][0];  //黑兵
	img[28].xx = a[6][2], img[28].yy = b[6][2];
	img[29].xx = a[6][4], img[29].yy = b[6][4];
	img[30].xx = a[6][6], img[30].yy = b[6][6];
	img[31].xx = a[6][8], img[31].yy = b[6][8];

}
//打印棋盘函数
void chat()
{
	int i;
	setbkcolor(RGB(255, 204, 102));
	setlinecolor(BLACK);
	cleardevice();
	line(25, -5, 25, 640);        //左|
	line(30, -5, 615, -5);        //上-
	line(30, 640, 615, 640);      //下-
	line(615, -5, 615, 640);      //右|
	for (i = 40; i <= 600; i = i + 70)
		line(i, 0, i, 280);            //上 竖
	for (i = 0; i <= 280; i = i + 70)
		line(40, i, 600, i);       //上 横
	for (i = 40; i <= 610; i = i + 70)
		line(i, 350, i, 630);      //下 竖
	for (i = 350; i <= 630; i = i + 70)    //下 横
		line(40, i, 600, i);
	line(250, 0, 390, 140);
	line(390, 0, 250, 140);
	line(250, 630, 390, 490);
	line(250, 490, 390, 630);
	settextstyle(40, 40, _T("隶书"));                //字体设置
	setcolor(BLACK);
	outtextxy(100, 300, _T("楚河"));
	settextstyle(20, 0, _T("华文楷体"));
	setcolor(RED);
	outtextxy(270, 310, _T("中國象棋"));
	settextstyle(40, 30, _T("华文行楷"), 0, 1800, 0, 0, 0, 0);
	setcolor(BLUE);
	outtextxy(360, 335, _T("汉界"));
	setfillcolor(GREEN);
	settextstyle(40, 40, _T("隶书"), 0, 0, 0, 0, 0, 0);
	solidcircle(670, 250, 15);   //solidcircle为无边框，fillcircle有边框
	settextstyle(25, 15, _T("隶书"));
	outtextxy(630, 270, _T("退出"));
}
//从硬盘读取所有棋子函数
void load(struct chess img[35])
{
	loadimage(&img[0].picture, _T("象棋图片\\1_king.jpg"), 60, 60, true);      //红帅 
	loadimage(&img[1].picture, _T("象棋图片\\1_guard.jpg"), 60, 60, true);     //红士
	loadimage(&img[2].picture, _T("象棋图片\\1_guard.jpg"), 60, 60, true);     //红士
	loadimage(&img[3].picture, _T("象棋图片\\1_eleph.jpg"), 60, 60, true);     //红相
	loadimage(&img[4].picture, _T("象棋图片\\1_eleph.jpg"), 60, 60, true);     //红相
	loadimage(&img[5].picture, _T("象棋图片\\1_horse.jpg"), 60, 60, true);     //红马
	loadimage(&img[6].picture, _T("象棋图片\\1_horse.jpg"), 60, 60, true);     //红马
	loadimage(&img[7].picture, _T("象棋图片\\1_rook.jpg"), 60, 60, true);      //红车
	loadimage(&img[8].picture, _T("象棋图片\\1_rook.jpg"), 60, 60, true);      //红车
	loadimage(&img[9].picture, _T("象棋图片\\1_cannon.jpg"), 60, 60, true);    //红炮
	loadimage(&img[10].picture, _T("象棋图片\\1_cannon.jpg"), 60, 60, true);    //红炮

	loadimage(&img[11].picture, _T("象棋图片\\1_pawn.jpg"), 60, 60, true);      //红兵
	loadimage(&img[12].picture, _T("象棋图片\\1_pawn.jpg"), 60, 60, true);      //红兵
	loadimage(&img[13].picture, _T("象棋图片\\1_pawn.jpg"), 60, 60, true);      //红兵
	loadimage(&img[14].picture, _T("象棋图片\\1_pawn.jpg"), 60, 60, true);      //红兵
	loadimage(&img[15].picture, _T("象棋图片\\1_pawn.jpg"), 60, 60, true);      //红兵

	loadimage(&img[16].picture, _T("象棋图片\\0_king.jpg"), 60, 60, true);      //黑帅
	loadimage(&img[17].picture, _T("象棋图片\\0_guard.jpg"), 60, 60, true);     //黑士
	loadimage(&img[18].picture, _T("象棋图片\\0_guard.jpg"), 60, 60, true);     //黑士
	loadimage(&img[19].picture, _T("象棋图片\\0_eleph.jpg"), 60, 60, true);     //黑相
	loadimage(&img[20].picture, _T("象棋图片\\0_eleph.jpg"), 60, 60, true);     //黑相
	loadimage(&img[21].picture, _T("象棋图片\\0_horse.jpg"), 60, 60, true);    //黑马
	loadimage(&img[22].picture, _T("象棋图片\\0_horse.jpg"), 60, 60, true);    //黑马
	loadimage(&img[23].picture, _T("象棋图片\\0_rook.jpg"), 60, 60, true);     //黑车
	loadimage(&img[24].picture, _T("象棋图片\\0_rook.jpg"), 60, 60, true);     //黑车

	loadimage(&img[25].picture, _T("象棋图片\\0_cannon.jpg"), 60, 60, true);    //黑炮
	loadimage(&img[26].picture, _T("象棋图片\\0_cannon.jpg"), 60, 60, true);    //黑炮

	loadimage(&img[27].picture, _T("象棋图片\\0_pawn.jpg"), 60, 60, true);      //黑兵
	loadimage(&img[28].picture, _T("象棋图片\\0_pawn.jpg"), 60, 60, true);      //黑兵
	loadimage(&img[29].picture, _T("象棋图片\\0_pawn.jpg"), 60, 60, true);      //黑兵
	loadimage(&img[30].picture, _T("象棋图片\\0_pawn.jpg"), 60, 60, true);      //黑兵
	loadimage(&img[31].picture, _T("象棋图片\\0_pawn.jpg"), 60, 60, true);      //黑兵
}
void name(struct chess img[35])
{
	img[0].name = img[16].name = 'k';
	img[1].name = img[2].name = img[17].name = img[18].name = 'g';
	img[3].name = img[4].name = img[19].name = img[20].name = 'e';
	img[5].name = img[6].name = img[21].name = img[22].name = 'h';
	img[7].name = img[8].name = img[23].name = img[24].name = 'r';
	img[9].name = img[10].name = img[25].name = img[26].name = 'c';
	img[11].name = img[12].name = img[13].name = img[14].name = img[15].name = 'p';
	img[27].name = img[28].name = img[29].name = img[30].name = img[31].name = 'p';
}
void help()
{
	MOUSEMSG m;
	initgraph(700, 700);
	setbkcolor(RGB(201, 218, 238)); cleardevice();
	setlinecolor(RGB(50, 102, 222));
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
	rectangle(50, 100, 650, 650);
	settextstyle(50, 0, _T("华文行楷"));
	setcolor(RGB(214, 10, 0));
	outtextxy(300, 20, _T("帮助"));
	settextstyle(30, 0, _T("华文行楷"));
	outtextxy(60, 150, _T("1.游戏规则:"));
	outtextxy(60, 420, _T("2.操作方法:"));
	settextstyle(20, 0, _T("楷体"));
	setcolor(BLACK);
	outtextxy(60, 180, _T("  (1)开始游戏时，先选择游戏游戏开始选项。"));
	outtextxy(60, 200, _T("  (2)双方各执十六颗棋子，双方轮流移动棋盘中棋子到，每次一"));
	outtextxy(60, 220, _T("     方只能走一步，双方轮流执子"));
	outtextxy(60, 240, _T("	  (3)走棋规则是: 象飞田，马踏日，车走直线，炮打隔三子，"));
	outtextxy(60, 260, _T("     士只能走方格内的斜线，将只能在方格中间走，卒没过河之"));
	outtextxy(60, 280, _T("     前只能走向前走，不能后退，不能左右走动，过了河之后"));
	outtextxy(60, 300, _T("     才能左右走但是不能后退。"));
	outtextxy(60, 320, _T("  _T(（注意）马踏日时，只有长线上无子时方可以!"));
	outtextxy(60, 340, _T("	  (4)一方吃掉对方的将时，该玩家取得胜利！"));
	outtextxy(60, 360, _T("	   （注意）若双方棋子数目都较少，双方都无法吃掉对方的将"));
	outtextxy(60, 380, _T("	   时，则双方平局！"));
	outtextxy(60, 450, _T("	 (1)本游戏为鼠标操作，点击鼠标即可下棋子。"));
	outtextxy(60, 470, _T("	 (2)走棋子时先选取要走的棋子，再点击要走的位置即可。"));
	settextstyle(40, 0, _T("华文行楷"));
	setcolor(RGB(22, 69, 173));
	outtextxy(250, 550, _T("	 游戏愉快!"));
	settextstyle(20, 0, _T("华文行楷"));
	outtextxy(545, 600, _T("	 退出帮助"));
	setcolor(GREEN);
	rectangle(540, 590, 635, 625);
	while (true)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		if (m.x >= 540 && m.x <= 635 && m.y >= 590 && m.y <= 625)
			break;
	}
}
int srtart()
{
	MOUSEMSG m;
	setbkcolor(RGB(243, 179, 9)); cleardevice();
	IMAGE beijing;
	setbkmode(TRANSPARENT);		// 设置文字背景为透明色
	loadimage(&beijing, _T("象棋图片\\1234.jpg"), 750, 750, true);
	putimage(0, 0, &beijing);
	setlinecolor(RGB(50, 102, 222));
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
	rectangle(220, 180, 460, 260);
	rectangle(220, 280, 460, 360);
	rectangle(220, 380, 460, 460);
	rectangle(220, 480, 460, 560);
	settextstyle(80, 0, _T("华文行楷"));
	setcolor(RGB(214, 10, 0));
	outtextxy(200, 50, _T("中国象棋"));
	settextstyle(50, 0, _T("华文行楷"));
	setcolor(RGB(69, 221, 232));
	outtextxy(240, 200, _T("开始游戏"));
	outtextxy(240, 300, _T("游戏帮助"));
	outtextxy(240, 400, _T("退出游戏"));
	outtextxy(240, 500, _T("游戏版本"));
	while (true)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x >= 220 && m.x <= 460 && m.y >= 180 && m.y <= 260)
				return 1;
			if (m.x >= 220 && m.x <= 460 && m.y >= 280 && m.y <= 360)
				return 2;
			if (m.x >= 220 && m.x <= 460 && m.y >= 480 && m.y <= 560)
				return 3;
			if (m.x >= 220 && m.x <= 460 && m.y >= 380 && m.y <= 460)
				return 0;
		}
	}
}
void jieshao()
{
	MOUSEMSG m;
	initgraph(700, 700);
	setbkcolor(RGB(255, 218, 255)); cleardevice();
	setlinecolor(RGB(50, 102, 222));
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
	rectangle(50, 100, 650, 650);
	settextstyle(50, 0, _T("华文行楷"));
	setcolor(RGB(214, 10, 0));
	outtextxy(300, 20, _T("介绍"));
	settextstyle(20, 0, _T("楷体"));
	setcolor(BLACK);
	outtextxy(60, 180, _T("        象棋，我国传统的棋类益智游戏，在我国有着悠久的历史"));
	outtextxy(60, 200, _T("	 先秦时期已有记载。属于二人对抗性游戏的一种，由于用具简单"));
	outtextxy(60, 220, _T("	 趣味性强，成为流行极为广泛的棋艺活动。主要流行于华人及汉"));
	outtextxy(60, 240, _T("	 字文化圈的国家，象棋是中国正式开展的78个体育运动项目之一"));
	outtextxy(60, 260, _T("        本游戏为一款益智小游戏，用鼠标实现生活中常见的象棋"));
	outtextxy(60, 280, _T("   这一大众所喜爱的娱乐项目，本游戏简单易学趣味多，对于脑"));
	outtextxy(60, 300, _T("   力的开发有着非常好的作用，也适合打发时间，放松心情！"));
	outtextxy(60, 320, _T("       由于制作者水平有限，游戏漏洞不少，还望见谅！"));
	outtextxy(60, 340, _T("	   "));
	outtextxy(60, 360, _T("	  "));
	outtextxy(60, 380, _T("	     感谢您对我们的支持，我们会更加努力为您奉献更加有趣的"));
	outtextxy(60, 400, _T("	  小游戏，有我更有趣！ "));

	outtextxy(60, 510, _T("	                          编写成员:冉瑞龙  夏文齐 徐文莉"));
	outtextxy(60, 530, _T("	                                         2014 年 4 月 28日"));
	settextstyle(40, 0, _T("华文行楷"));
	setcolor(RGB(22, 69, 173));
	outtextxy(250, 550, _T("	 游戏愉快!"));
	settextstyle(20, 0, _T("华文行楷"));
	outtextxy(545, 600, _T("	 退出介绍"));
	setcolor(GREEN);
	rectangle(540, 590, 635, 625);
	while (true)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		if (m.x >= 540 && m.x <= 635 && m.y >= 590 && m.y <= 625)
			break;
	}
}