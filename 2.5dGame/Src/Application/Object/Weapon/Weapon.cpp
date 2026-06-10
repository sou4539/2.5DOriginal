#include "Weapon.h"

#include"../Player/Player.h"

void Weapon::Update()
{
	
	if (ShotWait == 0)
	{
		m_pos = player->GetPos();
		//m_pos = { 5,0,0 };
		ShotWait = 30;
		ShotFlg = true;
	}

	ShotWait--;
	if (ShotWait <= 0)ShotWait = 0;

	if (!m_isExpired)
	{
		m_pos.z += 0.5;
	}

	if (m_pos.z >= 30)
	{
		ShotFlg = false;
	}

	// 座標行列
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);

	// 拡縮行列
	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(1);
	//scaleMat = Math::Matrix::CreateScale(100.0f, 100.0f, 100.0f);

	// 行列合成 (S * R * T)
	m_mWorld = scaleMat * transMat;
}

void Weapon::DrawLit()
{
	if (ShotFlg)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
	}
}

void Weapon::Init()
{
	m_pos = {};
	// メモリ確保
	m_polygon = std::make_shared<KdSquarePolygon>();

	// モデル読み込み
	m_polygon->SetMaterial("Asset/Textures/Object/Weapon/Weapon.png");
	player = std::make_shared<Player>();
}
