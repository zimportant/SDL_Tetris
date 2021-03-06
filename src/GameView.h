#pragma once
#include <memory>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <memory>
#include <exception>
#include <vector>
#include <mutex>
#include <map>
#include <string>
#include <algorithm>
#include "Exception.h"
#include "Constants.h"
#include "PointerDefinition.h"
#include "Board.h"
using namespace std;

struct DisplayObject {
    string path;
    SDL_Rect rect;
    DisplayObject(string _path, const SDL_Rect &_rect): path(_path), rect(_rect) {}
};

struct RectObject {
	SDL_Rect rect;
	SDL_Color color;
	RectObject(const SDL_Rect &_rect, const SDL_Color &_color): rect(_rect), color(_color) {}
};

struct FontObject {
	string text; 
	int fontSize; 
	SDL_Rect rect; 
	bool isBold;
	FontObject(string _text, const SDL_Rect &_rect): text(_text), fontSize(24), rect(_rect), isBold(false) {} 
	FontObject(string _text, int _fontSize, const SDL_Rect &_rect): 
		text(_text), fontSize(_fontSize), rect(_rect), isBold(false) {} 
	FontObject(string _text, int _fontSize, const SDL_Rect &_rect, bool _isBold): 
		text(_text), fontSize(_fontSize), rect(_rect), isBold(_isBold) {} 
};

struct TileObject {
	TileType type;
	SDL_Rect rect;
	TileObject(TileType _type, const SDL_Rect &_rect): type(_type), rect(_rect) {}
};

struct FullTileObject {
	TileType type;
	SDL_Rect rect;
	FullTileObject(TileType _type, const SDL_Rect &_rect): type(_type), rect(_rect) {}
};

class GameView {
private:
    static shared_ptr<GameView> instance;

	shared_ptr<SDL_Window> window;
	shared_ptr<SDL_Surface> windowSurface;
	shared_ptr<SDL_Renderer> renderer;
	map<TileType, shared_ptr<SDL_Texture> > tileTextures;
	map<TileType, shared_ptr<SDL_Texture> > fullTileTextures;

	SDL_Color colorWhite;

	void init();
	void initWindow();
	void initRenderer();
	void initImage();
	void initTileTexture();
	void initFullTileTexture();
	void initTextureText();

	shared_ptr<SDL_Texture> createTextureText(const string &text, int fontSize, SDL_Rect *rect, bool isBold = false);
	shared_ptr<SDL_Texture> createTexture(const string &path);
	shared_ptr<SDL_Surface> createSurface(const string &path);
	void copyTileToRenderer(Tile *tile);
	void copyFullTileToRenderer(Tile *tile, const SDL_Rect &rect);
public:
    static shared_ptr<GameView> getInstance();
    GameView();
    virtual ~GameView();

	void startSDL();

	void renderDisplayObject(shared_ptr<DisplayObject> displayObject);
	void renderDisplayObject(vector<shared_ptr<DisplayObject>> displayObjects);
	void renderFontObject(shared_ptr<FontObject> fontObject, int align = 0);
	void renderFontObject(vector<shared_ptr<FontObject>> fontObjects, int align = 0);
	void renderRectObject(shared_ptr<RectObject> rectObject);
	void renderRectObject(vector<shared_ptr<RectObject>> rectObjects);
	void renderTileObject(shared_ptr<TileObject> tileObject);
	void renderTileObject(vector<shared_ptr<TileObject>> tileObjects);
	void renderFullTileObject(shared_ptr<FullTileObject> fullTileObject);
	void renderFullTileObject(vector<shared_ptr<FullTileObject>> fullTileObjects);

	shared_ptr<SDL_Window> getWindow();
};