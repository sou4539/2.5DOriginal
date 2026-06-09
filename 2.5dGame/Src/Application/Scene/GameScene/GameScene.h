#pragma once

#include "../BaseScene/BaseScene.h"

class Player;

class GameScene : public BaseScene
{
public:

	GameScene() { Init(); }
	~GameScene() override {}

private:

	void Event() override;
	void Init()  override;

	std::shared_ptr<Player> m_player;
};