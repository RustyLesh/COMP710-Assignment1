// COMP710 GP Framework 2022
#ifndef __GAME_H__
#define __GAME_H__

#include <vector>

// Forward declarations:
class Renderer;
class InputSystem;
class GUIManager;
class SceneManager;

class Game
{
    // Member methods:
public:
    static Game& GetInstance();
    static void DestroyInstance();

    bool Initialise();
    bool DoGameLoop();
    void Quit();

	void ToggleDebugWindow();

protected:
    void Process(float deltaTime);
    void Draw(Renderer& renderer);

    void ProcessFrameCounting(float deltaTime);

	void DebugDraw();
	bool m_bShowDebugWindow;

private:
    Game();
    ~Game();
    Game(const Game& game);
    Game& operator=(const Game& game);

    // Member data:
public:
	InputSystem* m_pInputSystem;

protected:
    static Game* sm_pInstance;
    Renderer* m_pRenderer;

    __int64 m_iLastTime;
    float m_fExecutionTime;
    float m_fElapsedSeconds;
    int m_iFrameCount;
    int m_iFPS;

	int m_iCurrentScene;
	bool m_bPauseSimulation;

	SceneManager* m_pSceneManager;

#ifdef USE_LAG
    float m_fLag;
    int m_iUpdateCount;
#endif // USE_LAG

    bool m_bLooping;

private:

};

#endif // __GAME_H__
