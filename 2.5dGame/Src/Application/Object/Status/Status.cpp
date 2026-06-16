#include "Status.h"

void Status::Init()
{	
	m_attack = 1;
	m_health = 10;
	m_speed = 0.2f;
	m_WeaponWaitMax = 120;
	m_WeaponWait = m_WeaponWaitMax;
	m_WeaponSpeed = 0.05f;
	m_ExplodeFlg = true;
	m_ExplodeNum = 1;
	m_ExplodeWaitMax = 180;
	m_ExplodeWait = m_ExplodeWaitMax;
	m_ExplodeSpeed = 0.01f;
}