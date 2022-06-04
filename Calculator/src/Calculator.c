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

FILE *fin, *fout; //Declare variables for work with files

/* Структура для хранения данных
 * Structure for store the data
*/
typedef struct data {
	char mode, operation;
	int size;
	double *x, *y;
	double *result;
} data;

/* Структура для описания элемента очереди
 * Structure for declare element of queue
 */
typedef struct node {
	char mode, operation;
	int size;
	double *x, *y;
	double *result;
	struct node *next;
} node;

/* Структура для описания очереди
 * Structure for describing the queue
 */
typedef struct {
	node *head;
	node *tail;
} queue;

/* Функция для инициализирования очереди
 * Function to initialize the queue
 */
void init_queue(queue *q) {
	q->head = NULL;
	q->tail = NULL;
}

/* Функция для добавления элемента в очередь
 * Fucntion for add element of queue
 */
void enqueue(queue *q, data *value) {

	node * tmp = malloc(sizeof(node));
	tmp->operation = value->operation;
	tmp->mode = value->mode;
	tmp->result = value->result;
	tmp->x = value->x;
	tmp->y = value->y;
	tmp->size = value->size;

	if (q->tail != NULL) {
		q->tail->next = tmp;
	}

	q->tail = tmp;

	if(q->head == NULL) {
		q->head = tmp;
	}
}

/* Функция для изъятия данных из очереди
 * Function to dequeue data
 */
data* dequeue(queue *q) {
	data *result;
	result = malloc(sizeof(data));

	if (q->head == NULL){
		result = NULL;
		return result;
	}

	node *tmp = q->head;

	result->mode = tmp->mode;
	result->operation = tmp->operation;
	result->size = tmp->size;
	result->x = tmp->x;
	result->y = tmp->y;
	result->result = tmp->result;

	//take it off.
	q->head = q->head->next;
	if (q->head == NULL) {
		q->tail = NULL;
	}
	free(tmp);

	return result;
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


int main() {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	queue q1, q2;
	data *var;

	char input[259], output[259];
	char b;
	do {
		init_queue(&q1);
		init_queue(&q2);
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
			enqueue(&q1, var);
		}
		free(var);
		fclose(fin);
		while ((var = dequeue(&q1)) != NULL) {
			switch (var->mode) {
				case 'v':
					switch (var->operation) {
						case '+':
							var->result = doSumVector(var->x, var->y, var->size);
							enqueue(&q2, var);
							break;
						case '-':
							var->result = doSubstractionVector(var->x, var->y, var->size);
							enqueue(&q2, var);
							break;
						case '*':
							var->result = doMultiplyVector(var->x, var->y, var->size);
							enqueue(&q2, var);
							break;
					}
					break;
				case 'n':
					switch (var->operation) {
						case '+':
							var->result = doSum(*var->x, *var->y);
							enqueue(&q2, var);
							break;
						case '-':
							var->result = doSubstraction(*var->x, *var->y);
							enqueue(&q2, var);
							break;
						case '*':
							var->result = doMultiply(*var->x, *var->y);
							enqueue(&q2, var);
							break;
						case '/':
							var->result = doDivision(*var->x, *var->y);
							enqueue(&q2, var);
							break;
						case '!':
							var->result = doFactorial(*var->x);
							enqueue(&q2, var);
							break;
						case '^':
							var->result = doPow(*var->x, *var->y);
							enqueue(&q2, var);
							break;
					}
					break;
			}
		}
		if ((fout = fopen(output, "a")) == NULL) {
			fout = fopen(output, "w");
		}
		while ((var = dequeue(&q2)) != NULL) {
			switch (var->mode) {
				case 'v':
					fprintf(fout, "( ");
					for (int i = 0; i < var->size; i++) {
						if (i == var->size - 1){
							fprintf(fout, "%lf", var->x[i]);
						}
						else fprintf(fout, "%lf ", var->x[i]);
					}
					fprintf(fout, " ) %c ( ", var->operation);
					for (int i = 0; i < var->size; i++){
						if (i == var->size - 1){
							fprintf(fout, "%lf", var->y[i]);
						}
						else fprintf(fout, "%lf ", var->y[i]);
					}
					if (var->operation == '+' || var->operation == '-') {
						fprintf(fout, " ) = ( ");
						for (int i = 0; i < var->size; i++) {
							if (i == var->size - 1){
								fprintf(fout, "%lf", var->result[i]);
							}
							else fprintf(fout, "%lf ", var->result[i]);
						}
						fprintf(fout, " )\n");
					}
					else{
						fprintf(fout, " ) = %lf\n", *var->result);
					}
					break;
				case 'n':
					switch (var->operation) {
						case '+':
							fprintf(fout, "%lf + %lf = %lf\n", *var->x, *var->y, *var->result);
							break;
						case '-':
							fprintf(fout, "%lf - %lf = %lf\n", *var->x, *var->y, *var->result);
							break;
						case '*':
							fprintf(fout, "%lf * %lf = %lf\n", *var->x, *var->y, *var->result);
							break;
						case '/':
							fprintf(fout, "%lf / %lf = %lf\n", *var->x, *var->y, *var->result);
							break;
						case '!':
							fprintf(fout, "%lf! = %lf\n", *var->x, *var->result);
							break;
						case '^':
							fprintf(fout, "%lf^%lf = %lf\n", *var->x, *var->y, *var->result);
							break;
					}
			}
		}
		fclose(fout);
		puts("Continue working? y - yes, n - no");
			scanf(" %c", &b);
	}while(b!='n');
	return 0;
}
