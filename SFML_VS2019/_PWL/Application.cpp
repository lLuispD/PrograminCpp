#include "application.hpp"
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
	for (auto& Text : p_Texts)			delete Text;
	for (auto& Button : p_Btns)			delete Button;
	for (auto& TextBox : p_TxtBox)			delete TextBox;
	for (auto& Plot : p_plot)			delete Plot;

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
	for (auto& TextBox : p_TxtBox)			TextBox->updateCursor();
	for (auto& Button : p_plot)			Button->updateLine();
	for (auto& plotDot : p_plot)			plotDot->deleteDot();
}

void Application::Render() {
	for (auto& Text : p_Texts)			Window.draw(*Text);
	for (auto& Button : p_Btns)			Window.draw(*Button);
	for (auto& TextBox : p_TxtBox)			Window.draw(*TextBox);
	for (auto& Plot : p_plot)			Window.draw(*Plot);

}

void Application::LoadContent() {

	// Bloque para Textos
	{
		p_Texts.reserve(6);
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
			p_plot[0]->setyMin(p_TxtBox[0]->getFloat());

			////a->setText(a.);			
			//float x = a->getFloat();
			// p_plot[0]->setXmax();

			});

		p_TxtBox.push_back(a);

		GUI::TextBox* b = new GUI::TextBox(11 * Upx, 2 + 3 * Upx, 3 * Upx, Upx - 4, true);

		b->setOnEnterCallback([&](const std::string& textValue) {

			std::cout << "Text:" << textValue << "\n";
			p_plot[0]->setyMax(p_TxtBox[1]->getFloat());


			});


		p_TxtBox.push_back(b);

		GUI::TextBox* c = new GUI::TextBox(19 * Upx, 2 + 3 * Upx, 3 * Upx, Upx - 4, true);

		c->setOnEnterCallback([&](const std::string& textValue) {

			std::cout << "Text:" << textValue << "\n";

			p_plot[0]->setXmax(
				(std::stof(textValue) > 0) ? (p_TxtBox[2]->getFloat()) : (-1 * p_TxtBox[2]->getFloat())
			);


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

			std::string dir = GUI::openFileDialog();
			
			// Reemplaza todas las barras invertida
			
			

			// Reemplaza todas las barras invertidas
			std::replace(dir.begin(), dir.end(), '\\', '/');

			std::cerr << "Ruta corregida: " << dir << std::endl;


			p_plot[0]->setTextureFromFile( dir );
			p_plot[0]->setGridStatus(false);


			});


		GUI::Btn* b = new GUI::Btn;
		b->setText("Exportar *.txt");
		b->setSize(3 * Upx, Upx);
		b->setPosition(28 * Upx, Upx);
		b->setColorsOnOff(sf::Color(85, 85, 85), sf::Color(0, 170, 170));

		b->setCallback([&]() {
			std::cout << "se presiono el botm\n";
			// Generamos el aarchivo .txt con las coordenadas v t
			std::ofstream mytxt;
			mytxt.open("PWLsignal.txt", std::ios::out);
			if (mytxt.fail()) std::cout << "No se pudo abrir - Crear \n";
			else {
				auto coordenadas = p_plot[0]->getxyList();
				for (const auto& [x, y] : coordenadas) {
					std::cout << "x: " << x << ", y: " << y << std::endl;
					mytxt << x / 1000 /*entre mil pq son ms*/ << " " << y /*En voltios*/ << std::endl;
				}

			}

			mytxt.close();

			});

		p_Btns.push_back(b);

	}
	// Aqui se carga el grafico
	{


		GUI::Graph* u = new GUI::Graph(Upx, 5 * Upx, 30 * Upx, 12 * Upx, "Tiempo ms", "Voltaje V");

		p_plot.push_back(u);



	}


}


void Application::HandleEvents() {
	while (Window.pollEvent(Event)) {
		if (Event.type == sf::Event::Closed) Window.close();

		for (auto& c : p_Btns)		c->handleEvent(Event, Window);
		for (auto& a : p_TxtBox)	a->handleEvent(Event, Window);
		for (auto& a : p_plot)		a->handleEvent(Event, Window);
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


