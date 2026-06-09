#pragma once

//継承の場合のみインクルードを許可します！！！
#include"../BaseScene/BaseScene.h"

class TitleScene : public BaseScene
{
public:
	TitleScene() { Init(); }
	~TitleScene() {}

	void Init();
	void Update();
	void DrawSprite();
	void Release();

private:
	KdTexture m_titleTex;
	KdTexture m_startTex;

	float m_alpha = 1.0f;
	float m_addAlpha = 0.01f;
};