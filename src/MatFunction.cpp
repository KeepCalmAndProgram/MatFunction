#include <stdio.h>
#include <iostream>
#include <math.h>

class Display {

protected:

	virtual void display(int arry[]) {
		for (int i = 0; i < 3; i++) {
			std::cout << "arry[" << i << "] = " << arry[i] << std::endl;
		}
	}

	double add(double* sum, double* difference, double* sumr, double* sumu, double* pdelta, double* x1r, double* x2r, double* x1u, double* x2u) {

		if (*pdelta > 0) {
			*sum = *x1r + *x2r;
		}
		else if (pdelta < 0) {
			*sumr = *x1r + *x2r;
			*sumu = *x1u + *x2u;
			*sum = *sumr + *sumu;
		}
		return *sum;
	}
	double subtract(double* difference, double* differencer, double* differenceu, double* pdelta, double* x1r, double* x2r, double* x1u, double* x2u) {

		if (*pdelta > 0) {
			*difference = *x1r - *x2r;
		}
		else if (pdelta < 0) {
			*differencer = *x1r - *x2r;
			*differenceu = *x1u - *x2u;
			*difference = *differencer + *differenceu;
		}
		return *difference;
	}
};

class MyClass : public Display {

public:

	MyClass(int arry[], double err) {

		arry[0] = 0;
		arry[1] = 2;
		arry[2] = 3;

		err = 0.000001;

	}

	using Display::display;
	using Display::add;
	using Display::subtract;

	double calculateDelte(double* delta, int arry[]);
	double sqrtNewton(double* delta, double* pdelta, double err);
	double sqrtHeron(int arry[], double* pdelta);

	void addZespolS(double sr, double su);
	void addZespolR(double rr, double ru);
	void calculateTheRoot(double* delta, double* pdelta, int* arry, double x1r, double x2r, double x1u, double x2u, double sr, double su, double rr, double ru);
	void displayResult(double* delta, double* pdelta, int* arry, double x1r, double x2r, double x1u, double x2u);

};

double MyClass::calculateDelte(double* delta, int arry[]) {
	std::cout << "\n" << arry[0] << "xx + " << arry[1] << "x + " << arry[2] << " = 0" << std::endl;
	*delta = (((double)arry[1] * (double)arry[1]) - (4 * (double)arry[0] * (double)arry[2]));
	std::cout << "\n" << *delta << " = " << arry[1] << " - 4*" << arry[0] << "*" << arry[2] << std::endl;

	return *delta;
}
double MyClass::sqrtNewton(double* delta, double* pdelta, double err) {
	*pdelta = *delta / 2;
	while ((*pdelta - *delta / *pdelta) > err) //0.000001
	{
		*pdelta = (*pdelta + *delta / *pdelta) / 2;
		if (*pdelta * *pdelta == *delta) break;
	}
	std::cout << "Sqrt Newtona " << *pdelta << std::endl;

	return *pdelta;
}
double MyClass::sqrtHeron(int arry[], double* pdelta) {
	double p;

	p = ((arry[0] + arry[1] + arry[2]) / 2);
	p *= -1;
	*pdelta = sqrt((p * (p - arry[0]) * (p - arry[1]) * (p - arry[2])));
	std::cout << "Sqrt Herona " << *pdelta << std::endl;

	return *pdelta;
}
void MyClass::addZespolS(double sr, double su) {
	su += sr;
	std::cout << "su = " << su << std::endl;
}
void MyClass::addZespolR(double rr, double ru) {
	ru += rr;
	std::cout << "ru = " << ru << std::endl;
}

