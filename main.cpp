#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

// Screen size
const double WIDTH = 1280;
const double HEIGHT = 720;

// Color schema
Color appBackground = Color(245, 245, 245);
Color appDarkFontColor = Color(10, 10, 10);
Color appLightFontColor = Color(245, 245, 245);
Color circleColor = Color(219, 70, 90);
Color xColor = Color(70, 159, 219);
Color buttonColor = Color(70, 219, 142);
Color boardBorderColor = Color(10, 10, 10);
Color gameResultColor = Color(10, 10, 10, 200);
Color winingPlayerColor = Color(104, 232, 115);
Color losingPlayerColor = Color(219, 94, 94);

// Click event action type
enum Action {
    START,
    MOVE,
    PLAY_AGAIN
};

struct Dispatch {
    Action action;
    int payload;
};

class Config {
    public:
        Font font;
        Config() {
            font.loadFromFile("assets/Roboto-Regular.ttf");
        }
};

// An abstract class that is a wrapper for all scene objects
class DrawableContent {
    protected:
        Dispatch dispatchValue;
        bool isClickable = false;
    public:
        virtual void draw(RenderWindow& window) {};
        virtual void setPosition(int x, int y) {};
        virtual FloatRect getGlobalBounds() {};
        Dispatch dispatch() {
            return dispatchValue;
        };
        void setDispatchValue(Dispatch _dispatchValue) {
            dispatchValue = _dispatchValue;
        };
        void setIsClickable(bool _val) {
            isClickable = _val;
        };
        bool getIsClickable() {
            return isClickable;
        };
        bool isClicked(Event::MouseButtonEvent mousePos) {
            FloatRect bound = getGlobalBounds();

            if(mousePos.y >= bound.top && mousePos.y <= (bound.top + bound.height)) {
                if (mousePos.x >= bound.left && mousePos.x <= (bound.left + bound.width)) {
                    return true;
                }
            }
            return false;
        }
};

// Component that displays text on the screen
class DrawableText: public DrawableContent {
    public:
        string textNode;
        Config config;
        Text text;
        int fontSize;
        
        DrawableText(Config _config, int _fontSize) {
            config = _config;
            fontSize = _fontSize;

            text.setFont(config.font);
            text.setCharacterSize(fontSize);
            text.setFillColor(appDarkFontColor);
        }
        DrawableText(Config _config, string _textNode, int _fontSize) {
            config = _config;
            textNode = _textNode;
            fontSize = _fontSize;

            text.setFont(config.font);
            text.setString(textNode);
            text.setCharacterSize(fontSize);
            text.setFillColor(appDarkFontColor);
        }
        void draw(RenderWindow& window) {
            window.draw(text);
        }
        void setText(string _textNode) {
            textNode = _textNode;
            text.setString(textNode);
        }
        void setPosition(int x, int y) {
            text.setPosition(WIDTH * x / 100 - text.getLocalBounds().width / 2, HEIGHT * y / 100 - text.getLocalBounds().height);
        }
        void setColor(Color color) {
            text.setFillColor(color);
        }
        FloatRect getGlobalBounds() {
            return text.getGlobalBounds();
        }
};

// Component that displays button with text on the screen
class DrawableButton: public DrawableContent {
   public:
        int padding;
        Config config;
        RectangleShape shape;
        DrawableText text = DrawableText(config, 24);
        DrawableButton(Config _config, int _padding, string textNode) {
            config = _config;
            padding = _padding;
            text.setText(textNode);
            shape.setSize(Vector2f(text.text.getLocalBounds().width + padding * 2, text.text.getLocalBounds().height + padding * 2));
            shape.setFillColor(buttonColor);
        }
        void draw(RenderWindow& window) {

            window.draw(shape);
            text.draw(window);
        }
        void setPosition(int x, int y) {
            text.setPosition(x, y);
            shape.setPosition(Vector2f(text.text.getGlobalBounds().left - padding, text.text.getGlobalBounds().top - padding));
        }
        FloatRect getGlobalBounds() {
            return shape.getGlobalBounds();
        }
};

// Component that displays colored rectangle on the screen
class DrawableRect: public DrawableContent {
   public:
        Config config;
        RectangleShape shape;
        Color background;
        DrawableRect(Config _config, float width, float height, Color _background) {
            config = _config;
            background = _background;
            shape.setSize(Vector2f(width, height));
            shape.setFillColor(_background);
        }
        void draw(RenderWindow& window) {
            window.draw(shape);
        }
        void setPosition(int x, int y) {
            shape.setPosition(x, y);
        }
        FloatRect getGlobalBounds() {
            return shape.getGlobalBounds();
        }
};

