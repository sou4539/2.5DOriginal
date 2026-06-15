#pragma once

class Enemy;

class Explode : public KdGameObject
{
public:

	Explode() { Init(); }
	~Explode() override { Release(); }

	void Update() override;
	void PostUpdate() override;
	void OutroUpdate();
	void OnHit() override;

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
	Math::Vector3 m_pos;


	bool ShotFlg = false;
	std::shared_ptr<Enemy> m_enemy;
		
	float d = 0;
	bool m_outroFlg = false;

	//詠唱速度
	float m_SpellSpeed = 0.01;

	float m_anime = 0;
};