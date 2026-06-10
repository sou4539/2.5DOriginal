#include "Weapon.h"

void Weapon::Update()
{
	m_pos.z += 0.5;

	if (m_pos.z >= 30)
	{
		m_isExpired = true;
	}

	// 座標行列
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);

	// 拡縮行列
	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(1);

	// 行列合成 (S * R * T)
	m_mWorld = scaleMat * transMat;
}

void Weapon::DrawLit()
{

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);

}

void Weapon::Init()
{
	m_pos = {};

	// メモリ確保
	m_polygon = std::make_shared<KdSquarePolygon>();

	// モデル読み込み
	m_polygon->SetMaterial("Asset/Textures/Object/Weapon/Weapon.png");
}
