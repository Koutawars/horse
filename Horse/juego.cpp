#include "pch.h"
#include "Juego.h"
Juego::Juego() {}
Juego::~Juego() {}

// recuperar el singleton
Juego& Juego::GetInstance()
{
	static Juego instance;
	return instance;
}
//80-45 principio del mapa (tamaño prom ficha 55x55)
void Juego::actualizar(ALLEGRO_EVENT evento, bool* done) {
	switch (pantalla) {
	case 0: // Menu
	{
		if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (evento.mouse.button & 1)
			{
				// evento.mouse.x evento.mouse.y evento del mouse
				int mousey = evento.mouse.y;
				int mousex = evento.mouse.x;
				int i = 0;
				for (auto texto : *menu) {
					if (mousey >= texto->y - 85 && mousey <= texto->y + al_get_text_width(fuente, texto->contenido.c_str())) {
						switch (i) {
						case 0:
							this->cambiarPantalla(1);
							break;
						case 1:
							*done = true;
							break;
						}
					}

					i++;
				}
			}
		}
		break;
	}
	case 1:
	{

		
		if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (evento.mouse.button & 1)
			{
				int tamano = 55;
				int mouseX = evento.mouse.x;
				int mouseY = evento.mouse.y;
				int i, j;
				if (mouseX > 80 && mouseX < 520 && mouseY > 45 && mouseY < 480) {
					mouseX -= 80;
					mouseY -= 45;
					j = mouseX / 55;
					i = mouseY / 55;
					tablero.mover_Ficha(i, j);
					printf("i = [%d], j = [%d]", i, j);
					boleana_para_pintar = true;


				}
				
			}
		}
		

	
		break;
	}
	case 2:
	{
	
	}
	case 3:
	{
		if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (evento.mouse.button & 1)
			{
				int mouseX = evento.mouse.x;
				int mouseY = evento.mouse.y;
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 2; j++) {
						if (mouseX > 89 + (332 * i) && mouseX < 89 + (332 * i) + 153 && mouseY > 88 + (216 * j) && mouseY < 88 + (216 * j) + 153) {
							orientacion = j + i * 2;
							cambiarPantalla(1);
						}
					}
				}
			}
		}
		break;
	}
	}
}

void Juego::inicializar() {
	comenzarContador = false;
	boleana_para_pintar = true;
	contador = 0;
	switch (pantalla) {
	case 0:
		this->menu = new std::vector<Mensaje*>();
		fuente = al_load_font("Raphtalia DEMO.otf", 36, NULL);
		abut = al_load_font("Raphtalia DEMO.otf", 95, NULL);
		menuFondo = al_load_bitmap("menu.jpg");
		break;
	case 1:
		tablero = Tablero();
		imprimirmuertos = al_load_font("Raphtalia DEMO.otf", 20, NULL);
		fuente = al_load_font("Raphtalia DEMO.otf", 75, NULL);
		mapa = al_load_bitmap("Tablero.jpg");
		ficha = al_load_bitmap("ficha.jpg");
		break;

	case 2:
		fuente = al_load_font("SugarpunchDEMO.otf", 30, NULL);
		break;

	}
}

void Juego::pintar(ALLEGRO_DISPLAY * display) {
	switch (pantalla) {
	case 0: {
		al_draw_bitmap(menuFondo, 0, 0, NULL);
		int i = 0;
		al_draw_text(abut, al_map_rgb(0, 0, 0), 260, 45, ALLEGRO_ALIGN_CENTER, "Ajedrez");
		// recorrer el menu
		for (auto texto : *menu) {
			// se pinta de diferente color si esta seleccionado 
			texto->pintar(fuente, 0, 0, 0, ALLEGRO_ALIGN_CENTER);
			i++;
		}
		break;
	}
	case 1: {
		// dibujo el fondo
		al_draw_bitmap(mapa, 0, 0, NULL);
		if (this->piensa == true) {
			al_rest(0.8);
			piensa = false;
		}

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if( tablero.matrix[i][j] == 1)
					al_draw_bitmap(ficha, 80+(j*55)+55/22, 45 + (i * 55) + 55 / 22, NULL);
			}
		}
		// recorro los nodos y los dibujo 


	}
	}

}

void Juego::cargarcontenido() {
	switch (pantalla) {
	case 0: {
		// creando las opciones del menu
		menu->push_back(new Mensaje("Iniciar"));
		menu->push_back(new Mensaje("Salir"));
		int i = 0;
		// colocando la posición de las opciones de menu
		for (auto texto : *menu) {
			texto->y = 250 + (al_get_text_width(fuente, texto->contenido.c_str()) + 65) * i;
			texto->x = 450;
			i++;
		}
		break;
	}
	case 1:
	{
		
		tablero.mover_Ficha(0, 0);
			
		break;
	}
	}
}

//quitar el contenido
void Juego::deleteContenido() {
	switch (pantalla) {
	case 0:
		menu->clear();
		free(menu);
		al_destroy_font(fuente);
		al_destroy_bitmap(menuFondo);
		break;
	case 1:
		al_destroy_bitmap(mapa);
		al_destroy_bitmap(ficha);
		al_destroy_bitmap(jugador);
		al_destroy_bitmap(iaBitmap);
		al_destroy_bitmap(libre);
		al_destroy_font(fuente);
		
		break;
	case 2:
		al_destroy_font(fuente);
		break;
	case 3: {
		for (int i = 0; i < elegir_orientacion.size(); i++) al_destroy_bitmap(elegir_orientacion[i]);
		elegir_orientacion.clear();
		break;
	}
	}
}

// función para cambiar pantalla
void Juego::cambiarPantalla(int pantalla) {
	this->deleteContenido();
	this->pantalla = pantalla;
	this->inicializar();
	this->cargarcontenido();
	boleana_para_pintar = true;
}

// función para crear un camino de doble vía

// mata 
