#include "Player.h"

#include "../Status/Status.h"
#include "../Weapon/Weapon.h"
#include "../Explode/Explode.h"
#include "../../Scene/SceneManager.h"

void Player::Init()
{
	//デバック用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/Object/Player/Player.png");

	//画像の原点を変更
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	//画像を分割
	m_polygon->SetSplit(3, 4);
	//プレイヤーの初期位置
	m_pos = { 0,0,-5 };

	m_status = std::make_shared<Status>();
}

void Player::Update()
{
	if (m_pos.z < 0)
	{
		m_pos.z += 0.1;
	}
	else
	{
		m_pos.z = 0;
		if (m_status->GetWWait() == 0)
		{
			std::shared_ptr<Weapon> m_weapon;
			m_weapon = std::make_shared<Weapon>();
			m_weapon->SetPos(m_pos);
			m_weapon->SetOwner(shared_from_this());
			SceneManager::Instance().AddObject(m_weapon);
			m_status->SetWWait(m_status->GetWWaitMax());
		}
		if (m_status->GetExFlg())
		{
			for (int i = 0; i < m_status->GetExNum(); i++)
			{
				if (m_status->GetExWait() == 0)
				{
					std::shared_ptr<Explode> m_explode;
					m_explode = std::make_shared<Explode>();
					m_explode->SetPos(m_pos);
					m_explode->SetOwner(shared_from_this());
					SceneManager::Instance().AddObject(m_explode);
					m_status->SetExWait(m_status->GetExWaitMax());
				}
			}
		}

		m_Move += 0.05;
		if (m_Move >= 40)
		{
			m_EnemyReSpawn = true;
			m_Move = 0;
		}
	}

	m_polygon->SetUVRect(10);
	// 2.5D仕様の移動速度調整 (左右移動のみ)
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_pos.x -= m_status->GetSpd();
		m_polygon->SetUVRect(9);
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_pos.x += m_status->GetSpd();
		m_polygon->SetUVRect(11);
	}

	m_status->SetWWait(m_status->GetWWait() - 1.0f);
	if (m_status->GetWWait() <= 0)m_status->SetWWait(0);

	m_status->SetExWait(m_status->GetExWait() - 1.0f);
	if (m_status->GetExWait() <= 0)m_status->SetExWait(0);

	// 座標行列の作成とワールド行列の更新
	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}

void Player::PostUpdate()
{
	//当たる側
	//=======================================
	//レイ（光線）判定		必須！！
	//=======================================
	KdCollider::RayInfo ray;
	//レイの発射位置を設定
	ray.m_pos = m_pos;
	//ちょっと上からの位置にする
	ray.m_pos.y += 0.1f;
	//段差の許容範囲を設定
	float enableStepHigh = 0.2;
	ray.m_pos.y += enableStepHigh;
	//レイの発射方向を設定
	ray.m_dir = { 0,-1,0 };
	//レイの長さを設定
	ray.m_range = enableStepHigh;
	//当たり判定を行いたいタイプを設定
	ray.m_type = KdCollider::TypeGround;

	//デバック
	m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range);

	//レイに当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult> retRayList;
	//全オブジェクトと当たり判定をする
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		//それぞれのオブジェクトに対してレイと当たるのかどうかを判定する関数を呼び出す
		obj->Intersects(ray, &retRayList);
	}

	//レイリストから一番近いオブジェクトを探す
	float maxOverlap = 0;
	Math::Vector3 hitPos;
	bool hit = false;
	for (auto& ret : retRayList)
	{
		//レイを遮断しオーバーした長さが一番長いものを探す
		if (maxOverlap < ret.m_overlapDistance)
		{
			maxOverlap = ret.m_overlapDistance;
			hitPos = ret.m_hitPos;
			hit = true;
		}
	}
	if (hit == true)
	{
		//当たっていたらその座標をプレイヤーの座標にセット
		m_pos = hitPos += Math::Vector3(0, -0.1, 0);

	}

	//=======================================
	//球（スフィア）判定		必須！！！！！！！！！！！
	//=======================================
	//球判定用の変数を用意
	KdCollider::SphereInfo sphere;
	//球の中心座標を設定します
	sphere.m_sphere.Center = m_pos;
	sphere.m_sphere.Center.y += 0.5;
	//球の半径を設定
	sphere.m_sphere.Radius = 0.3;
	//当たり判定をしたいタイプを設定
	sphere.m_type = KdCollider::TypeGround;

	//デバック
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

	//球に当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult> retSphereList;
	//全オブジェクトと当たり判定をする
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		//全オブジェクトに対して球判定する関数を呼び出す
		obj->Intersects(sphere, &retSphereList);
	}

	//球に当たったリストから一番近いオブジェクトを探す
	//↓こいつ　レイ判定で宣言済みの物を使いまわす
	hit = false;
	Math::Vector3 hitDir;	//当たった方向
	for (auto& ret : retSphereList)
	{
		//球にめり込んだ長さが一番長いものを探す
		if (maxOverlap < ret.m_overlapDistance)
		{
			maxOverlap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;
			hit = true;
		}
	}

	if (hit == true)
	{
		//Z方向への押し戻しを無効
		hitDir.z = 0;
		//Y方向への押し戻しを無効
		hitDir.y = 0;
		//方向ベクトルは絶対長さ１
		//正規化(長さが１)
		hitDir.Normalize();

		//押し戻し処理
		m_pos += hitDir * maxOverlap;
	}
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}
void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}