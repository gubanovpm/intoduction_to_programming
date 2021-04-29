#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long int circle_hash(char *s, int length);

// поиск подстроки в тексте - оптимизация наивного решения с помощью циклического хеша
// алгоритм считает колчество вхожений подстроки
// будем использовать самый простой пример циклического хеша - сумму ascii кодов строки

int main() {

	FILE *inp = fopen("input.txt", "r");					// откроем для чтения("r") текстовый файл "input.txt", находящийся в той же папке где и программа
	fseek(inp, 0, SEEK_END);								// перевелем внутренний файловый указатель на конец
	long long int text_sz = ftell(inp);						// вычислим длину файла как разность между указателем на начао и на текущее значение внутреннего указателя(т е конца, а значит это длина файла)
	fseek(inp, 0, SEEK_SET);								// вернем внутренний указатель в положение начала
	char *text = (char *)malloc(sizeof(char) * text_sz);	// выделим место в паяти на весь кусок текста (не очень опттимально, но для демонстрации алгоритма подойдет)
	fread(text, sizeof(char), text_sz, inp);				// считаем в массив text элементы размера sizeof(char) в колчестве text_sz из файла inp
	fclose(inp);											// закрыть файл "input.txt" для чтения
	
	char sub[256] = {'\0'} ;								// объявление подстроки
	printf("Enter the substring you are looking for:\n");	// считаем искомую подстроку
	scanf("%s", sub);
	int n = strlen(sub);									// n - длина введенной подстроки
	
	char *tmp = (char *)calloc(n + 1, sizeof(char));			// выдкление памяти для временной строки, используемой потом для сравнеия
	for (int i = 0 ; i < n ; i++)						// перепишем первое значение
		tmp[i] = text[i];
	long long int hsub = circle_hash(sub, n);				// посчитаем хеш искомой подстроки
	long long int hs = circle_hash(tmp, n);					// посчитаем хеш того что во временной tmp строке
	long long int counter = 0;								// пересенная отвечающая за количество вхождений
	for (int i = 0; i < text_sz - n; i++) {					// перебираем по i где i - первый символ рассмтриваемой строки длины n
		if (hs == hsub) {									// если хеши строк равны, то проверим равны ли сами строки(т к возможны коллизии такие как при поиске подстроки 123 такой же хеш будет иметь подстрока 213)
			for (int j = 0; j < n; j++)						// для сравнения будем использовать библиотечную функцию сравнения строк, поэтому во врменную строку будем переписывать тот кусок исходного текста у которого совпал хеш
				tmp[j] = text[i + j];
			if (strcmp(tmp, sub) == 0)						// библиотечное сравнение строк
				counter++;
		}
		hs = hs - text[i] + text[i + n];					// так как хеш - циклический и представляет собой сумму ascii кодов
	}
	printf("word %s in input.txt %lld times\n", sub, counter); // итоговый вывод
	free(tmp);												// освобождаем занятую память
	free(text);
	return 0;

}

// функция подсчета хеша - суммы ascii кодов подстроки заданной длины по заданному указателю
long long int circle_hash(char *s, int length) {
	long long int hash_sum = 0;				// начальное значение суммы = 0
	for (int i = 0; i  < length; i++)		// пройдемся по всем символам строки
		hash_sum += s[i];					// просуммируем
	return hash_sum;
}
