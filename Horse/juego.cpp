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
				int mano = 20;
				int mouseX = evento.mouse.x;
				int mouseY = evento.mouse.y;
				if(mouseX > 20 && mouseX < 40 && mouseY > 20 && mouseY < 40)
				if (true) {
				

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
		menuFondo = al_load_bitmap("menu.bmp");
		break;
	case 1:
		tablero = Tablero();
		imprimirmuertos = al_load_font("Raphtalia DEMO.otf", 20, NULL);
		fuente = al_load_font("Raphtalia DEMO.otf", 66, NULL);
		mapa = al_load_bitmap("Tablero.bmp");
		jugador = al_load_bitmap("gallinaS.png");
		iaBitmap = al_load_bitmap("coyote.png");
		libre = al_load_bitmap("gallinaSa.png");
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
		al_draw_text(abut, al_map_rgb(128, 64, 0), 500, 65, ALLEGRO_ALIGN_CENTER, "El Coyote");
		// recorrer el menu
		for (auto texto : *menu) {
			// se pinta de diferente color si esta seleccionado 
			texto->pintar(fuente, 128, 64, 0, ALLEGRO_ALIGN_CENTER);
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
			texto->y = 290 + (al_get_text_width(fuente, texto->contenido.c_str()) + 85) * i;
			texto->x = 550;
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
