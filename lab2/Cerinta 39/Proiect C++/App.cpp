#include "EvaluareExpresie.h"

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main() {
	string expresie;

	cout << "Introdu expresia infixata: ";
	getline(cin, expresie);

	try {
		string postfixata;
		int rezultat = evalueazaInfixata(expresie, postfixata);

		cout << "Expresie postfixata: " << postfixata << "\n";
		cout << "Rezultat: " << rezultat << "\n";
	}
	catch (const exception& exceptie) {
		cout << "Eroare: " << exceptie.what() << "\n";
	}

	return 0;
}
