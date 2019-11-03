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
		if (input.isKeyPressed(evento, ALLEGRO_KEY_F)) {
			cambiarPantalla(0);
		}
		if (input.isKeyPressed(evento, ALLEGRO_KEY_R)) {
			cambiarPantalla(1);
		}
		
		if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (evento.mouse.button & 1)
			{
				int mano = 20;
				int mouseX = evento.mouse.x;
				int mouseY = evento.mouse.y;
				if(mouseX > 20 && mouseX < 40 && mouseY > 20 && mouseY < 40)
				if (select != NULL && !boleana_para_pintar) {
					select = NULL;
					boleana_para_pintar = true;
				}
			}
		}
		

	
		break;
	}
	case 2:
	{
		if (input.isKeyPressed(evento, ALLEGRO_KEY_F)) {
			cambiarPantalla(0);
		}
		break;
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
		pociciones = std::vector< std::vector<const char*> >(5);
		listaFichasTemporar = std::vector< std::vector<Ficha*> >(5);
		mapa = al_load_bitmap("Tablero.bmp");
		jugador = al_load_bitmap("gallinaS.png");
		iaBitmap = al_load_bitmap("coyote.png");
		libre = al_load_bitmap("gallinaSa.png");
		select = NULL;
		elturno = true;
		deaths = 0;
		comenzarContador = true;
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
		Ficha* aux = this->incio_lista, * aux2 = NULL;
		if (this->piensa == true) {
			al_rest(0.8);
			piensa = false;
		}
		// recorro los nodos y los dibujo 
		while (aux != NULL) {
			while (aux != NULL) {
				if (aux->ficha == 1) {
					al_draw_bitmap(jugador, aux->x, aux->y, ALLEGRO_ALIGN_CENTER);
				}
				else if (aux->ficha == 2) {
					al_draw_bitmap(iaBitmap, aux->x, aux->y, ALLEGRO_ALIGN_CENTER);
				}
				else if (select != NULL) {
					if (esAdyancente(select, aux))
						al_draw_bitmap(libre, aux->x, aux->y, ALLEGRO_ALIGN_CENTER);
				}
				aux2 = aux;
				aux = aux->derecha;
			}
			aux = aux2;
			if (aux->abajo == NULL)break;
			aux = aux->abajo;
			while (aux != NULL) {
				if (aux->ficha == 1) {
					al_draw_bitmap(jugador, aux->x, aux->y, ALLEGRO_ALIGN_CENTER);
				}
				else if (aux->ficha == 2) {
					al_draw_bitmap(iaBitmap, aux->x, aux->y, ALLEGRO_ALIGN_CENTER);
				}
				else if (select != NULL) {
					if (esAdyancente(select, aux))
						al_draw_bitmap(libre, aux->x, aux->y, ALLEGRO_ALIGN_CENTER);
				}
				aux2 = aux;
				aux = aux->izquierda;
			}
			aux = aux2;
			aux = aux->abajo;
		}
		if (deaths >= 3) {
			al_rest(0.5);
			al_draw_text(fuente, al_map_rgb(30, 90, 150), 350, 320, ALLEGRO_ALIGN_CENTER, "HAS PERDIDO");
			al_flip_display();
			al_rest(4);
			al_clear_to_color(al_map_rgb(0, 0, 0));
			cambiarPantalla(0);
			this->pintar(display);
		}
		break;
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
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				delete listaFichasTemporar[i][j];
			}
		}
		pociciones.clear();
		listaFichasTemporar.clear();

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
void Juego::CrearCamino(Ficha * a, Ficha * b, int dire) {
	switch (dire)
	{
	case 0:
		a->derecha = b;
		b->izquierda = a;
		break;
	case 1:
		a->derecha_abajo = b;
		b->izquierda_arriba = a;
		break;
	case 2:
		a->abajo = b;
		b->arriba = a;
		break;
	case 3:
		a->izquierda_abajo = b;
		b->derecha_arriba = a;
		break;
	case 4:
		a->izquierda = b;
		b->derecha = a;
		break;
	case 5:
		a->izquierda_arriba = b;
		b->derecha_abajo = a;
		break;
	case 6:
		a->arriba = b;
		b->abajo = a;
		break;
	case 7:
		a->derecha_arriba = b;
		b->izquierda_abajo = a;
		break;
	default:
		break;
	}
}

bool Juego::esAdyancente(Ficha * seleccionada, Ficha * b) {
	return (seleccionada->abajo == b || seleccionada->derecha == b || seleccionada->izquierda == b || seleccionada->arriba == b || seleccionada->derecha_abajo == b || seleccionada->izquierda_abajo == b || seleccionada->derecha_arriba == b || seleccionada->izquierda_arriba == b);
}

