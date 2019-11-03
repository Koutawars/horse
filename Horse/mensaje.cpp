#include "pch.h"
#include "Mensaje.h"

Mensaje::Mensaje() {}

Mensaje::Mensaje(std::string contenido)
{
	this->contenido = contenido;
	this->x = 0;
	this->y = 0;
}




void Mensaje::pintar(ALLEGRO_FONT* fuente, int r, int g, int b, int flags) {
	al_draw_text(fuente, al_map_rgb(r, g, b), this->x, this->y, flags, this->contenido.c_str());
}


Mensaje::~Mensaje()
{
}

