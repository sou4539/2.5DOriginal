#pragma once

class Enemy : public KdGameObject
{
public:
	Enemy() { Init(); }
	~Enemy() override { Release(); }

	void Update() override;
	void PostUpdate() override;
	void DrawLit() override;
	void GenerateDepthMapFromLight() override;

	void SetHp(float _hp) { m_Hp -= _hp; }
	float GetHp() { return m_Hp; }
private:
	void Init() override;
	void Release() {}

	std::shared_ptr<KdSquarePolygon> m_polygon;
	Math::Vector3 m_pos;
	float m_speed = 0.05f;

	float m_Hp = 10;
};