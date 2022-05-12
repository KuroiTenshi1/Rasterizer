#include <SFML/Graphics.hpp>
#include <iostream>
#include "Common.h"

/// <summary>
/// Draw a one pixel width vertical line in the specified image.
/// </summary>
/// <param name="tex"></param>
/// <param name="x">Abscisse of the line  </param>
/// <param name="y1">Starting height of the line </param>
/// <param name="y2">Ending height of the line  </param>
/// <param name="c"></param>
void drawVerticalLine(sf::Image &img, int x, int y1, int y2, const sf::Color &c) {
    for (int y = y1; y <= y2; ++y) {
        img.setPixel(x, y, c);
    }
}


/// <summary>
/// Draw a empty or filled rectangle in the specified image
/// </summary>
/// <param name="img"></param>
/// <param name="origin">top left point of the rectangle </param>
/// <param name="size">width and height of the rectangle </param>
/// <param name="c"></param>
/// <param name="filled">if true rect will be filled with color </param>
void drawRect(sf::Image &img, const sf::Vector2i &origin, const sf::Vector2i &size, const sf::Color &c) {
    int x1 = origin.x;
    int x2 = x1 + size.x;
    int y1 = origin.y;
    int y2 = y1 + size.y;
    for (int x = x1; x <= x2; ++x) {
        drawVerticalLine(img, x, y1, y2, c);
    }
}

/// <summary>
///  The World map
/// >0 is a wall
/// </summary>
static const int g_mapWidth = 24;
static const int g_mapHeight = 24;

int g_worldMap[g_mapWidth][g_mapHeight] =
        {
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
        };


