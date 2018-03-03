/*-------------------------------------
c��� ���ھ߱� �ΰ����� ������Ʈ
������ : �����   �Ҽ� : �뱸����Ʈ�������б�
������Ʈ �������� : 7�� 8��   «���� �ð����� ƴƴ�� �ڵ�

�� �ڵ忡 ���� ���۱��� ����� ���� ������ ���� ����� ���ؾ� �մϴ�.

������� 0.0

--��ġ��Ʈ--

----------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

void createainumber(int *ainum);
void scanfirst(int *usnum);
void scan(int(*usre)[100], int *ainum, int turn);
void aiscan(int(*aire)[100], int *usnum, int(*aiall)[10][10], int t);
void aicheck(int(*aiall)[10][10], int(*aire)[100], int t);
void record(int(*re)[100], int *num, int t);

int main() {

	srand((unsigned int)time(NULL));

	int i, j, k;

	int aire[5][100] = { 0, }; //3��° : s 4��° : b 5��° ����
	int aiall[10][10][10] = { 0, };
	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
			for (k = 0; k < 10; k++)
				if (i == j || j == k || i == k)
					aiall[i][j][k] = -1;
	int ainum[10] = { 0, };

	int usre[5][100] = { 0, };
	int usnum[3] = { 0, };

	int turn = 0;

	createainumber(ainum);
	scanfirst(usnum);


	while (aire[3][turn-1] != 3) {

		scan(usre, ainum, turn);
		aiscan(aire, usnum, aiall, turn);
		aicheck(aiall, aire, turn);

		turn++;
	}



	return 0;

}

void createainumber(int *ainum) {

	int i;

	for (i = 0; i < 3; i++) {

		ainum[i] = rand() % 10;

		if (i == 1 && ainum[i] == ainum[0])
			ainum[i--] = 0;
		else if (i == 2 && (ainum[i] == ainum[1] || ainum[i] == ainum[0]))
			ainum[i--] = 0;
		//printf("%d", ainum[i]);
	}
	printf("\n");

}

void scanfirst(int *usnum) {
	int i;
	printf("����� ���ڸ� ������ �ּ��� : ");

	for (i = 0; i < 3; i++) {
		usnum[i] = _getch() - '0';

		if (usnum[i] < 0 || usnum[i] > 9)
			usnum[i--] = 0;
		else if (i == 1 && usnum[i] == usnum[0])
			i--;
		else if (i == 2 && (usnum[i] == usnum[1] || usnum[i] == usnum[0])) {
			i--;
		}
		else
			printf("%d", usnum[i]);

	}

	printf("\n\n    ��                    AI\n\n\n");
}

void scan(int(*usre)[100], int *ainum, int t) {
	
	int i;

	for (i = 0; i < 3; i++) {

		usre[i][t] = _getch() - '0';

		if (usre[i][t] == 8 - '0') {
			usre[i - 1][t] = 0;
			i -= 2;
			printf("\b \b");
		}
		else if (usre[i][t] < 0 || usre[i][t] > 9)
			usre[i--][t] = 0;
		else if (i == 1 && usre[i][t] == usre[0][t])
			usre[i--][t] = 0;
		else if (i == 2 && (usre[i][t] == usre[0][t] || usre[i][t] == usre[1][t])) {
			usre[i--][t] = 0;
		}
		else
			printf("%d", usre[i][t]);

	}

	record(usre, ainum, t);
	

}

void aiscan(int(*aire)[100], int *usnum, int(*aiall)[10][10], int t) {

	
	int i;
	int x, y, z;
	x = y = z = 0;

	while (aiall[x][y][z] == -1) {
		x = y = z = 0;

		for (i = 0; i < 3; i++) 
			aire[i][t] = rand() % 10;
		
		x = aire[0][t];
		y = aire[1][t];
		z = aire[2][t];

	}
	
	printf("%d %d %d   ", aire[0][t], aire[1][t], aire[2][t]);
	record(aire, usnum, t);
	printf("\n");
	
}

void aicheck(int(*aiall)[10][10], int(*aire)[100], int t) {

	int i, j, k;
	int s = 0, b = 0;
	int t0 = aire[0][t], t1 = aire[1][t], t2 = aire[2][t];

	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			for (k = 0; k < 10; k++) {

				s = 0, b = 0;

				if (i == aire[0][t])
					s++;
				else if (i == aire[1][t])
					b++;
				else if (i == aire[2][t])
					b++;

				if (j == aire[1][t])
					s++;
				else if (j == aire[0][t])
					b++;
				else if (j == aire[2][t])
					b++;

				if (k == aire[2][t])
					s++;
				else if (k == aire[0][t])
					b++;
				else if (k == aire[1][t])
					b++;

				if (s != aire[3][t] || b != aire[4][t])
					aiall[i][j][k] = -1;
			}
		}
	}
}

void record(int(*re)[100], int *num, int t) {
	
	int i, s = 0, b = 0;
	int tmp1 = 0, tmp2 = 0;

	for (i = 0; i < 3; i++) {

		tmp1 = (i + 1) % 3;
		tmp2 = (i + 2) % 3;
		if (re[i][t] == num[i])
			s++;
		else if (re[i][t] == num[tmp1])
			b++;
		else if (re[i][t] == num[tmp2])
			b++;
	}

	re[3][t] = s;
	re[4][t] = b;
	printf("    %ds %db        ", s, b);
}