#include "Portal.h"

#include "../Status/Status.h"

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
	scaleMat = Math::Matrix::CreateScale(2, 3, 1);
	//scaleMat = Math::Matrix::CreateScale(100.0f, 100.0f, 100.0f);

	// 行列合成 (S * R * T)
	m_mWorld = scaleMat * transMat;
}

void Portal::DrawLit()
{
	// ポータル描画
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void Portal::OnHit()
{
	switch (m_PortalType)
	{
	case	AtkUp:	//攻撃力アップ
		m_status->SetAtk(m_status->GetAtk() + 1);
		break;
	case	HpUp:		//体力アップ
		m_status->SetHp(m_status->GetHp() + 1);
		break;
	case	MSpdUp:		//移動速度アップ
		m_status->SetSpd(m_status->GetSpd() + 0.01);
		break;
	case	WSpdUp:		//連射速度アップ
		m_status->SetWWait(m_status->GetWWait() - 0.1);
		break;
	case	WSplUp:		//詠唱速度アップ
		m_status->SetWSpd(m_status->GetWSpd() + 0.001);
		break;
	case	ExplodeOn:	//爆炎魔法のon/off
		m_status->SetExFlg(true);
		break;
	case	ExplodeUp:	//爆炎魔法の数アップ
		m_status->SetExNum(m_status->GetExNum() + 1);
		break;
	case	ExSpdUp:	//爆炎魔法の連射速度アップ
		m_status->SetExWait(m_status->GetExWait() + 1);
		break;
	case	ExSplUp:	//爆炎魔法の詠唱速度アップ
		m_status->SetExSpd(m_status->GetExSpd() + 0.001);
		break;
	}
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
	m_polygon->SetSplit(4, 2);
	m_polygon->SetUVRect(0);
	//プレイヤーの初期位置
	m_pos = {};

	//どの強化が出るのか
	m_PortalType = KdRandom::GetInt(0, 5);
	m_PortalNum[m_PortalType];

	//当たられる側の処理========================================
	//当たり判定をつけたいから実体化
	m_pCollider = std::make_unique<KdCollider>();
	//モデルの形状で当たり判定を登録
	m_pCollider->RegisterCollisionShape(
		"PortalCollision",		//当たり判定を識別名
		{ 0,0.5,0 },
		0.4f,
		KdCollider::TypeEvent);
	//==========================================================
}
