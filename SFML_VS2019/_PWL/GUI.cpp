#include    <functional>           // Para std::function
#include    "GUI.hpp" 
#include    <iostream>

#define fontAddress "../Fonts/arial.ttf"

GUI::Txt::Txt() {
    loadFont(fontAddress);
}

bool GUI::Txt::loadFont(const std::string& fontPath) {
    if (font.loadFromFile(fontPath)) {
        text.setFont(font);
        fontLoaded = true;
        return true;
    }
    return false;
}

void GUI::Txt::setText(const std::string& str) {
    if (!fontLoaded) {
        throw std::runtime_error("No se ha cargado ninguna fuente");
    }
    text.setString(str);
}

void GUI::Txt::setCharacterSize(unsigned int size) {
    text.setCharacterSize(size);
}

void GUI::Txt::setPosition(float x, float y) {
    text.setPosition(x, y);
}

void GUI::Txt::setRotationAngle(float RotationAngle) {
    text.setRotation(-1 * RotationAngle);
}

void GUI::Txt::setSize(unsigned int size) {
    text.setCharacterSize(size);
}

sf::Vector2f GUI::Txt::getBounds() {
    sf::FloatRect bounds = text.getLocalBounds();
    return sf::Vector2f(bounds.width, bounds.height);
}

void GUI::Txt::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!fontLoaded) {
        throw std::runtime_error("Intentando dibujar sin fuente cargada");
    }
    target.draw(text, states);
}

/****************************************************************************************************************************/
 
GUI::Btn::Btn() {  
    setSize(100, 12);       // Tamaño predeterminado
    setColorsOnOff(sf::Color(85, 85, 85), sf::Color(0, 170, 170));
    _BtnBox.setFillColor(inactiveColor);
}

void GUI::Btn::setPosition(float x, float y) {
    _BtnBox.setPosition(x, y);
    _TextBox.setPosition(
        x + (_BtnBox.getGlobalBounds().width  - _TextBox.getBounds().x) * .5f,
        y + (_BtnBox.getGlobalBounds().height - _TextBox.getBounds().y) * .3f
    );

}

void GUI::Btn::setRotationAngle(float angle) {
    _BtnBox.setRotation(angle);
    _TextBox.setRotationAngle(angle);
}

void GUI::Btn::setSize(float width, float height) {
    _BtnBox.setSize({ width, height });
}

void GUI::Btn::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (event.type == sf::Event::MouseButtonPressed) {
        if (_BtnBox.getGlobalBounds().contains(mousePos)) {
            isPressed = true;
            _BtnBox.setFillColor(activeColor);
            if (callback) {
                callback();
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        isPressed = false;
        _BtnBox.setFillColor(inactiveColor);
    }
}

void GUI::Btn::setCallback(std::function<void()> callback) {
    this->callback = callback;
}

bool GUI::Btn::getState() const {
    return isPressed;
}

void GUI::Btn::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_BtnBox, states);
    target.draw(_TextBox, states);
}

void GUI::Btn::setText(const std::string& Text) {
    _TextBox.setText(Text);
    _TextBox.setCharacterSize(20);

}

void GUI::Btn::setColorsOnOff(sf::Color onColor, sf::Color offColor) {
    activeColor = onColor;
    inactiveColor = offColor;
}
 



GUI::Graph::Graph(float Posx, float Posy, float Width, float Height, std::string x_AxisName, std::string y_AxisName, unsigned int x_Max, int y_Min, int y_Max, bool Grid) :
    xMax(x_Max), yMin(y_Min), yMax(y_Max), grid(Grid) {

    setPosnSize(Posx, Posy, Width, Height);
    setAxisNameSize(x_AxisName, y_AxisName, 20);
    // Configuramos el tipo de linea 
    linesFuncToDraw.setPrimitiveType(sf::LineStrip);
    
    background.setFillColor(sf::Color(10, 10, 10));  // Blanco opaco



}


