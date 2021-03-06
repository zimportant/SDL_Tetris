#pragma once
#include "GameView.h"
#include "GameController.h"
#include "GameSound.h"
#include <map>
#include <memory>
#include <functional>

using namespace std;

struct Score {
    shared_ptr<FontObject> user, score;

    Score(): user(), score() {}
    Score(shared_ptr<FontObject> _user, shared_ptr<FontObject> _score): user(_user), score(_score) {}
};

enum SceneType {
    BACK_TO_PREVIOUS = -1,
	START = 0,
	PLAY = 1,
	PAUSE = 2,
	INSTRUCTION = 3,
    BEFORE_ENDGAME,
    ENDGAME = 5,
};

struct Button {
    shared_ptr<DisplayObject> displayObject;
    function<void ()> callback;

    Button(): displayObject(), callback() {}

    Button(shared_ptr<DisplayObject> _displayObject, function<void (void)> _callback)
        :displayObject(_displayObject),
        callback(_callback)
    {
    }
};

class Scene {
private:
    vector<bool> togglingButtonStates;
    bool togglingButtonDefaultState;
    vector<Button> buttons;
    Button buttonDefault;

	void handleMouse(function<void (Button button)> callbackRender, function<void (Button button)> callbackClick);
	bool isMouseOverRect(const SDL_Rect &rect);
public:
    static shared_ptr<GameView> view;
    static shared_ptr<GameController> controller;
	static shared_ptr<GameSound> sound;
	static const SDL_Rect RECT_BACKGROUND;
    shared_ptr<DisplayObject> background;
    map<string, shared_ptr<DisplayObject> > displayObjects;
    SceneType sceneType, nextSceneType;

    Scene();
    virtual ~Scene();

    static shared_ptr<Scene> createSceneFromSceneType(SceneType sceneType);

    void addButton(shared_ptr<DisplayObject> buttonView, function<void ()> onMouseClick);
    void setButtonDefault(shared_ptr<DisplayObject> buttonView, function<void ()> onMouseClick);
    void clearButton();

    virtual void start();
    virtual void redraw();
    virtual SceneType gameLoop(SDL_Event &event);

    SceneType getType();
};