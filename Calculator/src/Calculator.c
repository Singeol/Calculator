/*
 ============================================================================
 Name        : Calculator.c
 Author      : Semyon Mikhailov
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/* Структура для хранения данных
 * Structure for store the data
*/
typedef struct data {
	char mode, operation;
	int size;
	double *x, *y;
	double *result;
} data;

/* Структура для описания элемента списка
 * Structure for declare element of list
 */
typedef struct node {
	char mode, operation;
	int size;
	double *x, *y;
	double *result;
	struct node *next;
} node;

/* Структура для описания списка
 * Structure for describing the list
 */
typedef struct {
	node *head;
	node *current;
} list;

/* Функция для инициализации списка
 * Function to initialize the list
 */
void init_list(list *l) {
	l->head = NULL;
	l->current = NULL;
}
FILE *fin, *fout; //Declare variables for work with files

/* Функция для добавления входных данных в конец списка
 * Function for add input data to end of list
 */
void pushElement(list *l, data *value) {

	node* tmp = malloc(sizeof(node));
	node *last = l->head;
	tmp->operation = value->operation;
	tmp->mode = value->mode;
	tmp->result = value->result;
	tmp->x = value->x;
	tmp->y = value->y;
	tmp->size = value->size;
	tmp->next = NULL;
	if(l->head == NULL){
		l->head = tmp;
		return;
	}

	while (last->next != NULL){
		last = last->next;
	}
	last->next = tmp;
	return;
}

// Удаляет первый элемент исходного списка
void deleteElement(list *l) {
  node *tmp;

  if(&l->head == NULL) return;

  tmp = l->head;

  l->head = l->head->next;

  free(tmp);
}

/* Функция для перемещения вперёд по списку
 * Function for move forward through list
 */
node* nextElement(list *l){
	l->current = l->current->next;
	return l->current;
}

/* Функция для сложения векторов
 * Function for adding vectors*/
double* doSumVector(double *x, double *y, int size){
	double *result;
	result = malloc(size*sizeof(double));
	for (int i = 0; i < size; i++) result[i] =  x[i] + y[i];
	return result;
}

/* Функция для разности векторов
 * Function for the difference of vectors*/
double* doSubstractionVector(double *x, double *y, int size){
	double *result;
	result = malloc(size*sizeof(double));
	for (int i = 0; i < size; i++) result[i] =  x[i] - y[i];
	return result;
}

/* Функция для умножения векторов
 * Function for multiplying vectors*/
double* doMultiplyVector(double *x, double *y, int size){
	double *result;
	result = malloc(sizeof(double));
	*result = 0;
	for (int i = 0; i < size; i++) *result +=  x[i] * y[i];
	return result;
}

/* Функция для нахождения модуля числа
 * Function for finding the modulus of a number*/
double doAbs(double x){
	if (x < 0){
		return x*(-1);
	}
	else return x;
}

/* Функция для нахождения суммы чисел
 * Function for finding the sum of numbers*/
double* doSum(double x, double y){
	double *result;
	result = malloc(1*sizeof(double));
	*result = x + y;
	return result;
}

/* Функция для нахождения разности чисел
 * Function for finding the difference of numbers*/
double* doSubstraction(double x, double y){
	double *result;
	result = malloc(1*sizeof(double));
	*result = x - y;
	return result;
}

/* Функция для нахождения произведения чисел
 * Function for finding the product of numbers*/
double* doMultiply(double x, double y){
	double *result;
	result = malloc(1*sizeof(double));
	*result = x * y;
	return result;
}

/* Функция для нахождения частного чисел
 * Function for finding the quotient of numbers*/
double* doDivision(double x, double y){
	double *result;
	result = malloc(1*sizeof(double));
	*result = x / y;
	return result;
}

/* Функция для нахождения факториала числа с помощью рекурсии
 * A function for finding the factorial of a number using recursion*/
double* doFactorial(int x){
	double *result;
	result = malloc(1*sizeof(double));
	*result = 1;
	for (int i = 2; i <= x; i++){
		*result *= i;
	}
	return result;
}

/* Функция для возведения числа в степень, работает с натуральными числами
 * При попытке использовать формулу для вычисления x^y=exp(y*ln(x))
 * Точность не очень хорошая, поэтому было решено сделать возведение
 * В степень только для натуральных чисел
 * A function for exponentiating a number, works with natural numbers
 * When trying to use the formula to calculate x^y=exp(y*ln(x))
 * The accuracy is not very good, so it was decided to do the construction
 * To the power only for natural numbers*/
double* doPow(int x, int y){
	/* Объявляем переменную для хранения результата
	 * We declare variable for storing the result*/
	double *result;
	result = malloc(1*sizeof(double));
	*result = 1;
	if (y < 0){
		y = doAbs(y);
		for (int i=1; i<=y; i++){
			*result *= x;
		}
		*result = (1/(*result));
	}
	else{
		for (int i=1; i<=y; i++){
			*result *= x;
		}
	}
	return result;
}


/* Основная функция, точка входа
 * Main function, entry point*/
