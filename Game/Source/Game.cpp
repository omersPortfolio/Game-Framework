#include "GamePCH.h"

#include "Game.h"
#include "Objects/Player.h"
#include "Objects/PlayerController.h"
#include "Objects/Shapes.h"
#include "Events/GameEvents.h"

Game::Game(fw::FWCore* pFramework) : fw::GameCore( pFramework )
{
    wglSwapInterval( m_VSyncEnabled ? 1 : 0 );
}

Game::~Game()
{
    delete m_pShader;
    delete m_pMeshHuman;
    delete m_pMeshEnemy;
    delete m_pMeshTest;

    for( fw::GameObject* pObject : m_Objects )
    {
        delete pObject;
    }

    delete m_pPlayerController;

    delete m_pEventManager;
    delete m_pImGuiManager;
}

void Game::Init()
{
    // OpenGL Settings.
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    m_pImGuiManager = new fw::ImGuiManager( m_pFramework );
    m_pImGuiManager->Init();

    m_pEventManager = new fw::EventManager();

    // Load some shaders.
    m_pShader = new fw::ShaderProgram( "Data/Basic.vert", "Data/Basic.frag" );

    // Create some meshes.
    m_pMeshHuman = new fw::Mesh( meshPrimType_Human, meshNumVerts_Human, meshAttribs_Human );
    m_pMeshEnemy = new fw::Mesh( meshPrimType_Enemy, meshNumVerts_Enemy, meshAttribs_Enemy );

    m_pMeshTest = new fw::Mesh();


    m_pPlayerController = new PlayerController();

    // Create some GameObjects.
    m_pPlayer = new Player( this, m_pPlayerController, "Player", vec2( 6, 5 ), m_pMeshHuman, m_pShader, vec4(0.0f, 1.0f, 0.0f, 0.5f) );

    m_Objects.push_back( new fw::GameObject( this, "Enemy 1", vec2(  0,  0 ), m_pMeshEnemy, m_pShader, nullptr, vec4::Red()   ) );
    m_Objects.push_back( new fw::GameObject( this, "Enemy 2", vec2( 10, 10 ), m_pMeshEnemy, m_pShader, nullptr, vec4::Red()   ) );
    m_Objects.push_back( new fw::GameObject( this, "Enemy 3", vec2(  5,  5 ), m_pMeshEnemy, m_pShader, nullptr, vec4::Red()   ) );
    m_Objects.push_back( new fw::GameObject( this, "Enemy 4", vec2(  1,  1 ), m_pMeshEnemy, m_pShader, nullptr, vec4::Red()   ) );
    m_Objects.push_back( new fw::GameObject( this, "Enemy 5", vec2(  1,  9 ), m_pMeshEnemy, m_pShader, nullptr, vec4::Red()   ) );
    //m_Objects.push_back( new fw::GameObject( this, "Test",    vec2(  3,  6 ), m_pMeshTest,  m_pShader, vec4::Blue()  ) );
    m_Objects.push_back( m_pPlayer );
}

void Game::StartFrame(float deltaTime)
{
    m_pImGuiManager->StartFrame( deltaTime );

    m_pPlayerController->StartFrame();

    // Process our events.
    m_pEventManager->DispatchAllEvents( deltaTime, this );
}

void Game::OnEvent(fw::Event* pEvent)
{
    m_pPlayerController->OnEvent( pEvent );

    if( pEvent->GetType() == RemoveFromGameEvent::GetStaticEventType() )
    {
        RemoveFromGameEvent* pRemoveFromGameEvent = static_cast<RemoveFromGameEvent*>( pEvent );
        fw::GameObject* pObject = pRemoveFromGameEvent->GetGameObject();

        auto it = std::find( m_Objects.begin(), m_Objects.end(), pObject );
        m_Objects.erase( it );

        delete pObject;
    }
}

void Game::Update(float deltaTime)
{
    //ImGui::ShowDemoWindow();

    // Display framerate.
    ImGui::Text( "%0.2f", 1/deltaTime );

    for( auto it = m_Objects.begin(); it != m_Objects.end(); it++ )
    {
        fw::GameObject* pObject = *it;
        pObject->Update( deltaTime );
    }

    // Check for collisions between objects.
    // Single For loop checking the player against everything else
    //   or
    // Nested For loop checking everything against everything else
    {
    }

    // Debug imgui stuff.
    {
        if( ImGui::Checkbox( "VSync", &m_VSyncEnabled ) )
        {
            wglSwapInterval( m_VSyncEnabled ? 1 : 0 );
        }
    }
}

void Game::Draw()
{
    glClearColor( 0, 0, 0.2f, 0 );
    glClear( GL_COLOR_BUFFER_BIT );

    glPointSize( 10 );
    
    for( auto it = m_Objects.begin(); it != m_Objects.end(); it++ )
    {
        fw::GameObject* pObject = *it;
        pObject->Draw();
    }

    m_pImGuiManager->EndFrame();
}
