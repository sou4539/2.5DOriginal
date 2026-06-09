#pragma once

//前方宣言
class BaseScene;

//全てのシーンを管理するクラス
class SceneManager
{
public:

	//シーン情報
	//enum = 列挙型 ・・・複数の定数をまとめて管理するための型
	//入る値は０から順番にint型で割り当てられる
	enum SceneType
	{
		Title,	//タイトルシーン
		Game,	//ゲームシーン
	};

	//Updateの前に実行するUpdate
	void preUpdate();

	void Update();
	void Draw();

	//外部から次のシーンをセットする関数
	//※この関数ではシーンは切り替わらない
	void SetNextScene(SceneType _nextScene)
	{
		m_nextSceneType = _nextScene;
	}

	//現在のシーンを取得する関数
	SceneType GetCurrentScene() const
	{
		return m_currentSceneType;
	}

private:

	//初期化や解放は自分でする
	void Init();
	void Release();

	//シーン切替の関数
	void ChangeScene(SceneType _sceneType);

	//原罪のシーンを管理するポインタ変数
	std::shared_ptr<BaseScene> m_currentScene;

	//現在のシーンを管理するフラグ変数
	SceneType m_currentSceneType = SceneType::Title;
	//次のシーンを管理するフラグ変数
	SceneType m_nextSceneType = m_currentSceneType;

	//シングルトンパターン(デザインパターン)
	//実態が一つしかないことを証明するためのパターン
private:

	//外で変数宣言できない
	SceneManager() { Init(); }
	~SceneManager() { Release(); }

public:

	static SceneManager& Instance()
	{
		static SceneManager instance;
		return instance;
	}

};