  /* Este programa sirve para diseniar filtros Butterworth de segundo orden
* Se deben establecer en orden
* Ganancia
* Frecuencia de corte
* Capacitores
* Resistencias
* La ultima resistencia se define auntomaticamente
*/


 
#include "UI.hpp"
#include "Bode.hpp"
#include "Filters.hpp"
#include <memory> // Para std::unique_ptr
#define HEIGHT_WINDOW 1510
#define WIDTH_WINDOW  850

int main(void) {

    sf::RenderWindow window(sf::VideoMode(HEIGHT_WINDOW, WIDTH_WINDOW), "Diseño de filtros activos Sallen Key VCVS de 2° orden");

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


    sf::Font myFont;
    if (!myFont.loadFromFile("C:/Users/pdL/source/C++/ButterworthFilters2Order/Fonts/arial.ttf")) {
        // Manejar error
    }
    auto BodeG = std::make_unique<Bode>(200, 200, 800,1000);

    BodeG->setFont(myFont);
    // Definir una función de transferencia para un filtro pasa-bajos Butterworth.
    // La función toma una frecuencia (en Hz) y retorna un par:
    // {magnitud en dB, fase en grados}.
    //
    // Usamos la función de transferencia:
    // H(jω) = 1/sqrt(1 + (ω/ωc)^2)
    // con ωc = 2π * fc, donde elegimos fc = 1000 Hz.
    auto tf = [&](double freqHz) {
        double fc = 1000.0; // 1 kHz
        double wc = 2.0 * dataF::PI * fc;
        double w = 2.0 * dataF::PI * freqHz;
        double mag = 1.0 / std::sqrt(1.0 + (w / wc) * (w / wc));
        double magdB = 20.0 * std::log10(mag);
        double phaseDeg = -std::atan(w / wc) * (180.0 / dataF::PI);
        return std::make_pair(magdB, phaseDeg);
        };

    BodeG->setTransferFunction(tf);

    // Ajustar rango dB y fase
    BodeG->setRangesDBPhase(-80.0, 10.0, -180.0, 0.0);

    // Ajustar subdivisiones
    BodeG->setGridDivisions(9, 8, 6);

    // Calcular
    BodeG->updateDiagram();





    // SE DAN VALORES DE RESISTENCIAS Y CAPACITORES
    btn_Calculate->setCallback([&]() { 
        // Valores por defecto en caso ser cero; si no, se guardan los valores
        if (std::fabs(txtBx_Gain->getFloat()) < 1e-6f) {
            txtBx_Gain->setText(std::to_string(dataF::Gain));
        } else dataF::Gain = txtBx_Gain->getFloat();
        if (std::fabs(txtBx_Fc->getFloat()) < 1e-6f) {
            txtBx_Fc->setText(std::to_string(dataF::CutFrequency));
        } else dataF::CutFrequency = txtBx_Fc->getFloat();
        if (std::fabs(txtBx_QualityFactor->getFloat()) < 1e-6f) {
            txtBx_QualityFactor->setText(std::to_string(dataF::QualityFactor));
        } else dataF::QualityFactor = txtBx_QualityFactor->getFloat();
                        
        if (drpdw_listFilters->getSelection() == FilterList[0]) { 
            /* Filtro Paso bajo */
            

        }
        else if (drpdw_listFilters->getSelection() == FilterList[1]) {
            /* Filtro paso alto */ 
          
            dataF::CutFrequency = txtBx_Fc->getFloat();
            dataF::C1 = dataF::createCapacitance();
            dataF::C2 = dataF::C1;
            dataF::R1 = 1.f / (2.f * dataF::PI * dataF::CutFrequency * dataF::C1);
            dataF::R2 = dataF::R1;
            dataF::QualityFactor = txtBx_QualityFactor->getFloat();
            dataF::Gain = 3.f - (1.f / dataF::QualityFactor);
            dataF::RB = dataF::createResistance();
            dataF::RA = dataF::RB * (dataF::Gain - 1);

            system("cls");
            txtBx_C1->setText(std::to_string(dataF::C1));
            txtBx_C2->setText(std::to_string(dataF::C2));
            txtBx_R1->setText(std::to_string(dataF::R1));
            txtBx_R2->setText(std::to_string(dataF::R2));
            txtBx_RA->setText(std::to_string(dataF::RA));
            txtBx_RB->setText(std::to_string(dataF::RB));
            txtBx_Gain->setText(std::to_string(dataF::Gain));


        }   


        
        std::cout << "RA: " << txtBx_RA->getFloat() << " \n";
        std::cout << "RB: " << txtBx_RB->getFloat() << "\n";
        std::cout << "R1: " << txtBx_R1->getFloat() << " = " << dataF::R1 << "\n";
        std::cout << "R2: " << txtBx_R2->getFloat() << "= " << dataF::R2 << "\n";
        std::cout << "C1: " << txtBx_C1->getFloat() << "= " << dataF::C1 << "\n";
        std::cout << "C2: " << txtBx_C2->getFloat() << "= " << dataF::C2 << "\n";
        

    });

    txtBx_RA->setOnEnterPressed([&]() {
        dataF::RA = txtBx_RA->getFloat();
        dataF::RB = dataF::Gain / dataF::RA;
        txtBx_RB->setText(std::to_string(dataF::RB));
    }); 
    txtBx_C1->setOnEnterPressed([&]() {
        dataF::C1 = txtBx_RA->getFloat();
        dataF::C2 = dataF::C1;
        txtBx_C2->setText(std::to_string(dataF::C2));
    });

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            drpdw_listFilters->handleEvent(event);
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

        window.draw(*BodeG);

        window.display();
    }

    return 0;
}

              
        