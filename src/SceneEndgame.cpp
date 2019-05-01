#include "SceneEndgame.h"
#include "SceneBeforeEndgame.h"

using namespace std;

const SDL_Rect SceneEndgame::RECT_BUTTON_OK = {
	368, 460,
	165, 70
};
const SDL_Rect SceneEndgame::RECT_RANKING_TOP_NAME[3] = {
	{180, 185, 275, 54},
	{180, 239, 275, 54},
	{180, 293, 275, 54}
};
const SDL_Rect SceneEndgame::RECT_RANKING_USER_NAME = {
	181, 371,
	275, 54
};
const SDL_Rect SceneEndgame::RECT_RANKING_TOP_SCORE[3] = {
	{717, 185, 275, 54},
	{717, 239, 275, 54},
	{717, 293, 275, 54},
};
const SDL_Rect SceneEndgame::RECT_RANKING_USER_SCORE = {
	717, 371,
	275, 54
};

shared_ptr<GameController> SceneEndgame::controller = GameController::getInstance();

SceneEndgame::SceneEndgame()
	:buttonOk(new DisplayObject(
        "assets/textures/button_ok_endgame.png", 
        RECT_BUTTON_OK
    )),
	rankings(),
	player(make_shared<Score>(
		make_shared<FontObject>(" ", 36, RECT_RANKING_USER_NAME, true),
		make_shared<FontObject>("123", 36, RECT_RANKING_USER_SCORE, true)
	))
{
    background = make_shared<DisplayObject>("assets/textures/scene_endgame.png", RECT_BACKGROUND);
	for (size_t i = 0; i < 3u; ++i) {
		rankings.push_back(make_shared<Score>(make_shared<FontObject>(
			"user " + to_string(i),
			36,
			RECT_RANKING_TOP_NAME[i],
			true
		), make_shared<FontObject>(
			to_string(i * 1000 + 314),
			36,
			RECT_RANKING_TOP_SCORE[i],
			true
		)));
	}
	player->user->text = SceneBeforeEndgame::getPlayerName();
}

SceneEndgame::~SceneEndgame() {

}

void SceneEndgame::start() {
	sceneType = nextSceneType = BEFORE_ENDGAME;
	redraw();

	clearButton();
	function<void ()> buttonOkCallback = bind(
		&SceneEndgame::onClickButtonOk,
		this
	);
	addButton(buttonOk, buttonOkCallback);
}

void SceneEndgame::redraw() {
	view->renderDisplayObject(background);
	for (auto score : rankings) {
		view->renderFontObject(score->user);
		view->renderFontObject(score->score, 2);
	}
	view->renderFontObject(player->user);
	view->renderFontObject(player->score, 2);
}

SceneType SceneEndgame::gameLoop(SDL_Event &event) {
	Scene::gameLoop(event);
	return nextSceneType;
}

void SceneEndgame::onClickButtonOk() {
	nextSceneType = START;
}