#pragma once

class Status;

class Portal : public KdGameObject
{
public:
	//強化の種類
	enum PowerUpType
	{
		AtkUp,		//攻撃力アップ
		HpUp,		//体力アップ
		MSpdUp,		//移動速度アップ
		WSpdUp,		//連射速度アップ
		WSplUp,		//詠唱速度アップ
		ExplodeOn,	//爆炎魔法のon/off
		ExplodeUp,	//爆炎魔法の数アップ
		ExSpdUp,	//爆炎魔法の連射速度アップ
		ExSplUp,	//爆炎魔法の詠唱速度アップ
	};

	Portal() { Init(); }
	~Portal() override { Release(); }

	void Update() override;
	//void PostUpdate() override;

	void DrawLit() override;
	//void GenerateDepthMapFromLight() override;

	void OnHit() override;

	void SetPos(const Math::Vector3& _pos)override
	{
		m_pos = _pos;
	}
private:
	void Init() override;
	void Release() {}

	std::shared_ptr<KdSquarePolygon> m_polygon = nullptr;
	Math::Vector3 m_pos = {};

	int m_PortalType = 0;
	int m_PortalNum[6];

	float m_speed = 0.05f;

	std::shared_ptr<Status> m_status;
};