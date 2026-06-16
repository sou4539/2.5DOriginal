#pragma once

class Player;
class Status;

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

	void SetOwner(std::shared_ptr<KdGameObject> owner)
	{
		m_wpOwner = owner;
	}
private:
	void Init() override;
	void Release() {}

	std::shared_ptr<KdSquarePolygon> m_polygon = nullptr;
	Math::Vector3 m_pos;


	bool ShotFlg = false;
		
	float d = 0;
	bool m_outroFlg = false;

	float m_anime = 0;

	std::weak_ptr<KdGameObject> m_wpOwner;

	std::shared_ptr<Status> m_status;

	bool HitFlg = false;
};