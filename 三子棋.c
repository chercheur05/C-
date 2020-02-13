#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//1.使用字符类型二维数组来表示棋盘（3*3）
//   使用‘x'表示玩家的子，‘o’表示电脑的子
//2.玩家落子，给玩家一个提示，提示让玩家落子，输入一个坐标（row，col）
//3.判定游戏结束
//		a）玩家获胜
//		b）电脑获胜
//		c）和棋
//		d）游戏没结束
//4.电脑落子，电脑随便下（随机数的方式）
//5.判定游戏结束
//		a）玩家获胜
//		b）电脑获胜
//		c）和棋
//		d）游戏没结束

#define	ROW 3
#define COL 3

//g_ 前缀表示全局变量
char g_broad[ROW][COL];

void Init() {
	//把数组中的每个元素都初始化成‘ ’空格
	for (int row = 0; row < ROW; ++row) {
		for (int col = 0; col < COL; ++col) {
			g_broad[row][col] = ' ';
		}
	}
}

void Print() {
	for (int row=0; row < ROW; ++row) {
		printf("| %c | %c | %c |\n", g_broad[row][0],
			g_broad[row][1], g_broad[row][2]);
		if (row != ROW - 1) {
			printf("|---|---|---|\n");
		}
		
	}
}

void PlayerMove() {
	printf("玩家落子！\n");
	while (1) {
		printf("请输入一组坐标（row col）：");
		int row = 0;
		int col = 0;
		scanf("%d %d", &row, &col);
		if (row < 0 || row >= ROW || col < 0 || col >= COL) {
			//用户输入坐标非法
			printf("坐标输入非法！请重新输入！\n");
			continue;
		}
		if (g_broad[row][col] != ' ') {
			printf("当前位置已经有子了，请重新输入！\n");
			continue;
		}
		g_broad[row][col] = 'x';
		break;
	}
}

void ComputerMove() {
	//随便下 电脑产生两个随机数
	printf("电脑落子！\n");
	while (1) {
		int row = rand() % ROW;
		int col = rand() % COL;
		if (g_broad[row][col] != ' ') {
			//当前的位置已经被占用了！
			continue;
		}
		g_broad[row][col] = 'o';
		break;
	}
}

//如果满了，返回1，如果没满，返回0
int IsFull() {
	for (int row = 0; row < ROW; ++row) {
		for (int col = 0; col < COL; ++col) {
			if (g_broad[row][col]==' ') {
				return 0;
			}
		}
	}
	//如果遍历结束也没有找到空格，说明棋盘满了！和棋
	return 1;
}
//这个函数返回了当前游戏胜负情况
//返回了‘x'，表示玩家获胜
//返回了‘o'，表示电脑获胜
//返回了‘q’，表示和棋
//返回了‘ ’，表示游戏还没有结束
char CheckWinner(){
	//先检查所有的行
	for (int row = 0; row < ROW; ++row) {
		if (g_broad[row][0] == g_broad[row][1]
			&& g_broad[row][0] == g_broad[row][2]
			&& g_broad[row][0] != ' ') {
			return g_broad[row][0];
		}
	}
	//再检查所有的列
	for (int col = 0; col < COL; ++col) {
		if (g_broad[0][col] == g_broad[1][col]
			&& g_broad[0][col] == g_broad[2][col]
			&& g_broad[0][col] != ' ') {
			return g_broad[0][col];
		}
	}
	//在检查所有的对角线
	if (g_broad[0][0] == g_broad[1][1]
		&& g_broad[0][0] == g_broad[2][2]
		&& g_broad[0][0] != ' ') {
		return g_broad[0][0];
	}
	if (g_broad[2][0] == g_broad[1][1]
		&& g_broad[2][0] == g_broad[0][2]
		&& g_broad[2][0] != ' ') {
		return g_broad[2][0];
	}
	if (IsFull()) {
		return 'q';
	}
	return ' ';
}

int main() {
	srand((unsigned int)time(0));//强制类型转换，防止有警告
	Init();//初始化函数,因为字符数组是全局变量，所以不需要传参
	char winner = '\0';
	while (1)
	{
		system("cls");//清理棋盘
		Print();//打印棋盘
		PlayerMove();
		winner = CheckWinner();
		if(winner != ' '){
			Print();
			printf("游戏结束，赢家是 %c\n",winner);
			return 0;
		}
		ComputerMove();
		winner = CheckWinner();
		if(winner != ' '){
			Print();
			printf("游戏结束，赢家是 %c\n",winner);
			return 0;
		}
	}
	system("pause");
	return 0;
}