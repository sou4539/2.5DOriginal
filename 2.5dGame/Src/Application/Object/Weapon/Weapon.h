#pragma once

class Player;

class Weapon : public KdGameObject
{
public:
	Weapon() { Init(); }
	~Weapon() override { Release(); }

	void Update() override;
	//void PostUpdate() override;

	void DrawLit() override;
	//void GenerateDepthMapFromLight() override;
	

private:
	void Init() override;
	void Release() {}

	std::shared_ptr<KdSquarePolygon> m_polygon = nullptr;
	Math::Vector3 m_pos;

	std::shared_ptr<Player> player;

	float ShotWait = 0.0;
	bool ShotFlg = false;
};