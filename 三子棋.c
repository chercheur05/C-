#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//1.ʹ���ַ����Ͷ�ά��������ʾ���̣�3*3��
//   ʹ�á�x'��ʾ��ҵ��ӣ���o����ʾ���Ե���
//2.������ӣ������һ����ʾ����ʾ��������ӣ�����һ�����꣨row��col��
//3.�ж���Ϸ����
//		a����һ�ʤ
//		b�����Ի�ʤ
//		c������
//		d����Ϸû����
//4.�������ӣ���������£�������ķ�ʽ��
//5.�ж���Ϸ����
//		a����һ�ʤ
//		b�����Ի�ʤ
//		c������
//		d����Ϸû����

#define	ROW 3
#define COL 3

//g_ ǰ׺��ʾȫ�ֱ���
char g_broad[ROW][COL];

void Init() {
	//�������е�ÿ��Ԫ�ض���ʼ���ɡ� ���ո�
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
	printf("������ӣ�\n");
	while (1) {
		printf("������һ�����꣨row col����");
		int row = 0;
		int col = 0;
		scanf("%d %d", &row, &col);
		if (row < 0 || row >= ROW || col < 0 || col >= COL) {
			//�û���������Ƿ�
			printf("��������Ƿ������������룡\n");
			continue;
		}
		if (g_broad[row][col] != ' ') {
			printf("��ǰλ���Ѿ������ˣ����������룡\n");
			continue;
		}
		g_broad[row][col] = 'x';
		break;
	}
}

void ComputerMove() {
	//����� ���Բ������������
	printf("�������ӣ�\n");
	while (1) {
		int row = rand() % ROW;
		int col = rand() % COL;
		if (g_broad[row][col] != ' ') {
			//��ǰ��λ���Ѿ���ռ���ˣ�
			continue;
		}
		g_broad[row][col] = 'o';
		break;
	}
}

//������ˣ�����1�����û��������0
int IsFull() {
	for (int row = 0; row < ROW; ++row) {
		for (int col = 0; col < COL; ++col) {
			if (g_broad[row][col]==' ') {
				return 0;
			}
		}
	}
	//�����������Ҳû���ҵ��ո�˵���������ˣ�����
	return 1;
}
//������������˵�ǰ��Ϸʤ�����
//�����ˡ�x'����ʾ��һ�ʤ
//�����ˡ�o'����ʾ���Ի�ʤ
//�����ˡ�q������ʾ����
//�����ˡ� ������ʾ��Ϸ��û�н���
char CheckWinner(){
	//�ȼ�����е���
	for (int row = 0; row < ROW; ++row) {
		if (g_broad[row][0] == g_broad[row][1]
			&& g_broad[row][0] == g_broad[row][2]
			&& g_broad[row][0] != ' ') {
			return g_broad[row][0];
		}
	}
	//�ټ�����е���
	for (int col = 0; col < COL; ++col) {
		if (g_broad[0][col] == g_broad[1][col]
			&& g_broad[0][col] == g_broad[2][col]
			&& g_broad[0][col] != ' ') {
			return g_broad[0][col];
		}
	}
	//�ڼ�����еĶԽ���
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
	srand((unsigned int)time(0));//ǿ������ת������ֹ�о���
	Init();//��ʼ������,��Ϊ�ַ�������ȫ�ֱ��������Բ���Ҫ����
	char winner = '\0';
	while (1)
	{
		system("cls");//��������
		Print();//��ӡ����
		PlayerMove();
		winner = CheckWinner();
		if(winner != ' '){
			Print();
			printf("��Ϸ������Ӯ���� %c\n",winner);
			return 0;
		}
		ComputerMove();
		winner = CheckWinner();
		if(winner != ' '){
			Print();
			printf("��Ϸ������Ӯ���� %c\n",winner);
			return 0;
		}
	}
	system("pause");
	return 0;
}