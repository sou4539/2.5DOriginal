#pragma once

class Stage : public KdGameObject
{
public:
	Stage() { Init(); }
	~Stage() override { Release(); }

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

	std::shared_ptr<KdModelData> m_model = nullptr;
	Math::Vector3 m_pos;
	static const int StageNum = 4;
};