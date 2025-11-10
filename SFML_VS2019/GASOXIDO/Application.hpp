#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"


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

	// std::vector<Collider*> m_Colliders;


	// void CheckCollision();
	void UpdateBox();

	void Update();
	void Render();

	void HandleEvents();

	void InitWindow();
};
