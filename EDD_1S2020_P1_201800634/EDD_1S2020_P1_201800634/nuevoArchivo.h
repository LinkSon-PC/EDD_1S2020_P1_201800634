#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
//#include <curses.h>

using namespace std;

class nuevoArchivo
{
private:
	char letra;
	nuevoArchivo* prev;
	nuevoArchivo* post;
	int size;
public:
	void archivo(void);
	nuevoArchivo();
	nuevoArchivo(char);
	void gotoxy(int, int);
	void Marco(void);
	void agregarLetra(char);
	void MostrarArchivo(void);
	
	//void borrarLetra(void);
};

nuevoArchivo* first;
nuevoArchivo* last;

void nuevoArchivo::agregarLetra(char _letra) {
	nuevoArchivo* nuevo = new nuevoArchivo(_letra);

	if (first == NULL)
	{
		first = nuevo;
		nuevo->post = last;
		last = nuevo;
		size++;
	}
	else
	{
		last->post = nuevo;
		nuevo->prev = last;
		last = nuevo;
		size++;
	}
	cout << _letra;
}

void nuevoArchivo::gotoxy(int x, int y) {
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}

void nuevoArchivo::Marco(void) {
	system("clear");
	for (int i = 0; i < 79; i++)
	{
		gotoxy(0 + i, 0);
		printf("%c", 219);

		gotoxy(0 + i, 23);
		printf("%c", 219);
	}

	for (int i = 0; i < 23; i++)
	{
		gotoxy(0, 0 + i);
		printf("%c", 219);

		gotoxy(79, 0 + i);
		printf("%c", 219);
	}
}

void nuevoArchivo::archivo() {
	//Marco();
	bool escribir = true;
	do
	{
		char ctr = _getch();
		if (ctr == 23) {//ASCII   CONTROL CODES
				escribir = false; //^W
		}
		else
		{
			if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT))
			{
				//borrarLetra();
			}
			else {
				agregarLetra(letra);
			}
		}
	}
	while (escribir);

	MostrarArchivo();
}


void nuevoArchivo::MostrarArchivo() {
	nuevoArchivo* aux = first;
	while (aux != NULL) {
		cout << aux->letra;
		aux = aux->post;
	}
	cout << endl << "FIN DEL ARCHIVO" << endl;
	system("pause");
}

nuevoArchivo::nuevoArchivo(char _letra) {
	letra = _letra;
	prev = NULL;
	post = NULL;
}

nuevoArchivo::nuevoArchivo() {
	letra = ' ';
	size = 0;
	prev = NULL;
	post = NULL;
	first = NULL;
	last = NULL;
}

