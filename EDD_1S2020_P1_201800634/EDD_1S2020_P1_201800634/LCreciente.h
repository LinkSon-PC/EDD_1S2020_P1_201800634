#pragma once
#include <string>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

class LCreciente
{
	LCreciente* post;
	string direccion;

public:
	LCreciente* first;
	LCreciente* last;

	LCreciente();
	LCreciente(string);

	void gotoxy(int, int);

	inline string getDireccion() { return this->direccion; };

	void Agregar(string);
	void Mostrar();
};

LCreciente::LCreciente() {
	first = NULL;
	last = NULL;
	post = NULL;
}

void LCreciente::gotoxy(int x, int y) {
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}

LCreciente::LCreciente(string _direccion) {
	this->direccion = _direccion;
}

void LCreciente::Agregar(string _direccion) {
	LCreciente* nuevo = new LCreciente(_direccion);

	if (first==NULL)
	{
		first = nuevo;
		last = nuevo;
		first->post = last;
		
	}
	else
	{
		last->post = nuevo;
		nuevo->post = first;
		last = nuevo;
	}
}

void LCreciente::Mostrar() {
	LCreciente* aux = first;
	if (aux!=NULL)
	{
		do
		{
			cout << aux->direccion << endl;
			aux = aux->post;
		} while (aux != first);

	}

	ofstream repCircular;
	repCircular.open("repCircular.txt", ios::out);

	if (repCircular.fail()) {
		cout << "ERROR ARCHIVO NO ENCONTRADO" << endl;
	}
	else
	{
		repCircular << "digraph G {rankdir =LR; style = filled; bgcolor = white; color = lightgrey; node[style = filled, color = red, shape = tripleoctagon];";
		LCreciente* aux = first;

		if (aux!=NULL)
		{
			do
			{
				repCircular << "op" << &*aux << "[label = \" " << aux->direccion << "\\n" << "archivo_memoria" << &*aux << "\"];";
				repCircular << "op" << &*aux << "->" << "op" << &*(aux->post) << "[arrowhead = halfopen color = blue];";
				aux = aux->post;
			} while (aux!=first);

			repCircular << "}";

			repCircular.close();

			char  dotT[] = "dot -Tjpg repCircular.txt -o repCircular.jpg";
			system(dotT);
			char  dotI[] = "repCircular.jpg";
			system(dotI);


			cout << endl << "REPORTE EJECUTADO" << endl;
		}

	}

	Sleep(5000);
}
 