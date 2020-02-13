#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define	ROW 9
#define COL 9
#define MINE_COUNT 10
int safe_blank_count = 0;

int Menu() {
	printf("==============\n");
	printf("1.开始游戏\n0.结束游戏\n");
	printf("==============\n");
	printf("请输入您的选择：\n");
	int choice = 0;
	scanf("%d", &choice);
	return choice;
}

void Init(char show_map[ROW + 2][COL + 2], char mine_map[ROW + 2][COL + 2]) {
	//形参二维数组的第二个下标必须要写，并且要与实参对应
	//1.把 show_map 初始化为全是‘ ’
	for (int row = 0; row < ROW + 2; ++row) {
		for (int col = 0; col < COL + 2; ++col) {
			show_map[row][col] = ' ';
		}
	}
	//2.把 mine_map 初始化为全是‘0’
	for (int row = 0; row < ROW + 2; ++row) {
		for (int col = 0; col < COL + 2; ++col) {
			mine_map[row][col] = '0';
		}
	}
	//3.把mine_map 哪些位置是地雷排布好
	int mine_count = MINE_COUNT;
	while (mine_count > 0) {
		//尝试随机设置地雷
		//[1,9]
		int row = rand() % ROW + 1;
		int col = rand() % COL + 1;
		if (mine_map[row][col]=='1') {
			//当前随机产生的坐标已经有地雷了 
			continue;
		}
		mine_map[row][col] = '1';
		--mine_count;
	}
}

void DisplayMap(char map[ROW + 2][COL + 2]) {
	//打印地图
	//不光要打印出地图的详细内容，顺便打印出坐标

	//先打印出左上角的空格
	printf("   ");
	//打印列的坐标
	for (int i = 1; i <= ROW; ++i) {
		printf(" %d", i);
	}
	printf("\n");
	//打印上边框
	for (int i = 1; i <= ROW; ++i) {
		printf("---");
	}
	printf("\n");
	//按行打印地图内容
	for (int row = 1; row <= ROW; ++row) {
		//先打印行号
		printf(" %d|", row);
		//打印该行的每一列
		for (int col = 1; col <= COL; ++col) {
			printf(" %c", map[row][col]);
		}
		printf("\n");
	}
}

void UpdataShowMap(char show_map[ROW + 2][COL + 2], char mine_map[ROW + 2][COL + 2], int row, int col) {
	//统计当前位置周围8个格子有几个地雷，把数字更新到格子上
	//row的范围[1,9]
	int count = 0;
	//如果不加边框，必须保证每个坐标访问的时候都不能越界
	//代码就要多加许多的 if 判定
	//if (row - 1 >= 0 && row + 1 < ROW + 1
	//	&& col - 1 >= 0 && col + 1 < COL + 1) {
	//	if (mine_map[row - 1][col - 1] == '1') {
	//		++count;
	//	}
	//}

	//有了边框之后，代码就可以简单写成
	//if (mine_map[row - 1][col - 1] == '1') {
	//	++count;
	//}
	//if (mine_map[row - 1][col] == '1') {
	//	++count;
	//}
	//if (mine_map[row - 1][col + 1] == '1') {
	//	++count;
	//}
	//if (mine_map[row][col - 1] == '1') {
	//	++count;
	//}
	//if (mine_map[row][col + 1] == '1') {
	//	++count;
	//}
	//if (mine_map[row + 1][col - 1] == '1') {
	//	++count;
	//}
	//if (mine_map[row + 1][col] == '1') {
	//	++count;
	//}
	//if (mine_map[row + 1][col+1] == '1') {
	//	++count;
	//}
	//更简化的方法
		count = (mine_map[row - 1][col - 1] - '0') + (mine_map[row - 1][col] - '0')
			+ (mine_map[row - 1][col + 1] - '0') + (mine_map[row][col - 1] - '0')
			+ (mine_map[row][col + 1] - '0') + (mine_map[row + 1][col - 1] - '0')
			+ (mine_map[row + 1][col] - '0') + (mine_map[row + 1][col + 1] - '0');
		//必须是个位数，否则无法转换为字符格式
		show_map[row][col] = '0' + count;
}

