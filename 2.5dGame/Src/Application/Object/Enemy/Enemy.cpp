#include "Enemy.h"

#include "../../Scene/SceneManager.h"

void Enemy::Init()
{
	m_Hp = 10;
	//デバック用
	//m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	//ポインタのままでは使い物にならないので、実体化
	m_polygon = std::make_shared<KdSquarePolygon>();

	m_polygon->SetMaterial("Asset/Textures/Object/Enemy/Enemy.png");

	//画像の原点を変更
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	//画像を分割
	m_polygon->SetSplit(3, 4);
	//プレイヤーの初期位置
	m_pos = { 0,0,0 };

	//当たられる側の処理========================================
	//当たり判定をつけたいから実体化
	m_pCollider = std::make_unique<KdCollider>();
	//モデルの形状で当たり判定を登録
	m_pCollider->RegisterCollisionShape(
		"EnemyCollision",		//当たり判定を識別名
		{ 0,0.5,0 },
		0.2f,
		KdCollider::TypeDamage);
	//==========================================================
}

void Enemy::Update()
{
	m_polygon->SetUVRect(1);
	// 奥から手前方向への自動スクロール
	m_pos.z -= m_speed;

	if (m_pos.z <= 0)m_pos.z += 30;
	//if (m_pos.z <= 10)m_isExpired = true;

	if (m_Hp <= 9)m_isExpired = true;

	//でかくする
	Math::Matrix scaleMat = Math::Matrix::CreateScale(1);
	//遠くに置く
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = scaleMat * transMat;
}

void Enemy::PostUpdate()
{

}

void Enemy::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}
void Enemy::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}