void GUI::Graph::setPosnSize(float Posx, float Posy, float Width, float Height){

    // Configurar el fondo (área Graph)
    background.setSize(sf::Vector2f(Width - 50, Height - 50));
    background.setPosition(Posx + 50, Posy);
    //background.setFillColor(sf::Color::Black);
    
    // yAxisName.setColor(sf::Color::White);
    yAxisName.setPosition(Posx + (Width / 3), Posy + Height - 30);

    // xAxisName.setColor(sf::Color::White);
    xAxisName.setPosition(Posx, Posy + (2 * Height / 3));
    xAxisName.setRotationAngle(90);
     

}

void GUI::Graph::setAxisNameSize(std::string & x_AxisName, std::string & y_AxisName, unsigned int Size) {
    yAxisName.setText(x_AxisName);
    yAxisName.setSize(20);

    // Configuración del nombre del eje Y
    xAxisName.setText(y_AxisName);
    xAxisName.setSize(20);
    // Configuración del nombre del eje X
}

void GUI::Graph::setXmax(unsigned int x_Max) {
    setLimits(x_Max,yMin,yMax);
}

void GUI::Graph::setyMin(int y_Min) {
    setLimits(xMax, y_Min, yMax);
}

void GUI::Graph::setyMax(unsigned int y_Max){
    setLimits(xMax, yMin, y_Max);
}

void GUI::Graph::setTextureFromFile(const std::string& filename) {
    if (!texture.loadFromFile(filename)) {
        std::cerr << "No se pudo cargar la textura\n";
    }
    else {
        background.setFillColor(sf::Color(100, 100, 100));
        background.setTexture(&texture);
    }
}


void GUI::Graph::setLimits(unsigned int x_Max, int y_Min, unsigned int y_Max) {
    
    xMax = x_Max;
    yMin = y_Min;
    yMax = y_Max;


    // Variables de coordenada x , y temporales 
    float xAdapted = 0.f;
    float yAdapted = 0.f;

    int sizeYAxis = 0;
    if (yMin < 0) {
        sizeYAxis = -1 * yMin + yMax;
    }
    else  sizeYAxis = yMax - yMin;
    // Recorremos la funcion para definir las lineas y puntos

    // Eliminar antuguos puntos para crear en la nueva coordenada
    for (const auto& dotXy : Dotsxyi) {
        if (!dotXy->Delete)        dotXy->Delete = true;
    }
    deleteDot();


    for (int i = 0;i < 2;i++) {
        // Almacenamos temporalmente para evitar recalcular
        xAdapted = (i == 0 ? 0 : xMax * (background.getSize().x / xMax)) + background.getPosition().x;
        yAdapted = (background.getPosition().y + background.getSize().y - ((-background.getSize().y * yMin) / sizeYAxis));

        yAdapted = ( yMin <= 0 ? 0 : yMin * (-background.getSize().y / sizeYAxis)) + background.getPosition().y + background.getSize().y - ((-background.getSize().y * yMin) / sizeYAxis);

        addDotxy(Dotsxyi.size(), xAdapted, yAdapted);         
      
    }
     
}



void GUI::Graph::setGridStatus(bool DoVisible) {
    grid = DoVisible;
}


std::vector<sf::Vector2f> GUI::Graph::getxyList() {
    std::vector<sf::Vector2f> coordenadas;
    coordenadas.reserve(Dotsxyi.size()); // Optimización de memoria
    float sizeYAxis;
    if (yMin < 0) {
        sizeYAxis = -1 * yMin + yMax;
    }
    else  sizeYAxis = yMax + yMin;

    for (const auto& objeto : Dotsxyi) {
        const auto& pos = objeto->getPos();
        coordenadas.emplace_back(
            (pos.x - background.getPosition().x) / (background.getSize().x / xMax),
            (pos.y + ((-background.getSize().y * yMin) / sizeYAxis) - background.getSize().y - background.getPosition().y) / (-background.getSize().y / sizeYAxis)
        );
    }
    return coordenadas;
}

  

bool GUI::Graph::getGridStatus() {
    return grid;
}

