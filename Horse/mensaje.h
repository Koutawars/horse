#pragma once
#include <string>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
class Mensaje
{
public:
	int x, y;
	std::string contenido;
	Mensaje(std::string contenido);
	Mensaje();
	void pintar(ALLEGRO_FONT* fuente, int r, int g, int b, int flags);
	~Mensaje();
};

