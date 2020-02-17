#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "PilaBR.h"
//#include <curses.h>

using namespace std;

class nuevoArchivo
{
private:
	char letra;
	nuevoArchivo* prev;
	nuevoArchivo* post;

	int X;
	int Y;
public:
	void archivo(void);
	nuevoArchivo();
	nuevoArchivo(char);
	~nuevoArchivo();

	void gotoxy(int, int);
	void Marco(void);

	void agregarLetra(char, int , int);
	void MostrarArchivo(void);
	void MostrarPantalla(void);
	void BorrarPalabra(int, int);

	void Buscar_Reemplazar(void);
	void Reemplazar(string, string);
	
	//void borrarLetra(void);
};

nuevoArchivo* first;
nuevoArchivo* last;

nuevoArchivo::nuevoArchivo() {
	letra = ' ';
	X = 0;
	Y = 0;
	prev = NULL;
	post = NULL;
	first = NULL;
	last = NULL;
}

nuevoArchivo::~nuevoArchivo() {
	first = NULL;
	last = NULL;
	prev = NULL;
	post = NULL;
	X = 0;
	Y = 0;
	letra = ' ';
}

nuevoArchivo::nuevoArchivo(char _letra) {
	letra = _letra;
	X = 0;
	Y = 0;

	prev = NULL;
	post = NULL;
}



void nuevoArchivo::agregarLetra(char _letra, int _X, int _Y) {
	nuevoArchivo* nuevo = new nuevoArchivo(_letra);
	nuevo->X = _X;
	nuevo->Y = _Y;

	if (first == NULL)
	{
		first = nuevo;
		nuevo->post = last;
		last = nuevo;
	}
	else if ((last->X)<_X || (last->Y)<_Y)
	{
		last->post = nuevo;
		nuevo->prev = last;
		last = nuevo;
	}
	else
	{
		bool carry = false;
		nuevoArchivo* aux = first;
		while (aux != NULL)
		{			
			if (carry == false)
			{
				if ((aux->X) == (_X) && (aux->Y) == _Y) {
					nuevo->post = aux->post;
					aux->post = nuevo;
					nuevo->prev = aux;
					if (nuevo->post == NULL)
					{
						last = nuevo;
						MostrarPantalla();
						return;
					}
					else
					{
						nuevo->post->prev = nuevo;
						carry = true;
					}
				}
			}
			else
			{
				if ((aux->Y) == _Y){
					aux->X++;
				}
			}
			aux = aux->post;
		}

	}
	MostrarPantalla();
}

void nuevoArchivo::gotoxy(int x, int y) {
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}



void nuevoArchivo::Marco(void) {
	system("cls");
	char marco[] = " ^w (GUARDAR Y REMPLAZAR)     ^C (REPORTES)   ^S (GUARDAR)";
	for (int i = 0; i < sizeof(marco); i++)
	{
		cout << marco[i];
		gotoxy(0 + i, 24);
	}
}

void nuevoArchivo::MostrarArchivo() {
	cout << endl<<endl << "MOSTRAR ARCHIVO" << endl;

	nuevoArchivo* aux = first;

	while (aux != NULL) {
		cout << aux->letra;
		aux = aux->post;
	}
	cout << endl << "FIN DEL ARCHIVO" << endl;
	Sleep(1000);
	system("cls");
}

void nuevoArchivo::MostrarPantalla() {
	nuevoArchivo* aux = first;

	while (aux != NULL) {
		gotoxy(aux->X, aux->Y);
		cout << aux->letra;
		aux = aux->post;
	}
}



PilaBR Pila;
void nuevoArchivo::archivo() {
	Marco();

	gotoxy(0, 0);
	int X = Y = 0;
	bool escribir = true;
	do
	{
		char ctr = _getch();
		if (ctr == 1) {//ASCII   CONTROL CODES
				escribir = false; //^X
		}
		else if (ctr == 23) {//ASCII   CONTROL CODES
			Buscar_Reemplazar();
		}
		else if (ctr == 26) {//ASCII   CONTROL CODES	^Z
			if (Pila.CtrZ !=NULL)
			{
				Reemplazar(Pila.CtrZ->getRem(), Pila.CtrZ->getBus());
				Pila.PopZ();
			}
		}
		else if (ctr == 25) {//ASCII   CONTROL CODES	^Y
			if (Pila.CtrY != NULL)
			{
				Reemplazar(Pila.CtrY->getBus(), Pila.CtrY->getRem());
				Pila.PopY();
			}
		}
		else if (ctr == 3) {//ASCII   CONTROL CODES		^c

		}
		else
		{
			if (GetAsyncKeyState(VK_LEFT))
			{
				if (X>=0)
				{
					X--;
					gotoxy(X, Y);
				}
			}
			else if (GetAsyncKeyState(VK_RIGHT))
			{
				X++;
				gotoxy(X, Y);
			}
			else if (GetAsyncKeyState(VK_UP))
			{
				if (Y >= 0)
				{
					Y--;
					gotoxy(X, Y);
				}
			}
			else if (GetAsyncKeyState(VK_DOWN))
			{
				Y++;
				gotoxy(X, Y);
			}
			else if (GetAsyncKeyState(VK_RETURN))
			{
				agregarLetra('\n',X, Y);
				X = 0;
				Y++;
				gotoxy(X, Y);
			}
			else if (GetAsyncKeyState(VK_SPACE))
			{
				agregarLetra(' ', X, Y);
				X++;
				gotoxy(X, Y);
			}
			else if (GetAsyncKeyState(VK_BACK))
			{
				if (X>0 || first != NULL)
				{
					BorrarPalabra(X, Y);
					cout << ' ';
					X--;
					gotoxy(X, Y);
				}
			}
			else {
				agregarLetra(ctr, X,Y);
				X++;
				gotoxy(X, Y);
			}
		}
	}
	while (escribir);
				MostrarArchivo();
}