void GUI::Graph::addDotxy(unsigned int inPos, float _x_, float _y_) {
    if (inPos > Dotsxyi.size()) {
        throw std::out_of_range("Posición fuera de rango");
    }

    auto it = Dotsxyi.begin();
    std::advance(it, inPos);

    // Inserta el nuevo elemento y obtiene su iterador
    auto inserted_it = Dotsxyi.insert(it, new GUI::Uxy());

    // Modifica directamente el elemento insertado
    (*inserted_it)->setPos(_x_, _y_);
}

void GUI::Graph::deleteDot() {
    // Buscar el primer punto marcado para eliminación
    auto it = std::find_if(Dotsxyi.begin(), Dotsxyi.end(),
        [](const auto& dot) { return dot->Delete; });

    if (it != Dotsxyi.end()) {
        std::cout << "** Se elimino UN PUNTO **\n";
        delete* it;
        Dotsxyi.erase(it);
    }
}
 
void GUI::Graph::updateLine() {

    linesFuncToDraw.clear();
      
    for (auto& a : Dotsxyi) {
        linesFuncToDraw.append(sf::Vertex(a->getPos(), sf::Color::Green));
    
    } 


}

// Manejo de eventos
void GUI::Graph::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (background.getGlobalBounds().contains(mousePos)) {

        if (event.type == sf::Event::MouseButtonPressed) {

            // Agregar vertice - Anticlic
            if (event.mouseButton.button == sf::Mouse::Right) {
                 
                
                toCreate = true;
                for (auto& a : Dotsxyi) {
                    // condición ? valor_si_verdadero : valor_si_falso;
                    if (a->getBounds().contains(mousePos)) {
                        toCreate = false;
                        std::cout << "NO se creo :c " << "\n";
                    }
                }
                if (toCreate) {
                    float lastx{ 0.f };
                    auto current_pos = 0u;
                    for (auto it = Dotsxyi.begin(); it != Dotsxyi.end();) {
                        const auto& a = *it;
                        const auto siguiente_it = std::next(it);

                        if (siguiente_it == Dotsxyi.end()) {
                            break;
                        }

                        GUI::Uxy* siguiente_elemento = *siguiente_it;

                        if ((mousePos.x > lastx) && (mousePos.x < siguiente_elemento->getPos().x)) {
                            addDotxy(current_pos + 1, mousePos.x, mousePos.y);
                            break;
                        }

                        lastx = a->getPos().x;
                        ++current_pos;
                        ++it;
                    }
                    std::cout << "Se creo un punto: " << "\n";
                }

                
            }

            // Click
            if (event.mouseButton.button == sf::Mouse::Left) {
                system("cls");
                std::cout << "Cantidad de Puntos: " << Dotsxyi.size() << "\n";
                std::cout << " xmax = " << xMax << "\nymin: " << yMin << "\nymax: " << yMax << "\n";
                
            }

        }
        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                // std::cout << "Dejo de mover\n";
            }
        }

        // Zoom centrado en el cursor
        if (event.type == sf::Event::MouseWheelScrolled) {
            /*
            */
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                float factor = (event.mouseWheelScroll.delta > 0) ? 1.1f : 1.f / 1.1f;
                std::string dc = (event.mouseWheelScroll.delta > 0) ? "Acercamiento\n" : "Alejamiento\n";
                std::cout << dc;

                // Obtener la posición del mouse en coordenadas "mundo" (antes de la transformación)
                // sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseWheelScroll.x, event.mouseWheelScroll.y));
                // Actualizar offset para mantener fijo el punto bajo el cursor:
                // La nueva posición del mouse debería ser igual a la antigua, de modo que:
                // newOffset = oldOffset + (1 - factor)*mousePos
                offset += (1.f - factor) * mousePos;
                // scale *= factor;
            }
        }


        // if(!background.getGlobalBounds().contains(mousePos))
        for (auto& a : Dotsxyi) {
            if (!background.getGlobalBounds().contains(a->getPos())) a->moving = false;
            a->handleEvent(event, window);
        }

    }
}

