#include "Portal.h"

void Portal::Update()
{
	m_pos.z -= m_speed;

	static float m_anime = 0;
	m_anime += 0.05;
	if (m_anime > 7)m_anime = 0;
	m_polygon->SetUVRect(int(m_anime));
	// 座標行列
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);

	// 拡縮行列
	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(2,3,1);
	//scaleMat = Math::Matrix::CreateScale(100.0f, 100.0f, 100.0f);

	// 行列合成 (S * R * T)
	m_mWorld = scaleMat * transMat;
}

void Portal::DrawLit()
{
	// ポータル描画
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void Portal::Init()
{
	// メモリ確保
	m_polygon = std::make_shared<KdSquarePolygon>();

	// 画像読み込み
	m_polygon->SetMaterial("Asset/Textures/Object/Portal/Portal.png");
	//デバック用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	//画像の原点を変更
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	//画像を分割
	m_polygon->SetSplit(4,2);
	m_polygon->SetUVRect(0);
	//プレイヤーの初期位置
	m_pos = {};
	
	m_PortalType = KdRandom::GetInt(0, 5);
	m_PortalNum[m_PortalType];
	
	//switch (m_PortalType)
	//{
	//case 0:
	//}
}
