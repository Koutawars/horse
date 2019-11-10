#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "InputManager.h"
#include "mensaje.h"
#include <stdlib.h>
#include <time.h>
class Juego
{
private:
	Juego();
	~Juego();
public:
	void  mover_Ficha(int x, int y);
	int matrix[8][8];
	std::pair<int, int> posCaballo;
	void mover_Caballo();
	int numMov; // numero de movimientos que faltan
	static Juego& GetInstance();
	void inicializar();
	void cargarcontenido();
	void deleteContenido();
	void actualizar(ALLEGRO_EVENT evento, bool* done);
	void pintar(ALLEGRO_DISPLAY* display);
	int contador = 0;
	bool comenzarContador = false;
	int tiempo = 600; // el tiempo en segundos 600 segundos = 10 minutos
	std::vector<Mensaje*>* menu; // vector de Mensaje para el menu
	
	/*------------Pantalla-----------*/
	void cambiarPantalla(int pantalla); // función para cambiar pantalla
	int pantalla = 0; // pantalla por defecto (menu = 0)
	ALLEGRO_BITMAP* menuFondo;
	/*------------Pantalla-----------*/

	/*-----------mapa incio_lista---------*/
	ALLEGRO_FONT* imprimirmuertos;
	ALLEGRO_FONT* abut;
	int orientacion = 2;//0 Norte, 1 este,2 sur, 3 oeste
	int deaths; // cuenta el numero de veces que mueres
	bool elturno;// true cuando es el elturno del jugador, false cuando es la CPU
	bool piensa = false; // variable para saber si piensa (sleep)
	bool mato; // Cuando mata  al menos uno el gato
	bool win = false; // variable es true cuando se gana
 // nodo seleccionado para mover
	ALLEGRO_BITMAP* mapa;// imagen del fondo/mapa
	ALLEGRO_BITMAP* ficha;
	ALLEGRO_BITMAP* jugador; // imagen del jugador
	ALLEGRO_BITMAP* iaBitmap; // imagen de la ia
	ALLEGRO_BITMAP* libre; // imagen donde hay un espacio libre para mover
	std::vector <ALLEGRO_BITMAP*> elegir_orientacion;
	InputManager input;

	/*-----------mapa incio_lista----------*/

	bool boleana_para_pintar; // es verdadero cuando se quiere actualizar la pantalla
	ALLEGRO_FONT* fuente; // fuente que se utiliza en el menu
};

