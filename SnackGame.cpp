#include<iostream>
#include<ctime>
#include<conio.h>
#include<Windows.h>
using namespace std;
//Snack game贪吃蛇小游戏
//用于判断游戏起始和结束
bool gameover;
//游戏墙的长宽,地图尺寸(墙内空格数长宽)
const int width = 20;
const int height = 20;
int tailX[100], tailY[100];//记录尾部所有位置的数组
int nTail=0;//指定尾部长度，不超过100
//蛇的头坐标，friut坐标位置，分数变量声明;注意我的x实际上在height，也就是纵轴上
int x, y, fruitX, fruitY, score;
//改变蛇的位置操作
enum eDirection
{
	STOP=0,LEFT,RIGHT,UP,DOWN
};
eDirection dir;//操作蛇的方向
//初始化游戏设置
void Setup()
{
	gameover = false;
	dir = STOP;
	/*tailX[0] = x;
	tailY[0] = y;*/
	//输入蛇头的起始位置
	x = height / 2;
	y = width / 2;
	//随机生成果实数目
	srand(time(0));
	fruitX = rand() % height;
	fruitY = rand() %width;
	score = 0;
}
//绘制游戏地图（以字符#代替墙）
void Draw()
{
	system("cls");
	
	//打印最上方墙
	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;
	//打印地图内部
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			//打印蛇头
			if (j == y && i == x)
				cout << "O";
			//打印果实
			else if (j == fruitY && i == fruitX)
				cout << "F";
			else
			{
				//很关键，判断是否打印尾巴，否则可能地图没有完全生成
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == i && tailY[k] == j)
					{
						cout << "o";
						print = true;
					}
					
				}
				if (!print)//如果没打印尾巴
					cout << " ";
			}
				
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}
	//打印最下方墙
	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;
	cout << endl;
	cout << "score:" << score << endl;
}
//新知识，关于如何让计算机读取操作者键盘上进行的指令的一些函数以及使用方法
void Input()
{
	//conio.h头文件的函数（同步程序进行，不会阻断）
	//从控制台窗口获取字符的函数
	if (_kbhit())//判断键盘是否有压力，如果有返回一个正数，如果没有返回0;而且应该是持续识别该字符，直到键盘上按下新的按钮
	{
		switch(_getch())
		{
			//这个函数会返回我的键盘上摁下的字符的ASCII码
			//利用键盘移动蛇头
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
//实现游戏的逻辑操作
void Logic()
{
	
	//记录尾部位置
	int prevX = tailX[0];
	int prevY = tailY[0];
	//辅助参数，记录过渡的尾部位置
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	//更新所有尾部位置
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
	//如果撞墙
	/*if (x > height || x<0 || y>width || y < 0)
		gameover = true;*/
	//a funny version:可以穿墙，不会因撞墙而死
	if (x >= height) x = 0;
	if (x < 0)x = height - 1;
	if (y >= width) y = 0;
	if (y < 0)y =width - 1;
	//如果我们撞到自己的尾巴，游戏结束
	for (int i = 0; i < nTail; i++)
	{
		if (x == tailX[i] && y == tailY[i])
			gameover = true;
	}
	if (x == fruitX && y == fruitY)
	{
		//吃到果实
		score += 100;
		fruitX = rand() % height;
		fruitY = rand() % width;
		nTail++;
	}
}
int main()
{
	
	Setup();
	// 新知识，Windows.h文件中的隐藏光标函数，由于Draw（）中的system("cls")，程序运行时间太快导致输出屏幕闪烁，隐藏光标
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
		Sleep(100);//增加延迟，控制刷新速度，单位毫秒
	}

	// 显示光标
	cursorInfo.bVisible = true;
	SetConsoleCursorInfo(hOut, &cursorInfo);

	cout << "Game Over!" << endl;
	system("pause");
	return 0;
}

//GetStdHandle函数：用于获取标准输出的句柄。通过指定STD_OUTPUT_HANDLE参数，可以获取控制台输出的句柄。
//
//GetConsoleCursorInfo函数：用于获取控制台光标信息。通过传入控制台输出的句柄和CONSOLE_CURSOR_INFO结构体的指针，可以获取光标的信息。
//
//SetConsoleCursorInfo函数：用于设置控制台光标信息。通过传入控制台输出的句柄和CONSOLE_CURSOR_INFO结构体的指针，可以设置光标的信息。
//
//Sleep函数：用于添加延迟。通过传入延迟的毫秒数，可以使程序暂停执行指定的时间。
//
//在这里，我使用GetStdHandle函数获取标准输出的句柄，然后使用GetConsoleCursorInfo函数获取光标信息。接着，我将光标的可见性设置为false，即隐藏光标，使用SetConsoleCursorInfo函数将设置应用到控制台输出上。
//
//这样做的目的是隐藏光标，避免光标在地图刷新时的闪烁。
//
//另外，我在游戏循环中使用了Sleep函数来添加延迟，控制刷新速度。通过调整延迟时间，你可以控制游戏的运行速度，减少闪烁问题的出现。
//
//最后，在游戏结束后，我使用SetConsoleCursorInfo函数将光标的可见性设置为true，即显示光标，以恢复默认状态。