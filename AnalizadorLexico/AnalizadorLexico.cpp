#include <algorithm> // for std::find
#include <iterator> // for std::begin, std::end#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>

#include <iostream>
#include <string>

bool isTDL(int c) {
	char chars[] = { ';', '<', ' ', '+'};
	bool cexists = std::find(std::begin(chars), std::end(chars), c) != std::end(chars);
	if (cexists) {
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
	int e_aceptacion = { 1, 9, 12, 15 };

	do {
		system("cls");
		printf("Ingrese la cadena: ");
		//gets_s(cadena);
		//std::string mystr;
		//std::getline(std::cin, mystr);

		std::ifstream ifs("../test.txt");
		std::string mystr((std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()));

		std::cout << "CADENA: " << mystr << "\n";

		const char *puntero = mystr.c_str();
		int estado = 0;
		char token = 0;
		const char *temp = puntero;
		temp++;

		while (*puntero != '\0') {
			switch (estado) {

				//Variable
			case 0:
				//ESTADO 5
				if (*puntero == 'B' && *temp == 'e') {
					estado = 5;
					token = 0;
				}
				// ESTADO 10
				else if (*puntero == 'E' && *temp == 'n') {
					estado = 10;
					token = 0;
				}
				//ESTADO 13
				else if (*puntero == 'i' && *temp == 'n') {
					estado = 13;
					token = 0;
				}
				//ESTADO 1
				else if (isalpha(*puntero)) {
					estado = 1;
					token = 1;
				}
				else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			case 1:
				if (isalpha(*puntero) || isdigit(*puntero)) {
					estado = 1;
					token = 0;
				}
				else if (isTDL(*puntero)) {
					estado = 0;
					token = 0;
				}
				else {
					estado = ERROR;
					estado = ERROR;
				}
				break;
			case 2:
				//TODO: CHECK
				if (isdigit(*puntero)) {
					estado = 2;
					token = 0;
				}
				break;
			//BEGIN
			case 5:
				if (*puntero == 'e') {
					estado = 6;
					token = 0;
				}
				else {
					estado = ERROR;
					estado = ERROR;
				}
				break;
			case 6:
				if (*puntero == 'g') {
					estado = 7;
					token = 0;
				}
				else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			case 7:
				if (*puntero == 'i') {
					estado = 8;
					token = 0;
				}
				else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			case 8:
				if (*puntero == 'n') {
					estado = 9;
					token = 0;
				}
				else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			case 9:
				if (*puntero == '\n') {
					estado = 0;
					token = 0;
				}
				else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			//END
			case 10:
				if (*puntero == 'n') {
					estado = 11;
					token = 0;
				} else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			case 11: 
				if (*puntero == 'd') {
					estado = 12;
					token = 0;
				} else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			case 12:
				if (*puntero == ' ') {
					estado = 0;
					token = 0;
				} else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			//INT
			case 13:
				if (*puntero == 'n') {
					estado = 14;
					token = 0;
				} else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			case 14:
				if (*puntero == 't') {
					estado = 15;
					token = 0;
				} else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			case 15:
				if (*puntero == ' ') {
					estado = 0;
					token = 0;
				} else {
					estado = ERROR;
					token = ERROR;
				}
				break;
			case -1:
				break;
			default:
				token = 0;
				break;

			}
			puntero++;
			temp++;

			printf("FT(q%d,%c)= q%d\n", estado, puntero[-1], estado);
			if (estado == ERROR) {
				break;
			}

		} // fin While*/

		printf("Token: %d\n", token);

		switch (token) {
		case 0:
			printf("No es identificador\n");
			break;
		case 1:
			printf("Es identificador\n");
			break;
		case 2:
			printf("otra cosa\n");
			break;
		}

		printf("ESTADO ACTUAL: %d", estado);

		// Comprobar si la cadena es aceptada
		bool aceptado = std::find(std::begin(e_aceptacion), std::end(e_aceptacion), estado) != std::end(e_aceptacion);
		if (aceptado) {
			printf("\n\nCadena aceptada\n\n");
		}
		else {
			printf("\n\nCadena no aceptada\n\n");
		}

		printf("Desea salir del programa (s/n)?:");
		scanf_s("%c", &salir);
	} while ((salir != 's') && (salir != 'S'));
}

/* possible solution for variable and reserved words
go to the state as normal but return to q0 if the second
letter is any other alpha character*/