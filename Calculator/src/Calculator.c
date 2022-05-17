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

double *x, *y, *result;

FILE *fin, *fout; //Declare variables for work with files

/* Функция для сложения векторов
 * Function for adding vectors*/
void doSumVector(double *x, double *y, int size){
	result = malloc(size*sizeof(double));
	for (int i = 0; i < size; i++) result[i] =  x[i] + y[i];
}

/* Функция для разности векторов
 * Function for the difference of vectors*/
void doSubstractionVector(double *x, double *y, int size){
	result = malloc(size*sizeof(double));
	for (int i = 0; i < size; i++) result[i] =  x[i] - y[i];
}

/* Функция для умножения векторов
 * Function for multiplying vectors*/
void doMultiplyVector(double *x, double *y, int size){
	result = malloc(1*sizeof(double));
	for (int i = 0; i < size; i++) *result +=  x[i] * y[i];
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
double doSum(double x, double y){
	return x + y;
}

/* Функция для нахождения разности чисел
 * Function for finding the difference of numbers*/
double doSubstraction(double x, double y){
	return x - y;
}

/* Функция для нахождения произведения чисел
 * Function for finding the product of numbers*/
double doMultiply(double x, double y){
	return x * y;
}

/* Функция для нахождения частного чисел
 * Function for finding the quotient of numbers*/
double doDivision(double x, double y){
	return x / y;
}

/* Функция для нахождения факториала числа с помощью рекурсии
 * A function for finding the factorial of a number using recursion*/
unsigned long long doFactorial(int x){
	if (x == 1 || x == 0){
		return 1;
	}
	else return doFactorial(x-1)*x;
}

/* Функция для возведения числа в степень, работает с натуральными числами
 * При попытке использовать формулу для вычисления x^y=exp(y*ln(x))
 * Точность не очень хорошая, поэтому было решено сделать возведение
 * В степень только для натуральных чисел
 * A function for exponentiating a number, works with natural numbers
 * When trying to use the formula to calculate x^y=exp(y*ln(x))
 * The accuracy is not very good, so it was decided to do the construction
 * To the power only for natural numbers*/
unsigned long long doPow(int x, int y){
	/* Объявляем переменную для хранения результата
	 * We declare variable for storing the result*/
	double result = 1;
	if (y < 0){
		y = doAbs(y);
		for (int i=1; i<=y; i++){
			result = result * x;
		}
		result = (1/result);
	}
	else{
		for (int i=1; i<=y; i++){
			result = result * x;
		}
	}
	return result;
}


/* Основная функция, точка входа
 * Main function, entry point*/
int main(int argc, char* argv[]){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	char input[259], output[259];
	char operation, mode;
	char b;
	do{
		puts("Enter filename to input");
		scanf("%s", input);
		puts("Enter filename to output");
		scanf("%s", output);
		fin = fopen(input, "r");
		if ((fout = fopen(output, "a")) == NULL){
			fout = fopen(output, "w");
		}
		while (feof(fin) == 0){
			fscanf(fin," %c %c", &operation, &mode);
			switch (mode){
				case 'v':
					int size;
					fscanf(fin, "%i", &size);
					x = malloc(size*sizeof(double));
					y = malloc(size*sizeof(double));
					for (int i = 0; i < size; i++) fscanf(fin, "%lf", &x[i]);
					for (int i = 0; i < size; i++) fscanf(fin, "%lf", &y[i]);
					switch (operation){
						case '+':
							doSumVector(x, y, size);
							break;
						case '-':
							doSubstractionVector(x, y, size);
							break;
						case '*':
							doMultiplyVector(x, y, size);
							break;
						default:
							fprintf(fout, "There is no such operation, repeat the input\n");
							fclose(fout);
					}
					fprintf(fout, "( ");
					for (int i = 0; i < size; i++){
						if (i == size - 1){
							fprintf(fout, "%lf", x[i]);
						}
						else fprintf(fout, "%lf ", x[i]);
					}
					fprintf(fout, " ) %c ( ", operation);
					for (int i = 0; i < size; i++){
						if (i == size - 1){
							fprintf(fout, "%lf", y[i]);
						}
						else fprintf(fout, "%lf ", y[i]);
					}
					if (operation == '+' || operation == '-'){
						fprintf(fout, " ) = ( ");
						for (int i = 0; i < size; i++){
							if (i == size - 1){
								fprintf(fout, "%lf", result[i]);
							}
							else fprintf(fout, "%lf ", result[i]);
						}
						fprintf(fout, " )\n");
					}
					else{
						fprintf(fout, " ) = %lf\n", *result);
					}
					free(x);
					free(y);
					free(result);
					break;
				case 'n':
					x = malloc(1 * sizeof(double));
					y = malloc(1 * sizeof(double));
					switch (operation){
						case '+':
							fscanf(fin, "%lf %lf", x, y);
							fprintf(fout, "%lf + %lf = %lf\n", *x, *y, doSum(*x, *y));
							break;
						case '-':
							fscanf(fin, "%lf %lf", x, y);
							fprintf(fout, "%lf - %lf = %lf\n", *x, *y, doSubstraction(*x, *y));
							break;
						case '*':
							fscanf(fin, "%lf %lf", x, y);
							fprintf(fout, "%lf * %lf = %lf\n", *x, *y, doMultiply(*x, *y));
							break;
						case '/':
							fscanf(fin, "%lf %lf", x, y);
							fprintf(fout, "%lf / %lf = %lf\n", *x, *y, doDivision(*x, *y));
							break;
						case '!':
							fscanf(fin, "%lf", x);
							fprintf(fout, "%lf! = %llu\n", *x, doFactorial(*x));
							break;
						case '^':
							fscanf(fin, "%lf %lf", x, y);
							fprintf(fout, "%lf^%lf = %llu\n", *x, *y, doPow(*x, *y));
							break;
						default:
							fprintf(fout, "There is no such operation, repeat the input\n");
					}
					free(x);
					free(y);
					break;
				default:
					fprintf(fout, "There is no such mode\n");
				}
			}
		fclose(fin);
		fclose(fout);
		puts("Continue working? y - yes, n - no");
		scanf(" %c", &b);
	}
	while(b!='n');
	return 0;
}
