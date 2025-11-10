#include "SFML_MFB.hpp"
#include <iostream>
#include <fstream>
// #include <>

#define WINDOW_WIDTH	1440		// 32 Upx
#define WINDOW_HEIGHT	810			// 18 Upx

#define			Upx		45


Application* Application::Instance = nullptr;
float		 Application::DT = 0.0f;

const float& dt = Application::DT;



Application::Application() {
	InitWindow();
	LoadContent();

}

Application::~Application() {

	
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



void Application::Update() {

}

void Application::Render() {

}

void Application::LoadContent() {

	// Bloque para Textos
	{
		GUI::Txt* a = new GUI::Txt;
		a->setText("min: ");
		a->setPosition(Upx, 3 * Upx);
		p_Texts.push_back(a);

		GUI::Txt* b = new GUI::Txt;
		b->setText(" V");
		b->setPosition(6 * Upx, 3 * Upx);
		p_Texts.push_back(b);

		GUI::Txt* c = new GUI::Txt;
		c->setText("max: ");
		c->setPosition(9 * Upx, 3 * Upx);
		p_Texts.push_back(c);

		GUI::Txt* d = new GUI::Txt;
		d->setText(" V");
		d->setPosition(14 * Upx, 3 * Upx);
		p_Texts.push_back(d);

		GUI::Txt* e = new GUI::Txt;
		e->setText("Lim: ");
		e->setPosition(17 * Upx, 3 * Upx);
		p_Texts.push_back(e);

		GUI::Txt* f = new GUI::Txt;
		f->setText(" ms");
		f->setPosition(22 * Upx, 3 * Upx);
		p_Texts.push_back(f);
	}
	// Aqui van los bloques de textos
	{
		GUI::TextBox* a = new GUI::TextBox(03 * Upx, 2 + 3 * Upx, 3 * Upx, Upx - 4, true);

		a->setOnEnterCallback([&](const std::string& textValue) {

			//a->setText("45.5");
			std::cout << "Text:" << textValue << "\n";


			////a->setText(a.);			
			//float x = a->getFloat();
			// p_plot[0]->setXmax();

			});

		p_TxtBox.push_back(a);

		GUI::TextBox* b = new GUI::TextBox(11 * Upx, 2 + 3 * Upx, 3 * Upx, Upx - 4, true);

		b->setOnEnterCallback([&](const std::string& textValue) {

			std::cout << "Text:" << textValue << "\n";



			});


		p_TxtBox.push_back(b);

		GUI::TextBox* c = new GUI::TextBox(19 * Upx, 2 + 3 * Upx, 3 * Upx, Upx - 4, true);

		c->setOnEnterCallback([&](const std::string& textValue) {

			std::cout << "Text:" << textValue << "\n";



			});

		p_TxtBox.push_back(c);

	}
	/*	Bloque para Botones	*/
	{
		GUI::Btn* a = new GUI::Btn;
		a->setText("Cargar fondo");
		a->setSize(3 * Upx, Upx);
		a->setPosition(Upx, Upx);
		a->setColorsOnOff(sf::Color(0, 170, 170), sf::Color(85, 85, 85));
		p_Btns.push_back(a);

		a->setCallback([&]() {


			// Reemplaza todas las barras invertida




			GUI::Btn* b = new GUI::Btn;
			b->setText("Exportar *.txt");
			b->setSize(3 * Upx, Upx);
			b->setPosition(28 * Upx, Upx);
			b->setColorsOnOff(sf::Color(85, 85, 85), sf::Color(0, 170, 170));


			p_Btns.push_back(b);

			});



	}

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
	Window.create(mode, "Diseño de PWL (*.txt)", sf::Style::Close, settings);
	Window.setFramerateLimit(144);
}


