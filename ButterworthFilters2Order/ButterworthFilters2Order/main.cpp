  /* Este programa sirve para diseniar filtros Butterworth de segundo orden
* Se deben estableces en orden
* Ganancia
* Frecuencia de corte
* Capacitores
* Resistencias
* La ultima resistencia se define auntomaticamente
*/


 
#include "UI.hpp"
#include "Filters.hpp"
#include <memory> // Para std::unique_ptr
#define HEIGHT_WINDOW 1510
#define WIDTH_WINDOW  850

int main(void) {

    sf::RenderWindow window(sf::VideoMode(HEIGHT_WINDOW, WIDTH_WINDOW), "Diseño de filtros");

    // Usamos punteros inteligentes para evitar fugas de memoria
   
    // Seleccion Filtro
    auto drpdw_listFilters = std::make_unique<UI::Dropdown>(FilterList, 340, (WIDTH_WINDOW / 13) * 1, 30, 150);

    // Ganancia
    auto txt_Gain = std::make_unique<UI::Texto>("Ganancia (k): ", 65, (WIDTH_WINDOW / 13)*2, 25);
    auto txtBx_Gain = std::make_unique<UI::TextBox>(110, (WIDTH_WINDOW / 13) * 2, 70, 30, true);
    
    // Factor de Calidad 
    auto txt_QualityFactor = std::make_unique<UI::Texto>("Factor de calidad: ", 65, (WIDTH_WINDOW / 13) * 3, 25);
    auto txtBx_QualityFactor = std::make_unique<UI::TextBox>(110, (WIDTH_WINDOW / 13)*3, 70, 30, true);
    
    // Frecuencia de corte 
    auto txt_Fc = std::make_unique<UI::Texto>("Frecuencia de corte (Fc): ", 65, (WIDTH_WINDOW / 13)* 4 , 25);
    auto txtBx_Fc = std::make_unique<UI::TextBox>(110, (WIDTH_WINDOW / 13)*4, 70, 30, true);
    auto drpdw_Fc = std::make_unique<UI::Dropdown>(FrecMultList, 300, (WIDTH_WINDOW / 13)*4, 30, 50);
    

    // Btn_Calcular 
    auto btn_Calculate = std::make_unique<UI::Button>(400, (WIDTH_WINDOW / 13)*5, 50, 100, "Calcular", sf::Color(22, 160, 141), sf::Color(32, 200, 228));
       

    // RA 
    auto txt_RA = std::make_unique<UI::Texto>("RA: ", 65, (WIDTH_WINDOW / 13)*6, 25);
    auto txtBx_RA = std::make_unique<UI::TextBox>(110, (WIDTH_WINDOW / 13)*6, 70, 30, true);
    auto drpdw_RA = std::make_unique<UI::Dropdown>(ResMultList, 200, (WIDTH_WINDOW / 13)*6, 30, 40);
    // RB 
    auto txt_RB = std::make_unique<UI::Texto>("RB: ", 65, (WIDTH_WINDOW / 13)*7, 25);
    auto txtBx_RB = std::make_unique<UI::TextBox>(110, (WIDTH_WINDOW / 13)*7, 70, 30, true);
    auto drpdw_RB = std::make_unique<UI::Dropdown>(ResMultList, 200, (WIDTH_WINDOW / 13)*7, 30, 40);
    // C1  
    auto txt_C1 = std::make_unique<UI::Texto>("C1: ", 65, (WIDTH_WINDOW / 13)*8, 25);
    auto txtBx_C1 = std::make_unique<UI::TextBox>(110, (WIDTH_WINDOW / 13)*8, 70, 30, true);
    auto drpdw_C1 = std::make_unique<UI::Dropdown>(CapMultList, 200, (WIDTH_WINDOW / 13)*8, 30, 40);
    // C2 
    auto txt_C2 = std::make_unique<UI::Texto>("C2: ", 65, (WIDTH_WINDOW / 13)*9, 25);
    auto txtBx_C2 = std::make_unique<UI::TextBox>(110, (WIDTH_WINDOW / 13)*9, 70, 30, true);
    auto drpdw_C2 = std::make_unique<UI::Dropdown>(CapMultList, 200, (WIDTH_WINDOW / 13)*9, 30, 40);

   // R1 
    auto txt_R1 = std::make_unique<UI::Texto>("R1: ", 65, (WIDTH_WINDOW / 13)*10, 25);
    auto txtBx_R1 = std::make_unique<UI::TextBox>(110, (WIDTH_WINDOW / 13)*10, 70, 30, true);
    auto drpdw_R1 = std::make_unique<UI::Dropdown>(ResMultList, 200, (WIDTH_WINDOW / 13) * 10, 30, 40);
    // R2 
    auto txt_R2 = std::make_unique<UI::Texto>("R2: ", 65, (WIDTH_WINDOW / 13) * 11, 25);
    auto txtBx_R2 = std::make_unique<UI::TextBox>(110, (WIDTH_WINDOW / 13)*11, 70, 30, true);
    auto drpdw_R2 = std::make_unique<UI::Dropdown>(ResMultList,200, (WIDTH_WINDOW / 13)*11, 30, 40);

    // Aqui se dan valores por primera vez a las resistencias y capacitores
    btn_Calculate->setCallback([&]() { 
        // Valores por defecto en caso ser cero (TextBox vacio)
        if (std::fabs(txtBx_Gain->getFloat()) < 1e-6f)  txtBx_Gain->setText("1");
        if (std::fabs(txtBx_Fc->getFloat()) < 1e-6f)  txtBx_Fc->setText("1");
        if (std::fabs(txtBx_QualityFactor->getFloat()) < 1e-6f)  txtBx_QualityFactor->setText("1");
        if (std::fabs(txtBx_RA->getFloat()) < 1e-6f)  txtBx_RA->setText("1");



        txtBx_RB->setText(std::to_string( (txtBx_Gain->getFloat() - 1.0f) * txtBx_RA->getFloat() ));
        //txtBx_Gain->setText("10") ? txtBx_Gain->getFloat == 0;
        std::cout << "Ganancia: " << txtBx_Gain->getFloat() << " \n";
        std::cout << "RA: " << txtBx_RA->getFloat() << "\n";
        std::cout << "RB: " <<txtBx_RB->getFloat() << "\n";
        std::cout << "Factor de calidad: " << txtBx_QualityFactor->getFloat() << "\n";
        std::cout << "Frecuencia de corte: " << txtBx_Fc->getFloat() << "\n";
        
    });

    txtBx_Gain->setOnEnterPressed([&]() {

        std::cout << "Se presionó Enter. Texto actual: " << txtBx_Gain->getFloat() << std::endl;
        txtBx_RA->setText("3.33");
    }); 


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            txtBx_Gain->handleEvent(event,window);
            txtBx_QualityFactor->handleEvent(event,window);
            txtBx_Fc->handleEvent(event,window);
            drpdw_Fc->handleEvent(event);
            btn_Calculate->handleEvent(event,window);
            txtBx_RA->handleEvent(event,window);
            drpdw_RA->handleEvent(event);
            txtBx_RB->handleEvent(event, window);
            drpdw_RB->handleEvent(event);
            txtBx_C1->handleEvent(event, window);
            drpdw_C1->handleEvent(event);
            txtBx_C2->handleEvent(event, window);
            drpdw_C2->handleEvent(event);
            txtBx_R1->handleEvent(event, window);
            drpdw_R1->handleEvent(event);
            txtBx_R2->handleEvent(event,window);
            drpdw_R2->handleEvent(event);

        }

        // Update cursosrs        
        txtBx_Gain->updateCursor();
        txtBx_QualityFactor->updateCursor();
        txtBx_Fc->updateCursor();
        txtBx_RA->updateCursor();
        txtBx_RB->updateCursor();
        txtBx_C1->updateCursor();
        txtBx_C2->updateCursor();
        txtBx_R1->updateCursor();
        txtBx_R2->updateCursor();

        window.clear(sf::Color::White);
        // Lista Filtros
        window.draw(*drpdw_listFilters);
        // Ganancia
        window.draw(*txt_Gain);
        window.draw(*txtBx_Gain);
        // Factor de Calidad
        window.draw(*txt_QualityFactor);
        window.draw(*txtBx_QualityFactor);
        // Frecuencia de corte
        window.draw(*txt_Fc);
        window.draw(*txtBx_Fc);
        window.draw(*drpdw_Fc);
        // Boton
        window.draw(*btn_Calculate);
        // RA
        window.draw(*txt_RA);
        window.draw(*txtBx_RA);
        window.draw(*drpdw_RA);
        // RB
        window.draw(*txt_RB);
        window.draw(*txtBx_RB);
        window.draw(*drpdw_RB);
        // C1
        window.draw(*txt_C1);
        window.draw(*txtBx_C1);
        window.draw(*drpdw_C1);
        // C2
        window.draw(*txt_C2);
        window.draw(*txtBx_C2);
        window.draw(*drpdw_C2);
        // R1
        window.draw(*txt_R1);
        window.draw(*txtBx_R1);
        window.draw(*drpdw_R1);
        // R2 
        window.draw(*txt_R2);
        window.draw(*txtBx_R2);
        window.draw(*drpdw_R2);

        window.display();
    }

    return 0;
}

              
        