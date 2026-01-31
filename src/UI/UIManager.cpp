#include <UI/UIManager.h>
#include <UI/UIScreenHUD.h>
#include "UI/UIScreenVictory.h"
#include "UI/UIScreenGameOver.h"


UIManager::~UIManager()
{
    for (auto s : m_states)
        delete s;
}

UIManager::UIManager(Player* player)
{
    for (int i = 0; i < State_Count; ++i)
        m_states[i] = nullptr;

    m_states[State_HUD] = new UIScreenHUD(player);
    m_states[State_Victory] = new UIScreenVictory();
    m_states[State_GameOver] = new UIScreenGameOver();

    m_currentState = State_HUD;
}


void UIManager::setState(UIState state)
{
    m_currentState = state;
}

UIScreen* UIManager::getCurrentScreen()
{
    return m_states[m_currentState];
}

void UIManager::update(float delta)
{
    if (m_states[m_currentState])
        m_states[m_currentState]->update(delta);
}

void UIManager::render(sf::RenderWindow& window)
{
    if (m_states[m_currentState])
        m_states[m_currentState]->render(window);
}