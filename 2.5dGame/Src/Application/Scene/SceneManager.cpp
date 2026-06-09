#include "SceneManager.h"

//各シーンのヘッダーをインクルード
#include "TitleScene/TitleScene.h"
#include "GameScene/GameScene.h"

void SceneManager::preUpdate()
{
	//シーン切り替え
	if (m_currentSceneType != m_nextSceneType)
	{
		ChangeScene(m_nextSceneType);
	}
}

void SceneManager::Update()
{
	//ポリモーフィズム
	//同じ関数名であっても、呼び出すオブジェクトによって処理内容が変わること
	m_currentScene->Update();
}

void SceneManager::Draw()
{
	m_currentScene->DrawSprite();
}

void SceneManager::Init()
{
	ChangeScene(m_currentSceneType);
}

void SceneManager::Release()
{
}

void SceneManager::ChangeScene(SceneType _sceneType)
{

	//①次のシーンを作成し、②フラグを更新する

	//①
	switch (_sceneType)
	{
	case SceneType::Title:
		//アップキャスト
		m_currentScene = std::make_shared<TitleScene>();
		break;
	case SceneType::Game:
		//アップキャスト
		m_currentScene=std::make_shared<GameScene>();
		break;
	}

	//②フラグを更新
	m_currentSceneType = _sceneType;
}
