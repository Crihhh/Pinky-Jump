#include <UI/UIScreen.h>

UIScreen::~UIScreen()
{
    for (auto w : m_widgets)
        delete w;
}

void UIScreen::update(float deltaMiliseconds)
{
    for (auto w : m_widgets)
        w->update(deltaMiliseconds);
}

void UIScreen::render(sf::RenderWindow& window)
{
    for (auto w : m_widgets)
        w->render(window);
}