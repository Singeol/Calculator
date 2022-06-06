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

FILE *fin, *fout;


/* Структура для описания элемента стека
 * Structure for declare element of queue
 */
typedef struct node {
	double x;
	struct node *next;
} node;

/* Структура для описания стека
 * Structure for describing the stack
 */
typedef struct stack {
	node *head;
} stack;

/* Функция для инициализирования стека
 * Function to initialize the stack
 */
void init_stack(stack *s) {
	s->head = NULL;
}

/* Функция для добавления элемента в стек
 * Fucntion for add element of stack
 */
void push(stack *s, double number) {

	node * tmp = malloc(sizeof(node));

	tmp->x = number;

	tmp->next = s->head;

	s->head = tmp;

}

/* Функция для изъятия данных из стека
 * Function to pop element from stack
 */
double pop(stack *s) {
	node *tmp;
	tmp = malloc(sizeof(node));
	tmp = s->head;

	s->head = s->head->next;

	return tmp->x;
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

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	char input[259], output[259], in[256], b, operation;
	double nm;
	stack s1;
	do {
		init_stack(&s1);
		puts("Enter filename to input");
		scanf("%s", input);
		puts("Enter filename to output");
		scanf("%s", output);
		fin = fopen(input, "r");
		if ((fout = fopen(output, "a")) == NULL) {
			fout = fopen(output, "w");
		}
		while (feof(fin) == 0) {
			fscanf(fin, "%s", in);
				if (atof(in) == 0) {
					operation = in[0];
					switch (operation) {
						case '+':
							push(&s1, *doSum(pop(&s1), pop(&s1)));
							break;
						case '-':
							push(&s1, *doSubstraction(pop(&s1), pop(&s1)));
							break;
						case '*':
							push(&s1, *doMultiply(pop(&s1), pop(&s1)));
							break;
						case '/':
							push(&s1, *doDivision(pop(&s1), pop(&s1)));
							break;
						case '!':
							push(&s1, *doFactorial(pop(&s1)));
							break;
						case '^':
							push(&s1, *doPow(pop(&s1), pop(&s1)));
							break;
						case '=':
							fprintf(fout, "%lf\n", pop(&s1));
							break;
					}
				}
				else {
					nm = atof(in);
					push(&s1, nm);
				}
		}
		fclose(fin);
		fclose(fout);
		puts("Continue working? y - yes, n - no");
		scanf(" %c", &b);
	}while(b != 'n');
}
