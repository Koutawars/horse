// Caballo.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "pch.h"
#include "Juego.h"
#include <iostream>

#include <allegro5/allegro.h>

#include <allegro5/keyboard.h>
#include <allegro5/allegro_image.h>


int main(int argc, char** argv) {
	ALLEGRO_DISPLAY* display = NULL;
	srand(time(NULL));
	if (!al_init()) {
		std::cout << "failed to inicializar allegro!\n";
		return -1;
	}

	display = al_create_display(700, 700);//640, 480
	if (!display) {
		std::cout << "failed to create display!\n";
		return -1;
	}

	al_install_keyboard();
	al_install_mouse();

	al_init_image_addon();
	al_init_primitives_addon();

	al_init_font_addon();
	al_init_ttf_addon();

	Juego::GetInstance().inicializar();
	Juego::GetInstance().cargarcontenido();

	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	ALLEGRO_TIMER* timer = al_create_timer(1.0f);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	bool done = false;
	al_start_timer(timer);


	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		Juego::GetInstance().actualizar(ev, &done);
		if (Juego::GetInstance().boleana_para_pintar) {
			Juego::GetInstance().pintar(display);
			Juego::GetInstance().boleana_para_pintar = false;
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (Juego::GetInstance().comenzarContador) {
				Juego::GetInstance().contador++;
			}
		}
	}

	Juego::GetInstance().deleteContenido();
	al_destroy_display(display);

	return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln