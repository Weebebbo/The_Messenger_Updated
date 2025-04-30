// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2024 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "SpriteFactory.h"
#include "SDL_image.h"
#include "graphicsUtils.h"
#include "sdlUtils.h"
#include "Window.h"
#include "AnimatedSprite.h"
#include "TiledSprite.h"
#include "FilledSprite.h"
#include "Game.h"
#include <iostream>

using namespace agp;

SpriteFactory::SpriteFactory()
{
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return;
	}

	SDL_Renderer* renderer = Game::instance()->window()->renderer();
	// OLD Super Mario hud 
	_spriteSheets["hud"] = loadTexture(renderer, std::string(SDL_GetBasePath()) + "sprites/hud.png", { 147, 187, 236 });

	_spriteSheets["ninja"] = loadTextureAutoDetect(renderer, std::string(SDL_GetBasePath()) + "sprites/ninja.png", _autoTiles["ninja"], { 237, 28, 36 }, { 26, 188, 156 }, 5, false, true);
	_spriteSheets["effects"] = loadTextureAutoDetect(renderer, std::string(SDL_GetBasePath()) + "sprites/ninja_effects.png", _autoTiles["effects"], { 237, 28, 36 }, { 26, 188, 156 }, 5, false, true);
	_spriteSheets["enemies2"] = loadTextureAutoDetect(renderer, std::string(SDL_GetBasePath()) + "sprites/nemici_del_messaggero.png", _autoTiles["enemies2"], { 237, 28, 36 }, { 26, 188, 156 }, 5, false, true, true);

	_spriteSheets["hud1"] = loadTextureAutoDetect(renderer, std::string(SDL_GetBasePath()) + "sprites/hud1.png", _autoTiles["hud1"], { 237, 28, 36 }, { 26, 188, 156 }, 5, false, true);
	_spriteSheets["items"] = loadTextureAutoDetect(renderer, std::string(SDL_GetBasePath()) + "sprites/items.png", _autoTiles["items"], { 237, 28, 36 }, { 26, 188, 156 }, 5, false, true, true);
	_spriteSheets["candlestick_on"] = loadTextureAutoDetect(renderer, std::string(SDL_GetBasePath()) + "sprites/candlestick_on.png", _autoTiles["candlestick_on"], { 69, 67, 255 }, { 255, 13, 13 });
	_spriteSheets["candlestick_off"] = loadTextureAutoDetect(renderer, std::string(SDL_GetBasePath()) + "sprites/candlestick_off.png", _autoTiles["candlestick_off"], { 69, 67, 255 }, { 255, 1, 1 });
	
	//Aggiunta mappe
	_spriteSheets["room1"] = loadTexture(renderer, std::string(SDL_GetBasePath()) + "levels/room1.png");
	_spriteSheets["room2"] = loadTexture(renderer, std::string(SDL_GetBasePath()) + "levels/room2.png");
	_spriteSheets["room3"] = loadTexture(renderer, std::string(SDL_GetBasePath()) + "levels/room3.png");
	_spriteSheets["room4"] = loadTexture(renderer, std::string(SDL_GetBasePath()) + "levels/room4.png");
	_spriteSheets["room5"] = loadTexture(renderer, std::string(SDL_GetBasePath()) + "levels/room5.png");
	_spriteSheets["room6"] = loadTexture(renderer, std::string(SDL_GetBasePath()) + "levels/room6.png");
	_spriteSheets["room9"] = loadTexture(renderer, std::string(SDL_GetBasePath()) + "levels/room9.png");
	_spriteSheets["room10"] = loadTexture(renderer, std::string(SDL_GetBasePath()) + "levels/room10.png");
	_spriteSheets["room11"] = loadTexture(renderer, std::string(SDL_GetBasePath()) + "levels/room11.png");
	_spriteSheets["room12"] = loadTexture(renderer, std::string(SDL_GetBasePath()) + "levels/room12.png");

}

// anchors
static RectI hud_letter(519, 254, 8, 8);
static RectI hud_number(519, 263, 8, 8);
static RectI hud_letter_disabled(519, 366, 8, 8);
static RectI hud_number_disabled(519, 375, 8, 8);
static RectI hud_coin(519, 289, 8, 8);

Sprite* SpriteFactory::get(const std::string& id)
{
	std::vector< RectI> rects;

	// single-frame sprites
	// MAPS
	if (id == "room1")
		return new FilledSprite(_spriteSheets["room1"]);
	else if (id == "room2")
		return new FilledSprite(_spriteSheets["room2"]);
	else if (id == "room3")
		return new FilledSprite(_spriteSheets["room3"]);
	else if (id == "room4")
		return new FilledSprite(_spriteSheets["room4"]);
	else if (id == "room5")
		return new FilledSprite(_spriteSheets["room5"]);
	else if (id == "room6")
		return new FilledSprite(_spriteSheets["room6"]);
	else if (id == "room9")
		return new FilledSprite(_spriteSheets["room9"]);
	else if (id == "room10")
		return new FilledSprite(_spriteSheets["room10"]);
	else if (id == "room11")
		return new FilledSprite(_spriteSheets["room11"]);
	else if (id == "room12")
		return new FilledSprite(_spriteSheets["room12"]);

	// OLD Super Mario sprites
	else if (id == "welcome")
		return new Sprite(_spriteSheets["hud"], RectI(1, 2 + 16 * 2, 16 * 16, 13 * 16));
	else if (id == "gameover")
		return new Sprite(_spriteSheets["hud"], RectI(260, 253, 16 * 16, 15 * 16));

	// NINJA Sprites
	else if (id == "jump_rise")
		return new Sprite(_spriteSheets["ninja"], _autoTiles["ninja"][1][0]);
	else if (id == "jump_fall")
		return new Sprite(_spriteSheets["ninja"], _autoTiles["ninja"][1][1]);
	else if (id == "ninja_crouch")
		return new Sprite(_spriteSheets["ninja"], _autoTiles["ninja"][0][2]);
	else if (id == "bat_stand")
		return new Sprite(_spriteSheets["enemies2"], _autoTiles["enemies2"][0][4]);
	else if (id == "skelouton_stand")
		return new Sprite(_spriteSheets["enemies2"], _autoTiles["enemies2"][10][0]);
	else if (id == "money_hud")
		return new Sprite(_spriteSheets["hud1"], _autoTiles["hud1"][0][5]);
	else if (id == "ninja_stand")
		return new Sprite(_spriteSheets["ninja"], _autoTiles["ninja"][0][0]);
	else if (id == "ninja_stationaryClimb")
		return new Sprite(_spriteSheets["ninja"], _autoTiles["ninja"][12][3]);
	else if (id == "ninja_take_damage")
		return new Sprite(_spriteSheets["ninja"], _autoTiles["ninja"][9][2]);

	//roba dell'HUD
	else if (id == "hud_gem")
		return new Sprite(_spriteSheets["hud1"], _autoTiles["hud1"][0][5]);
	else if (id == "hud_health_bar")
		return new Sprite(_spriteSheets["hud1"], _autoTiles["hud1"][0][1]);
	else if (id == "hud_health_bar2")
		return new Sprite(_spriteSheets["hud1"], _autoTiles["hud1"][0][2]);

	// animated sprites
	else if (id == "mario_walk")
		return new AnimatedSprite(_spriteSheets["mario"], { _autoTiles["mario"][0].begin() + 2, _autoTiles["mario"][0].begin() + 5 }, 10);
	else if (id == "mario_run")
		return new AnimatedSprite(_spriteSheets["mario"], { _autoTiles["mario"][0].begin() + 2, _autoTiles["mario"][0].begin() + 5 }, 20);
	else if (id == "box")
		return new AnimatedSprite(_spriteSheets["tiles"], { _autoTiles["tiles"][3].begin(), _autoTiles["tiles"][3].begin() + 3 }, 5, { 0, 1, 2, 1, 0 });
	else if (id == "hud_coin")
	{
		rects.push_back(moveBy(hud_coin, 0, 0));
		rects.push_back(moveBy(hud_coin, 1, 0, 8, 8));
		rects.push_back(moveBy(hud_coin, 2, 0, 8, 8));
		rects.push_back(moveBy(hud_coin, 1, 0, 8, 8));
		rects.push_back(moveBy(hud_coin, 0, 0));
		rects.push_back(moveBy(hud_coin, 0, 0));
		return new AnimatedSprite(_spriteSheets["hud"], rects, 6);
	}
	else if (id == "jump_ball")
		return new AnimatedSprite(_spriteSheets["ninja"], { _autoTiles["ninja"][2][0], _autoTiles["ninja"][2][3] }, 10);
	else if (id == "ninja_walk")
		return new AnimatedSprite(_spriteSheets["ninja"], { _autoTiles["ninja"][3][0], _autoTiles["ninja"][3][3] }, 10);
	else if (id == "ninja_climbMovement")
		return new AnimatedSprite(_spriteSheets["ninja"], { _autoTiles["ninja"][12].begin(), _autoTiles["ninja"][12].begin() + 3 }, 8);

	//Animazioni degli attacchi
	else if (id == "running_attack")
		return new AnimatedSprite(_spriteSheets["ninja"], { _autoTiles["ninja"][4].begin(), _autoTiles["ninja"][4].begin() + 4 }, 12);
	else if (id == "standing_attack1")
		return new AnimatedSprite(_spriteSheets["ninja"], { _autoTiles["ninja"][6].begin(), _autoTiles["ninja"][6].begin() + 4 }, 12);
	else if (id == "standing_attack2")
		return new AnimatedSprite(_spriteSheets["ninja"], { _autoTiles["ninja"][7].begin(), _autoTiles["ninja"][7].begin() + 4 }, 12);
	else if (id == "jump_attack")
		return new AnimatedSprite(_spriteSheets["ninja"], { _autoTiles["ninja"][5].begin(), _autoTiles["ninja"][5].begin() + 4 }, 12);
	else if (id == "crouch_attack")
		return new AnimatedSprite(_spriteSheets["ninja"], { _autoTiles["ninja"][11].begin(), _autoTiles["ninja"][11].begin() + 4 }, 12);
	
	//Animazioni dei nemici
	else if (id == "ranged_kappa_stand")
		return new AnimatedSprite(_spriteSheets["enemies2"], { _autoTiles["enemies2"][6].begin(), _autoTiles["enemies2"][6].begin() + 4 }, 6);
	else if (id == "ranged_kappa_fireball")
		return new AnimatedSprite(_spriteSheets["enemies2"], { _autoTiles["enemies2"][7].begin(), _autoTiles["enemies2"][7].begin() + 4 }, 8);
	else if (id == "fireball")
		return new AnimatedSprite(_spriteSheets["enemies2"], { _autoTiles["enemies2"][8].begin(), _autoTiles["enemies2"][8].begin() + 4 }, 6);
	else if (id == "bat_flying")
		return new AnimatedSprite(_spriteSheets["enemies2"], { _autoTiles["enemies2"][0].begin(), _autoTiles["enemies2"][0].begin() + 4 }, 10);
	else if (id == "green_kappa_walk")
		return new AnimatedSprite(_spriteSheets["enemies2"], { _autoTiles["enemies2"][5].begin(), _autoTiles["enemies2"][5].begin() + 4 }, 6);
	else if (id == "skelouton_walk")
		return new AnimatedSprite(_spriteSheets["enemies2"], { _autoTiles["enemies2"][9].begin(), _autoTiles["enemies2"][9].begin() + 4 }, 6);
	else if (id == "skelouton_run")
		return new AnimatedSprite(_spriteSheets["enemies2"], { _autoTiles["enemies2"][9].begin(), _autoTiles["enemies2"][9].begin() + 4 }, 12);
	else if (id == "skelouton_walk_on")
		return new AnimatedSprite(_spriteSheets["enemies2"], { _autoTiles["enemies2"][10].begin(), _autoTiles["enemies2"][10].begin() + 4 }, 6);

	//Animazioni items
	else if (id == "emerald")
		return new AnimatedSprite(_spriteSheets["items"], { _autoTiles["items"][10].begin(), _autoTiles["items"][10].begin() + 5 }, 6);
	else if (id == "crystal")
		return new AnimatedSprite(_spriteSheets["items"], { _autoTiles["items"][0].begin(), _autoTiles["items"][0].begin() + 4 }, 5);
	else if (id == "candlestick_off")
		return new Sprite(_spriteSheets["candlestick_off"], _autoTiles["candlestick_off"][0][0]);
	else if (id == "candlestick_on")
		return new AnimatedSprite(_spriteSheets["candlestick_on"], { _autoTiles["candlestick_on"][0].begin(), _autoTiles["candlestick_on"][0].begin() + 4}, 6);
	else if (id == "smash")
		return new AnimatedSprite(_spriteSheets["items"], { _autoTiles["items"][13].begin(), _autoTiles["items"][13].begin() + 4 }, 6);

	//Animazione danno nemici (prova)
	else if (id == "hit")
		return new AnimatedSprite(_spriteSheets["enemies2"], { _autoTiles["enemies2"][11].begin(), _autoTiles["enemies2"][11].begin() + 4 }, 6);

	else
	{
		std::cerr << "Cannot find sprite \"" << id << "\"\n";
		return nullptr;
	}
}

Sprite* SpriteFactory::getText(std::string text, const Vec2Df& size, int fillN, char fillChar, bool enabled)
{
	std::vector< RectI> tiles;

	if (fillN)
		while (text.size() != fillN)
			text = fillChar + text;

	RectI& number_anchor = enabled ? hud_number : hud_number_disabled;
	RectI& letter_anchor = enabled ? hud_letter : hud_letter_disabled;

	for (auto& c : text)
	{
		if(isdigit(c))
			tiles.push_back(moveBy(number_anchor, c - '0', 0, 8, 8));
		else if (isalpha(c))
			tiles.push_back(moveBy(letter_anchor, toupper(c) - 'A', 0, 8, 8));
		else if (c == '-')
			tiles.push_back(moveBy(number_anchor, 10, 0, 8, 8));
		else if (c == '*')
			tiles.push_back(moveBy(number_anchor, 11, 0, 8, 8));
		else if (c == '!')
			tiles.push_back(moveBy(number_anchor, 12, 0, 8, 8));
		else if (c == '©')
			tiles.push_back(moveBy(number_anchor, 13, 0, 8, 8));
		else if (c == '.')
			tiles.push_back(moveBy(number_anchor, 14, 0, 8, 8));
		else
			tiles.push_back(moveBy(hud_letter, 0, -5, 8, 8));	// empty space
	}

	return new TiledSprite(_spriteSheets["hud"], tiles, size);
}