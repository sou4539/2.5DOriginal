#include "Ground.h"

void Ground::Init()
{
	//●モデルの読み込み
	//ポインタのままでは使い物にならないので、実体化
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/SideViewMap/SideViewMap.gltf");
	//横向きに拡大して描画
	Math::Matrix scaleMat = Math::Matrix::CreateScale(5.0f, 1.0f, 1.0f);
	m_mWorld = scaleMat;

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

void Ground::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}