#ifndef EVALUARE_EXPRESIE_H
#define EVALUARE_EXPRESIE_H

#include <cstddef>
#include <string>

class Coada;
class Stiva;

namespace PolishNotation
{
    /**
     * Verifica daca un simbol este operator binar admis
     * @param simbol caracterul verificat
     * @pre Nu exista 
     * @post Returneaza true daca simbol este unul dintre: +, -, *, /
     * @return true daca simbolul este operator, false in caz contrar
     * Complexitate Theta(1)
     */
    bool isOp(char simbol);

    /**
     * Verifica daca un token intreg reprezinta un operator codificat
     * @param token valoarea verificata
     * @pre Nu exista 
     * @post Returneaza true daca token-ul reprezinta un operator codificat intern
     * @return true daca token-ul este operator codificat, false altfel
     * Complexitate Theta(1)
     */
    bool esteOperatorCodificat(int token);

    /**
     * Codifica un operator/caracter special intr-un int
     * @param simbol operatorul sau caracterul special
     * @pre simbol trebuie sa fie un operator valid sau un caracter special folosit intern
     * @post Returneaza codificarea intreaga a simbolului
     * @return codificarea simbolului
     * Complexitate Theta(1)
     */
    int codificaOperator(char simbol);

    /**
     * Decodifica un token intreg intr-un caracter operator
     * @param token token codificat
     * @pre token trebuie sa reprezinte un operator codificat valid
     * @post Returneaza simbolul asociat token-ului
     * @return caracterul operator decodificat
     * Complexitate Theta(1)
     */
    char decodificaOperator(int token);

    /**
     * Returneaza prioritatea unui operator
     * @param simbol operatorul pentru care se cere prioritatea
     * @pre simbol trebuie sa fie operator valid sau '~' pentru minus unar
     * @post Returneaza prioritatea operatorului
     * @return 3 pentru ~, 2 pentru * sau /, 1 pentru + sau -, 0 altfel
     * Complexitate Theta(1)
     */
    int prioritate(char simbol);

    /**
     * Verifica daca un operator este asociativ la stanga
     * @param simbol operatorul verificat
     * @pre simbol trebuie sa fie operator valid sau '~'
     * @post Returneaza true daca operatorul este asociativ la stanga
     * @return true daca este asociativ la stanga, false altfel
     * Complexitate Theta(1)
     */
    bool esteAsociativLaStanga(char simbol);

    /**
     * Muta operatorul din varful stivei in coada postfixata
     * @param operatori stiva de operatori
     * @param postfixata coada ce retine expresia postfixata
     * @pre stiva operatori nu este vida
     * @post Elementul din varful stivei este eliminat si adaugat in coada postfixata
     * Complexitate Theta(1)
     */
    void mutaOperatorInCoada(Stiva &operatori, Coada &postfixata);

    /**
     * Transforma un token intr-o reprezentare text
     * @param token numar sau operator codificat
     * @pre token trebuie sa fie fie un numar valid, fie un operator codificat valid
     * @post Returneaza forma text a token-ului
     * @return numarul sub forma de string sau simbolul operatorului
     * Complexitate O(numarul de cifre ale token-ului)
     */
    std::string textToken(int token);

    /**
     * Construieste reprezentarea text a unei cozi postfixate
     * Coada este restaurata la final
     * @param postfixata coada postfixata
     * @pre postfixata contine o expresie postfixata valida sau partial valida
     * @post Returneaza forma text a cozii, iar continutul cozii ramane neschimbat
     * @return expresia postfixata sub forma de text
     * Complexitate O(n), unde n este numarul de token-uri
     */
    std::string postfixataCaText(Coada &postfixata);

    /**
     * Aplica un operator peste valorile din stiva
     * @param vals stiva de valori
     * @param simbol operatorul aplicat
     * @pre Pentru operator binar trebuie sa existe cel putin 2 operanzi in stiva
     *      pentru '~' trebuie sa existe cel putin 1 operand
     * @post Rezultatul operatiei este pus inapoi in stiva
     * @throws std::runtime_error daca expresia postfixata este invalida sau apare impartire la zero
     * Complexitate Theta(1)
     */
    void aplicaOperator(Stiva &vals, char simbol);

    /**
     * Evalueaza o expresie postfixata
     * @param postfixata coada ce contine expresia postfixata
     * @pre postfixata trebuie sa contina o expresie postfixata valida
     * @post Returneaza valoarea expresiei; continutul cozii este consumat
     * @return rezultatul evaluarii
     * @throws std::runtime_error daca expresia este invalida
     * Complexitate O(n), unde n este numarul de token-uri
     */
    int evalueazaPostfixata(Coada &postfixata);

    /**
     * Sare peste spatiile consecutive din expresie, incepand de la o pozitie data
     * @param expresie expresia analizata
     * @param idx pozitia de start
     * @pre idx <= expresie.size()
     * @post Returneaza prima pozitie >= idx care nu contine spatiu sau expresie.size()
     * @return noul index
     * Complexitate O(k), unde k este numarul de spatii consecutive sarite
     */
    std::size_t sariSpatii(const std::string &expresie, std::size_t idx);

    /**
     * Construieste forma postfixata a unei expresii infixate
     * @param expresie expresia infixata
     * @param answers coada in care se construieste postfixata
     * @pre expresia trebuie sa contina doar numere naturale, operatorii + - * /,
     *      paranteze si spatii; minusul unar este permis
     * @post answers contine expresia in forma postfixata
     * @throws std::runtime_error daca expresia este invalida
     * Complexitate O(n), unde n este lungimea expresiei
     */
    void construiestePostfixata(const std::string &expresie, Coada &answers);
}

/**
 * Transforma o expresie infixata in expresie postfixata text
 * @param expresie expresia infixata
 * @param postfixata string-ul rezultat
 * @pre expresia trebuie sa fie valida
 * @post postfixata contine forma postfixata a expresiei
 * @throws std::runtime_error daca expresia este invalida
 * Complexitate O(n), unde n este lungimea expresiei
 */
void transformaInPostfixata(const std::string &expresie, std::string &postfixata);

/**
 * Evalueaza o expresie infixata si intoarce si forma postfixata
 * @param expresie expresia infixata
 * @param postfixata string in care se pune forma postfixata
 * @pre expresia trebuie sa fie valida
 * @post postfixata contine forma postfixata, iar functia returneaza valoarea expresiei
 * @return rezultatul evaluarii expresiei
 * @throws std::runtime_error daca expresia este invalida
 * Complexitate O(n), unde n este lungimea expresiei
 */
int evalueazaInfixata(const std::string &expresie, std::string &postfixata);

#endif