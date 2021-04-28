#include <stdio.h>
#include <stdlib.h>

// Перебор с возвратом основанный на правиле Варнсдорфа
// Правило - откуда меньше ходов туда и пойдем
// Вообще правило как оказалось позже имеет контрпримеры
// Но они встречаются значительно реже, чем позиции с которых оно работает,
// А работу алгоритма оно ускоряет в разы(например попробуй точку начала 2 2 для N = 8)
// В обеих программах

void knight_turn(int **board, int N, int M, int i, int j, int d);
void print_board(int **board, int N, int M);
int turn_num(int **board,int N, int M, int x, int y);
int isMovePossible(int N, int M, int x, int y);


int main() {

	printf("Enter the board size: ");
	int N = 0, M = 0;
	scanf("%d%d", &N, &M);
	
	int **board = (int **)malloc(sizeof(int *) * N);
	for (int i = 0; i < N; i++)
		board[i] = (int *)calloc(M, sizeof(int));
	
	printf("Knight's position on %dx%d board?\n", N, M);
	int i = 0, j = 0;
	scanf("%d%d", &i, &j);
	i--;
	j--;
	board[i][j] = 1;
	
	knight_turn(board, N, M, i, j, 2);
	print_board(board, N, M);

	return 0;

}

void knight_turn(int **board, int N, int M, int i, int j, int d) {
	int turn_x[8] = { 1,  2,  1,  2, -1, -2, -1, -2};
	int turn_y[8] = { 2,  1, -2, -1,  2,  1, -2, -1};
	int min_turn = 9;
	int X = -1, Y = -1;
	int num_turns;
	int x = j;
	int y = i;
	for (int k = 0; k < 8; k++) {
		x = j + turn_x[k];
		y = i + turn_y[k];
		num_turns = 0;
		if (isMovePossible(N, M, x, y) && board[y][x] == 0) {
			if (d == N * M) {
				X = x;
				Y = y;
			}
			num_turns = turn_num(board, N, M, x, y);
		}
		if (num_turns < min_turn && num_turns != 0) {
			X = x;
			Y = y;
			min_turn = num_turns;
		}
	}
	if (X >= 0 && Y >= 0) {
		board[Y][X] = d;
		knight_turn(board, N, M, Y, X, d + 1);
	}
}

void print_board(int **board, int N, int M) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			if (board[i][j] != 0)
				printf("%3d", board[i][j]);
			else
				printf("###");
		printf("\n");
	}
}

int turn_num(int **board,int N, int M, int x, int y) {
	int turn_x[8] = { 1,  2,  1,  2, -1, -2, -1, -2};
	int turn_y[8] = { 2,  1, -2, -1,  2,  1, -2, -1};
	int count = 0;
	int x_1, y_1;
	for (int i = 0; i < 8; i++) {
		x_1 = x + turn_x[i];
		y_1 = y + turn_y[i];
		if (isMovePossible(N, M, x_1, y_1) && board[y_1][x_1] == 0)
			count++;
	}
	return count;
}

int isMovePossible(int N, int M, int x, int y) {
	return ((x < M) && (x > -1) && (y < N) && (y > -1));
}
