#pragma once

class Enemy : public KdGameObject
{
public:
	Enemy() { Init(); }
	~Enemy() override { Release(); }

	void Update() override;
	void PostUpdate() override;
	void DrawLit() override;

private:
	void Init() override;
	void Release() {}

	//std::shared_ptr<KdModelData> m_model = nullptr;
	std::shared_ptr<KdSquarePolygon> m_polygon;
	Math::Vector3 m_pos;
	float m_speed = 0.05f;
};