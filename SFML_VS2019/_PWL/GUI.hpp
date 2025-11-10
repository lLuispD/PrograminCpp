#pragma	once 
#include	<SFML/Graphics.hpp>
#include    <functional>           // Para std::function


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
        void setColorsOnOff(sf::Color onColor , sf::Color offColor);
        void setText(const std::string & Text);
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

    class Uxy :public sf::Drawable {
    public:

        Uxy();
        void setPos(float x, float y); 
        sf::Vector2f getPos();
        void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
        // FUNCION

    protected:
        sf::FloatRect getBounds();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


    private:
        friend class Graph;
        sf::CircleShape dotXY;
        bool moving;
        bool Delete = 0;
         
    };

    class Graph : public sf::Drawable {

    public:
         
        // Constructor: x_AxisName, y_AxisName, xLim e yLim son los valores máximos en cada eje.
        Graph(float Posx, float Posy, float Width, float Height, std::string x_AxisName = "X", std::string y_AxisName = "Y", unsigned int x_Max = 10.f, int y_Min = -5.f , int y_Max = 10.f, bool Grid = true);

        // Set
        

        void setPosnSize(float Posx, float Posy, float Width, float Height);
        
        void setAxisNameSize(std::string & x_AxisName, std::string & y_AxisName, unsigned int Size);
        
        void setXmax(unsigned int x_Max);
        void setyMin(int y_Min);
        void setyMax(unsigned int y_Max);

        void setTextureFromFile(const std::string& filename);


        
        void setGridStatus(bool DoVisible);


        // void setFunction(std::vector<sf::Vector2f>& Points, sf::Color ColorDot = sf::Color::White, bool Conect = true, bool ShowDots = true, sf::Color ColorLines = sf::Color::Red);

        // Get

        std::vector<sf::Vector2f> getxyList();


        bool getGridStatus();

        void deleteDot();

        void updateLine();

        void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

        // FUNCION


    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        void addDotxy(unsigned int inPos, float _x_, float _y_);

        void setLimits(unsigned int x_Max, int y_Min, unsigned int y_Max);
        // Factor de escala
        // float scale;
        // Fondo, donde se graficara todo 
        sf::Texture texture;
        sf::RectangleShape background;   // Fondo del área de dibujo
        // EJES
        GUI::Txt xAxisName;             // Nombre del eje X
        GUI::Txt yAxisName;             // Nombre del eje Y

        bool grid;                     // Bandera para mostrar/ocultar cuadrícula

        // Limites de ejes
        unsigned int xMax;                    // Limite del eje X
        int yMin;                             // Inicio Y
        unsigned int yMax;                    // Limite del eje Y


        // FUNCION
       std::list<GUI::Uxy*> Dotsxyi;


        //std::vector<sf::Vector2f> functionDot;  // coordenadas 

        sf::VertexArray linesFuncToDraw;          // lineas funcion 
        bool toCreate = true;



        // Variables para zoom y pan
        sf::Vector2f offset;           // Desplazamiento (pan)
        bool dragging;                 // Indica si se está arrastrando
        sf::Vector2f lastMousePos;     // Última posición del mouse (para pan)




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




    std::string openFileDialog();

}