void GUI::Graph::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    auto numLabel = std::make_unique <GUI::Txt>();
    auto lines = std::make_unique <sf::VertexArray>(sf::Lines);
    
    // HORIZONTALES

    int sizeYAxis = 0;
    if (yMin < 0) {
        sizeYAxis = -1 * yMin + yMax;
    }
    else  sizeYAxis = yMax - yMin;
    // std::cerr << sizeYAxis<<"\n";
    float sizeGrid = background.getSize().y / sizeYAxis;
    
    int tmpl = 0;

    // Grid
    for (int valy = 0; valy <= sizeYAxis; valy++) {
        // Lineas Horizontales 
        lines->append(sf::Vertex(sf::Vector2f(background.getPosition().x - 5,                  // x inicial
            background.getPosition().y + sizeGrid * valy), sf::Color(150, 150, 150)));          // y inicial
        lines->append(sf::Vertex(sf::Vector2f(background.getPosition().x + (grid ? background.getSize().x : 0), // x final
            background.getPosition().y + sizeGrid * valy), sf::Color(150, 150, 150)));    // Coordenadas finales  x , y 

        // Numeros por linea    

        tmpl = yMax - valy;
       
        numLabel->setText(std::to_string(tmpl));
        numLabel->setSize(12);
        // numLabel->setColor(sf::Color::Black);
        numLabel->setPosition(background.getPosition().x - 20, background.getPosition().y - 10 + sizeGrid * valy);
        numLabel->setRotationAngle(0);
        target.draw(*numLabel, states);

    }  // condición ? valor_si_verdadero : valor_si_falso;

    // VERTICALES
    sizeGrid = background.getSize().x / xMax;
    for (int valx = 0; valx <= xMax; valx++) {
        lines->append(sf::Vertex(sf::Vector2f(background.getPosition().x + sizeGrid * valx,                                             // x inicial
            (grid ? background.getPosition().y : (background.getPosition().y + background.getSize().y))), sf::Color(150, 150, 150)));   // y inicial
        lines->append(sf::Vertex(sf::Vector2f(background.getPosition().x + sizeGrid * valx,                                             // x final
            background.getPosition().y + background.getSize().y + 5), sf::Color(150, 150, 150)));                                       // y final

        // Numeros por linea
        numLabel->setText(std::to_string(valx));
        numLabel->setSize(12);
        // numLabel->setColor(sf::Color::Black);
        numLabel->setPosition(background.getPosition().x - 5 + sizeGrid * valx, background.getPosition().y + background.getSize().y + 5);
        numLabel->setRotationAngle(0);
        target.draw(*numLabel, states);

    }

    // Dibujar todo
    target.draw(xAxisName);
    target.draw(yAxisName);
    target.draw(background, states);
    target.draw(*lines);
     
    target.draw(linesFuncToDraw);

    for (const auto& dotXy : Dotsxyi) target.draw(*dotXy);
     
}

 
GUI::Uxy::Uxy() {    
    moving = false;
    dotXY.setRadius(5);
    dotXY.setOrigin(5, 5);
    dotXY.setFillColor(sf::Color::Transparent);
    dotXY.setOutlineThickness(1);
    dotXY.setOutlineColor(sf::Color::White);
}

void GUI::Uxy::setPos(float x, float y) {
    dotXY.setPosition(x, y);
}
 

 

sf::Vector2f GUI::Uxy::getPos() {
    return  dotXY.getPosition();
}

void GUI::Uxy::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {

    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (moving)         dotXY.setPosition(mousePos);        

    if (event.type == sf::Event::MouseButtonPressed) {
        if (dotXY.getGlobalBounds().contains(mousePos)) {
            if (event.mouseButton.button == sf::Mouse::Middle) {
                if (!Delete)        Delete = true;
            }

            moving = true;
            
        }

    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        moving = false;
        
    }
    
}

sf::FloatRect GUI::Uxy::getBounds(){
    return dotXY.getGlobalBounds();
}

void GUI::Uxy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    //std::cout << "Se esta dibujando un punto en __ " << dotXY.getPosition().x << " , " << dotXY.getPosition().y <<" \n";
    target.draw(dotXY);
}
  



// Constructor



