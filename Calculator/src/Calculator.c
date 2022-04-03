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

/* Функция для сложения векторов
 * Function for adding vectors*/
void doSumVector(int size){
	double *x, *y, *result;
	x = malloc(size*sizeof(double));
	y = malloc(size*sizeof(double));
	result = malloc(size*sizeof(double));
	for (int i = 0; i < size; i++) scanf("%lf", &x[i]);
	for (int i = 0; i < size; i++) scanf("%lf", &y[i]);
	for (int i = 0; i < size; i++) result[i] =  x[i] + y[i];
	printf("(");
	for (int i = 0; i < size; i++){
		if (i == size - 1){
			printf("%lf", x[i]);
		}
		else printf("%lf ", x[i]);
	}
	printf(" ) + ( ");
	for (int i = 0; i < size; i++){
		if (i == size - 1){
			printf("%lf", y[i]);
		}
		else printf("%lf ", y[i]);
	}
	printf(") = (");
	for (int i = 0; i < size; i++){
		if (i == size - 1){
			printf("%lf", result[i]);
		}
		else printf("%lf ", result[i]);
	}
	printf(")\n");
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
	for (int i = 0; i < size; i++) scanf("%lf", &x[i]);
	for (int i = 0; i < size; i++) scanf("%lf", &y[i]);
	for (int i = 0; i < size; i++) result[i] =  x[i] - y[i];
	printf("(");
	for (int i = 0; i < size; i++){
		if (i == size - 1){
			printf("%lf", x[i]);
		}
		else printf("%lf ", x[i]);
	}
	printf(" ) - ( ");
	for (int i = 0; i < size; i++){
		if (i == size - 1){
			printf("%lf", y[i]);
		}
		else printf("%lf ", y[i]);
	}
	printf(") = (");
	for (int i = 0; i < size; i++){
		if (i == size - 1){
			printf("%lf", result[i]);
		}
		else printf("%lf ", result[i]);
	}
	printf(")\n");
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
	for (int i = 0; i < size; i++) scanf("%lf", &x[i]);
	for (int i = 0; i < size; i++) scanf("%lf", &y[i]);
	for (int i = 0; i < size; i++) result +=  x[i] * y[i];
	printf("(");
	for (int i = 0; i < size; i++){
		if (i == size - 1){
			printf("%lf", x[i]);
		}
		else printf("%lf ", x[i]);
	}
	printf(" ) * ( ");
	for (int i = 0; i < size; i++){
		if (i == size - 1){
			printf("%lf", y[i]);
		}
		else printf("%lf ", y[i]);
	}
	printf(") = (%lf)", result);
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

/* Функция для нахождения экспоненты числа с помощью ряда Тейлора
 * A function for finding the exponent of a number using a Taylor series*/
double doExp(double x){
	double result = 1, degree;
	int j;
	for (int i = 1; i < 21; i++){
		j = 1;
		degree = 1;
		while (j <= i){
			degree*=x;
			j+=1;
		}
		result += degree/doFactorial(i);
	}
	return result;
}

/* Функция для нахождения натурального логарифма числа с помощью ряда Тейлора
 * A function for finding the natrual logarithm of a number using a Taylor series*/
double doLn(double x){
	/* Объявляем переменные для хранения результата и для промежуточных вычислений
	 * We declare variables for storing the result and for intermediate calculations*/
	double result = 0, degree;
	int j, i = 1;
	while (i < 21){
		degree = 1;
		j = 1;
		while (j <= i){
			degree*=((x-1)/(x+1));
			j+=1;
		}
		degree = (degree / i);
		result = (result + degree);
		i+=2;
	}
	return result*2;
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

/* Функция для нахождения квадратного корня числа используя свойства логарифмов
 * A function for finding the square root of a number
 * Using the properties of logarithms*/
double doSqrt(double x){
	return doExp(0.5 * doLn(x));
}

/* Функция для нахождения кубического корня числа используя свойства логарифмов
 * A function for finding the cubic root of a number
 * Using the properties of logarithms*/
double doCbrt(double x){
	return doExp(doLn(x)/3);
}

/* Функция для реализации интерфейса с Английским языком
 * A function for implementing an interface with English*/
void en(void){
	char a;
	int operation;
	char mode;
	do{
		puts("Select the operating mode v - for working with vectors, n - for normal mode");
		scanf(" %c", &mode);
		switch (mode){
			case 'v':
				int size;
				puts("Welcome to vector mode calculator!");
				puts("Here are the main operations supported by the vector mode:");
				puts("1. +		(Adds vectors)");
				puts("2. -		(Subtracts the second vector from the first)");
				puts("3. *		(Calculates the scalar product of vectors)");
				puts("Enter the operation number from the list, then the coordinates of the vectors in order)");
				puts("Enter the operation number from the list");
				scanf(" %i", &operation);
				puts("Enter the length of the vector");
				scanf("%i", &size);
				switch (operation){
					case 1:
						doSumVector(size);
						break;
					case 2:
						doSubstractionVector(size);
						break;
					case 3:
						doMultiplyVector(size);
						break;
					default:
						puts("There is no such operation, repeat the input");
				}
				break;
			case 'n':
				double x, y;
				puts("Welcome to normal mode calculator!");
				puts("Here are the main operations supported by the normal mode:");
				puts("1. +		(Adds up the input numbers)");
				puts("2. -		(Subtracts the second number from the first)");
				puts("3. *		(Multiplies the first number by the second)");
				puts("4. /		(Divides the first number by the second)");
				puts("5. !		(Finds the factorial of a number)");
				puts("6. pow		(Raises a number to the power of another number, works only with integers");
				puts("7. ln		(Finds the natural logarithm of a number");
				puts("8. sqrt		(Finds the square root of a number)");
				puts("9. cbrt		(Finds the cubic root of a number)");
				puts("10. abs		(Finds the number module");
				puts("11. exp		(Finds the exponent in the power of a number)");
				puts("Enter the operation number from the list, then two numbers in order");
				puts("Enter the operation number from the list");
				scanf(" %i", &operation);
				switch (operation){
					case 1:
						puts("Enter the first number");
						scanf("%lf", &x);
						puts("Enter the second number");
						scanf("%lf", &y);
						printf("%lf + %lf = %lf", x, y, doSum(x, y));
						break;
					case 2:
						puts("Enter the first number");
						scanf("%lf", &x);
						puts("Enter the second number");
						scanf("%lf", &y);
						printf("%lf - %lf = %lf", x, y, doSubstraction(x, y));
						break;
					case 3:
						puts("Enter the first number");
						scanf("%lf", &x);
						puts("Enter the second number");
						scanf("%lf", &y);
						printf("%lf * %lf = %lf", x, y, doMultiply(x, y));
						break;
					case 4:
						puts("Enter the first number");
						scanf("%lf", &x);
						puts("Enter the second number");
						scanf("%lf", &y);
						printf("%lf / %lf = %lf", x, y, doDivision(x, y));
						break;
					case 5:
						puts("Enter a number");
						scanf("%lf", &x);
						printf("%lf! = %llu", x, doFactorial(x));
						break;
					case 6:
						puts("Enter a number to exponentiate");
						scanf("%lf", &x);
						puts("Enter the degree to which you want to raise the number");
						scanf("%lf", &y);
						printf("%lf^%lf = %llu", x, y, doPow(x, y));
						break;
					case 7:
						puts("Enter a number to find the natural logarithm");
						scanf("%lf", &x);
						printf("ln(%lf) = %.3lf", x, doLn(x));
						break;
					case 8:
						puts("Enter a number to find the square root");
						scanf("%lf", &x);
						printf("sqrt(%lf) = %.3lf", x, doSqrt(x));
						break;
					case 9:
						puts("Enter a number to find the cubic root");
						scanf("%lf", &x);
						printf("cbrt(%lf) = %.3lf", x, doCbrt(x));
						break;
					case 10:
						puts("Enter a number to find the module");
						scanf("%lf", &x);
						printf("abs(%lf) = %lf", x, doAbs(x));
						break;
					case 11:
						puts("Enter a number to find the exponent");
						scanf("%lf", &x);
						printf("exp(%lf) = %.3lf", x, doExp(x));
						break;
					default:
						puts("There is no such operation, repeat the input");
				}
				break;
		default: puts("There is no such mode");
		}
		puts("\nContinue working? y - yes, n - no");
		scanf(" %c", &a);
	}
	while(a!='n');
}


/* Функция для реализации интерфейса с Русским языком
 * Function for implementing the interface with the Russian language*/
void ru(void){
	char a;
	int operation;
	char mode;
	do{
		puts("Выберите режим работы v - для работы с векторами, n - для обычного режима");
		scanf(" %c", &mode);
		switch (mode)
			{
			case 'v':
				int size;
				puts("Приветствую в векторном режиме калькулятора");
				puts("Вот основные операции, поддерживаемые векторным режимом:");
				puts("1. +		(Складывает векторы)");
				puts("2. -		(Вычитает второй вектор из первого)");
				puts("3. *		(Вычисляет скалярное произведение векторов)");
				puts("Введите номер операции из списка, затем координаты векторов по порядку)");
				puts("Введите номер операции из списка");
				scanf(" %i", &operation);
				puts("Введите длину вектора");
				scanf("%i", &size);
				switch (operation){
					case 1:
						doSumVector(size);
						break;
					case 2:
						doSubstractionVector(size);
						break;
					case 3:
						doMultiplyVector(size);
						break;
					default:
						puts("Такой операции нет, повторите ввод");
					}
				break;
			case 'n':
				double x, y;
				puts("Приветствую в обычном режиме калькулятора!");
				puts("Здесь перечислены операции, поддерживаемые обычным режимом:");
				puts("1. +		(Складывает входные числа)");
				puts("2. -		(Вычитает второе число из первого");
				puts("3. *		(Умножает первое число на второе)");
				puts("4. /		(Делит первое число на второе)");
				puts("5. !		(Находит факториал числа)");
				puts("6. pow		(Возводит число в степень другого числа, работает только с целыми числами");
				puts("7. ln		(Находит натуральный логарифм числа)");
				puts("8. sqrt		(Находит квадратный корень числа)");
				puts("9. cbrt		(Находит кубический корень числа)");
				puts("10. abs		(Находит модуль числа");
				puts("11. exp		(Находит экспоненту в степени числа)");
				puts("Введите номер операции из списка, затем два числа по порядку");
				puts("Введите номер операции из списка");
				scanf(" %i", &operation);
				switch (operation){
					case 1:
						puts("Введите первое число");
						scanf("%lf", &x);
						puts("Введите второе число");
						scanf("%lf", &y);
						printf("%lf + %lf = %lf", x, y, doSum(x, y));
						break;
					case 2:
						puts("Введите первое число");
						scanf("%lf", &x);
						puts("Введите второе число");
						scanf("%lf", &y);
						printf("%lf - %lf = %lf", x, y, doSubstraction(x, y));
						break;
					case 3:
						puts("Введите первое число");
						scanf("%lf", &x);
						puts("Введите второе число");
						scanf("%lf", &y);
						printf("%lf * %lf = %lf", x, y, doMultiply(x, y));
						break;
					case 4:
						puts("Введите первое число");
						scanf("%lf", &x);
						puts("Введите второе число");
						scanf("%lf", &y);
						printf("%lf / %lf = %lf", x, y, doDivision(x, y));
						break;
					case 5:
						puts("Введите число");
						scanf("%lf", &x);
						printf("%lf! = %llu", x, doFactorial(x));
						break;
					case 6:
						puts("Введите число для возведения в степень");
						scanf("%lf", &x);
						puts("Введите степень, в которую нужно возвести число");
						scanf("%lf", &y);
						printf("%lf^%lf = %llu", x, y, doPow(x, y));
						break;
					case 7:
						puts("Введите число для нахождения натурального логарифма");
						scanf("%lf", &x);
						printf("ln(%lf) = %.3lf", x, doLn(x));
						break;
					case 8:
						puts("Введите число для нахождения квадратного корня");
						scanf("%lf", &x);
						printf("sqrt(%lf) = %.3lf", x, doSqrt(x));
						break;
					case 9:
						puts("Введите число для нахождения кубического корня");
						scanf("%lf", &x);
						printf("cbrt(%lf) = %.3lf", x, doCbrt(x));
						break;
					case 10:
						puts("Введите число для нахождения модуля");
						scanf("%lf", &x);
						printf("abs(%lf) = %lf", x, doAbs(x));
						break;
					case 11:
						puts("Введите число для нахождения экспоненты");
						scanf("%lf", &x);
						printf("exp(%lf) = %.3lf", x, doExp(x));
						break;
					default:
						puts("Такой операции нет, повторите ввод");
				}
				break;
			default: puts("Такого режима нет");
			}
	puts("\nПродолжить работу? y - да, n - нет");
	scanf(" %c", &a);
	}
	while(a!='n');
}

/* Основная функция, точка входа
 * Main function, entry point*/
int main(int argc, char* argv[]){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	/* Переменные для хранения значения языка
	 * И для выхода из цикла по завершению программы
	 * Variables for storing the language value
	 * And for exiting the loop at the end of the program*/
	int language, chk = 1;
	puts("Select a language, to do this, enter 1 - en or 2 - ru");
	puts("Выберите язык, для этого введите 1 - en или 2 - ru");
	while (chk == 1){
		scanf(" %i", &language);
		switch (language){
			case 1:
				en();
				chk = 0;
				break;
			case 2:
				ru();
				chk = 0;
				break;
			default:
				puts("Поддержка этого языка отсутствует");
				puts("There is no support for this language");
		}
	}
	return 0;
}