// Component that displays players circle shape
class DrawableCircle: public DrawableContent {
    public:
        Config config;
        CircleShape shape;
        CircleShape innerShape;
        float borderWidth;
        float padding;
        DrawableCircle(Config _config, float size, float _borderWidth, float _padding, Color surroundingBackground) {
            config = _config;
            borderWidth = _borderWidth;
            padding = _padding;

            shape.setFillColor(circleColor);
            shape.setRadius((size - padding * 2) / 2);
            
            innerShape.setFillColor(surroundingBackground);
            innerShape.setRadius(((size - padding * 2) - _borderWidth) / 2);
        }
        void draw(RenderWindow& window) {
            window.draw(shape);
            window.draw(innerShape);
        }
        void setPosition(int x, int y) {
            shape.setPosition(x + padding, y + padding);
            innerShape.setPosition(x + borderWidth / 2.0 + padding, y + borderWidth / 2.0 + padding);
        }
        FloatRect getGlobalBounds() {
            return shape.getGlobalBounds();
        }
};

// Component that displays players x shape
class DrawableX: public DrawableContent {
    public: 
        Config config;
        RectangleShape vertical;
        RectangleShape horizontal;
        RectangleShape wrapper;
        float width;
        float padding;
        float size;
        DrawableX(Config _config, float _size, float _width, float _padding) {
            config = _config;
            size = _size;
            padding = _padding;
            width = _width;

            wrapper.setSize(Vector2f(size, size));
            wrapper.setFillColor(Color::Transparent);

            vertical.setSize(Vector2f(size - padding * 2, width));
            vertical.setFillColor(xColor);
            vertical.setOrigin(size / 2, width / 2);

            horizontal.setSize(Vector2f(width, size - padding * 2));
            horizontal.setFillColor(xColor);
            horizontal.setOrigin(width / 2, size / 2);
        }
        void draw(RenderWindow& window) {
            window.draw(wrapper);
            window.draw(horizontal);
            window.draw(vertical);
        }
        void setPosition(int x, int y) {
            wrapper.setPosition(x, y);
            horizontal.setPosition(x + size / 2.0 - width, y + padding + size / 2.0);
            horizontal.setRotation(45);

            vertical.setPosition(x + padding + size / 2.0 - width, y + padding + size / 2.0);
            vertical.setRotation(45);
        }
        FloatRect getGlobalBounds() {
            return wrapper.getGlobalBounds();
        }
};

// A struct that contains all information about the player
struct Player {
    string name;
    int boardValue;
    char shape;
    int totalScore;
};

struct SceneObject {
    int id; // unique object identifier
    DrawableContent* object;
};