void nuevoArchivo::BorrarPalabra(int _X, int _Y) {
	nuevoArchivo* aux = first;
	bool carry = false;

	while (aux!=NULL)
	{
		if (carry == false)
		{
			if (aux->Y == _Y && aux->X == _X)
			{
				if (aux == first)
				{
					if (aux->post!=NULL)
					{
						first = aux->post;
						aux->post->prev = NULL;
					}
					else
					{
						first = NULL;
						last = NULL;
					}
				}
				else
				{
					aux->prev->post = aux->post;
					if (aux->post == NULL)
					{
						last = aux->prev;
					}
					else
					{
						aux->post->prev = aux->prev;
					}
					carry = true;
				}
			}
			else if (aux->Y == _Y && aux->X > _X)
			{
				aux->X--;
			}
		}
		aux = aux->post;
	}
	Marco();
	MostrarPantalla();
}

void nuevoArchivo::Buscar_Reemplazar() 
{
	char ctr = _getch();
	bool enter = true;

	system("cls");
	char marco[] = " BUSCAR Y REEMPLAZAR:";
	for (int i = 0; i < sizeof(marco); i++)
	{
		cout << marco[i];
		gotoxy(0 + i, 23);
	}
	gotoxy(20, 23);
	
	string buscar;
	cin >> buscar;

	string _bus;
	string _rem;

	bool carry = false;

	for (int i = 0; i < size(buscar); i++)
	{
		if (carry == false)
		{
			if (buscar[i] != 59)
			{
				_bus += buscar[i];
			}
			else
			{
				carry = true;
			}
		}
		else
		{
			_rem += buscar[i];
		}
	}

	Pila.PushZ(_bus, _rem);
	Reemplazar(_bus, _rem);
	Sleep(5000);
}

void nuevoArchivo::Reemplazar(string _bus, string _rem) {

	nuevoArchivo* aux = first;
	bool _resultado = false;
	int nodo = 0;
	int _nodoBusqueda = 0;

	bool carry = false;

	nuevoArchivo* inicioP = NULL;
	nuevoArchivo* finP = NULL;

	while (aux != NULL)
	{
		for (int i = 0; i < size(_bus); i++)
		{
			if (aux != NULL)
			{
				//cout << "palabra" << aux->letra << endl;

				if (aux->letra == _bus[i])
				{
					//cout << "LETRA " << _bus[i] << endl;
					//cout << aux->letra << " ";
					_nodoBusqueda++;

					if (aux->letra == _bus[0])
					{
						inicioP = aux->prev;
						cout << "INICIO LETRA" << _bus[i] << endl;
					}
					else if (size(_bus) == _nodoBusqueda)
					{
						cout << "FIN LETRA" << _bus[i] << endl<< "PALABRA ENCONTRADA" << endl;
						finP = aux->post;

						for (int i = 0; i < size(_rem); i++)
						{
								if (aux->post == last) {
									last == aux->prev;
									last->post = NULL;
								}
								else {
									aux->prev->post = aux->post;
									aux->post->prev = aux->prev;
								}
								aux = aux->prev;
						}
						for (int i = 0; i < size(_rem); i++)
						{
							nuevoArchivo* nuevo = new nuevoArchivo(_rem[i]);
							if (aux == last)
							{
								last->post = nuevo;
								nuevo->prev = last;
								last = nuevo;
							}
							else
							{
								nuevo->post = aux->post;
								aux->post = nuevo;
								nuevo->prev = aux;
								nuevo->Y = aux->Y;
								nuevo->X = aux->X + 1;
							}aux = nuevo;
						}
						_nodoBusqueda = 0;
					}

				}
				else
				{
					_nodoBusqueda = 0;
					if (carry == true )
					{
						if (aux->prev != NULL)
						{
							if (aux->prev->Y == aux->Y)
							{
								aux->X += size(_rem) - size(_bus);
							}
						}
					}
					break;
				}

			aux = aux->post;
			}

		}
		if (aux!=NULL)
		{
			aux = aux->post;
		}
	}

	Sleep(5000);

	Marco();
	MostrarPantalla();
}