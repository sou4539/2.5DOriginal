#pragma once

class Portal : public KdGameObject
{
public:
	enum PowerUpType
	{
		AtkUp,		//攻撃力アップ
		HpUp,		//体力アップ
		MSpdUp,		//移動速度アップ
		ASpdUp,		//連射速度アップ
		SSpdUp,		//詠唱速度アップ
		Explode,	//爆炎魔法
	};

	Portal() { Init(); }
	~Portal() override { Release(); }

	void Update() override;
	//void PostUpdate() override;

	void DrawLit() override;
	//void GenerateDepthMapFromLight() override;

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
};