#pragma once

class Player : public KdGameObject
{
public:
	Player() { Init(); }
	~Player() override { Release(); }

	void Update() override;
	void PostUpdate() override;

	void DrawLit() override;
	void GenerateDepthMapFromLight() override;


private:
	void Init() override;
	void Release() {}

	//std::shared_ptr<KdModelData> m_model = nullptr;
	std::shared_ptr<KdSquarePolygon> m_polygon;
	Math::Vector3 m_pos;

	//各種ステータス
	//攻撃力
	float m_attack = 1;
	//体力
	float m_health = 10;
	//移動速度
	float m_speed = 0.2;
	//攻撃速度
	float WeaponWait = 0;
	//詠唱速度
	//Weaponクラスで使う関数なのでここにはない
	//爆炎魔法
	//習得済みかどうか
	bool ExplodeFlg = false;
	//攻撃速度
	float ExplodeWait = 0;
	//詠唱速度
	//Explodeクラスで使う関数なのでここにはない


};