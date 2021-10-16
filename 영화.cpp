#include <bangtal>
#include <iostream>
using namespace bangtal;

ScenePtr scene2;
ObjectPtr box_board[16];
ObjectPtr button;
TimerPtr timer;
int count = 16;



int main(){
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);


	scene2 = Scene::create("영화", "images/오징어게임.png");

	//가림박스 생성-숨김
	for (int i = 0; i < 16; i++) {
		box_board[i] = Object::create("images/box.png", scene2, 265 + 189 * (i % 4), 522 - 123 * (i / 4));
		box_board[i]->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
			piece->hide();
			count--;

			return true;
			});
	}


	//정답입력
	button = Object::create("images/정답.png", scene2, 500, 60);
	button->setOnMouseCallback([&](auto object, auto x, auto y, auto action)->bool {
		showKeypad("squidgame", button);
		return true;
		});

	button->setOnKeypadCallback([&](ObjectPtr object)->bool {
		button->hide();
		showMessage("정답은 squidgame (오징어게임)입니다.");
		return true;
		});


	//타이머
	TimerPtr timer = Timer::create(40.f);
	showTimer(timer);
	timer->setOnTimerCallback([&](TimerPtr)->bool {
		button->hide();
		showMessage("시간초과! 미션 실패");
		//실패 화면으로 이동하기
		return true;
		});


	auto scene = Scene::create("메인화면", "images/배경1.png");
	auto startB = Object::create("images/시작.png", scene, 450, 150);
	startB->setScale(0.5f);
	startB->setOnMouseCallback([&](auto object, auto x, auto y, auto action)->bool {
		scene2->enter();
		timer->start();
		return true;
		});



	startGame(scene);
}