/// <summary>
/// Return a unnormalized vector perpendicular to the direction
/// </summary>
/// <param name="dir"></param>
/// <returns></returns>
inline sf::Vector2f Perpendicular(const sf::Vector2f &dir) {
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
inline float Dot(const sf::Vector2f &a, const sf::Vector2f &b) {
    return a.x * b.x + a.y * b.y;
}

/// <summary>
/// Return length of a vector2f
/// </summary>
/// <param name="a"></param>
/// <returns></returns>
inline float Length(const sf::Vector2f &a) {
    return sqrtf(Dot(a, a));
}

/// <summary>
/// Normalize a 2D vector
/// </summary>
/// <param name="a">Vector to normalize</param>
/// <returns>normalized vector</returns>
inline sf::Vector2f Normalize(const sf::Vector2f &a) {
    return a / Length(a);
}

/// <summary>
/// Rotate a 2D Direction vector with an angle in degree
/// </summary>
/// <param name="dir"></param>
/// <param name="angleInDegree">rotation angle</param>
/// <returns></returns>
inline sf::Vector2f RotateVector(const sf::Vector2f &dir, float angleInDegree) {
    sf::Transform rotation;
    rotation.rotate(angleInDegree);
    return rotation.transformPoint(dir);
}

//calculate ray direction from abscisse in normalized 0-1 and camera direction
inline sf::Vector2f GetRayDir(float x, const sf::Vector2f &camDir) {
    sf::Vector2f rightVec = Perpendicular(camDir);
    //x-coordinate in camera space -1.0f to 1.0f
    float camX = (2.0f * x) - 1.0f;
    sf::Vector2f rayDir = camDir + rightVec  * camX;
    //sf::Vector2f rayDir = camDir + rightVec * 0.66f * camX;
    return Normalize(rayDir);
}


/// <summary>
/// Clamp a sf::vector2f between min and max
/// </summary>
/// <param name="pos"></param>
/// <param name="min"></param>
/// <param name="max"></param>
/// <returns>clamped vector</returns>
inline sf::Vector2f ClampVector(const sf::Vector2f &pos, const sf::Vector2f &min, const sf::Vector2f &max) {
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
float GetCameraMovementFromInput(float &deltaPos) {
    float angle = 0.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        // move left...
        angle += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        // move right...
        angle -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        deltaPos += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        deltaPos -= 1.f;
    }
    return angle;
}

// Solution start 
// ------------------------------------------------------------------
void
RasterizeScene(const sf::Vector2f &camPos, const sf::Vector2f &camDir, sf::Image &raster, const int *worldMap, int W,
               int H) {

    int w = 1920, h = 1080; //screen resolution

    for (int x = 0; x < w; x++) {
        //calculate ray position and direction
        //sf::Vector2f rayDir = GetRayDir(x, camDir);

        float cameraX = 2.0f * x / w - 1.0f; //x-coordinate in camera space -1.0f to 1.0f
        float rayDirX = camDir.x + Perpendicular(camDir).x * cameraX;
        float rayDirY = camDir.y + Perpendicular(camDir).y * cameraX;
        //float rayDirX = rayDir.x;
        //float rayDirY = rayDir.y;

        //which box of the map we're in
        int mapX = int(camPos.x);
        int mapY = int(camPos.y);

        //length of ray from current position to next x or y-side
        float sideDistX;
        float sideDistY;

        float deltaDistX = fabs(1 / rayDirX);
        float deltaDistY = fabs(1 / rayDirY);

        float perpWallDist;

        //what direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;

        int hit = 0; //was there a wall hit?
        int side; //was a NS or a EW wall hit?
        //calculate step and initial sideDist
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (camPos.x - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - camPos.x) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (camPos.y - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - camPos.y) * deltaDistY;
        }
        //perform DDA
        while (hit == 0) {
            //jump to next map square, either in x-direction, or in y-direction
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            //Check if ray has hit a wall
            if (worldMap[mapX + mapY * W] > 0) {
                hit = 1;
            }
        }

        if (side == 0) perpWallDist = (mapX - camPos.x + (1 - stepX) / 2) / rayDirX;
        else perpWallDist = (mapY - camPos.y + (1 - stepY) / 2) / rayDirY;

        //Calculate height of line to draw on screen
        int lineHeight = (int)(h / perpWallDist);

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + h / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + h / 2;
        if (drawEnd >= h) drawEnd = h - 1;

        //choose wall color
        sf::Color color;
        switch (worldMap[mapX + mapY * W]) {
            case 1:
                color = sf::Color::Red;
                break; //red
            case 2:
                color = sf::Color::Green;
                break; //green
            case 3:
                color = sf::Color::Cyan;
                break; //cyan
            case 4:
                color = sf::Color::White;
                break; //white
            default:
                color = sf::Color::Yellow;
                break; //yellow
        }

        //give x and y sides different brightness
        if (side == 1) {
            color.r = (int) (color.r * 0.5);
            color.g = (int) (color.g * 0.5);
            color.b = (int) (color.b * 0.5);
        }

        //draw the pixels of the stripe as a vertical line
        drawVerticalLine(raster, x, drawStart, drawEnd, color);
    }

}
// -------------------------------------------------------------------
// Solution End 


int main() {
    sf::Vector2i resolutionScreen = sf::Vector2i(1920, 1080);
    sf::RenderWindow window(sf::VideoMode(resolutionScreen.x, resolutionScreen.y), "SFML Raycaster");
    // Vertical sync to don't waste energy running over 60 FPS
    window.setVerticalSyncEnabled(true);

    // select the font
    sf::Font font;
    if (!font.loadFromFile("assets/arialbi.ttf")) {
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
    while (window.isOpen()) {
        // Update delta time
        sf::Time elapsed = clock.restart();
        if (elapsed.asSeconds() > 0.1f)
            elapsed = sf::seconds(0.1f);
        updateTime += elapsed;

        // Grab inputs events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                }
            }
        }

        // Get inputs
        float deltaPos = 0.0f;;
        float rotationSign = GetCameraMovementFromInput(deltaPos);

        // Update Logic and physics at fixed timesteps
        while (updateTime >= fixedPhysic) {
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

            RasterizeScene(camPos, camDir, raster, reinterpret_cast<int *>(g_worldMap), g_mapWidth, g_mapHeight);
            // Update texture from image
            rasterTex.loadFromImage(raster);
        }
        //FPS
        text.setString(std::to_string(1.0f / elapsed.asSeconds()));
        text.setPosition(10, 10);
        window.draw(text);

        std::cout << 1.0f / elapsed.asSeconds() << std::endl;


        window.draw(test);
        // UI
        window.setView(window.getDefaultView());

        window.display();
    }

    return 0;
}