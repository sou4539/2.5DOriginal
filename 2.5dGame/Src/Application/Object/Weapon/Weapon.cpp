#include "Weapon.h"

#include "../Status/Status.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
//#include "../../Scene/SceneManager.h"

void Weapon::Update()
{
	if (m_outroFlg)
	{
		OutroUpdate();
		return;
	}

	if (d > 0)
	{
		d -= m_status->GetWSpd();
	}
	else 
	{
		d = 0;
		m_pos.z += 0.5;
	}

	if (m_pos.z >= 30)
	{
		m_isExpired = true;
	}

	static float m_anime = 0;
	m_anime += 0.05;
	if (m_anime > 4)m_anime = 0;
	m_polygon->SetUVRect(int(m_anime));

	// 座標行列
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);

	// 拡縮行列
	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(1);

	// 行列合成 (S * R * T)
	m_mWorld = scaleMat * transMat;
}

void Weapon::PostUpdate()
{
	//球判定
	KdCollider::SphereInfo sphere;
	sphere.m_sphere.Center = GetPos();
	sphere.m_sphere.Center = sphere.m_sphere.Center + Math::Vector3(0, 0.5f, 0);
	sphere.m_sphere.Radius = 0.3f;
	sphere.m_type = KdCollider::Type::TypeDamage;

	//デバック
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius, kRedColor);

	// 手順①オーナー(プレイヤー = 弾を発射した人)を受け取る
	std::shared_ptr<Player> _player = std::static_pointer_cast<Player>(m_wpOwner.lock());
	if (_player)
	{
		// 手順②オーナー(プレイヤー)が持っている敵のリストを取得
		std::list<std::weak_ptr<Enemy>> _enemyList = _player->GetEnemyList();
		auto it = _enemyList.begin();

		while (it != _enemyList.end())
		{
			std::shared_ptr<Enemy> _enemy = it->lock();
			if (_enemy)
			{
				if (_enemy->Intersects(sphere, nullptr)) {
					//　当たった
					//　敵オブジェクト確定！！
					if (!HitFlg)
					{
						_enemy->SetDamage(1);
						HitFlg = true;
					}
					else
					{
						_enemy->SetDamage(0);
					}
					_enemy->OnHit();
					OnHit();
				}
			}
			++it;	// 次の要素へイテレータを進める
		}
	}
}

void Weapon::OutroUpdate()
{
	d += 0.5;
	if (d > 1)
	{
		m_isExpired = true;
	}
}

void Weapon::OnHit()
{
	m_outroFlg = true;
}

void Weapon::DrawLit()
{
	float range = 0.05;
	Math::Vector3 color = { 1,0.3,0.3 };
	KdShaderManager::Instance().m_StandardShader.SetDissolve(d, &range, &color);

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);

}

void Weapon::Init()
{
	m_pos = {};
	d = 1;
	m_pos.x + 0.5;
	HitFlg = false;
	// メモリ確保
	m_polygon = std::make_shared<KdSquarePolygon>();

	m_polygon->SetSplit(4, 1);

	// モデル読み込み
	m_polygon->SetMaterial("Asset/Textures/Object/Weapon/Weapon.png");

	//画像の原点を変更
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	//デバック用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_status = std::make_shared<Status>();
}
