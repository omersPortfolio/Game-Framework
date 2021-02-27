#pragma once

class PlayerController;
class Player;

class Game : public fw::GameCore
{
public:
    Game(fw::FWCore* pFramework);
    virtual ~Game();

    void Init();
    virtual void StartFrame(float deltaTime) override;
    virtual void OnEvent(fw::Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    Player* GetPlayer() { return m_pPlayer; }

protected:
    fw::ImGuiManager* m_pImGuiManager = nullptr;

    fw::ShaderProgram* m_pShader = nullptr;
    fw::Mesh* m_pMeshHuman = nullptr;
    fw::Mesh* m_pMeshEnemy = nullptr;
    fw::Mesh* m_pMeshTest = nullptr;

    PlayerController* m_pPlayerController = nullptr;

    Player* m_pPlayer = nullptr;
    std::vector<fw::GameObject*> m_Objects;

    // Settings.
    bool m_VSyncEnabled = true;
};
