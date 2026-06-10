#include "Stage.h"

void Stage::Init()
{
	//初期化
	m_pos = {};
	//●モデルの読み込み
	//ポインタのままでは使い物にならないので、実体化
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Model/Stage/Stage.gltf");

	//当たられる側の処理========================================
	//当たり判定をつけたいから実体化
	m_pCollider = std::make_unique<KdCollider>();
	//モデルの形状で当たり判定を登録
	m_pCollider->RegisterCollisionShape(
		"GroundCollision",
		m_model,
		KdCollider::TypeGround);

	//==========================================================
}

void Stage::Update()
{
	m_pos.z -= 0.5;
	if (m_pos.z <= 0)m_pos.z = 70;

	Math::Matrix scaleMat = Math::Matrix::CreateScale(5.0f, 1.0f, 1.0f);
	m_mWorld = scaleMat;
}

void Stage::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}