class GameState {
    public:
        int currentPlayer = 0;
        int currentPlayerTextId = -1;
        int winner = -1;
        int board[9]{};
        int objectLastId = 0;
        vector<SceneObject> objects;
        Player players[2];
        Config config;
        RenderWindow window;
        GameState() {
            window.create(VideoMode(WIDTH, HEIGHT), "Tic Tac Toe");
            players[0] = Player {"Player 1", 1, 'x'};
            players[1] = Player {"Player 2", 2, 'o'};
        }
        // Checks if someone won if yes returns true, otherwise false
        bool hasGameWinner() {
            for (int i = 0; i < 9; i += 3) {
                if(board[i] != 0 && board[i] == board[i + 1] && board[i] == board[i + 2]) {
                    return true;
                }
            }

            for (int i = 0; i < 3; i++) {
                if(board[i] != 0 && board[i] == board[i + 3] && board[i] == board[i + 6]) {
                    return true;
                }
            }

            if(board[0] != 0 && board[0] == board[4] && board[0] == board[8]) {
                return true;
            }

            if(board[2] != 0 && board[2] == board[4] && board[2] == board[6]) {
                return true;
            }

            return false;
        }
        // Checks if board is full
        bool isBoardFull() {
            for (int i = 0; i < 9; i++) {
                if (board[i] == 0) return false;
            }

            return true;
        }
        // Renders initial game page
        void createStartGameScene() {
            DrawableText* text = new DrawableText(config, "Tic Tac Toe", 54);
            text->setPosition(50, 25);

            DrawableText* rulesText = new DrawableText(config, "Game rules:\n1. The game is played on a grid that's 3 squares by 3 squares.\n2. You are X, your friend (or the computer in this case) is O. Players take turns putting their marks in empty squares.\n3. The first player to get 3 of her marks in a row (up, down, across, or diagonally) is the winner.\n4. When all 9 squares are full, the game is over. If no player has 3 marks in a row, the game ends in a tie.", 18);
            rulesText->setPosition(50, 47.5);

            DrawableButton* button = new DrawableButton(config, 10, "Start game");
            button->setDispatchValue({ START, 0 });
            button->setIsClickable(true);
            button->setPosition(50, 57.5);

            addObject(text);
            addObject(rulesText);
            addObject(button);
        };
        // Renders game page
        void handleStartGame() {
            clearStage();

            double size = 450.0;
            double left = WIDTH / 2 - size / 2;
            double top = HEIGHT / 2 - size / 2;
            
            DrawableRect* verticalLine1 = new DrawableRect(config, 4, size, boardBorderColor);
            verticalLine1->setPosition(left + size / 3.0, top);

            DrawableRect* verticalLine2 = new DrawableRect(config, 4, size, boardBorderColor);
            verticalLine2->setPosition(left + size * 2 / 3.0, top);

            DrawableRect* horizontalLine1 = new DrawableRect(config, size, 4, boardBorderColor);
            horizontalLine1->setPosition(left, top + size / 3.0);

            DrawableRect* horizontalLine2 = new DrawableRect(config, size, 4, boardBorderColor);
            horizontalLine2->setPosition(left, top + size * 2 / 3.0);
            
            DrawableText* player1Name = new DrawableText(config, "- " + players[0].name, 24);
            player1Name->setPosition(7.5, 5);

            DrawableX* player1Shape = new DrawableX(config, 24, 4, 0);
            player1Shape->setPosition(WIDTH * 0.075 - 75, HEIGHT * 0.05 - 18);

            DrawableText* player2Name = new DrawableText(config, "- " + players[1].name, 24);
            player2Name->setPosition(7.5, 10);

            DrawableCircle* player2Shape = new DrawableCircle(config, 24, 6, 0, appBackground);
            player2Shape->setPosition(WIDTH * 0.075 - 85, HEIGHT * 0.1 - 18);

            DrawableText* currentPlayerText = new DrawableText(config, players[currentPlayer].name, 36);
            currentPlayerText->setPosition(50, 10);

            addObject(verticalLine1);
            addObject(verticalLine2);
            addObject(horizontalLine1);
            addObject(horizontalLine2);
            addObject(player1Name);
            addObject(player1Shape);
            addObject(player2Name);
            addObject(player2Shape);
            currentPlayerTextId = addObject(currentPlayerText);

            int n = 0;

            for(int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    DrawableRect* box = new DrawableRect(config, size / 3.0, size / 3.0, Color::Transparent);
                    box->setPosition(left + size / 3.0 * j, top + size / 3.0 * i);
                    box->setIsClickable(true);
                    box->setDispatchValue({ MOVE, n });

                    addObject(box);
                    n++;
                }
            }
        }
        void handleMove(int position) {
            if(board[position] != 0 || winner != -1) return;

            double size = 450.0;
            double left = WIDTH / 2 - size / 2;
            double top = HEIGHT / 2 - size / 2;

            switch (players[currentPlayer].shape) {
                case 'o': {
                    DrawableCircle* box = new DrawableCircle(config, size / 3.0, 10, 20, appBackground);
                    
                    box->setPosition(left + size / 3.0 * (position % 3), top + size / 3.0 * (position > 5 ? 2 : (position > 2 ? 1 : 0)));
                    addObject(box);
                    
                    break;
                }
                case 'x': {
                    DrawableX* box = new DrawableX(config, size / 3.0, 6, 20);
                    
                    box->setPosition(left + size / 3.0 * (position % 3), top + size / 3.0 * (position > 5 ? 2 : (position > 2 ? 1 : 0)));
                    addObject(box);

                    break;
                }
            }


            board[position] = players[currentPlayer].boardValue;

            if(hasGameWinner()) {
                winner = currentPlayer;
                players[currentPlayer].totalScore += 1;

                renderGameResult();
            } else if (isBoardFull()) {
                renderGameResult();
            } else {
                currentPlayer = currentPlayer == 0 ? 1 : 0;
                if (currentPlayerTextId != -1) {
                    dynamic_cast<DrawableText&>(*getObject(currentPlayerTextId)).setText(players[currentPlayer].name);
                }
            }
        }
        // Renders game result
        void renderGameResult() {
                DrawableText* text = new DrawableText(config, winner == -1 ? "Draw!" :  players[winner].name +  " Won!", 54);
                text->setColor(appLightFontColor);
                text->setPosition(50, 40);

                DrawableButton* button = new DrawableButton(config, 10, "Play again");
                button->setDispatchValue({ PLAY_AGAIN, 0 });
                button->setIsClickable(true);
                button->setPosition(50, 75);

                DrawableRect* wrapper = new DrawableRect(config, WIDTH, HEIGHT, gameResultColor);
                wrapper->setPosition(0, 0);

                DrawableText* player1Name = new DrawableText(config, players[0].name, 24);
                player1Name->setPosition(40, 50);
                player1Name->setColor(appLightFontColor);

                DrawableX* player1Shape = new DrawableX(config, 24, 4, 0);
                player1Shape->setPosition(WIDTH * 0.4 - 65, HEIGHT / 2 - 20);

                DrawableText* player1Score = new DrawableText(config, to_string(players[0].totalScore), 72);
                player1Score->setPosition(39, 60);
                player1Score->setColor(getPlayerScoreColor(0));

                DrawableText* player2Name = new DrawableText(config, players[1].name, 24);
                player2Name->setPosition(60, 50);
                player2Name->setColor(appLightFontColor);

                DrawableCircle* player2Shape = new DrawableCircle(config, 24, 6, 0, gameResultColor);
                player2Shape->setPosition(WIDTH * 0.6 - 70, HEIGHT / 2 - 20);

                DrawableText* player2Score = new DrawableText(config, to_string(players[1].totalScore), 72);
                player2Score->setPosition(59, 60);
                player2Score->setColor(getPlayerScoreColor(1));

                DrawableText* scoreSep = new DrawableText(config, "-", 72);
                scoreSep->setPosition(50, 53);
                scoreSep->setColor(appLightFontColor);

                addObject(wrapper);
                addObject(text);
                addObject(button);
                addObject(player1Name);
                addObject(player1Shape);
                addObject(player1Score);
                addObject(player2Name);
                addObject(player2Shape);
                addObject(player2Score);
                addObject(scoreSep);
        }
        // Returns player score color by his total score
        Color getPlayerScoreColor(int playerIndex) {
            int otherPlayerIndex = playerIndex == 0 ? 1 : 0;

            if(players[playerIndex].totalScore == players[otherPlayerIndex].totalScore) {
                return appLightFontColor;
            }

            return players[playerIndex].totalScore > players[otherPlayerIndex].totalScore ? winingPlayerColor : losingPlayerColor;
        }
        // Clears game state
        void handlePlayAgain() {
            for(int i = 0; i < 9; i++) {
                board[i] = 0;
            }

            currentPlayerTextId = -1;
            winner = -1;
            currentPlayer = currentPlayer == 0 ? 1 : 0;

            handleStartGame();
        }
        // Renders game on the screen and components that are on the scene
        void render() {
            while(window.isOpen()) {
                Event event;    
                while (window.pollEvent(event)) {
                    switch (event.type) {
                        case Event::Closed:
                            window.close();
                            break;
                        case Event::MouseButtonPressed:
                            if (event.mouseButton.button == sf::Mouse::Left) {
                                for(auto &value: objects) {
                                    if(value.object->getIsClickable() && value.object->isClicked(event.mouseButton)) {
                                        Dispatch dispatch = value.object->dispatch();
                                        switch(dispatch.action){
                                            case START: {
                                                handleStartGame();
                                                break;
                                            }
                                            case MOVE: {
                                                handleMove(dispatch.payload);
                                                break;
                                            }
                                            case PLAY_AGAIN: {
                                                handlePlayAgain();
                                                break;
                                            }
                                        }
                                    }
                                }                
                            }
                        break;
                    }
                }
                window.clear(appBackground);
                
                for(auto &value: objects) {
                    value.object->draw(window);
                }

                window.display();
            }
        }
        // Removes all objects from the scene
        void clearStage() {
            objects.clear();
        }
        // Adds an object to the scene
        int addObject(DrawableContent* object) {
            objectLastId += 1;
            objects.push_back({ objectLastId, object });

            return objectLastId;
        }
        // Returns object by id from the scene
        DrawableContent* getObject(int id) {
            for(auto &value: objects) {
                if(value.id == id) {
                    return value.object;
                }
            }
        }
};

int main() {
    GameState game;

    game.createStartGameScene();
    game.render();

    return 0;
}