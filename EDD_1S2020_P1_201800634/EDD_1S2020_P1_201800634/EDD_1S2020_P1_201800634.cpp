// EDD_1S2020_P1_201800634.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include <fstream>
#include "LCreciente.h"
#include "nuevoArchivo.h"

using namespace std;

void gotoxy(int,int);
void Marco(void);
void Abrir(void);

nuevoArchivo nuevo;
LCreciente reciente;

void Menu(void);
int OpcionMenu(const char* s[]);

bool sesion = true;

int main()
{
	Marco();
	Menu();
	 return 0;
}

 void gotoxy(int x, int y) {
	 HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	 COORD dwPos;
	 dwPos.X = x;
	 dwPos.Y = y;
	 SetConsoleCursorPosition(hcon, dwPos);
 }

 void Marco() {
	 system("cls");
	 for (int i = 0; i < 79; i++)
	 {
		 gotoxy(0 + i, 0);
		 printf("%c", 219);

		 gotoxy(0 + i, 24);
		 printf("%c", 219);
	 }

	 for (int i = 0; i < 24; i++)
	 {
		 gotoxy(0, 0+i);
		 printf("%c", 219);

		 gotoxy(79, 0+i);
		 printf("%c", 219);
	 }
 }

 void Menu() {

	 do
	 {
		 Marco();
		 gotoxy(20, 5); printf("UNIVERSIDAD DE SAN CARLOS DE GUATEMALA");
		 gotoxy(20, 6); printf("FACULTAD DE INGENIERIA");
		 gotoxy(20, 7); printf("ESTRUCTURA DE DATOS");
		 gotoxy(20, 8); printf("PRACTICA 1");
		 gotoxy(20, 9); printf("ANTHONY FERNANDO SON MUX");
		 gotoxy(20, 10); printf("201800634");

		 gotoxy(20, 14); printf("MENU");
		 const char* opciones[] = {"CREAR ARCHIVO","ABRIR ARCHIVO","ARCHIVOS RECIENTES","SALIR"};
		 int opcion;
		 opcion = OpcionMenu(opciones);

		 switch (opcion)
		 {
		 case 1:
			 //CREAR ARCHIVO
			 system("cls");

			 nuevo.archivo();
			 nuevo.~nuevoArchivo();
			 break;
		 case 2:
			 //ABRIR ARCHIVO
			 system("cls");
			 Abrir();
			 			 
			 break;
		 case 3:
			 //VER RECIENTES
			 system("cls");
			 reciente.Mostrar();
			 Marco();
			 break;
		 case 4:
			 //SALIR
			 return;
			 break;
		 default:
			 opcion = 0;
			 break;
		 }

	 } while (true);
 }

 int OpcionMenu(const char* _opcion[]) {
	 bool repetir = true;
	 int op = sizeof(_opcion);

	 int posicion = 1;
	 char _tecla;

		 for (int i = 0; i < op; i++)
		 {
			 gotoxy(20, 15+i); printf(_opcion[i]);
		 }
		 
		 gotoxy(16, 14 + posicion);
		 printf("*");

		 do
		 {
			 Sleep(500);
			 if (GetAsyncKeyState(VK_UP))//ARIBA
			 {
			 gotoxy(16, 14 + posicion);
			 printf(" ");
				 if (posicion > 1)
				 {
					 posicion--;
				 }
				 else { posicion = op; }
			 }
			 else if (GetAsyncKeyState(VK_DOWN))//ABAJO
			 {
				 gotoxy(16, 14 + posicion);
				 printf(" ");
				 if (posicion < 4)
				 {
					 posicion++;
				 }
				 else { posicion = 1; }
			 }
			 gotoxy(16, 14 + posicion);
			 printf("*");
		 } while (!GetAsyncKeyState(VK_RETURN));
		 return posicion;

 }

 void Abrir(){
	 Marco();

	 ifstream archivo;
	 string texto;

	 string direccion;

	 char marco[] = " ESCRIBA DIRECCION DEL ARCHIVO  ";
	 for (int i = 0; i < sizeof(marco); i++)
	 {
		 cout << marco[i];
		 gotoxy(10 + i, 10);
	 }
	 gotoxy(11, 11);

	 cin >> direccion;
	 archivo.open(direccion.c_str(), ios::in);

	 if (archivo.fail())
	 {
		 cout << endl << "DIRECCION NO ENCONTRADA";
		 archivo.close();
	 }
	 else
	 {
		 reciente.Agregar(direccion);
		 system("cls");
		 while (!archivo.eof())
		 {
			 getline(archivo, texto);
		 }
		 archivo.close();
		 nuevo.AbrirArchivo(texto);
		 nuevo.~nuevoArchivo();
	 }
	 fflush(stdin);
 }