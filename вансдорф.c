#include <stdio.h>
#include <stdlib.h>
#define N 3 // изменение параметров доски

int board[N][N];
int turn_x[8] = { 1,  2,  1,  2, -1, -2, -1, -2};
int turn_y[8] = { 2,  1, -2, -1,  2,  1, -2, -1};

// Перебор с возвратом основанный на правиле Варнсдорфа
// Правило - откуда меньше ходов туда и пойдем
// Вообще правило как оказалось позже имеет контрпримеры
// Но они встречаются значительно реже, чем позиции с которых оно работает,
// А работу алгоритма оно ускоряет в разы(например попробуй точку начала 2 2 для N = 8)
// В обеих программах

void knight_turn(int i, int j, int d);
void print_board();

int main() {

	printf("Knight's position on %dx%d board?\n", N, N);
	int i = 0, j = 0;
	scanf("%d%d", &i, &j);
	board[i][j] = 1;
	
	knight_turn(i, j, 2);
	print_board();

	return 0;

}

void knight_turn(int i, int j, int d) {
	int min_turn = N;
	int X = -1, Y = -1;
	int num_turns = 0;
	int x = j;
	int y = i;
	for (int k = 0; k < 8; k++) {
		x = j + turn_x[k];
		y = i + turn_y[k];
		num_turns = 0;
		if (x >= 0 && x < N && y >= 0 && y < N && board[y][x] == 0) {
			if (d == N * N) {
				X = x;
				Y = y;
			}
			for (int q = 0; q < 8 ; q++) {
				int t_x = x + turn_x[q];
				int t_y = y + turn_y[q];
				if (t_x >= 0 && t_x < N && t_y >= 0 && t_y < N && board[t_y][t_x] == 0) {
					num_turns++;
				}
			}
		}
		if (num_turns < min_turn && num_turns != 0) {
			X = x;
			Y = y;
			min_turn = num_turns;
		}
	}
	if (X >= 0 && Y >= 0) {
		board[Y][X] = d;
		knight_turn(Y, X, d + 1);
	}
}

void print_board() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			if (board[i][j] != 0)
				printf("%3d", board[i][j]);
			else
				printf("###");
		printf("\n");
	}
	printf("\n");
}
