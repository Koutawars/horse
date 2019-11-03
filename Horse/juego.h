#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "tablero.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "mensaje.h"
#include <stdlib.h>
#include <time.h>
class Juego
{
private:
	Juego();
	~Juego();
public:

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
	Tablero tablero;
	/*------------Pantalla-----------*/
	void cambiarPantalla(int pantalla); // funci�n para cambiar pantalla
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
	Ficha* gato; // nodo que apunta donde esta el gato
	Ficha* incio_lista; // nodo padre del mapa
	Ficha* select; // nodo seleccionado para mover
	ALLEGRO_BITMAP* mapa; // imagen del fondo/mapa
	ALLEGRO_BITMAP* jugador; // imagen del jugador
	ALLEGRO_BITMAP* iaBitmap; // imagen de la ia
	ALLEGRO_BITMAP* libre; // imagen donde hay un espacio libre para mover
	void CrearCamino(Ficha* a, Ficha* b, int dire); // funci�n para crear caminos de un nodo a otro
	bool esAdyancente(Ficha* select, Ficha* b); // funci�n para saber si un nodo es adyacente de otro o no
	std::vector <ALLEGRO_BITMAP*> elegir_orientacion;
	// matrices temporales del mapa
	std::vector< std::vector<const char*> > pociciones;
	std::vector< std::vector<Ficha*> > listaFichasTemporar;
	InputManager input;// input manager para las reclas
	void matar(); //esto mata chabon

	/*-----------mapa incio_lista----------*/

	bool boleana_para_pintar; // es verdadero cuando se quiere actualizar la pantalla
	ALLEGRO_FONT* fuente; // fuente que se utiliza en el menu

};
