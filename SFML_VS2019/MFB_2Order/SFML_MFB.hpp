#pragma once

#include	"SFML/Graphics/RenderWindow.hpp"
#include	"SFML/Window/Event.hpp"
#include	"MDFLogic.hpp"
#include	"MGraphics.hpp"


class Application {
public:
	Application();
	~Application();

	void Run();

	static Application* Instance;
	static float		DT;

	sf::RenderWindow Window;
	sf::Event		 Event;

private:
	sf::Clock m_dtClock;

	void Update();
	void Render();
	void HandleEvents();
	void InitWindow();
	void LoadContent();
	 
	/* Componentes de aplicacion */

	std::vector<GUI::Txt*>		p_Texts;
	std::vector<GUI::Btn*>		p_Btns;
	std::vector<GUI::TextBox*>	p_TxtBox;
	std::vector<GUI::Dropdown*>	p_DrpDwn;

 
};
