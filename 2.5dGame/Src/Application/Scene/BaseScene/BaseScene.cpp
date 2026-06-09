#include "BaseScene.h"

void BaseScene::Init()
{
}

void BaseScene::Update()
{
}

void BaseScene::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawCircle(0, 0, 100);
}

void BaseScene::Release()
{
}