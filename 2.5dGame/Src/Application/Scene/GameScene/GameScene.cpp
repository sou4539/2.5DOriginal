#include "GameScene.h"
#include "../SceneManager.h"

#include "../../Object/Player/Player.h"
//#include "../../Object/Ground/Ground.h"
#include "../../Object/Enemy/Enemy.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Result);
	}
}

void GameScene::Init()
{
	// カメラ実体化
	m_camera = std::make_unique<KdCamera>();

	// 地面追加
	//std::shared_ptr<Ground> ground = std::make_shared<Ground>();
	//m_objList.push_back(ground);

	// プレイヤー追加
	m_player = std::make_shared<Player>();
	m_objList.push_back(m_player);

	// 敵（雑魚）を追加
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
	m_objList.push_back(enemy);
}