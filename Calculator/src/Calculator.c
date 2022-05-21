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


/* Структура для хранения входных данных
 * Structure for storing input data
 * */
struct Element {
    char operation, mode;
    int size;
    double *x, *y;
    struct Element *next;
};

/* Структура для хранения выходных данных
 * Structure for storing output data
 * */
struct Result {
	int size;
    double *res;
    struct Result *next;
};

typedef struct Element Element;
typedef struct Result Result;

FILE *fin, *fout; //Declare variables for work with files

/* Функция для загрузки результата в структуру
 * Fucnction for upload data to output structure
 * */
void pushResult(Result** head, int size, double *data){
	Result* tmp = (Result*) malloc(sizeof(Result));
	Result *last = *head;
	tmp->size = size;
	tmp->res = data;
	tmp->next = NULL;
		if(*head == NULL){
			*head = tmp;
			return;
		}

	while (last->next != NULL){
		last = last->next;
	}
	last->next = tmp;
	return;
}

/* Функция для добавления входных данных в конец списка
 * Function for add input data to end of list
 */
void pushElement(Element** head){
	Element* tmp = (Element*) malloc(sizeof(Element));
	Element *last = *head;
	fscanf(fin," %c %c", &tmp->operation, &tmp->mode);
	switch (tmp->mode){
		case 'n':
			tmp->size = 1;
			if (tmp->operation == '!'){
				tmp->x = malloc(1 * sizeof(double));
				for (int i = 0; i < tmp->size; i++) fscanf(fin, "%lf", &tmp->x[i]);
	            tmp->y = NULL;
	        }
	        else{
	        	tmp->x = malloc(1 * sizeof(double));
	            tmp->y = malloc(1 * sizeof(double));
	            for (int i = 0; i < tmp->size; i++) fscanf(fin, "%lf", &tmp->x[i]);
	            for (int i = 0; i < tmp->size; i++) fscanf(fin, "%lf", &tmp->y[i]);
	        }
	        break;
	    case 'v':
	    	fscanf(fin, "%i", &tmp->size);
	    	tmp->x = malloc(tmp->size*sizeof(double));
	        tmp->y = malloc(tmp->size*sizeof(double));
	        for (int i = 0; i < tmp->size; i++) fscanf(fin, "%lf", &tmp->x[i]);
	        for (int i = 0; i < tmp->size; i++) fscanf(fin, "%lf", &tmp->y[i]);
	        break;
	    }
	tmp->next = NULL;
	if(*head == NULL){
		*head = tmp;
		return;
	}

	while (last->next != NULL){
		last = last->next;
	}
	last->next = tmp;
	return;
}

/* Функция для очистки списка входных данных
 * Function for clear input data list
 */
void deleteElements(Element *head){
	Element *current;
	while (head != NULL){
		current = head;
		head = head->next;
		free(current);
	}
}

/* Функция для очистки списка результата
 * Fucntion for clear output data list
 */
void deleteResults(Result *head){
	Result *current;
	while (head != NULL){
		current = head;
		head = head->next;
		free(current);
	}
}

/* Функция для перемещения вперёд по списку
 * Function for move forward through list
 */
Element* nextElement(Element *current){
	return current->next;
}

/* Функция для перемещения вперёд по списку
 * Function for move forward through list
 */
Result* nextResult(Result *current){
	return current->next;
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
	result = malloc(1*sizeof(double));
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
	Element* head; // Указатель на голову списка данных
	Element* current; // Указатель на текущий элемент списка данных
	Result* res_head; // Указатель на голову списка результата
	Result* res_current; // Указатель на текущий элемент списка результата
	char input[259], output[259]; // Переменные для хранения имени файлов
	char b; // Переменная продолжения работа
	do{
		head = NULL;
		current = NULL;
		res_head = NULL;
		res_current = NULL;
		puts("Enter filename to input");
		scanf("%s", input);
		puts("Enter filename to output");
		scanf("%s", output);
		fin = fopen(input, "r");
		while (feof(fin) == 0){
			pushElement(&head);
		}
		fclose(fin);
		current = head;
		while (current != NULL){
			switch (current->mode){
				case 'v':
					switch (current->operation){
						case '+':
							pushResult(&res_head, current->size, doSumVector(current->x, current->y, current->size));
							break;
						case '-':
							pushResult(&res_head, current->size, doSubstractionVector(current->x, current->y, current->size));
							break;
						case '*':
							pushResult(&res_head, 1, doMultiplyVector(current->x, current->y, current->size));
							break;
					}
					break;
					case 'n':
						switch (current->operation){
							case '+':
								pushResult(&res_head, current->size, doSum(*current->x, *current->y));
								break;
							case '-':
								pushResult(&res_head, current->size, doSubstraction(*current->x, *current->y));
								break;
							case '*':
								pushResult(&res_head, current->size, doMultiply(*current->x, *current->y));
								break;
							case '/':
								pushResult(&res_head, current->size, doDivision(*current->x, *current->y));
								break;
							case '!':
								pushResult(&res_head, current->size, doFactorial(*current->x));
								break;
							case '^':
								pushResult(&res_head, current->size, doPow(*current->x, *current->y));
								break;
						}
						break;
				}
			current = nextElement(current);
		}
		current = head;
		res_current = res_head;
		if ((fout = fopen(output, "a")) == NULL){
			fout = fopen(output, "w");
		}
		while (current != NULL){
				switch (current->mode){
					case 'v':
						fprintf(fout, "( ");
						for (int i = 0; i < current->size; i++){
							if (i == current->size - 1){
								fprintf(fout, "%lf", current->x[i]);
							}
							else fprintf(fout, "%lf ", current->x[i]);
						}
						fprintf(fout, " ) %c ( ", current->operation);
						for (int i = 0; i < current->size; i++){
							if (i == current->size - 1){
								fprintf(fout, "%lf", current->y[i]);
							}
							else fprintf(fout, "%lf ", current->y[i]);
						}
						if (current->operation == '+' || current->operation == '-'){
							fprintf(fout, " ) = ( ");
							for (int i = 0; i < res_current->size; i++){
								if (i == res_current->size - 1){
									fprintf(fout, "%lf", res_current->res[i]);
								}
								else fprintf(fout, "%lf ", res_current->res[i]);
							}
							fprintf(fout, " )\n");
						}
						else{
							fprintf(fout, " ) = %lf\n", *res_current->res);
						}
						break;
					case 'n':
						switch (current->operation){
							case '+':
								fprintf(fout, "%lf + %lf = %lf\n", *current->x, *current->y, *res_current->res);
								break;
							case '-':
								fprintf(fout, "%lf - %lf = %lf\n", *current->x, *current->y, *res_current->res);
								break;
							case '*':
								fprintf(fout, "%lf * %lf = %lf\n", *current->x, *current->y, *res_current->res);
								break;
							case '/':
								fprintf(fout, "%lf / %lf = %lf\n", *current->x, *current->y, *res_current->res);
								break;
							case '!':
								fprintf(fout, "%lf! = %lf\n", *current->x, *res_current->res);
								break;
							case '^':
								fprintf(fout, "%lf^%lf = %lf\n", *current->x, *current->y, *res_current->res);
								break;
						}
				}
			current = nextElement(current);
			res_current = nextResult(res_current);
		}
		fclose(fout);
		deleteElements(head);
		deleteResults(res_head);
		puts("Continue working? y - yes, n - no");
		scanf(" %c", &b);
	}
	while(b!='n');
	return 0;
}
