#include "Ground.h"

#include "Ground.h"

void Ground::DrawLit()
{
	// 地面描画
// 地面には陰影がつくべきなので DrawLit() で描画する
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Ground::Init()
{
	// メモリ確保
	m_model = std::make_shared<KdModelData>();

	// モデル読み込み
	m_model->Load("Asset/Data/LessonData/Terrain/Terrain.gltf");

	// 座標行列
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(0, 0, 0);

	// 拡縮行列
	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(100.0f);
	//scaleMat = Math::Matrix::CreateScale(100.0f, 100.0f, 100.0f);

	// 行列合成 (S * R * T)
	m_mWorld = scaleMat * transMat;
}
