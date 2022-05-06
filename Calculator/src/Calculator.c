/*
 ============================================================================
 Name        : Calculator.c
 Author      : Semyon Mikhailov
 Version     :
 Copyright   :
 Description : Calculator with 11 basic functions
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

FILE *fin, *fout; //Declare variables for work with files

/* Функция для сложения векторов
 * Function for adding vectors*/
void doSumVector(int size){
	double *x, *y, *result;
	x = malloc(size*sizeof(double));
	y = malloc(size*sizeof(double));
	result = malloc(size*sizeof(double));
	for (int i = 0; i < size; i++) fscanf(fin, "%lf", &x[i]);
	for (int i = 0; i < size; i++) fscanf(fin, "%lf", &y[i]);
	for (int i = 0; i < size; i++) result[i] =  x[i] + y[i];
	fprintf(fout, "(");
	for (int i = 0; i < size; i++){
		if (i == size - 1){
			fprintf(fout, "%lf", x[i]);
		}
		else fprintf(fout, "%lf ", x[i]);
	}
	fprintf(fout, " ) + ( ");
	for (int i = 0; i < size; i++){
		if (i == size - 1){
			fprintf(fout, "%lf", y[i]);
		}
		else fprintf(fout, "%lf ", y[i]);
	}
	fprintf(fout, ") = (");
	for (int i = 0; i < size; i++){
		if (i == size - 1){
			fprintf(fout, "%lf", result[i]);
		}
		else fprintf(fout, "%lf ", result[i]);
	}
	fprintf(fout, ")\n");
	free(x);
	free(y);
	free(result);
}

/* Функция для разности векторов
 * Function for the difference of vectors*/
void doSubstractionVector(int size){
	double *x, *y, *result;
	x = malloc(size*sizeof(double));
	y = malloc(size*sizeof(double));
	result = malloc(size*sizeof(double));
	for (int i = 0; i < size; i++) fscanf(fin, "%lf", &x[i]);
	for (int i = 0; i < size; i++) fscanf(fin, "%lf", &y[i]);
	for (int i = 0; i < size; i++) result[i] =  x[i] - y[i];
	fprintf(fout, "(");
	for (int i = 0; i < size; i++){
		if (i == size - 1){
			fprintf(fout, "%lf", x[i]);
		}
		else fprintf(fout, "%lf ", x[i]);
	}
	fprintf(fout, " ) - ( ");
	for (int i = 0; i < size; i++){
		if (i == size - 1){
			fprintf(fout, "%lf", y[i]);
		}
		else fprintf(fout, "%lf ", y[i]);
	}
	fprintf(fout, ") = (");
	for (int i = 0; i < size; i++){
		if (i == size - 1){
			fprintf(fout, "%lf", result[i]);
		}
		else fprintf(fout, "%lf ", result[i]);
	}
	fprintf(fout, ")\n");
	free(x);
	free(y);
	free(result);
}

/* Функция для умножения векторов
 * Function for multiplying vectors*/
void doMultiplyVector(int size){
	double *x, *y, result = 0;
	x = malloc(size*sizeof(double));
	y = malloc(size*sizeof(double));
	for (int i = 0; i < size; i++) fscanf(fin, "%lf", &x[i]);
	for (int i = 0; i < size; i++) fscanf(fin, "%lf", &y[i]);
	for (int i = 0; i < size; i++) result +=  x[i] * y[i];
	fprintf(fout, "(");
	for (int i = 0; i < size; i++){
		if (i == size - 1){
			fprintf(fout, "%lf", x[i]);
		}
		else fprintf(fout, "%lf ", x[i]);
	}
	fprintf(fout, " ) * ( ");
	for (int i = 0; i < size; i++){
		if (i == size - 1){
			fprintf(fout, "%lf", y[i]);
		}
		else fprintf(fout, "%lf ", y[i]);
	}
	fprintf(fout, ") = %lf\n", result);
	free(x);
	free(y);
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
	char a, b;
	do{
		puts("Enter filename to input");
		scanf("%s", input);
		puts("Enter filename to output");
		scanf("%s", output);
		fin = fopen(input, "r");
			do{
			if ((fout = fopen(output, "a")) == NULL){
				fout = fopen(output, "w");
			}
			fscanf(fin," %c %c", &operation, &mode);
			printf("%c", operation);
			printf("%c", mode);
			if (operation != '+' && operation != '-' && operation != '*' && operation != '/' && operation != '!' && operation != '^'){
				a = 'n';
			}
			switch (mode){
				case 'v':
					int size;
//					puts("Welcome to vector mode calculator!");
//					puts("Here are the main operations supported by the vector mode:");
//					puts("1. +		(Adds vectors)");
//					puts("2. -		(Subtracts the second vector from the first)");
//					puts("3. *		(Calculates the scalar product of vectors)");
//					puts("Enter the operation from the list, then the coordinates of the vectors in order)");
//					puts("Enter the operation from the list");
					fscanf(fin, "%i", &size);
					switch (operation){
						case '+':
							doSumVector(size);
							fclose(fout);
							break;
						case '-':
							doSubstractionVector(size);
							fclose(fout);
							break;
						case '*':
							doMultiplyVector(size);
							fclose(fout);
							break;
						default:
							fprintf(fout, "There is no such operation, repeat the input\n");
							fclose(fout);
					}
					break;
				case 'n':
					double x, y;
//					puts("Welcome to normal mode calculator!");
//					puts("Here are the main operations supported by the normal mode:");
//					puts("1. +		(Adds up the input numbers)");
//					puts("2. -		(Subtracts the second number from the first)");
//					puts("3. *		(Multiplies the first number by the second)");
//					puts("4. /		(Divides the first number by the second)");
//					puts("5. !		(Finds the factorial of a number)");
//					puts("6. ^		(Raises a number to the power of another number, works only with integers");
//					puts("Enter the operation from the list, then two numbers in order");
//					puts("Enter the operation from the list");
					switch (operation){
						case '+':
							fscanf(fin, "%lf %lf", &x, &y);
							fprintf(fout, "%lf + %lf = %lf\n", x, y, doSum(x, y));
							fclose(fout);
							break;
						case '-':
							fscanf(fin, "%lf %lf", &x, &y);
							fprintf(fout, "%lf - %lf = %lf\n", x, y, doSubstraction(x, y));
							fclose(fout);
							break;
						case '*':
							fscanf(fin, "%lf %lf", &x, &y);
							fprintf(fout, "%lf * %lf = %lf\n", x, y, doMultiply(x, y));
							fclose(fout);
							break;
						case '/':
							fscanf(fin, "%lf %lf", &x, &y);
							fprintf(fout, "%lf / %lf = %lf\n", x, y, doDivision(x, y));
							fclose(fout);
							break;
						case '!':
							fscanf(fin, "%lf", &x);
							fprintf(fout, "%lf! = %llu\n", x, doFactorial(x));
							fclose(fout);
							break;
						case '^':
							fscanf(fin, "%lf %lf", &x, &y);
							fprintf(fout, "%lf^%lf = %llu\n", x, y, doPow(x, y));
							fclose(fout);
							break;
						default:
							fprintf(fout, "There is no such operation, repeat the input\n");
							fclose(fout);
					}
					break;
				default:
					fprintf(fout, "There is no such mode\n");
					fclose(fout);
			}
			}while(a != 'n');
		fclose(fin);
		fclose(fout);
		puts("Continue working? y - yes, n - no");
		scanf(" %c", &b);
	}
	while(b!='n');
	fclose(fin);
	fclose(fout);
	return 0;
}
