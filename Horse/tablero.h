#pragma once
#include <iostream>

class Tablero
{
public:
	int matrix[8][8];
	void mover_Ficha(int x, int y);
	void mover_Caballo(int x, int y, int n);
	void imprimir();
	Tablero();
	~Tablero();
};