// Constructor
GUI::TextBox::TextBox(float x, float y, float width, float height, bool numbersOnly)
    : isActive(false), onlyNumbers(numbersOnly), cursorPos(0), cursorVisible(true)
{
    box.setSize(sf::Vector2f(width, height));
    box.setPosition(x, y);
    box.setFillColor(sf::Color::White);
    box.setOutlineThickness(2);
    box.setOutlineColor(sf::Color::Black);

    if (!font.loadFromFile(fontAddress)) {
        std::cerr << "Error: No se pudo cargar la fuente.\n";
    }

    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x + 5, y + 5);

    cursor.setSize(sf::Vector2f(2, text.getCharacterSize()));
    cursor.setFillColor(sf::Color::Black);
    cursor.setPosition(text.getPosition().x, text.getPosition().y);
}

// Dibuja el cuadro de texto y el cursor
void GUI::TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(box, states);
    target.draw(text, states);
    if (isActive && cursorVisible) {
        target.draw(cursor, states);
    }
}

// Manejo de eventos
void GUI::TextBox::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        isActive = box.getGlobalBounds().contains(mousePos);

        box.setOutlineColor(isActive ? sf::Color::Blue : sf::Color::Black);
        if (isActive) cursorTimer.restart();
    }

    if (isActive) {
        // Entrada de texto
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 8) { // Backspace
                if (cursorPos > 0) {
                    inputString.erase(cursorPos - 1, 1);
                    cursorPos--;
                }
            }
            else if (event.text.unicode < 128) {
                char enteredChar = static_cast<char>(event.text.unicode);

                if (onlyNumbers) {
                    if (std::isdigit(enteredChar) || enteredChar == '.' || enteredChar == '-') {
                        inputString.insert(cursorPos, 1, enteredChar);
                        cursorPos++;
                    }
                }
                else {
                    inputString.insert(cursorPos, 1, enteredChar);
                    cursorPos++;
                }
            }

            text.setString(inputString);
        }

        // Movimiento del cursor con flechas y Enter
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Left && cursorPos > 0) {
                cursorPos--;
            }
            if (event.key.code == sf::Keyboard::Right && cursorPos < inputString.size()) {
                cursorPos++;
            }

            // --- Nuevo: Detectar Enter ---
            if (event.key.code == sf::Keyboard::Enter) {
                // Llamar a la función callback si está configurada
                if (onEnterCallback) {
                    onEnterCallback(inputString);
                }
                isActive = false;
                box.setOutlineColor(sf::Color::Black);
            }
        }

        // Actualizar la posición del cursor
        float cursorOffset = text.findCharacterPos(cursorPos).x;
        cursor.setPosition(cursorOffset, text.getPosition().y);
    }
}

// Alternar visibilidad del cursor (parpadeo)
void GUI::TextBox::updateCursor() {
    if (cursorTimer.getElapsedTime().asSeconds() > 0.5f) {
        cursorVisible = !cursorVisible;
        cursorTimer.restart();
    }
}

// Devuelve el texto ingresado (string)
std::string GUI::TextBox::getText() const {
    return inputString;
}

// Devuelve el texto como número flotante
float GUI::TextBox::getFloat() const {
    try {
        return std::stof(inputString);
    }
    catch (...) {
        return 0.0f;
    }
}

// Configuración de colores y fuente
void GUI::TextBox::setFont(const sf::Font& font) {
    this->font = font;
    text.setFont(this->font);
}

void GUI::TextBox::setTextColor(const sf::Color& color) {
    text.setFillColor(color);
}

void GUI::TextBox::setBoxColor(const sf::Color& color) {
    box.setFillColor(color);
}

void GUI::TextBox::setActiveColor(const sf::Color& color) {
    if (isActive) {
        box.setOutlineColor(color);
    }
}

// --- Nuevo: Asignar la función callback para Enter ---
void GUI::TextBox::setOnEnterCallback(const std::function<void(const std::string&)>& callback) {
    onEnterCallback = callback;
}


  //void GUI::TextBox::setOnEnterPressed(std::function<void()> callback) {
//    enterCallback = std::move(callback);
//}
