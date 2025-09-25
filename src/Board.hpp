#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
class Board {

public:
  Board() = default;

  int Square[64];
  std::vector<sf::RectangleShape> board;
  float squareSize = 64;

  // Pawn = 1
  // Knight = 2
  // Bishop = 3
  // Rook = 4
  // Queen = 5
  // King = 6

  std::vector<sf::RectangleShape> getBoard() { return board; }

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
        square.setPosition({(i + 2) * squareSize, 720 - (j + 2) * squareSize});
        board.push_back(square);
      }
    }
  }
};
