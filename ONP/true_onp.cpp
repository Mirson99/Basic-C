#include <iostream>
#include <stdio.h>
#include "Stack.h" // stos operatorów
#include <math.h>
#include "DStack.h" //stos z liczbami

#define DOT '.'

void skipSpaces(); // pomijanie spacji
double getNum(); // uzyskaj liczbe
int isDigit(char c); // czy liczba
char getOper(); // uzyskaj operator
char getDigit(); // uzyskaj cyfre
int isOper(char cOper); // czy operator
int prior(char cOper); // porownuje priorytet operatorów
double Calc(double arg1, double arg2, char cOperator); // zwraca wynik działania
void ONP(); // funkcja główna
void CalcInBrackets(StackItem** pStack, DStackItem** pDStack);

int main(int argc, char *argv[])
{
	printf("Podaj wyrazenie: ");
	ONP();

	return 0;
}
void skipSpaces()
{
	char c;
	while ((c = getchar()) == ' ');
	ungetc(c, stdin);
}
double getNum()
{
	char c;
	double num = 0;
	int sign = 0;
	skipSpaces();
	//	( c=getchar() == '-' ) ? o=-1 : ungetc( c, stdin );
	if ((c = getchar()) == '+' || c == '-')
	{
		if (c == '-') sign = -1;
	}
	else ungetc(c, stdin);
	while (isDigit(c = getchar()))
		num = num * 10 + (c - '0');
	if (c == DOT)
	{
		double coef = 0.1;
		while (isDigit(c = getchar()))
		{
			num += (c - '0')*coef;
			coef *= 0.1;
		}


	}
	ungetc(c, stdin);
	return (sign) ? -num : num;
}
char getDigit()
{
	skipSpaces();
	return getchar();
}
int isDigit(char c)
{
	return (c >= '0') && (c <= '9') || (c==DOT);
}
char getOper()
{
	skipSpaces();
	return getchar();
}
int isOper(char cOper)
{
	switch (cOper)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '^':
	case '(':
	case ')': return 1;
	}
	return 0;

}
int prior(char cOper)
{
	switch (cOper)
	{
	case '+':
	case '-': return 2;
	case '*':
	case '/': return 3;
	case '^': return 4;
	case '(': 
	case ')':  return 1; //normalnie wrzucam nawiasy otwierające na stos operatorów
	}
	return 0;
}
void ONP()
{
	char c;
	StackItem *pStack = NULL;
	makeEmptyStack(&pStack);
	DStackItem *pDStack = NULL;
	dmakeEmptyStack(&pDStack);
	//Stack będzie stosem operatorów
	//DStack będzie zawierał nasze onp
	//*******dpush(&pDStack, getNum()); //wrzucam na stos pierwsza liczbe
	/*while (isDigit(c = getDigit())) //wrzucam pierwszą liczbę na stos
	{
		dpush(&pDStack, c);

	}*/
	while ((c = getchar())!='\n')
	{
		if (isOper(c)) //dopoki jest operator
		{
			if (c != '(')
			{

				while (prior(c) <= prior(top(pStack)))
				{
					if (top(pStack) == '(')
					{
						del(&pStack);
						break;
					}
					dpush(&pDStack, pop(&pStack)); //zrzucam operator ze stosu operatorów i zapisuje go do stosu onp
					

				}

				push(&pStack, c);
			}
			else push(&pStack, c); // wkladamy nawias otwierajacy na stos operatorow
			//*********dpush(&pDStack, getNum()); //wkladamy na stos onp kolejna liczbe

			
			


		}
		if (isDigit(c))
		{
			while(isDigit(c=getDigit()))
			dpush(&pDStack, c);
		}
	}
	while (!isEmpty(pStack))
	{
		
		dpush(&pDStack, pop(&pStack));//wrzucamy pozostałe operatory na stos onp
	}
	
	while (!isDEmpty(pDStack))
	{
		printf("%c", dpop(&pDStack)); 
	}
	
}

double Calc(double arg1, double arg2, char cOperator)
{
	switch (cOperator)
	{
	case '+': return arg1 + arg2;
	case '-': return arg1 - arg2;
	case '*': return arg1 * arg2;
	case '/': if (fabs(arg2 > 1e-14)) return arg1 / arg2;
		cout << "Error: division by 0!!\n";
		break;
	case '^': return pow(arg1, arg2);
	}
	return 0;
}

void CalcInBrackets(StackItem** pStack, DStackItem** pDStack)
{
	char c;
	while ((c = pop(pStack)) != '(') // zrzucamy do momentu napotkania ( bo to wyrazenie jest w nawiasach
	{
		dpush(pDStack, c);
	}
}