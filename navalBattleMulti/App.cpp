#include "Framework.h"

App::App()
{
	m_sysTime = timeGetTime();
}

App::~App()
{
}

void App::Init()
{
	m_window = new RenderWindow(VideoMode(900, 600), "Bataille navale");
	m_state = PLAY;
	CreateScene();
}

void App::PrintDebug(String textDebug)
{
    m_debugText.setFont(m_font);
    m_debugText.setString(textDebug);
    m_debugText.setPosition(800, 0);
    m_debugText.setCharacterSize(20);
    m_debugText.setFillColor(Color::White);
}

void App::DrawDebug()
{
    m_window->draw(m_debugText);
}

void App::CreateScene()
{
    m_scene = new Scene(m_window);
	m_scene->SetPlaying(true);
}

bool App::UpdateTime()
{
    DWORD newSysTime = timeGetTime();
    DWORD elapsedSysTime = newSysTime - m_sysTime;
    if (elapsedSysTime < 5)
        return false;
    m_sysTime = newSysTime;
    if (elapsedSysTime > 40)
        elapsedSysTime = 40;

    m_elapsedTime = elapsedSysTime / 1000.0f;
    m_time += m_elapsedTime;
    return true;
}

float App::GetTime()
{
    return m_time;
}

float App::GetElapsedTime()
{
    return m_elapsedTime;
}

Scene* App::GetScene()
{
    return m_scene;
}

void App::Start()
{
    while (m_window->isOpen())
    {
        Event event;
        while (m_window->pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                m_window->close();
            }
        }

        if (m_scene->IsPlaying())
        {
            if (UpdateTime())
            {
                m_scene->Update();
                m_scene->Render();
            }
        }
        else
        {
            m_window->close();
        }

    }
}