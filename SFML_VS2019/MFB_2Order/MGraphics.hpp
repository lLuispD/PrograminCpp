#pragma	once 
#include	<SFML/Graphics.hpp>
#include    <functional>           // Para std::function
  
namespace fResponse {
    void Bessel();
    void Butterworth();
    void Chebyshev();

}


namespace GUI {


    class Txt : public sf::Drawable {
    public:
        // Constructor vacío
        Txt();

        // Carga la fuente desde un archivo
        bool loadFont(const std::string& fontPath);

        // Establece el texto a mostrar
        void setText(const std::string& str);

        // Modifica el tamaño del texto
        void setCharacterSize(unsigned int size);

        // Establece la posición del texto
        void setPosition(float x, float y);

        // Establece la rotacion del texto
        void setRotationAngle(float RotationAngle);

        void setSize(unsigned int size);

        sf::Vector2f getBounds();
        // Implementación obligatoria del método draw
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        sf::Font font;           // La fuente del texto
        sf::Text text;           // El texto renderizable
        bool fontLoaded = false;         // Indica si la fuente se cargó correctamente

    };

    class Btn : public sf::Drawable {
    public:
        Btn();
        void setPosition(float x, float y);
        void setColorsOnOff(sf::Color onColor, sf::Color offColor);
        void setText(const std::string& Text);
        void setCallback(std::function<void()> callback);
        void setRotationAngle(float angle);
        void setSize(float width, float height);

        void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
        bool getState() const;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        GUI::Txt _TextBox;              // Texto de boton
        sf::RectangleShape _BtnBox;

        sf::Color activeColor;
        sf::Color inactiveColor;
        sf::Vector2f sizeBox;
        bool isPressed = false;
        std::function<void()> callback;

    };

    class TextBox : public sf::Drawable {
    private:
        sf::RectangleShape box;
        sf::Text text;
        sf::Font font;
        bool isActive;
        bool onlyNumbers;
        std::string inputString;
        int cursorPos;

        sf::RectangleShape cursor;
        sf::Clock cursorTimer;
        bool cursorVisible;

        std::function<void(const std::string&)> onEnterCallback;

    protected:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    public:
        TextBox(float x, float y, float width, float height, bool numbersOnly = false);

        void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
        void updateCursor();

        std::string getText() const;
        float getFloat() const;

        void setFont(const sf::Font& font);
        void setTextColor(const sf::Color& color);
        void setBoxColor(const sf::Color& color);
        void setActiveColor(const sf::Color& color);

        // --- Nuevo: método para registrar la función que se llamará al presionar Enter ---
        void setOnEnterCallback(const std::function<void(const std::string&)>& callback);
    };

    class Dropdown : public sf::Drawable {
    public:
        Dropdown(std::vector<std::string> optionsList, float posx, float posy, float height, float width);
        std::string getSelection() const; // Ahora es const
        void handleEvent(const sf::Event& event);

    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        sf::Font font;
        sf::Text textBox;
        sf::RectangleShape dropdownBox;
        std::vector<std::string> optionsList;
        std::vector<sf::RectangleShape> optionsBoxes;
        std::vector<sf::Text> optionsTexts;
        float posx, posy, height, width;
        bool isOpen = false;

        std::string selectedOption; // Almacena la opción seleccionada
    };

}

