#pragma once

class Status : public KdGameObject
{
public:
	Status() { Init(); }
	~Status() override { Release(); }

	//ステータスゲッター
	//攻撃力
	float GetAtk() { return m_attack; }
	//体力
	float GetHp() { return m_health;}
	//移動速度
	float GetSpd() { return m_speed; }
	//攻撃速度
	float GetWWait() { return m_WeaponWait; }
	float GetWWaitMax() { return m_WeaponWaitMax; }
	//詠唱速度
	float GetWSpd() { return m_WeaponSpeed; }
	//爆炎魔法
	//習得済みかどうか
	bool GetExFlg() { return m_ExplodeFlg; }
	//攻撃速度
	float GetExWait() { return m_ExplodeWait; }
	float GetExWaitMax() { return m_ExplodeWaitMax; }
	//詠唱速度
	float GetExSpd() { return m_ExplodeSpeed; }

	//ステータスセッター
	//攻撃力
	void SetAtk(float _attack) { m_attack = _attack; }
	//体力
	void SetHp(float _health) { m_health = _health; }
	//移動速度
	void SetSpd(float _speed) { m_speed = _speed; }
	//攻撃速度
	void SetWWait(float _WeaponWait) {m_WeaponWait = _WeaponWait; }
	//詠唱速度
	void SetWSpd(float _WeaponSpeed) { m_WeaponSpeed = _WeaponSpeed; }
	//爆炎魔法
	//習得済みかどうか
	void SetExFlg(bool _ExplodeFlg) { m_ExplodeFlg = _ExplodeFlg; }
	//攻撃速度
	void SetExWait(float _ExplodeWait) { m_ExplodeWait = _ExplodeWait; }
	//詠唱速度
	void SetExSpd(float _ExplodeSpeed) { m_ExplodeSpeed = _ExplodeSpeed; }

private:
	void Init() override;
	void Release() {}


	//各種ステータス
	//攻撃力
	float m_attack = 1;
	//体力
	float m_health = 10;
	//移動速度
	float m_speed = 0.2;
	//攻撃速度
	float m_WeaponWait = 0;
	float m_WeaponWaitMax = 120;
	//詠唱速度
	float m_WeaponSpeed = 0.05;
	//爆炎魔法
	//習得済みかどうか
	bool m_ExplodeFlg = false;
	//攻撃速度
	float m_ExplodeWait = 0;
	float m_ExplodeWaitMax = 180;
	//詠唱速度
	float m_ExplodeSpeed = 0.01;
};