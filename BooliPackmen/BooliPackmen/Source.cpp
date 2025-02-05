#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
typedef char string[256];
#define NUM 10


void PrintMat(char mat[NUM + 1][NUM + 1]) {
	for (int i = 1; i <= NUM; i++) {
		for (int j = 1; j <= NUM; j++) {
			printf("%c\t", mat[i][j]);
		}
		printf("\n");
	}
}

void GetWalls(char mat[][NUM], int* PointsInBoard)
{
	int i, j;
	while (1) {
		printf("Enter values for a wall, row: ");
		scanf("%d", &i);
		printf("                  and column: ");
		scanf("%d", &j);
		if (i == 0 || j == 0)
			break;
		else
			mat[i][j] = '*';
	}

	for (int i = 0; i < NUM; i++) {
		for (int j = 0; j < NUM; j++) {
			if (mat[i][j] != '*') {
				mat[i][j] = '.';
				(*PointsInBoard)++;
			}
		}
	}
}
int checkBorders(int i, int j)
{
	if ((i < NUM) && (j < NUM) && (i >= 0) && (j >= 0))
		return 1;
	else
		return 0;
}
void BooliMovment(char mat[NUM][NUM], int numMovment, int* Bi, int* Bj, int* BooliPoints)
{
	if (numMovment == 1)
	{

		if (mat[*Bi][*Bj + 1] != '*' && (checkBorders))
		{
			if (mat[*Bi][*Bj + 1] == '.')
				++(*BooliPoints);  // הגדלת המשתנה לפני השימוש בו
			mat[*Bi][*Bj] = ' ';
			mat[*Bi][++*Bj] = 'B';
		}
	}
	else if (numMovment == 2)
	{

		if (mat[*Bi][*Bj - 1] != '*' && (checkBorders))
		{
			if (mat[*Bi][*Bj - 1] == '.')
				++(*BooliPoints);  // הגדלת המשתנה לפני השימוש בו
			mat[*Bi][*Bj] = ' ';
			mat[*Bi][--*Bj] = 'B';
		}
	}
	else if (numMovment == 3)
	{

		if (mat[*Bi - 1][*Bj] != '*' && (checkBorders))
		{
			if (mat[*Bi - 1][*Bj] == '.')
				++(*BooliPoints);  // הגדלת המשתנה לפני השימוש בו
			mat[*Bi][*Bj] = ' ';
			mat[--*Bi][*Bj] = 'B';
		}
	}
	else if (numMovment == 4)
	{

		if (mat[*Bi + 1][*Bj] != '*' && (checkBorders))
		{
			if (mat[*Bi + 1][*Bj] == '.')
				++(*BooliPoints);  // הגדלת המשתנה לפני השימוש בו
			mat[*Bi][*Bj] = ' ';
			mat[++*Bi][*Bj] = 'B';
		}
	}
}
void DovMovment(char mat[NUM][NUM], int* Di, int* Dj, int Bi, int Bj, char* oldValue)
{
	int iMove, jMove;

	if ((Bi - *Di) > 0)
		iMove = 1;
	else if ((Bi - *Di) < 0)
		iMove = -1;
	else
		iMove = 0;

	if ((Bj - *Dj) > 0)
		jMove = 1;
	else if ((Bj - *Dj) < 0)
		jMove = -1;
	else
		jMove = 0;

	if (mat[*Di + iMove][*Dj + jMove] != '*' && (*Di + iMove <= NUM) && (*Dj + jMove <= NUM) && (*Di + iMove >= 0) && (*Dj + jMove >= 0))
	{
		mat[*Di][*Dj] = *oldValue;
		*oldValue = mat[*Di + iMove][*Dj + jMove];
		mat[*Di + iMove][*Dj + jMove] = 'D';

		*Di = *Di + iMove;
		*Dj = *Dj + jMove;
	}
}
void MainGame()
{
	int Bi, Bj, Di, Dj, numMovment, numMovment2, PointsInBoard = 0;
	char mat[NUM][NUM] = { 0 };
	int checkEnd = 0;
	int BooliPoints = 0;
	char oldValue = ' ';

	GetWalls(mat, &PointsInBoard);
	printf("Enter values for the location of Booli, i and j: ");
	scanf("%d %d", &Bi, &Bj);
	mat[Bi][Bj] = 'B';

	printf("Enter values for the location of Dov, i and j: ");
	scanf("%d %d", &Di, &Dj);
	mat[Di][Dj] = 'D';

	PrintMat(mat);

	while (!checkEnd) {
		printf("Enter Booli movement (1=right, 2=left, 3=up, 4=down): ");
		scanf("%d", &numMovment);

		if (numMovment == 1 || numMovment == 2 || numMovment == 3 || numMovment == 4) {
			BooliMovment(mat, numMovment, &Bi, &Bj, &BooliPoints);
			DovMovment(mat, &Di, &Dj, Bi, Bj, &oldValue);
			PrintMat(mat);

			if (BooliPoints == PointsInBoard) {
				printf("\n\nBooli Won!!!");
				checkEnd = 1;
			}

			if (Bi == Di && Bj == Dj) {
				printf("\n\nBooli Lost!!!");
				checkEnd = 1;
			}
		}
		else {
			printf("\nYou can't move there");
			printf("\nBooli Lost!!!");
			checkEnd = 1;
		}
	}
}
void main()
{
	MainGame();
	printf("\n\nGood Game.\n\n\n");
}