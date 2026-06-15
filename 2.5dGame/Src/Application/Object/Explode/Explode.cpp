#include "Explode.h"

#include "../Enemy/Enemy.h"
#include "../../Scene/SceneManager.h"

void Explode::Update()
{
	
	if (m_outroFlg)
	{
		OutroUpdate();
		return;
	}

	if (d > 0)
	{
		d -= m_SpellSpeed;
	}
	else 
	{
		d = 0;
		m_pos.z += 0.5;
		m_polygon->SetUVRect(0);
	}

	if (m_pos.z >= 30)
	{
		m_isExpired = true;
	}

	// 座標行列
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);

	// 拡縮行列
	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(2);

	// 行列合成 (S * R * T)
	m_mWorld = scaleMat * transMat;
}

void Explode::PostUpdate()
{
	//球判定
	KdCollider::SphereInfo sphere;
	sphere.m_sphere.Center = GetPos();
	sphere.m_sphere.Center = sphere.m_sphere.Center + Math::Vector3(0, 0.5f, 0);
	sphere.m_sphere.Radius = 0.3f;
	sphere.m_type = KdCollider::Type::TypeDamage;

	//デバック
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius, kRedColor);

	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		//								↓リストをセットしていた
		if (obj->Intersects(sphere, nullptr)) {
			//　当たった
			//　敵オブジェクト確定！！
			m_enemy->SetDamage(1);
			obj->OnHit();
			OnHit();
		}
	}
}

void Explode::OutroUpdate()
{
	d += 0.01;
	if (d > 1)
	{
		m_isExpired = true;
	}
}

void Explode::OnHit()
{

	m_anime += 0.5;
	m_polygon->SetUVRect(int(m_anime));
	m_outroFlg = true;
	
}

void Explode::DrawLit()
{
	float range = 0.05;
	Math::Vector3 color = { 1,0.3,0.3 };
	KdShaderManager::Instance().m_StandardShader.SetDissolve(d, &range, &color);

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void Explode::Init()
{
	m_pos = {};
	d = 1;
	m_anime = 0;
	// メモリ確保
	m_polygon = std::make_shared<KdSquarePolygon>();

	// モデル読み込み
	m_polygon->SetMaterial("Asset/Textures/Object/Explode/Explode.png");

	m_polygon->SetSplit(4, 4);
	m_polygon->SetUVRect(0);

	//画像の原点を変更
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	//デバック用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();


	m_enemy = std::make_shared<Enemy>();
}
