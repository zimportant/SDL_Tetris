#include "SceneInstruction.h"

using namespace std;

const SDL_Rect SceneInstruction::RECT_BUTTON_OK = {
    369, 442,
    165, 70
};

SceneInstruction::SceneInstruction() 
    :buttonOk(new DisplayObject(
        "assets/textures/button_ok.png",
        RECT_BUTTON_OK
    ))
{
    background = make_shared<DisplayObject>("assets/textures/scene_instruction.png", RECT_BACKGROUND);
}

SceneInstruction::~SceneInstruction() {

}

void SceneInstruction::start() {
	sceneType = nextSceneType = INSTRUCTION;
    view->renderDisplayObject(background);

	clearButton();
    setButtonDefault(background, nullptr);
	function<void ()> buttonOkCallback = bind(
		&SceneInstruction::onClickButtonOk,
		this
	);
	addButton(buttonOk, buttonOkCallback);
}

SceneType SceneInstruction::gameLoop(SDL_Event &event) {
    Scene::gameLoop(event);
    return nextSceneType;
}

void SceneInstruction::onClickButtonOk() {
    nextSceneType = BACK_TO_PREVIOUS;
}