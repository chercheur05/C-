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
	printf("1.��ʼ��Ϸ\n0.������Ϸ\n");
	printf("==============\n");
	printf("����������ѡ��\n");
	int choice = 0;
	scanf("%d", &choice);
	return choice;
}

void Init(char show_map[ROW + 2][COL + 2], char mine_map[ROW + 2][COL + 2]) {
	//�βζ�ά����ĵڶ����±����Ҫд������Ҫ��ʵ�ζ�Ӧ
	//1.�� show_map ��ʼ��Ϊȫ�ǡ� ��
	for (int row = 0; row < ROW + 2; ++row) {
		for (int col = 0; col < COL + 2; ++col) {
			show_map[row][col] = ' ';
		}
	}
	//2.�� mine_map ��ʼ��Ϊȫ�ǡ�0��
	for (int row = 0; row < ROW + 2; ++row) {
		for (int col = 0; col < COL + 2; ++col) {
			mine_map[row][col] = '0';
		}
	}
	//3.��mine_map ��Щλ���ǵ����Ų���
	int mine_count = MINE_COUNT;
	while (mine_count > 0) {
		//����������õ���
		//[1,9]
		int row = rand() % ROW + 1;
		int col = rand() % COL + 1;
		if (mine_map[row][col]=='1') {
			//��ǰ��������������Ѿ��е����� 
			continue;
		}
		mine_map[row][col] = '1';
		--mine_count;
	}
}

void DisplayMap(char map[ROW + 2][COL + 2]) {
	//��ӡ��ͼ
	//����Ҫ��ӡ����ͼ����ϸ���ݣ�˳���ӡ������

	//�ȴ�ӡ�����ϽǵĿո�
	printf("   ");
	//��ӡ�е�����
	for (int i = 1; i <= ROW; ++i) {
		printf(" %d", i);
	}
	printf("\n");
	//��ӡ�ϱ߿�
	for (int i = 1; i <= ROW; ++i) {
		printf("---");
	}
	printf("\n");
	//���д�ӡ��ͼ����
	for (int row = 1; row <= ROW; ++row) {
		//�ȴ�ӡ�к�
		printf(" %d|", row);
		//��ӡ���е�ÿһ��
		for (int col = 1; col <= COL; ++col) {
			printf(" %c", map[row][col]);
		}
		printf("\n");
	}
}

void UpdataShowMap(char show_map[ROW + 2][COL + 2], char mine_map[ROW + 2][COL + 2], int row, int col) {
	//ͳ�Ƶ�ǰλ����Χ8�������м������ף������ָ��µ�������
	//row�ķ�Χ[1,9]
	int count = 0;
	//������ӱ߿򣬱��뱣֤ÿ��������ʵ�ʱ�򶼲���Խ��
	//�����Ҫ������� if �ж�
	//if (row - 1 >= 0 && row + 1 < ROW + 1
	//	&& col - 1 >= 0 && col + 1 < COL + 1) {
	//	if (mine_map[row - 1][col - 1] == '1') {
	//		++count;
	//	}
	//}

	//���˱߿�֮�󣬴���Ϳ��Լ�д��
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
	//���򻯵ķ���
		count = (mine_map[row - 1][col - 1] - '0') + (mine_map[row - 1][col] - '0')
			+ (mine_map[row - 1][col + 1] - '0') + (mine_map[row][col - 1] - '0')
			+ (mine_map[row][col + 1] - '0') + (mine_map[row + 1][col - 1] - '0')
			+ (mine_map[row + 1][col] - '0') + (mine_map[row + 1][col + 1] - '0');
		//�����Ǹ�λ���������޷�ת��Ϊ�ַ���ʽ
		show_map[row][col] = '0' + count;
}

void Updata(char show_map[ROW+2][COL+2], char mine_map[ROW + 2][COL + 2],int row,int col) {
	if (row >= 1 && row <= ROW && col >= 1 && col <= COL&& show_map[row][col] == ' ') {
		//������[1,9]��������,��δ����ֵ���ſɽ��еݹ�
		UpdataShowMap(show_map, mine_map, row, col);
		++safe_blank_count;
		if (show_map[row][col] == '0') {
			//��ø�����Χ�İ˸����ӣ�һֱ�����ֲ�Ϊ0
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

//1.ʹ�ö�ά�����ʾ��ͼ
//	a�����ײ��ֵ�ͼ��char���͵Ķ�ά���飬��'0'��ʾ���ǵ��ף�'1'��ʾ�ǵ��ף�
//	b����ҿ����ĵ�ͼ����Щλ��δ��������Щλ���ѷ�������
//	  ��char���͵Ķ�ά�����ʾ�������' ',��ʾδ������
//	   ���ֱ�ʾ�ѷ��������ҵ�ǰλ����Χ8�������м����ף�
//2.��ʼ��
//	a�����׵Ĳ��ֵ�ͼ���Ȱ������ά����ȫ����ʼ���ɡ�0������������趨����λ��Ϊ����
//	b����ҿ����ĵ�ͼ��ȫ����ʼ���ɡ� ����ʾδ����
//3.�ȴ�ӡ��ͼ����ҿ��ĵ�ͼ������ʾ����������꣬У��������������Ƿ�Ϸ�
//4.�����ҷ����ĸ����ǵ��ף���Ϸ��������ʾɨ��ʧ�ܣ�
//5.�����ҷ����ĸ��Ӳ��ǵ��ף�������������ǵ�ͼ�Ϸǵ��׵����һ��λ�ã�ɨ�׳ɹ�
//6.�����ҷ����Ĳ��ǵ��ף�����������Ӳ��ǵ�ͼ�����һ���ǵ��׵ĸ��ӣ�
//  �Ͱѵ�ͼ�ϵ�λ����Ϊչ��״̬�����Ҹ��¸�λ�ø�����8�����ӵĵ�����Ŀ
void Game() {
	//�ڵ�ͼ�����һȦ�߿�
	char show_map[ROW+2][COL+2];
	char mine_map[ROW+2][COL+2];
	//����������Ϊ��������ʽת��Ϊָ�룬������������������������Ѿ���Ϊָ���ˣ�
	//�ں����ڲ��Բ��������޸��ǻ�Ӱ�쵽�ⲿ�������
	Init(show_map,mine_map);

	
	while (1) {
		DisplayMap(show_map);
		int row = 0;
		int col = 0;
		printf("���������꣺");
		scanf("%d %d", &row, &col);
		if (row<1 || row>ROW || col<1 || col>col) {
			//��������Ƿ�.��Ҫע�⣡��ͼ�Ǵ��߿�ģ������ж�����ҪС�ĶԴ�
			printf("����������겻�Ϸ������������룡\n");
			continue;
		}
		//��֤�Ƿ�ȵ�����
		if (mine_map[row][col] == '1') {
			printf("��Ϸ������ɨ��ʧ��\n");
			break;
		}
		//��֤�Ƿ�ɨ�׳ɹ�
		if (safe_blank_count+1 == ROW * COL - MINE_COUNT) {
			printf("��Ϸ������ɨ�׳ɹ���\n");
			break;
		}
		//���µ�ͼ��״̬
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