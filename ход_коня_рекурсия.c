#include <stdio.h>
#include <stdlib.h>

// перебор с возвратом без правила Варнсдорфа
// идем рекурсивно в глубину функции, где глубина - номер хода
// если попадаем в ситуацию, где невозможен никакой ход, а 
// глубина(т е номер хода не равен последнему возможному(т е N * N), 
// то возвращаемся на уровень, где флаг еще был равен 1 и рассматриваем оставшиеся варианты

void knight_turn(int **board, int N, int M, int i, int j, int d);
void print_board(int **board, int N, int M);
int isMovePossible(int x, int y, int N, int M);

unsigned long long main() {

	printf("Enter the board size:\n");
	int N = 0, M = 0;
	scanf("%d%d", &N, &M);

	int **board = (int **)malloc(N * sizeof(int *));
	for (int i = 0; i < N; i++)
		board[i] = (int *)calloc(M, sizeof(int));

	printf("Knight's position on %dx%d board?\n", N, M);
	int i = 0, j = 0;
	scanf("%d%d", &i, &j);
	i--;
	j--;
	board[i][j] = 1;
	
	knight_turn(board, N, M, i, j, 2);

	return 0;

}

void knight_turn(int **board, int N, int M, int i, int j, int d) {
//	print_board(board, N, M);                        // чтобы посмотреть все вспомогательные матрицы расскомментируй
	int turn_x[8] = { 1,  2,  1,  2, -1, -2, -1, -2};
	int turn_y[8] = { 2,  1, -2, -1,  2,  1, -2, -1};
	int x = 0, y = 0;
	for (int k = 0; k < 8; k++) {
		x = j + turn_x[k];
		y = i + turn_y[k];
		if (isMovePossible(x, y, N, M) && board[y][x] == 0) {
			board[y][x] = d;
			if (d == N * M) {
				print_board(board, N, M);
				exit(0);
			}
			knight_turn(board, N, M, y, x, d + 1);
			board[y][x] = 0;
		}
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
	printf("\n");
}

int isMovePossible(int x, int y, int N, int M) {
	return ((-1 < x) && (x < M) && (-1 < y) && (y < N));
}
