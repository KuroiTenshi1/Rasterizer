#include <SFML/Graphics.hpp>

/// <summary>
/// Draw a one pixel width vertical line in the specified image.
/// </summary>
/// <param name="tex"></param>
/// <param name="x">Abscisse of the line  </param>
/// <param name="y1">Starting height of the line </param>
/// <param name="y2">Ending height of the line  </param>
/// <param name="c"></param>
void drawVerticalLine(sf::Image& img, int x, int y1, int y2, const sf::Color& c)
{
    // Todo
}


/// <summary>
/// Draw a empty or filled rectangle in the specified image
/// </summary>
/// <param name="img"></param>
/// <param name="origin">top left point of the rectangle </param>
/// <param name="size">width and height of the rectangle </param>
/// <param name="c"></param>
/// <param name="filled">if true rect will be filled with color </param>
void drawRect(sf::Image& img, const sf::Vector2i& origin, const sf::Vector2i& size, const sf::Color& c)
{
    // Todo
}


/// <summary>
///  The World map
/// >0 is a wall
/// </summary>
static const int g_mapWidth = 24;
static const int g_mapHeight = 24;

int g_worldMap[g_mapWidth][g_mapHeight] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


/// <summary>
/// Return a unnormalized vector perpendicular to the direction
/// </summary>
/// <param name="dir"></param>
/// <returns></returns>
inline sf::Vector2f Perpendicular(const sf::Vector2f& dir)
{
    sf::Vector2f perp = sf::Vector2f(dir.y, -dir.x);
    return perp;
}

static const float PI = 3.14159265359f;
/// <summary>
/// Return dot product between a and b
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
inline float Dot(const sf::Vector2f& a, const sf::Vector2f& b)
{
    return a.x * b.x + a.y * b.y;
}

/// <summary>
/// Return length of a vector2f
/// </summary>
/// <param name="a"></param>
/// <returns></returns>
inline float Length(const sf::Vector2f& a)
{
    return sqrtf(Dot(a, a));
}

/// <summary>
/// Normalize a 2D vector
/// </summary>
/// <param name="a">Vector to normalize</param>
/// <returns>normalized vector</returns>
inline sf::Vector2f Normalize(const sf::Vector2f& a)
{
    return a / Length(a);
}
/// <summary>
/// Rotate a 2D Direction vector with an angle in degree
/// </summary>
/// <param name="dir"></param>
/// <param name="angleInDegree">rotation angle</param>
/// <returns></returns>
inline sf::Vector2f RotateVector(const sf::Vector2f& dir, float angleInDegree)
{
    sf::Transform rotation;
    rotation.rotate(angleInDegree);
    return rotation.transformPoint(dir);
}

//calculate ray direction from abscisse in normalized 0-1 and camera direction
inline sf::Vector2f GetRayDir(float x,const sf::Vector2f& camDir)
{
    sf::Vector2f rightVec = Perpendicular(camDir);
    //x-coordinate in camera space -1.0f to 1.0f
    float camX = (2.0f * x) - 1.0f; 
    sf::Vector2f rayDir = camDir + rightVec * 0.66f*camX;
    return Normalize(rayDir);
}



/// <summary>
/// Clamp a sf::vector2f between min and max
/// </summary>
/// <param name="pos"></param>
/// <param name="min"></param>
/// <param name="max"></param>
/// <returns>clamped vector</returns>
inline sf::Vector2f ClampVector(const sf::Vector2f& pos, const sf::Vector2f& min, const sf::Vector2f& max)
{
    sf::Vector2f res;

    res.x = (pos.x > max.x) ? max.x : (pos.x < min.x) ? min.x : pos.x;
    res.y = (pos.y > max.y) ? max.y : (pos.y < min.y) ? min.y : pos.y;

    return res;
}
/// <summary>
/// Return rotation sign (-1 right, 1 left, 0 no rotation) and position delta vector based on current inputs
/// </summary>
/// <param name="deltaPos">(Out) position delta vector</param>
/// <returns>rotation sign</returns>
float GetCameraMovementFromInput(float& deltaPos)
{
    float angle = 0.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        // move left...
        angle+=1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        // move right...
        angle -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        deltaPos += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        deltaPos -= 1;
    }
    return angle;
}

// Solution start 
// ------------------------------------------------------------------
void RasterizeScene(const sf::Vector2f& camPos, const sf::Vector2f& camDir, sf::Image& raster, const int* worldMap, int W, int H)
{
    // Todo
}
// -------------------------------------------------------------------
// Solution End 


int main()
{
    sf::Vector2i resolutionScreen = sf::Vector2i(1920, 1080);
    sf::RenderWindow window(sf::VideoMode(resolutionScreen.x, resolutionScreen.y), "SFML Raycaster");
    // Vertical sync to don't waste energy running over 60 FPS
    window.setVerticalSyncEnabled(true);

    // select the font
    sf::Font font;
    if (!font.loadFromFile("arialbi.ttf"))
    {
        return 0;
    }
    sf::Text text;
    text.setFont(font); // font is a sf::Font
    text.setCharacterSize(20); // in pixels, not points!
    text.setFillColor(sf::Color::Black);

    // Image
    sf::Image raster;
    raster.create(window.getSize().x, window.getSize().y, sf::Color::Black);

    sf::Texture rasterTex;
    rasterTex.loadFromImage(raster);
    sf::Sprite test(rasterTex);

    // Initial Camera position
    sf::Vector2f camPos(22, 12);
    // Initial camera direction vector
    sf::Vector2f camDir(-1, 0);
    // Camera rotation in speed in degree per second
    const float rotationSpeed = 45.0f;

    // Camera movement speed in m per second
    const float movementSpeed = 1.0f;

    // Main loop    
    sf::Clock clock;
    sf::Time fixedPhysic = sf::microseconds(16666);
    sf::Time updateTime;
    while (window.isOpen())
    {
        // Update delta time
        sf::Time elapsed = clock.restart();
        if (elapsed.asSeconds() > 0.1f)
            elapsed = sf::seconds(0.1f);
        updateTime += elapsed;

        // Grab inputs events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                }
            }
        }

        // Get inputs
        float deltaPos = 0.0f;;
        float rotationSign = GetCameraMovementFromInput(deltaPos);

        // Update Logic and physics at fixed timesteps
        while (updateTime >= fixedPhysic)
        {
            // Update physics
            camDir = RotateVector(camDir, rotationSign * rotationSpeed * fixedPhysic.asSeconds());
            camDir = Normalize(camDir);
            camPos += camDir * deltaPos * movementSpeed * fixedPhysic.asSeconds();

            // Clamp world position
            camPos = ClampVector(camPos, sf::Vector2f(0, 0), sf::Vector2f(g_mapWidth, g_mapHeight));

            updateTime -= fixedPhysic;
        }
       
        // Rendering
        window.clear(sf::Color(0, 128, 0));

        {
            // Fill image with blue color
            drawRect(raster, sf::Vector2i(0, 0), resolutionScreen, sf::Color::Blue);

            RasterizeScene(camPos, camDir, raster, reinterpret_cast<int*>(g_worldMap), g_mapWidth, g_mapHeight);
            // Update texture from image
            rasterTex.loadFromImage(raster);
        }

        window.draw(test);
        // UI
        window.setView(window.getDefaultView());

        window.display();
    }

    return 0;
}