#include "EvaluareExpresie.h"

#include "../../TAD Coada/Proiect C++/Coada.h"
#include "../../TAD Stiva/Proiect C++/Stiva.h"

#include <cctype>
#include <limits>
#include <stdexcept>
#include <string>

namespace PolishNotation
{
	const int MARCAJ_OPERATOR = numeric_limits<int>::min();
	const int MAX_COD_OPERATOR = MARCAJ_OPERATOR + 255;

	bool isOp(char simbol)
	{
		return simbol == '+' || simbol == '-' || simbol == '*' || simbol == '/';
	}

	bool esteOperatorCodificat(int token)
	{
		return token >= MARCAJ_OPERATOR && token <= MAX_COD_OPERATOR;
	}

	int codificaOperator(char simbol)
	{
		return MARCAJ_OPERATOR + static_cast<unsigned char>(simbol);
	}

	char decodificaOperator(int token)
	{
		return static_cast<char>(token - MARCAJ_OPERATOR);
	}
	
	int prioritate(char simbol)
	{
		if (simbol == '~')
			return 3;
		if (simbol == '*' || simbol == '/')
			return 2;
		if (simbol == '+' || simbol == '-')
			return 1;
		return 0;
	}

	bool esteAsociativLaStanga(char simbol)
	{
		return simbol != '~';
	}

	void mutaOperatorInCoada(Stiva &operatori, Coada &postfixata)
	{
		postfixata.adauga(operatori.sterge());
	}

	string textToken(int token)
	{
		if (!esteOperatorCodificat(token))
		{
			return to_string(token);
		}

		char simbol = decodificaOperator(token);
		if (simbol == '~')
		{
			return "u-";
		}

		return string(1, simbol);
	}

	string postfixataCaText(Coada &postfixata)
	{
		Coada aux;
		string rezultat;
		bool primulToken = true;

		while (!postfixata.vida())
		{
			int token = postfixata.sterge();
			if (!primulToken)
				rezultat += " ";
			rezultat += textToken(token);
			aux.adauga(token);
			primulToken = false;
		}

		while (!aux.vida())
			postfixata.adauga(aux.sterge());

		return rezultat;
	}

	void aplicaOperator(Stiva &vals, char symbol)
	{
		if (symbol == '~')
		{
			if (vals.vida())
				throw runtime_error("Expresie postfixata invalida.");

			int operand = vals.sterge();
			vals.adauga(-operand);
			return;
		}

		if (vals.vida())
			throw runtime_error("Expresie postfixata invalida.");

		int right = vals.sterge();

		if (vals.vida())
			throw runtime_error("Expresie postfixata invalida.");

		int left = vals.sterge();

		if (symbol == '+')
		{
			vals.adauga(left + right);
			return;
		}
		if (symbol == '-')
		{
			vals.adauga(left - right);
			return;
		}
		if (symbol == '*')
		{
			vals.adauga(left * right);
			return;
		}
		if (symbol == '/')
		{
			if (right == 0)
			{
				throw runtime_error("Impartire la zero.");
			}

			vals.adauga(left / right);
			return;
		}

		throw runtime_error("Operator necunoscut.");
	}

	int evalueazaPostfixata(Coada &postfixata)
	{
		Stiva vals;

		while (!postfixata.vida())
		{
			int token = postfixata.sterge();
			if (!esteOperatorCodificat(token))
				vals.adauga(token);
			else
				aplicaOperator(vals, decodificaOperator(token));
		}

		if (vals.vida())
			throw runtime_error("Expresie postfixata invalida.");

		int answer = vals.sterge();
		if (!vals.vida())
			throw runtime_error("Expresie postfixata invalida.");

		return answer;
	}

	size_t sariSpatii(const string &expresion, size_t idx)
	{
		while (idx < expresion.size() and isspace(static_cast<unsigned char>(expresion[idx])))
			idx++;
		return idx;
	}

	void construiestePostfixata(const string &expresion, Coada &answers)
	{
		Stiva op; /// operatori
		bool asteaptaOperand = true;
		bool areToken = false;

		for (size_t i = 0; i < expresion.size();)
		{
			i = sariSpatii(expresion, i);
			if (i >= expresion.size())
				break;

			char symbol = expresion[i];

			if (isdigit(symbol))
			{
				int num = 0;
				while (i < expresion.size() and isdigit(expresion[i]))
				{
					num = num * 10 + (expresion[i] - '0');
					i++;
				}

				answers.adauga(num);
				asteaptaOperand = false;
				areToken = true;
				continue;
			}

			if (symbol == '(')
			{
				op.adauga(codificaOperator(symbol));
				asteaptaOperand = true;
				areToken = true;
				i++;
				continue;
			}

			if (symbol == ')')
			{
				if (asteaptaOperand)
					throw runtime_error("Paranteze inchise in pozitie invalida.");

				while (!op.vida() and decodificaOperator(op.element()) != '(')
					mutaOperatorInCoada(op, answers);

				if (op.vida())
					throw runtime_error("Paranteze neechilibrate.");

				op.sterge();
				if (!op.vida() and decodificaOperator(op.element()) == '~')
					mutaOperatorInCoada(op, answers);

				asteaptaOperand = false;
				i++;
				continue;
			}

			if (isOp(symbol))
			{
				char operatorCurent = symbol;

				if (asteaptaOperand)
				{
					if (symbol != '-')
						throw runtime_error("Operator in pozitie invalida.");

					operatorCurent = '~';
				}

				while (!op.vida())
				{
					char operatorVarf = decodificaOperator(op.element());
					if (operatorVarf == '(')
						break;

					int TopPriority = prioritate(operatorVarf);
					int CurrPriority = prioritate(operatorCurent);
					bool trebuieScos = TopPriority > CurrPriority;

					if (!trebuieScos and esteAsociativLaStanga(operatorCurent))
						trebuieScos = TopPriority == CurrPriority;

					if (!trebuieScos)
						break;

					mutaOperatorInCoada(op, answers);
				}

				op.adauga(codificaOperator(operatorCurent));
				asteaptaOperand = true;
				areToken = true;
				i++;
				continue;
			}

			throw runtime_error("Caracter invalid in expresie.");
		}

		if (!areToken)
			throw runtime_error("Expresia este vida.");

		if (asteaptaOperand)
			throw runtime_error("Expresia se termina cu operator.");

		while (!op.vida())
		{
			char simbol = decodificaOperator(op.sterge());
			if (simbol == '(')
				throw runtime_error("Paranteze neechilibrate.");

			answers.adauga(codificaOperator(simbol));
		}
	}
}

void transformaInPostfixata(const string &expresie, string &postfixata)
{
	Coada rezultate;
	PolishNotation::construiestePostfixata(expresie, rezultate);
	postfixata = PolishNotation::postfixataCaText(rezultate);
}

int evalueazaInfixata(const string &expresie, string &postfixata)
{
	Coada rezultate;
	PolishNotation::construiestePostfixata(expresie, rezultate);
	postfixata = PolishNotation::postfixataCaText(rezultate);
	return PolishNotation::evalueazaPostfixata(rezultate);
}
