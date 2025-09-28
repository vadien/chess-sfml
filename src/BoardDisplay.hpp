#include "Piece.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
class BoardDisplay {

public:
  sf::Texture texPieces;
  std::vector<int> pieces;
  std::vector<sf::RectangleShape> boardDisplay;
  std::vector<sf::Sprite> pieceDisplay;
  float squareSize = 64;

  BoardDisplay() {
    // TODO: Initialise with default chess starting position
    pieces.assign(64, 0);
    pieces[0] = Piece::WHITE + Piece::BISHOP;
    pieces[7] = Piece::BLACK + Piece::KNIGHT;
    pieces[63] = Piece::BLACK + Piece::QUEEN;
  };

  std::vector<sf::RectangleShape> getBoard() { return boardDisplay; }
  std::vector<sf::Sprite> getPieces() { return pieceDisplay; }

  void generateBoard() {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        // TODO: Make square size a variable
        sf::RectangleShape square({squareSize, squareSize});
        if ((i + j) % 2 == 0) {
          square.setOutlineColor(sf::Color(50, 50, 50));
          square.setFillColor(sf::Color(50, 50, 50));
        } else {
          square.setOutlineColor(sf::Color::White);
          square.setFillColor(sf::Color::White);
        }
        square.setOrigin({square.getPosition().x + squareSize / 2,
                          square.getPosition().y + squareSize / 2});
        square.setPosition({(i + 2) * squareSize, 720 - (j + 2) * squareSize});
        boardDisplay.push_back(square);
      }
    }
    std::cout << "boardDisplay length = " << boardDisplay.size() << std::endl;
    std::cout << "Board gen complete, now attempting pieces..." << std::endl;

    for (int i = 0; i < pieces.size(); i++) {
      if (pieces[i] != 0) {
        // TODO: Vary IntRect based on piece type
        sf::Sprite sprite(texPieces);
        sprite.setTextureRect(sf::IntRect({0, 60}, {60, 60}));
        sprite.setOrigin({squareSize / 2, squareSize / 2});
        sprite.setPosition(boardDisplay[i].getPosition());
        pieceDisplay.push_back(sprite);
      }
    }
    std::cout << "pieceDisplay length = " << pieceDisplay.size() << std::endl;
    std::cout << "All pieces ready" << std::endl;
  }
};