int main(int argc, char* argv[]){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	data *var;
	list l1, l2;
	char input[259], output[259]; // Переменные для хранения имени файлов
	char b; // Переменная продолжения работа
	do{
		init_list(&l1);
		init_list(&l2);
		puts("Enter filename to input");
		scanf("%s", input);
		puts("Enter filename to output");
		scanf("%s", output);
		fin = fopen(input, "r");
		var = malloc(sizeof(data));
		while (feof(fin) == 0) {
			fscanf(fin," %c %c", &var->operation, &var->mode);
			switch (var->mode){
				case 'n':
					var->size = 1;
					if (var->operation == '!'){
						var->x = malloc(1 * sizeof(double));
						for (int i = 0; i < var->size; i++) fscanf(fin, "%lf", &var->x[i]);
						var->y = NULL;
					}
					else{
					   	var->x = malloc(1 * sizeof(double));
					    var->y = malloc(1 * sizeof(double));
					    for (int i = 0; i < var->size; i++) fscanf(fin, "%lf", &var->x[i]);
					    for (int i = 0; i < var->size; i++) fscanf(fin, "%lf", &var->y[i]);
					}
					break;
				case 'v':
				   	fscanf(fin, "%i", &var->size);
				   	var->x = malloc(var->size*sizeof(double));
				    var->y = malloc(var->size*sizeof(double));
				    for (int i = 0; i < var->size; i++) fscanf(fin, "%lf", &var->x[i]);
				    for (int i = 0; i < var->size; i++) fscanf(fin, "%lf", &var->y[i]);
				    break;
			}
			pushElement(&l1, var);
		}
		fclose(fin);
		l1.current = l1.head;
		while (l1.current != NULL){
			var->mode = l1.current->mode;
			var->operation = l1.current->operation;
			var->size = l1.current->size;
			var->x = l1.current->x;
			var->y = l1.current->y;
			switch (var->mode){
				case 'v':
					switch (var->operation){
						case '+':
							var->result = doSumVector(var->x, var->y, var->size);
							pushElement(&l2, var);
							break;
						case '-':
							var->result = doSubstractionVector(var->x, var->y, var->size);
							pushElement(&l2, var);
							break;
						case '*':
							var->result = doMultiplyVector(var->x, var->y, var->size);
							pushElement(&l2, var);
							break;
					}
					break;
					case 'n':
						switch (l1.current->operation){
							case '+':
								var->result = doSum(*var->x, *var->y);
								pushElement(&l2, var);
								break;
							case '-':
								var->result = doSubstraction(*var->x, *var->y);
								pushElement(&l2, var);
								break;
							case '*':
								var->result = doMultiply(*var->x, *var->y);
								pushElement(&l2, var);
								break;
							case '/':
								var->result = doDivision(*var->x, *var->y);
								pushElement(&l2, var);
								break;
							case '!':
								var->result = doFactorial(*var->x);
								pushElement(&l2, var);
								break;
							case '^':
								var->result = doPow(*var->x, *var->y);
								pushElement(&l2, var);
								break;
						}
						break;
				}
			nextElement(&l1);
		}
		free(var);
		l1.current = l1.head;
		l2.current = l2.head;
		if ((fout = fopen(output, "a")) == NULL){
			fout = fopen(output, "w");
		}
		while (l2.current != NULL){
				switch (l2.current->mode){
					case 'v':
						fprintf(fout, "( ");
						for (int i = 0; i < l2.current->size; i++){
							if (i == l2.current->size - 1){
								fprintf(fout, "%lf", l2.current->x[i]);
							}
							else fprintf(fout, "%lf ", l2.current->x[i]);
						}
						fprintf(fout, " ) %c ( ", l2.current->operation);
						for (int i = 0; i < l2.current->size; i++){
							if (i == l2.current->size - 1){
								fprintf(fout, "%lf", l2.current->y[i]);
							}
							else fprintf(fout, "%lf ", l2.current->y[i]);
						}
						if (l2.current->operation == '+' || l2.current->operation == '-'){
							fprintf(fout, " ) = ( ");
							for (int i = 0; i < l2.current->size; i++){
								if (i == l2.current->size - 1){
									fprintf(fout, "%lf", l2.current->result[i]);
								}
								else fprintf(fout, "%lf ", l2.current->result[i]);
							}
							fprintf(fout, " )\n");
						}
						else{
							fprintf(fout, " ) = %lf\n", *l2.current->result);
						}
						break;
					case 'n':
						switch (l2.current->operation){
							case '+':
								fprintf(fout, "%lf + %lf = %lf\n", *l2.current->x, *l2.current->y, *l2.current->result);
								break;
							case '-':
								fprintf(fout, "%lf - %lf = %lf\n", *l2.current->x, *l2.current->y, *l2.current->result);
								break;
							case '*':
								fprintf(fout, "%lf * %lf = %lf\n", *l2.current->x, *l2.current->y, *l2.current->result);
								break;
							case '/':
								fprintf(fout, "%lf / %lf = %lf\n", *l2.current->x, *l2.current->y, *l2.current->result);
								break;
							case '!':
								fprintf(fout, "%lf! = %lf\n", *l2.current->x, *l2.current->result);
								break;
							case '^':
								fprintf(fout, "%lf^%lf = %lf\n", *l2.current->x, *l2.current->y, *l2.current->result);
								break;
						}
				}
			nextElement(&l2);
		}
		fclose(fout);
		while (l1.head != NULL){
			deleteElement(&l1);
		}
		while (l2.head != NULL){
			deleteElement(&l2);
		}
		puts("Continue working? y - yes, n - no");
		scanf(" %c", &b);
	} while(b!='n');
	return 0;
}
