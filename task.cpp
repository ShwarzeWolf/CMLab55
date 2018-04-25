// Lab4CountigMaths.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <cmath>
#include <iostream>

using namespace std;

float f(float x) {
	return pow(x, 3) / (1 + x * x);
}

float fFirstDeriative(float x) {
	return(pow(x, 4) + 3 * pow(x, 2)) / pow(1 + x * x, 2);
}

float fSecondDeriative(float x) {
	return (6 * x - 2 * pow(x, 3)) / pow(1 + x * x, 3);
}

//step 1
float findM(int a, int b) {
	float result = 0.00;
	for (float i = a; i <= b; i+= 0.001 )
		if (abs(fSecondDeriative(i)) > result)
			result = abs(fSecondDeriative(i));
	return result;
}

float findStepAproximately(int a, int b) {
	return pow(12 * 0.001 / (findM(a, b) * abs(b - a)), 0.5);
}

int numberOfSteps(int a, int b) {
	return ceil((b - a) / findStepAproximately(a,b) / 4.0) * 4 ;
}

float findStep(int a, int b, int numberOfSteps) {
	return (b - a) / float(numberOfSteps);
}

//task2
//trapeze formula
float calculateIntegralTrapese(int a, int b, float step) {
	float sum = (f(a) + f(b)) / 2.00;

	for (float i = a + step; i <= b - step; i += step) {
		cout << i << ' ' << sum << '\n';
		sum += f(i);
	};

	return sum * step;
}
//calculate error using Runge Rule
float calculateTrapezeError(int a, int b, float step) {
	return abs(calculateIntegralTrapese(a, b, step) - calculateIntegralTrapese(a, b, 2 * step)) / 3.00;
}

//task3
//Simpson Method
float calculateIntegralSimpson(int a, int b, float step){
	float sum = (f(a) + f(b)) / 2.00;
	float i = a + step;

	while (i <= b - step) {
		sum += 2 * f(i);
		cout << i << ' ' << sum << '\n';
		i += step;
		sum +=  f(i);
		cout << i <<  ' ' << sum << '\n';
		i += step;
	};

	return 2.00 * sum * step / 3.00;
}

float calculateSimpsonError(int a, int b, float step) {
	return abs(calculateIntegralSimpson(a, b, step) - calculateIntegralSimpson(a, b, 2 * step)) / 15.00;
}


int main()
{
	int a = 0;
	int b = 2;

	//task1 
	int n = numberOfSteps(a, b);
	float step = findStep(a, b, n);
	cout << "step: "<< step << "\nnumber of steps:" << n << endl;

	//task2
	cout << "Value calculated by trapeze method: " << calculateIntegralTrapese(a, b, step) << " +- " << calculateTrapezeError(a, b, step) << endl;
	cout << "Value calculated by Simpson method: " << calculateIntegralSimpson(a, b, step / 100) << " +- " << calculateSimpsonError(a, b, step / 100) << endl;

	system("pause");
    return 0;
}

