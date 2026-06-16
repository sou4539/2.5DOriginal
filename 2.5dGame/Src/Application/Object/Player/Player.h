#pragma once

class Enemy;
class Status;

class Player : public KdGameObject
{
public:
	Player() { Init(); }
	~Player() override { Release(); }

	void Update() override;
	void PostUpdate() override;

	void DrawLit() override;
	void GenerateDepthMapFromLight() override;

	void RegistEnemy(std::shared_ptr<Enemy> enemy)
	{
		m_wpEnemyList.push_back(enemy);
	}

	std::list<std::weak_ptr<Enemy>> GetEnemyList()
	{
		return m_wpEnemyList;
	}

	bool GetEnemyReSpawn()
	{
		return m_EnemyReSpawn;
	}

	void SetEnemyReSpawn(bool _EnemyReSpawn){m_EnemyReSpawn=_EnemyReSpawn;}

private:
	void Init() override;
	void Release() {}

	//std::shared_ptr<KdModelData> m_model = nullptr;
	std::shared_ptr<KdSquarePolygon> m_polygon;
	Math::Vector3 m_pos;

	std::list<std::weak_ptr<Enemy>> m_wpEnemyList;
	std::shared_ptr<Status> m_status;

	//プレイヤーの移動量を格納する変数
	float m_Move = 0;
	//敵のリスポーン関数
	bool m_EnemyReSpawn = false;
};