void MyClass::calculateTheRoot(double* delta, double* pdelta, int* arry, double x1r, double x2r, double x1u, double x2u, double sr, double su, double rr, double ru) {

	if (*delta >= 0) {
		*pdelta = sqrt(*pdelta);
		x1r = ((-(double)arry[1] - *pdelta) / (2 * (double)arry[0])); //delta +
		x2r = ((-(double)arry[1] + *pdelta) / (2 * (double)arry[0]));
	}
	else if (*delta < 0) {
		*pdelta = sqrt((sqrt((double)arry[0] * (double)arry[0] + (double)arry[1] * (double)arry[1] + (double)arry[0]) / 2) + (sqrt((double)arry[0] * (double)arry[0] + (double)arry[1] * (double)arry[1] - (double)arry[0]) / 2));
		x1r = ((-(double)arry[1]) / (2 * (double)arry[0]));   //delta -
		x2r = x1r;
		x1u = ((-*pdelta) / (2 * (double)arry[0]));
		x2u = -x1u;
		x1r += x1u;
		x2r += x2u;
	}

	sr = x1r + x2r;
	su = x1u + x2u;
	rr = x1r - x2r;
	ru = x1u - x2u;
	addZespolS(sr, su);
	addZespolR(rr, ru);

}
void MyClass::displayResult(double* delta, double* pdelta, int* arry, double x1r, double x2r, double x1u, double x2u) {

	if (delta > 0) {
		std::cout << "          _____" << std::endl;
		std::cout << "pdelta = Vdelta" << std::endl;
		std::cout << "x1r = ("<< arry[1] << "-" << *pdelta << ")/2*" << arry[0] << std::endl;
		std::cout << "x1r = (" << arry[1] << "+" << *pdelta << ")/2*" << arry[0] << std::endl;
	}
	else if (delta < 0) {
		std::cout << "          _______" << std::endl;
		std::cout << "pdelta = V|delta|" << std::endl;

		std::cout << "x1r = -" << arry[1] << "/2*" << arry[0] << std::endl;
		std::cout << "x2r = " << x1r << std::endl;
		std::cout << "x1u = " << *pdelta  << "/2*" << arry[0] << std::endl;
		std::cout << "x2u = " << x1u << std::endl;
		std::cout << x1r << "+" << x1u << std::endl;
		std::cout << x2r << "+" << x2u << std::endl;
	}
	else if (delta == 0) {
		std::cout << "x1r = " << arry[1] << "/2*" << arry[0] << std::endl;
	}
}

int main()
{
	double sr, su, rr, ru;
	sr = su = rr = ru = 0;
	double delta, pdelta, x1r, err, x2r, x1u, x2u, x;
	delta = pdelta = err = x1r = x2r = x1u = x2u = x = 0;
	double sum, difference, sumr, sumu, differencer, differenceu;
	sum = difference = sumr = sumu = differencer = differenceu = 0;

	int* arry = new int[3];
	MyClass* obj = new MyClass(arry, err);

	if (arry[0] == 0 && arry[1] == 0 && arry[2] == 0) {
		std::cout << "Zle dane !!!" << std::endl;
		return 0;
	}
	if (arry[0] == 0) {
		if (arry[1] != 0) {
			x1r = -(double)arry[2] / (double)arry[1];
			std::cout << x1r << " = " << arry[2] << "/" << arry[1] << std::endl;
			if (x1r > 0) {
				x1r = sqrt(x1r);
				std::cout << "Pierwiastek = " << x1r << std::endl;
			}
			else if (x1r < 0) {
				x1r = sqrt(-1 * x1r);
				std::cout << "Pierwiastek = " << x1r << "i" << std::endl;
			}
			return 0;
		}
		else if (arry[1] == 0 && arry[2] != 0) {
			std::cout << "Rownanie sprzeczne" << std::endl;
			return 0;
		}
		else if (arry[1] == 0 && arry[2] == 0) {
			std::cout << "Rownanie tozsamosciowe" << std::endl;
			return 0;
		}
	}

	obj->display(arry);
	obj->calculateDelte(&delta, arry);

	if (err == 0) {
		pdelta = sqrt(delta);
		obj->calculateTheRoot(&delta, &pdelta, arry, x1r, x2r, x1u, x2u, sr, su, rr, ru);
		obj->displayResult(&delta, &pdelta, arry, x1r, x2r, x1u, x2u);
	}
	else if (err > 0.1) {
		obj->sqrtNewton(&delta, &pdelta, err);
		obj->calculateTheRoot(&delta, &pdelta, arry, x1r, x2r, x1u, x2u, sr, su, rr, ru);
		obj->displayResult(&delta, &pdelta, arry, x1r, x2r, x1u, x2u);
	}
	else if (err > 0 && err < 0.1) {
		obj->sqrtHeron(arry, &pdelta);
		obj->calculateTheRoot(&delta, &pdelta, arry, x1r, x2r, x1u, x2u, sr, su, rr, ru);
		obj->displayResult(&delta, &pdelta, arry, x1r, x2r, x1u, x2u);
	}
	obj->add(&sum, &difference, &sumr, &sumu, &pdelta, &x1r, &x2r, &x1u, &x2u);
	obj->subtract(&difference, &differencer, &differenceu, &pdelta, &x1r, &x2r, &x1u, &x2u);

	return 0;
}