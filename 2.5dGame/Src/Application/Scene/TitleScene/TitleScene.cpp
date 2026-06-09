#include"TitleScene.h"
#include"../SceneManager.h"

void TitleScene::Init()
{
	m_titleTex.Load("Asset/Textures/title.png");
	m_startTex.Load("Asset/Textures/start.png");
}

void TitleScene::Update()
{
	m_alpha += m_addAlpha;
	if (m_alpha >1.0f)
	{
		m_alpha = 1.0f;
		m_addAlpha *= -1.0f;
	}
	else if (m_alpha <= 0.0f)
	{
		m_alpha = 0.0f;
		m_addAlpha *= -1.0f;
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
	}
}

void TitleScene::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_titleTex, 0, 0);
	Math::Color color = { 1.0f, 1.0f, 1.0f, m_alpha };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_startTex, 0, -200,nullptr,&color);
}

void TitleScene::Release()
{
	m_titleTex.Release();
	m_startTex.Release();
}
