#include "Status.h"

void Status::Init()
{
	//各種ステータス
	//攻撃力
	m_attack = 1;
	//体力
	m_health = 10;
	//移動速度
	m_speed = 0.2;
	//攻撃速度
	m_WeaponWaitMax = 120;
	m_WeaponWait = m_WeaponWaitMax;
	//詠唱速度
	m_WeaponSpeed = 0.05;
	//爆炎魔法
	//習得済みかどうか
	m_ExplodeFlg = false;
	//爆炎魔法の打てる数
	m_ExplodeNum = 1;
	//攻撃速度
	m_ExplodeWaitMax = 180;
	m_ExplodeWait = m_ExplodeWaitMax;
	//詠唱速度
	m_ExplodeSpeed = 0.01;
}