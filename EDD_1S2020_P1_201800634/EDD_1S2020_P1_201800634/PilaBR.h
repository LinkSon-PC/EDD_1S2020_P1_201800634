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