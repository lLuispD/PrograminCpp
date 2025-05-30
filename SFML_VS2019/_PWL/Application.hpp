#pragma once

#include <SFML/Graphics.hpp>
#include "GUI.hpp"

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
	void LoadContent();
	void HandleEvents();
	void InitWindow();

	/* Componentes de aplicacion */

	std::vector<GUI::Txt*>		p_Texts;
	std::vector<GUI::Btn*>		p_Btns;
	std::vector<GUI::TextBox*>	p_TxtBox;
	std::vector<GUI::Graph*>	p_plot;
	 

};
