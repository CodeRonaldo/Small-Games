#include<iostream>
#include<ctime>
#include<conio.h>
#include<Windows.h>
using namespace std;
//Snack gamḛ����С��Ϸ
//�����ж���Ϸ��ʼ�ͽ���
bool gameover;
//��Ϸǽ�ĳ���,��ͼ�ߴ�(ǽ�ڿո�������)
const int width = 20;
const int height = 20;
int tailX[100], tailY[100];//��¼β������λ�õ�����
int nTail=0;//ָ��β�����ȣ�������100
//�ߵ�ͷ���꣬friut����λ�ã�������������;ע���ҵ�xʵ������height��Ҳ����������
int x, y, fruitX, fruitY, score;
//�ı��ߵ�λ�ò���
enum eDirection
{
	STOP=0,LEFT,RIGHT,UP,DOWN
};
eDirection dir;//�����ߵķ���
//��ʼ����Ϸ����
void Setup()
{
	gameover = false;
	dir = STOP;
	/*tailX[0] = x;
	tailY[0] = y;*/
	//������ͷ����ʼλ��
	x = height / 2;
	y = width / 2;
	//������ɹ�ʵ��Ŀ
	srand(time(0));
	fruitX = rand() % height;
	fruitY = rand() %width;
	score = 0;
}
//������Ϸ��ͼ�����ַ�#����ǽ��
void Draw()
{
	system("cls");
	
	//��ӡ���Ϸ�ǽ
	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;
	//��ӡ��ͼ�ڲ�
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			//��ӡ��ͷ
			if (j == y && i == x)
				cout << "O";
			//��ӡ��ʵ
			else if (j == fruitY && i == fruitX)
				cout << "F";
			else
			{
				//�ܹؼ����ж��Ƿ��ӡβ�ͣ�������ܵ�ͼû����ȫ����
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == i && tailY[k] == j)
					{
						cout << "o";
						print = true;
					}
					
				}
				if (!print)//���û��ӡβ��
					cout << " ";
			}
				
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}
	//��ӡ���·�ǽ
	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;
	cout << endl;
	cout << "score:" << score << endl;
}
//��֪ʶ����������ü������ȡ�����߼����Ͻ��е�ָ���һЩ�����Լ�ʹ�÷���
void Input()
{
	//conio.hͷ�ļ��ĺ�����ͬ��������У�������ϣ�
	//�ӿ���̨���ڻ�ȡ�ַ��ĺ���
	if (_kbhit())//�жϼ����Ƿ���ѹ��������з���һ�����������û�з���0;����Ӧ���ǳ���ʶ����ַ���ֱ�������ϰ����µİ�ť
	{
		switch(_getch())
		{
			//��������᷵���ҵļ��������µ��ַ���ASCII��
			//���ü����ƶ���ͷ
		case 'a':
			dir = LEFT;
			break;
        case 'd':
	        dir = RIGHT;
	        break;
		case'w':
			dir = UP;
			break;
		case's':
			dir = DOWN;
			break;
		case'x':
			dir = STOP;
			gameover = true;
			break;
		}
	}
}
//ʵ����Ϸ���߼�����
void Logic()
{
	
	//��¼β��λ��
	int prevX = tailX[0];
	int prevY = tailY[0];
	//������������¼���ɵ�β��λ��
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	//��������β��λ��
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch(dir)
	{
	case STOP:
		break;
	case LEFT:
		y--;
		break;
	case RIGHT:
		y++;
		break;
	case UP:
		x--;
		break;
	case DOWN:
		x++;
		break;
	default:
		break;

	}
	//���ײǽ
	/*if (x > height || x<0 || y>width || y < 0)
		gameover = true;*/
	//a funny version:���Դ�ǽ��������ײǽ����
	if (x >= height) x = 0;
	if (x < 0)x = height - 1;
	if (y >= width) y = 0;
	if (y < 0)y =width - 1;
	//�������ײ���Լ���β�ͣ���Ϸ����
	for (int i = 0; i < nTail; i++)
	{
		if (x == tailX[i] && y == tailY[i])
			gameover = true;
	}
	if (x == fruitX && y == fruitY)
	{
		//�Ե���ʵ
		score += 100;
		fruitX = rand() % height;
		fruitY = rand() % width;
		nTail++;
	}
}
int main()
{
	
	Setup();
	// ��֪ʶ��Windows.h�ļ��е����ع�꺯��������Draw�����е�system("cls")����������ʱ��̫�쵼�������Ļ��˸�����ع��
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hOut, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hOut, &cursorInfo);
	while (!gameover)
	{
		Draw();
		Input();
		Logic();
		Sleep(100);//�����ӳ٣�����ˢ���ٶȣ���λ����
	}

	// ��ʾ���
	cursorInfo.bVisible = true;
	SetConsoleCursorInfo(hOut, &cursorInfo);

	cout << "Game Over!" << endl;
	system("pause");
	return 0;
}

//GetStdHandle���������ڻ�ȡ��׼����ľ����ͨ��ָ��STD_OUTPUT_HANDLE���������Ի�ȡ����̨����ľ����
//
//GetConsoleCursorInfo���������ڻ�ȡ����̨�����Ϣ��ͨ���������̨����ľ����CONSOLE_CURSOR_INFO�ṹ���ָ�룬���Ի�ȡ������Ϣ��
//
//SetConsoleCursorInfo�������������ÿ���̨�����Ϣ��ͨ���������̨����ľ����CONSOLE_CURSOR_INFO�ṹ���ָ�룬�������ù�����Ϣ��
//
//Sleep��������������ӳ١�ͨ�������ӳٵĺ�����������ʹ������ִͣ��ָ����ʱ�䡣
//
//�������ʹ��GetStdHandle������ȡ��׼����ľ����Ȼ��ʹ��GetConsoleCursorInfo������ȡ�����Ϣ�����ţ��ҽ����Ŀɼ�������Ϊfalse�������ع�꣬ʹ��SetConsoleCursorInfo����������Ӧ�õ�����̨����ϡ�
//
//��������Ŀ�������ع�꣬�������ڵ�ͼˢ��ʱ����˸��
//
//���⣬������Ϸѭ����ʹ����Sleep����������ӳ٣�����ˢ���ٶȡ�ͨ�������ӳ�ʱ�䣬����Կ�����Ϸ�������ٶȣ�������˸����ĳ��֡�
//
//�������Ϸ��������ʹ��SetConsoleCursorInfo���������Ŀɼ�������Ϊtrue������ʾ��꣬�Իָ�Ĭ��״̬��