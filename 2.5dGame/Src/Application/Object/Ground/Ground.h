#pragma once

class Ground : public KdGameObject
{
public:
	Ground() { Init(); }
	~Ground() override { Release(); }

	void Update() override;
	void PostUpdate() override;

	void DrawLit() override;
	void GenerateDepthMapFromLight() override;
	

private:
	void Init() override;
	void Release() {}

	std::shared_ptr<KdModelData> m_model = nullptr;
};