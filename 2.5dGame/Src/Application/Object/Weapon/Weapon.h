#pragma once

class Weapon : public KdGameObject
{
public:
	Weapon() { Init(); }
	~Weapon() override { Release(); }

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
	Math::Vector3 m_pos;


	bool ShotFlg = false;
};