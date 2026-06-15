#pragma once

class Portal;

class Enemy : public KdGameObject
{
public:
	Enemy() { Init(); }
	~Enemy() override { Release(); }

	void Update() override;
	void PostUpdate() override;
	void DrawLit() override;
	void GenerateDepthMapFromLight() override;
	void OnHit()override;

	void SetDamage(float _damage) { m_Damage = _damage; }
private:
	void Init() override;
	void Release() {}

	std::shared_ptr<Portal>m_portal;

	std::shared_ptr<KdSquarePolygon> m_polygon;
	Math::Vector3 m_pos;
	float m_speed = 0.05f;

	float m_Hp = 10;
	float m_Damage = 0;
};