void Updata(char show_map[ROW+2][COL+2], char mine_map[ROW + 2][COL + 2],int row,int col) {
	if (row >= 1 && row <= ROW && col >= 1 && col <= COL&& show_map[row][col] == ' ') {
		//行数在[1,9]的区间内,且未赋过值，才可进行递归
		UpdataShowMap(show_map, mine_map, row, col);
		++safe_blank_count;
		if (show_map[row][col] == '0') {
			//算该格子周围的八个格子，一直到数字不为0
			Updata(show_map, mine_map, row - 1, col - 1);
			Updata(show_map, mine_map, row - 1, col);
			Updata(show_map, mine_map, row - 1, col + 1);
			Updata(show_map, mine_map, row, col - 1);
			Updata(show_map, mine_map, row, col + 1);
			Updata(show_map, mine_map, row + 1, col - 1);
			Updata(show_map, mine_map, row + 1, col);
			Updata(show_map, mine_map, row + 1, col + 1);
		}
		else {
			return;
		}
	}
}

//1.使用二维数组表示地图
//	a）地雷布局地图（char类型的二维数组，用'0'表示不是地雷，'1'表示是地雷）
//	b）玩家看到的地图（哪些位置未翻开，哪些位置已翻开），
//	  （char类型的二维数组表示，如果是' ',表示未翻开，
//	   数字表示已翻开，并且当前位置周围8个格子有几个雷）
//2.初始化
//	a）地雷的布局地图，先把这个二维数组全都初始化成‘0’，再随机的设定若干位置为地雷
//	b）玩家看到的地图，全部初始化成‘ ’表示未翻开
//3.先打印地图（玩家看的地图），提示玩家输入坐标，校验玩家输入数据是否合法
//4.如果玩家翻开的格子是地雷，游戏结束（提示扫雷失败）
//5.如果玩家翻开的格子不是地雷，并且这个格子是地图上非地雷的最后一个位置，扫雷成功
//6.如果玩家翻开的不是地雷，并且这个格子不是地图上最后一个非地雷的格子，
//  就把地图上的位置设为展开状态，并且更新该位置附近的8个格子的地雷数目
void Game() {
	//在地图外加上一圈边框
	char show_map[ROW+2][COL+2];
	char mine_map[ROW+2][COL+2];
	//由于数组作为参数会隐式转换为指针，拿着数组名传到函数里面就已经成为指针了，
	//在函数内部对参数进行修改是会影响到外部的数组的
	Init(show_map,mine_map);

	
	while (1) {
		DisplayMap(show_map);
		int row = 0;
		int col = 0;
		printf("请输入坐标：");
		scanf("%d %d", &row, &col);
		if (row<1 || row>ROW || col<1 || col>col) {
			//坐标输入非法.需要注意！地图是带边框的，所以判定规则要小心对待
			printf("您输入的坐标不合法，请重新输入！\n");
			continue;
		}
		//验证是否踩到地雷
		if (mine_map[row][col] == '1') {
			printf("游戏结束！扫雷失败\n");
			break;
		}
		//验证是否扫雷成功
		if (safe_blank_count+1 == ROW * COL - MINE_COUNT) {
			printf("游戏结束！扫雷成功！\n");
			break;
		}
		//更新地图的状态
		Updata(show_map, mine_map,row, col);
		system("cls");
	}
	DisplayMap(mine_map);
}


int main() {
	//srand((unsigned int)time(0));
	while (1) {
		int choice = Menu();
		if (choice == 0) {
			printf("Goodbye!\n");
			break;
		}
		if (choice == 1) {
			Game();
		}
	}
	system("pause");
	return 0;
}