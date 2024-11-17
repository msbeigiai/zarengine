#include "Game.h"
#include <iostream>

Game::Game() {
	std::cout << "Game constructor called\n";
}

Game::~Game(){
	std::cout << "Game destructor called\n";
}

void Game::Initialize(){
}

void Game::Run(){
	while (true) {
		ProcessInput();
		Update();
		Render();
	}
}

void Game::ProcessInput(){}

void Game::Update(){}

void Game::Render(){}

void Game::Destroy(){}