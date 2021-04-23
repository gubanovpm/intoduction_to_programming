#include <stdio.h>
#include <stdlib.h>

int tryQueen(int **board, int N, int i);	// рекурсивная функция построения, возвращаемое значение - можно ли поставить королеву на i горизонталь
void setQueen(int **board, int N, int i, int j);     			// поставить королеву на позицию [i, j]
void resetQueen(int **board, int N, int i, int j);   			// убрать королеву с позиции [i, j]
void print_board(int **board, int N);

int main() {
	
	printf("Enter the board size: ");
	int N = 0;
	scanf("%d", &N);
	int **board = (int **)malloc(N * sizeof(int *));
	for (int i = 0; i < N; i++)
		board[i] = (int *)calloc(N, sizeof(int));
	tryQueen(board, N, 0);             // рекурсивная функция, ставящая королеву на i строку 
	print_board(board, N);           // вывести построенный функцией tryQueen вариант
	for (int i = 0; i < N; i++)
		free(board[i]);
	free(board);
	return 0;

}

// основная идея - добавление 1 в [i,j] клетку доски, если она перекрывается ходом поставленной королевы
// т е поставить королеву мы может только в клетку со значением 0(в нее нет хода не одной королевой)
// а когда мы ставим королеву то добавляем в клетки, куда можем ею попасть, значение 1

int tryQueen(int **board, int N, int i) {
	int result = 0;
	for (int j = 0; j < N; j++) {                              // проходим по всем клеткам i строки
		if (board[i][j] == 0) {                            // если в клетку не может попасть ходом никакая королева
			setQueen(board, N, i, j);
			if (i == N - 1) 
				result = 1;
			else if (1 - (result = tryQueen(board, N,i + 1)))
				resetQueen(board, N, i, j);
		}
		if (result)
			break;
	}
	return result;
}

void setQueen(int **board, int N, int i, int j) {
	for (int k = 0; k < N; k++) {
		board[k][j]++;
		board[i][k]++;
		int diag = j - i + k;
		if (diag >= 0 && diag < N)
			board[k][diag]++;
		diag = j + i - k;
		if (diag >= 0 && diag < N)
			board[k][diag]++;
	}
	board[i][j] = -1;
}

void resetQueen(int **board, int N, int i, int j) {
	for (int k = 0; k < N; k++) {
		board[k][j]--;
		board[i][k]--;
		int diag = j - i + k;
		if (diag >= 0 && diag < N)
			board[k][diag]--;
		diag = j + i - k;
		if (diag >= 0 && diag < N)
			board[k][diag]--;
	}
	board[i][j] = 0;
}

void print_board(int **board, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == -1)
				printf(" Q ");
			else
				printf(" * ");
		}
		printf("\n");
	}
}
