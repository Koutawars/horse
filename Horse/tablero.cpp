#include "tablero.h"
#include "time.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "pch.h"

Tablero::Tablero(){}
Tablero::~Tablero(){}
void  Tablero::mover_Ficha(int x, int y) {
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i == x && j == y) {
				matrix[i][j] = 1;
			}
			else
			{
				matrix[i][j] = 0;
			}
		}
	}
}
void Tablero::imprimir() {
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			std::cout<<"[" << matrix[i][j] << "]";
		}
		std::cout<<std::endl;
	}
	std::cout << std::endl;
}
void Tablero::mover_Caballo(int x, int y, int n) {

	if (n > 0) {
		int p = n;
		int indice = rand() % 8;
		if (x - 2 > 0 && y + 1 < 8 && indice == 0) {
			matrix[x][y] = 0;
			x -= 2;
			y += 1;
			matrix[x][y] = 1;
			n--;
		}
		else if (x - 2 > 0 && y - 1 > 0 && indice == 1) {
			matrix[x][y] = 0;
			x -= 2;
			y -= 1;
			matrix[x][y] = 1;
			n--;
		}
		else if (x + 2 < 8 && y + 1 < 8 && indice == 2) {
			matrix[x][y] = 0;
			x += 2;
			y += 1;
			matrix[x][y] = 1;
			n--;
		}
		else if (x + 2 < 8 && y - 1 < 0 && indice == 3) {
			matrix[x][y] = 0;
			x += 2;
			y -= 1;
			matrix[x][y] = 1;
			n--;
		}
		else if (x - 2 > 0 && y + 1 < 8 && indice == 4) {
			matrix[x][y] = 0;
			x -= 2;
			y += 1;
			matrix[y][x] = 1;
			n--;
		}
		else if (x - 2 > 0 && y - 1 > 0 && indice == 5) {
			matrix[x][y] = 0;
			x -= 2;
			y -= 1;
			matrix[y][x] = 1;
			n--;
		}
		else if (x + 2 < 8 && y + 1 < 8 && indice == 6) {
			matrix[x][y] = 0;
			x += 2;
			y += 1;
			matrix[y][x] = 1;
			n--;
		}
		else if (x + 2 < 8 && y - 1 < 0 && indice == 7) {
			matrix[x][y] = 0;
			x += 2;
			y -= 1;
			matrix[y][x] = 1;
			n--;
		}
		if (p > n) {
			imprimir();
		}
		mover_Caballo(x, y, n);


	}

}
