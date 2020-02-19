#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <conio.h>
using namespace std;

class PilaBR
{
	string buscar;
	string remplazar;
	bool estado;
	int posicion;
	PilaBR* post;

	bool bandera;
public:

	PilaBR* CtrY;
	PilaBR* CtrZ;

	PilaBR();
	PilaBR(string _bus, string _rem);
	~PilaBR();

	void PushY(string _bus, string _rem);
	void PopY();

	void PushZ(string _bus, string _rem);
	void PopZ();

	void ReportePila();

	string getBus(void);
	string getRem(void);
};


PilaBR::PilaBR(){}
PilaBR::PilaBR(string _bus, string _rem) 
{
	buscar = _bus;
	remplazar = _rem;
	post = NULL;
}

PilaBR::~PilaBR() {
	CtrY = NULL;
	CtrZ = NULL;
}


void PilaBR::PushY(string _bus, string _rem)
{
	PilaBR* nuevo = new PilaBR(_bus, _rem);
	if (CtrY == NULL)
	{
		CtrY = nuevo;
	}
	else
	{
		nuevo->post = CtrY;
		nuevo->estado = false;
		CtrY = nuevo;
	}
}

void PilaBR::PopY() 
{
	if (CtrY != NULL)
	{
		PushZ(CtrY->buscar, CtrY->remplazar);
		CtrY = CtrY->post;
	}
}

void PilaBR::PushZ(string _bus, string _rem)
{
	PilaBR* nuevo = new PilaBR(_bus, _rem);
	if (CtrZ == NULL)
	{
		CtrZ = nuevo;
	}
	else
	{
		nuevo->post = CtrZ;
		nuevo->estado = true;
		CtrZ = nuevo;
	}
}

void PilaBR::PopZ()
{
	if (CtrZ!=NULL)
	{
		PushY(CtrZ->buscar, CtrZ->remplazar);
		CtrZ = CtrZ->post;
	}
}

string PilaBR::getBus() {
	return this->buscar;
}

string PilaBR::getRem() {
	return this->remplazar;
}

void PilaBR::ReportePila() {
	ofstream repPilaY;
	repPilaY.open("repLOGY.txt", ios::out);

	if (repPilaY.fail()) {
		cout << "ERROR ARCHIVO NO ENCONTRADO" << endl;
	}
	else
	{
		PilaBR* aux = CtrY;

		if (aux != NULL)
		{
			repPilaY << "digraph Y {rankdir =LR; style = filled; bgcolor = white; color = green; node[style = filled, color = green, shape = tripleoctagon];";
			while (aux != NULL)
			{
				repPilaY << "op" << &*aux << "[label = \" " << " PALABRA BUSCADA: " << aux->buscar << "\\n" << " REMPLAZADO POR: " << aux->remplazar << "\\n" << " ESTADO: NO REVERTIDO" << "\\n" << " PALABRE: null" << "\\n" << " POSICION: null" << "\"];";
				repPilaY << "op" << &*aux << "->" << "op" << &*(aux->post) << "[arrowhead = halfopen color = blue];";
				aux = aux->post;
			}
			repPilaY << "}";
		}



		aux = CtrZ;

		if (aux != NULL)
		{
			repPilaY << "digraph Z {rankdir =LR; style = filled; bgcolor = white; color = red; node[style = filled, color = red, shape = tripleoctagon];";
			while (aux != NULL)
			{
				repPilaY << "op" << &*aux << "[label = \" " << " PALABRA BUSCADA: " << aux->buscar << "\\n" << " REMPLAZADO POR: " << aux->remplazar << "\\n" << " ESTADO:REVERTIDO" << "\\n" << " PALABRE: null" << "\\n" << " POSICION: null" << "\"];";
				repPilaY << "op" << &*aux << "->" << "op" << &*(aux->post) << "[arrowhead = halfopen color = blue];";
				aux = aux->post;
			}
			repPilaY << "}";
		}

		repPilaY.close();

		char  dotT[] = "dot -Tjpg repLOGY.txt -o repLOGY.jpg";
		system(dotT);
		char  dotI[] = "repLOGY.jpg";
		system(dotI);


		cout << endl << "REPORTE EJECUTADO" << endl;
	}


	ofstream repPilaZ;
	repPilaZ.open("repLOGZ.txt", ios::out);

	if (repPilaZ.fail()) {
		cout << "ERROR ARCHIVO NO ENCONTRADO" << endl;
	}
	else
	{
		PilaBR* aux = CtrZ;

		if (aux != NULL)
		{
			repPilaZ << "digraph Z {rankdir =LR; style = filled; bgcolor = white; color = red; node[style = filled, color = red, shape = tripleoctagon];";
			while (aux != NULL)
			{
				repPilaZ << "op" << &*aux << "[label = \" " << " PALABRA BUSCADA: " << aux->buscar << "\\n" << " REMPLAZADO POR: " << aux->remplazar << "\\n" << " ESTADO:REVERTIDO" << "\\n" << " PALABRE: null" << "\\n" << " POSICION: null" << "\"];";
				repPilaZ << "op" << &*aux << "->" << "op" << &*(aux->post) << "[arrowhead = halfopen color = blue];";
				aux = aux->post;
			}
			repPilaZ << "}";
		}

		repPilaZ.close();

		char  dotT[] = "dot -Tjpg repLOGZ.txt -o repLOGZ.jpg";
		system(dotT);
		char  dotI[] = "repLOGZ.jpg";
		system(dotI);


		cout << endl << "REPORTE EJECUTADO" << endl;
	}
}