#include "TitleScene.h"
#include "../SceneManager.h"

#include "../../Object/Stage/Stage.h"
#include "../../Object/Ground/Ground.h"

void TitleScene::Event()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Game
		);
	}

	Math::Vector3 camPos = { 0,10,-5 };
	Math::Matrix rotateMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	Math::Matrix transMat = Math::Matrix::CreateTranslation(camPos);
	m_camera->SetCameraMatrix(rotateMat * transMat);
}

void TitleScene::Init()
{
	// カメラ実体化
	m_camera = std::make_unique<KdCamera>();

	// ステージを追加
	std::shared_ptr<Stage> stage;
	for (int i = 0; i < 4; i++)
	{
		stage = std::make_shared<Stage>();
		stage->SetPos({ 0,0,i * 12.0f - 1.0f });
		m_objList.push_back(stage);
	}

	// 地面追加
	std::shared_ptr<Ground> ground;
	ground = std::make_shared<Ground>();
	m_objList.push_back(ground);
}
