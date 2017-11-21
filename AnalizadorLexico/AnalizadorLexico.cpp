#include <algorithm> // for std::find
#include <iterator> // for std::begin, std::end#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>

#include <iostream>
#include <string>

#include <vector>

bool isTDL(int c) {
	char chars[] = {' ', '(', ')', '[', ']', '"', '=', ';', '\n'};
	bool cexists = std::find(std::begin(chars), std::end(chars), c) != std::end(chars);
	if (cexists) {
		return true;
	}
	else {
		return false;
	}
}

bool isSim(int c) {
	char chars[] = {'+', '-', '*', '/', '^', '<', '>'};
	bool cexists = std::find(std::begin(chars), std::end(chars), c) != std::end(chars);
	if (cexists) {
		return true;
	}
	else {
		return false;
	}
}

bool isPalabraR(std::string palabra) {
	//Palabras reservadas
	std::string reserved_w[] = {"Begin", "End", "int", "String", "boolean", "double", "if", "then", "else", "do", "while", "for", "TRUE", "FALSE", "char", "null", "return"};

	bool exists = std::find(std::begin(reserved_w), std::end(reserved_w), palabra) != std::end(reserved_w);
	if (exists) {
		return true;
	}
	else {
		return false;
	}
}

int main() {
	char cadena[2];
	char salir;

	int ERROR = -1;
	int e_aceptacion[5] = { 1, 9, 12, 15 };

	//Contadores
	int pReservadasCounter = 0;
	int variablesCounter = 0;
	int numerosCounter = 0;
	int operadoresCounter = 0;
	int erroresCounter = 0;

	int current_linea = 0;
	int current_col = 0;

	//Errores
	std::vector<int> lineas_err = {};
	std::vector<int> cols_err = {};


	do {
		system("cls");
		//printf("Ingrese la cadena: ");
		//gets_s(cadena);
		//std::string mystr;
		//std::getline(std::cin, mystr);

		std::ifstream ifs("../test.txt");
		std::string mystr((std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()));

		std::cout << "CONTENIDO A EVALUAR:\n " << mystr << "\n\n";

		const char *puntero = mystr.c_str();
		int estado = 0;
		char token = 0;
		const char *temp = puntero;
		std::string acumulador = "";
		//Adelantar puntero
		temp++;

		while (*puntero != '\0') {
			switch (estado) {

				//Variable
			case 0:
				//;
				if (*puntero == ';') {
					estado = 3;
					token = 0;
				}
				//digitos
				else if (isdigit(*puntero)) {
					estado = 4;
					token = 0;
				}
				//==
				else if (*puntero == '=' && *temp == '=') {
					estado = 7;
					token = 0;
				}
				//&&
				else if (*puntero == '&' && *temp == '&') {
					estado = 9;
					token = 0;
				}
				//||
				else if (*puntero == '|' && *temp == '|') {
					estado = 11;
					token = 0;
				}
				//<=
				else if (*puntero == '<' && *temp == '=') {
					estado = 13;
					token = 0;
				}
				//>=
				else if (*puntero == '>' && *temp == '=') {
					estado = 15;
					token = 0;
				}
				//SIM
				else if (isSim(*puntero)) {
					estado = 2;
					token = 0;
				}
				//ALPHA
				else if (isalpha(*puntero)) {
					estado = 1;
					token = 1;
					//Acumular caracter
					acumulador += *puntero;
				}
				else if ()
				else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			case 1:
				if (isalpha(*puntero) || isdigit(*puntero)) {
					estado = 1;
					token = 0;
					//Acumular caracter
					acumulador += *puntero;
				}
				else if (isTDL(*puntero)) {
					estado = 0;
					token = 0;

					//Contador varibles
					if (!isPalabraR(acumulador)) {
						variablesCounter++;
					}
					if (isPalabraR(acumulador)) {
						pReservadasCounter++;
					}
					//Reiniciar acumulador
					acumulador = "";
				}
				else if (*puntero == ';') {
					estado = 3;
					token = 0;

					//Contador varibles
					if (!isPalabraR(acumulador)) {
						variablesCounter++;
					}
					if (isPalabraR(acumulador)) {
						pReservadasCounter++;
					}
					//Reiniciar acumulador
					acumulador = "";
				}
				else {
					estado = ERROR;
					token = ERROR;

					//Contador varibles
					if (!isPalabraR(acumulador)) {
						variablesCounter++;
					}
					if (isPalabraR(acumulador)) {
						pReservadasCounter++;
					}
					//Reiniciar acumulador
					acumulador = "";
				}

				break;
			//Simbolos
			case 2:
				if (isTDL(*puntero)) {
					estado = 0;
					token = 0;

					//Contar operador
					operadoresCounter++;
				}
				else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			case 3:
				if (*puntero == '\n') {
					estado = 0;
					token = 0;
				}
				else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			//DIGITOS
			case 4:
				if (isdigit(*puntero)) {
					estado = 4;
					token = 0;
				}
				else if (*puntero == '.') {
					estado = 5;
					token = 0;
				}
				else if (isTDL(*puntero)) {
					estado = 0;
					token = 0;

					//Contar numero
					numerosCounter++;
				}
				else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			case 5 :
				if (isdigit(*puntero) && isdigit(*temp)) {
					estado = 5;
					token = 0;
				}
				else if (isdigit(*puntero) && !isdigit(*temp)) {
					estado = 6;
					token = 0;
				}
				else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			case 6:
				if (isTDL(*puntero)) {
					estado = 0;
					token = 0;

					//Contar numero
					numerosCounter++;
				}
				else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			//==
			case 7:
				if (*puntero == '=') {
					estado = 8;
					token = 0;
				}
				else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			case 8:
				if (isTDL(*puntero)) {
					estado = 0;
					token = 0;

					//Contar operador
					operadoresCounter++;
				}
				else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			//&&
			case 9:
				if (*puntero == '&') {
					estado = 10;
					token = 0;
				}
				else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			case 10:
				if (isTDL(*puntero)) {
					estado = 0;
					token = 0;

					//Contar operador
					operadoresCounter++;
				}
				else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			// ||
			case 11:
				if (*puntero == '|') {
					estado = 12;
					token = 0;
				}
				else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			case 12:
				if (isTDL(*puntero)) {
					estado = 0;
					token = 0;

					//Contar operador
					operadoresCounter++;
				}
				else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			// <=
			case 13:
				if (*puntero == '=') {
					estado = 14;
					token = 0;
				}
				else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			case 14:
				if (isTDL(*puntero)) {
					estado = 0;
					token = 0;

					//Contar operador
					operadoresCounter++;
				}
				else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			// >= 
			case 15:
				if (*puntero == '=') {
					estado = 16;
					token = 0;
				}
				else {
					estado = ERROR;
					token = ERROR;
				}
			case 16:
				if (isTDL(*puntero)) {
					estado = 0;
					token = 0;

					//Contar operador
					operadoresCounter++;
				}
				else {
					estado = ERROR;
					token = ERROR;
				}
			case -1:
				//EROR
				estado = 0;
				erroresCounter++;

				//Go back col
				current_col--;
				//log errors
				cols_err.push_back(current_col);
				lineas_err.push_back(current_linea);

				//Go back *
				puntero--;
				temp--;
				break;
			}
			//Lineas y cols
			current_col++;

			//Count lineas
			if (*puntero == '\n') {
				current_linea++;
				current_col = 0;
			}

			puntero++;
			temp++;

			printf("FT(q%d,%c)= q%d\n", estado, puntero[-1], estado);
			/*if (estado == ERROR) {
				break;
			}*/

		} // fin While*/

		if (estado == 1) {
			//std::cout << "\n# P Reservadas: " << acumulador;
			if (isPalabraR(acumulador)) {
				pReservadasCounter++;
			} 
			if (!isPalabraR(acumulador)) {
				variablesCounter++;
			}
		}
		//Contadores
		printf("\n\n*********** Contadores ***********\n");
		std::cout << "\n# P Reservadas: " << pReservadasCounter;
		std::cout << "\n# Variables: " << variablesCounter;
		std::cout << "\n# Numeros: " << numerosCounter;
		std::cout << "\n# Operadores: " << operadoresCounter;
		std::cout << "\n# Errores: " << erroresCounter;
		printf("\n\n**********************************\n\n");

		printf("ESTADO FINAL: %d\n", estado);

		//Errores
		printf("\n\n*********** Errores ***********\n");
		for (int i = 0; i < lineas_err.size(); i++) {
			std::cout << "\nError| Linea " << lineas_err[i] + 1 << " en la columna " << cols_err[i] + 1;
		}
		printf("\n\n**********************************\n\n");

		printf("Desea salir del programa (s/n)?:");
		scanf_s("%c", &salir);
	} while ((salir != 's') && (salir != 'S'));
}

/* possible solution for variable and reserved words
go to the state as normal but return to q0 if the second
letter is any other alpha character*/