// mata 
void Juego::matar() {
	if (this->gato->derecha != NULL && mato == false) {
		if (this->gato->derecha->ficha == 1) {
			if (this->gato->derecha->derecha != NULL) {
				if (this->gato->derecha->derecha->ficha == 0) {
					this->gato->derecha->ficha = 0;
					this->gato->ficha = 0;
					this->gato->derecha->derecha->ficha = 2;
					this->gato = this->gato->derecha->derecha;
					this->elturno = true;
					this->mato = true;
				}
			}
		}
	}
	if (this->gato->derecha_abajo != NULL && mato == false) {
		if (this->gato->derecha_abajo->ficha == 1) {
			if (this->gato->derecha_abajo->derecha_abajo != NULL) {
				if (this->gato->derecha_abajo->derecha_abajo->ficha == 0) {
					this->gato->derecha_abajo->ficha = 0;
					this->gato->ficha = 0;
					this->gato->derecha_abajo->derecha_abajo->ficha = 2;
					this->gato = this->gato->derecha_abajo->derecha_abajo;
					this->elturno = true;
					this->mato = true;
				}
			}
		}
	}
	if (this->gato->abajo != NULL && mato == false) {
		if (this->gato->abajo->ficha == 1) {
			if (this->gato->abajo->abajo != NULL) {
				if (this->gato->abajo->abajo->ficha == 0) {
					this->gato->abajo->ficha = 0;
					this->gato->ficha = 0;
					this->gato->abajo->abajo->ficha = 2;
					this->gato = this->gato->abajo->abajo;
					this->elturno = true;
					this->mato = true;
				}
			}
		}
	}
	if (this->gato->izquierda_abajo != NULL && mato == false) {
		if (this->gato->izquierda_abajo->ficha == 1) {
			if (this->gato->izquierda_abajo->izquierda_abajo != NULL) {
				if (this->gato->izquierda_abajo->izquierda_abajo->ficha == 0) {
					this->gato->izquierda_abajo->ficha = 0;
					this->gato->ficha = 0;
					this->gato->izquierda_abajo->izquierda_abajo->ficha = 2;
					this->gato = this->gato->izquierda_abajo->izquierda_abajo;
					this->elturno = true;
					this->mato = true;
				}
			}
		}
	}
	if (this->gato->izquierda != NULL && mato == false) {
		if (this->gato->izquierda->ficha == 1) {
			if (this->gato->izquierda->izquierda != NULL) {
				if (this->gato->izquierda->izquierda->ficha == 0) {
					this->gato->izquierda->ficha = 0;
					this->gato->ficha = 0;
					this->gato->izquierda->izquierda->ficha = 2;
					this->gato = this->gato->izquierda->izquierda;
					this->elturno = true;
					this->mato = true;
				}
			}
		}
	}
	if (this->gato->izquierda_arriba != NULL && mato == false) {
		if (this->gato->izquierda_arriba->ficha == 1) {
			if (this->gato->izquierda_arriba->izquierda_arriba != NULL) {
				if (this->gato->izquierda_arriba->izquierda_arriba->ficha == 0) {
					this->gato->izquierda_arriba->ficha = 0;
					this->gato->ficha = 0;
					this->gato->izquierda_arriba->izquierda_arriba->ficha = 2;
					this->gato = this->gato->izquierda_arriba->izquierda_arriba;
					this->elturno = true;
					this->mato = true;
				}
			}
		}
	}
	if (this->gato->arriba != NULL && mato == false) {
		if (this->gato->arriba->ficha == 1) {
			if (this->gato->arriba->arriba != NULL) {
				if (this->gato->arriba->arriba->ficha == 0) {
					this->gato->arriba->ficha = 0;
					this->gato->ficha = 0;
					this->gato->arriba->arriba->ficha = 2;
					this->gato = this->gato->arriba->arriba;
					this->elturno = true;
					this->mato = true;
				}
			}
		}
	}
	if (this->gato->derecha_arriba != NULL && mato == false) {
		if (this->gato->derecha_arriba->ficha == 1) {
			if (this->gato->derecha_arriba->derecha_arriba != NULL) {
				if (this->gato->derecha_arriba->derecha_arriba->ficha == 0) {
					this->gato->derecha_arriba->ficha = 0;
					this->gato->ficha = 0;
					this->gato->derecha_arriba->derecha_arriba->ficha = 2;
					this->gato = this->gato->derecha_arriba->derecha_arriba;
					this->elturno = true;
					this->mato = true;
				}
			}
		}
	}
	if (mato) {
		deaths++;
	}
}
