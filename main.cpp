#include <iostream>
#include<sstream>
#include <SFML/Graphics.hpp>



using namespace sf;
int main() {


    VideoMode vm(1200, 1080);
    RenderWindow window(vm, "Timber!!!", Style::Default);
    // Create a texture to hold a graphic on the GPU
    Texture textureBackground;

    // Load a graphic into the texture
    textureBackground.loadFromFile("/home/bukenya/CLionProjects/Timber/graphics/background.png");

    // Create a sprite
    Sprite spriteBackground;
    // Attach the texture to the sprite
    spriteBackground.setTexture(textureBackground);

    // Set the spriteBackground to cover the screen
    spriteBackground.setPosition(0,0);

    // Make a tree sprite
    Texture textureTree;
    textureTree.loadFromFile("/home/bukenya/CLionProjects/Timber/graphics/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);

    // Prepare the bee
    Texture textureBee;
    textureBee.loadFromFile("/home/bukenya/CLionProjects/Timber/graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);

    // Is the bee currently moving?
    bool beeActive = false;
    // How fast can the bee fly
    float beeSpeed = 0.0f;

    // make 3 cloud sprites from 1 texture
    Texture textureCloud;
    // Load 1 new texture
    textureCloud.loadFromFile("/home/bukenya/CLionProjects/Timber/graphics/cloud.png");

    // 3 New sprites with the same texture
    Sprite spriteCloud1;
    Sprite spriteCloud2;
    Sprite spriteCloud3;
    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);

    // Position the clouds on the left of the screen
    // at different heights
    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0, 250);
    spriteCloud3.setPosition(0, 500);

    // Are the clouds currently on screen?
    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;

    // How fast is each cloud ?
    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;

    // Variables to control time itself
    Clock clock;
    sf::RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1200 / 2) - timeBarStartWidth / 2, 980);

    Time getTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;


    bool paused = true;

    int score = 0;
    sf::Text messageText;
    sf::Text scoreText;

    // Font
    sf::Font font;
    font.loadFromFile("/home/bukenya/CLionProjects/Timber/fonts/KOMIKAP_.ttf");

    // set font to message
    messageText.setFont(font);
    scoreText.setFont(font);

    // Assign actual message
    messageText.setString("Press Enter to start");
    scoreText.setString("Score: = 0");


    // Make it big
    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);


    // choose color
    messageText.setFillColor(sf::Color::White);
    scoreText.setFillColor(sf::Color::White);

    // Position the text
    sf::FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left +
        textRect.width / 2.0f,
        textRect.top +
        textRect.height / 2.0f),
    messageText.setPosition(1200 / 2.0f, 1080 / 2.0f);
    scoreText.setPosition(20,20);


    while (window.isOpen())
    {
        /*
         *
         *************************************************
         Handle the Players input
         *************************************************/
        if(Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        // start the game
        if(Keyboard::isKeyPressed(sf::Keyboard::Return)){
            paused = false;
            // Reset the time and the score
            score = 0;
            timeRemaining = 6.0f;
        }
        /*
         *************************************************
         Update the Scene
         *************************************************/
        // Measure time
        if(!paused){

            Time dt = clock.restart();

            // subtract from the amount of time remaining
            timeRemaining -= dt.asSeconds();
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

            if(timeRemaining <= 0.0f){
                paused = true;
                messageText.setString("Game Over, Out of Time");

                // Reposition the text based on the new text size
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left +
                                      textRect.width / 2.0f,
                                      textRect.top +
                                      textRect.height / 2.0f);
                messageText.setPosition(1200 / 2.0f, 1080 / 2.0f);
            }
            // Setup the bee
            if (!beeActive) {
                // How fast is the bee
                srand((int) time(0));
                beeSpeed = (rand() % 200) + 200;
                // How high is the bee
                srand((int) time(0) * 10);
                float height = (rand() % 500) + 500;
                spriteBee.setPosition(2000, height);

                beeActive = true;
            }else
            {
                // Move the bee
                spriteBee.setPosition(
                        spriteBee.getPosition().x -
                        (beeSpeed * dt.asSeconds()),
                        spriteBee.getPosition().y);
                // Has the bee reached the left-hand edge of the screen?
                if (spriteBee.getPosition().x < -100)
                {
                    // Set it up ready to be a whole new bee next frame
                    beeActive = false;
                }
            }
            // Manage the clouds
            // Cloud 1
            if (!cloud1Active)
            {
                // How fast is the cloud
                srand((int)time(0) * 10);
                cloud1Speed = (rand() % 200);
                // How high is the cloud
                srand((int)time(0) * 10);
                float height = (rand() % 150);
                spriteCloud1.setPosition(-200, height);
                cloud1Active = true;
            }else
            {
                spriteCloud1.setPosition(
                        spriteCloud1.getPosition().x +
                        (cloud1Speed * dt.asSeconds()),
                        spriteCloud1.getPosition().y);
                // Has the cloud reached the right hand edge of the screen?
                if (spriteCloud1.getPosition().x > 1920)
                {
                    // Set it up ready to be a whole new cloud next frame
                    cloud1Active = false;
                }
            }

            // Cloud 2
            if (!cloud2Active)
            {
                // How fast is the cloud
                srand((int)time(0) * 20);
                cloud2Speed = (rand() % 200);
                // How high is the cloud
                srand((int)time(0) * 20);
                float height = (rand() % 300) - 150;
                spriteCloud2.setPosition(-200, height);
                cloud2Active = true;
            }
            else
            {
                spriteCloud2.setPosition(
                        spriteCloud2.getPosition().x +
                        (cloud2Speed * dt.asSeconds()),
                        spriteCloud2.getPosition().y);
                // Has the cloud reached the right hand edge of the screen?
                if (spriteCloud2.getPosition().x > 1920)
                {
                    // Set it up ready to be a whole new cloud next frame
                    cloud2Active = false;
                }
            }

            if (!cloud3Active)
            {
                // How fast is the cloud
                srand((int)time(0) * 30);
                cloud3Speed = (rand() % 200);
                // How high is the cloud
                srand((int)time(0) * 30);
                float height = (rand() % 450) - 150;
                spriteCloud3.setPosition(-200, height);
                cloud3Active = true;
            }else
            {
                spriteCloud3.setPosition(
                        spriteCloud3.getPosition().x +
                        (cloud3Speed * dt.asSeconds()),
                        spriteCloud3.getPosition().y);
                // Has the cloud reached the right hand edge of the screen?
                if (spriteCloud3.getPosition().x > 1920)
                {
                    // Set it up ready to be a whole new cloud next frame
                    cloud3Active = false;
                }
            }
            // Update the score
            std::stringstream ss;
            ss << "Score: " << score;
            scoreText.setString(ss.str());

        }


        /*
         *************************************************
         Draw the Scene
         *************************************************/

        window.clear();
        //Draw our game scene here
        window.draw(spriteBackground);

        // Draw the clouds
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        // Draw the tree
        window.draw(spriteTree);
        // Draw the insect
        window.draw(spriteBee);
        //Show everything we just drew

        // Draw the score
        window.draw(scoreText);

        // Draw the timebar
        window.draw(timeBar);
        if(paused){
            // draw our message
            window.draw(messageText);
        }

        window.display();

    }
    return 0;
}
