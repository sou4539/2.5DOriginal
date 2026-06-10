#include "GameScene.h"
#include "../SceneManager.h"

#include "../../Object/Player/Player.h"
#include "../../Object/Ground/Ground.h"
#include "../../Object/Enemy/Enemy.h"
#include "../../Object/Stage/Stage.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
	}

	Math::Vector3 camPos = { 0,1,-5 };
	Math::Matrix transMat = Math::Matrix::CreateTranslation(camPos + m_player->GetPos());
	m_camera->SetCameraMatrix(transMat);
}

void GameScene::Init()
{
	// カメラ実体化
	m_camera = std::make_unique<KdCamera>();

	// 地面追加
	std::shared_ptr<Ground> ground = std::make_shared<Ground>();
	m_objList.push_back(ground);

	// プレイヤー追加
	m_player = std::make_shared<Player>();
	m_objList.push_back(m_player);

	// 敵（雑魚）を追加
	std::shared_ptr<Enemy> enemy;
	enemy = std::make_shared<Enemy>();
	m_objList.push_back(enemy);

	// ステージを追加
	std::shared_ptr<Stage> stage;
	for (int i = 0; i < 5; i++)
	{
		stage = std::make_shared<Stage>();
		stage->SetPos({ 0,0,i * 14.0f });
		m_objList.push_back(stage);
	}
}