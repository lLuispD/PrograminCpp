#include "application.hpp"

#define WINDOW_WIDTH	1080
#define WINDOW_HEIGHT	620


Application* Application::Instance = nullptr;
float		 Application::DT = 0.0f;

const float& dt = Application::DT;



Application::Application() {
	InitWindow();


}

Application::~Application() {
	// for (auto& c : m_Colliders)		delete c;

}

void Application::Run() {
	m_dtClock.restart();

	while (Window.isOpen()) {
		HandleEvents();
		Update();

		Window.clear(sf::Color(13, 17, 31));
		Render();
		Window.display();

		DT = m_dtClock.restart().asSeconds();
	}
}

void Application::UpdateBox() {
	constexpr float smoothness = 16.0f;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

	}

}

void Application::Update() {
	UpdateBox();
}

void Application::Render() {
	// for (auto& c : m_Colliders)		Window.draw(*c);

	// Window.draw(m_box);
}

void Application::HandleEvents() {
	while (Window.pollEvent(Event)) {
		if (Event.type == sf::Event::Closed) Window.close();

	}
}

void Application::InitWindow() {
	sf::VideoMode mode;
	mode.width = WINDOW_WIDTH;
	mode.height = WINDOW_HEIGHT;

	sf::ContextSettings settings;

	Window.create(mode, "blank window", sf::Style::Close, settings);
	Window.setFramerateLimit(144);
}

