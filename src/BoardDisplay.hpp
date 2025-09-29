#include "Piece.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <string>
class BoardDisplay {

public:
  sf::Texture texPieces;
  sf::Font font;
  sf::Text boardText;
  std::vector<int> pieces;
  std::vector<sf::RectangleShape> boardDisplay;
  std::vector<sf::Sprite> pieceDisplay;
  std::vector<sf::Text> squareLabels;
  float squareSize = 64;

  BoardDisplay() : font("assets/fonts/Roboto.ttf"), boardText(font) {
    sf::Font font("assets/fonts/Roboto.ttf");
    sf::Text boardText(font);

    // Initialise with default chess starting position, supposedly
    pieces.assign(64, 0);
    pieces[0] = Piece::WHITE + Piece::ROOK;
    pieces[1] = Piece::WHITE + Piece::KNIGHT;
    pieces[2] = Piece::WHITE + Piece::BISHOP;
    pieces[3] = Piece::WHITE + Piece::QUEEN;
    pieces[4] = Piece::WHITE + Piece::KING;
    pieces[5] = Piece::WHITE + Piece::BISHOP;
    pieces[6] = Piece::WHITE + Piece::KNIGHT;
    pieces[7] = Piece::WHITE + Piece::ROOK;

    pieces[8] = Piece::WHITE + Piece::PAWN;
    pieces[9] = Piece::WHITE + Piece::PAWN;
    pieces[10] = Piece::WHITE + Piece::PAWN;
    pieces[11] = Piece::WHITE + Piece::PAWN;
    pieces[12] = Piece::WHITE + Piece::PAWN;
    pieces[13] = Piece::WHITE + Piece::PAWN;
    pieces[14] = Piece::WHITE + Piece::PAWN;
    pieces[15] = Piece::WHITE + Piece::PAWN;

    pieces[48] = Piece::BLACK + Piece::PAWN;
    pieces[49] = Piece::BLACK + Piece::PAWN;
    pieces[50] = Piece::BLACK + Piece::PAWN;
    pieces[51] = Piece::BLACK + Piece::PAWN;
    pieces[52] = Piece::BLACK + Piece::PAWN;
    pieces[53] = Piece::BLACK + Piece::PAWN;
    pieces[54] = Piece::BLACK + Piece::PAWN;
    pieces[55] = Piece::BLACK + Piece::PAWN;

    pieces[56] = Piece::BLACK + Piece::ROOK;
    pieces[57] = Piece::BLACK + Piece::KNIGHT;
    pieces[58] = Piece::BLACK + Piece::BISHOP;
    pieces[59] = Piece::BLACK + Piece::QUEEN;
    pieces[60] = Piece::BLACK + Piece::KING;
    pieces[61] = Piece::BLACK + Piece::BISHOP;
    pieces[62] = Piece::BLACK + Piece::KNIGHT;
    pieces[63] = Piece::BLACK + Piece::ROOK;
  };

  std::vector<sf::RectangleShape> getBoard() { return boardDisplay; }
  std::vector<sf::Sprite> getPieces() { return pieceDisplay; }
  std::vector<sf::Text> getSquareLabels() { return squareLabels; }

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
        square.setPosition({(j + 2) * squareSize, 720 - (i + 2) * squareSize});
        boardDisplay.push_back(square);
        sf::Text squareLabel = sf::Text(font, std::to_string((i * 8) + j));
        squareLabel.setFillColor(sf::Color::Green);
        squareLabel.setOutlineColor(sf::Color::Green);
        squareLabel.setPosition(
            {square.getPosition().x, square.getPosition().y});
        squareLabels.push_back(squareLabel);
      }
    }
    std::cout << "boardDisplay length = " << boardDisplay.size() << std::endl;
    std::cout << "Board gen complete, now attempting pieces..." << std::endl;

    for (int i = 0; i < pieces.size(); i++) {
      if (pieces[i] != 0) {
        sf::Sprite sprite(texPieces);
        sprite.setTextureRect(getPieceTexture(pieces[i]));
        sprite.setOrigin({squareSize / 2, squareSize / 2});
        sprite.setPosition(boardDisplay[i].getPosition());
        pieceDisplay.push_back(sprite);
      }
    }
    std::cout << "pieceDisplay length = " << pieceDisplay.size() << std::endl;
    std::cout << "All pieces ready" << std::endl;
  }

  // TODO: Separate function for centre of square, or should it be stored
  // somewhere?

  sf::IntRect getPieceTexture(int pieceInt) {
    const sf::Vector2i pieceSize = {60, 60};
    switch (pieceInt) {
    case Piece::BLACK + Piece::QUEEN:
      return sf::IntRect({0, 0}, pieceSize);
      break;
    case Piece::BLACK + Piece::KING:
      return sf::IntRect({60, 0}, pieceSize);
      break;
    case Piece::BLACK + Piece::ROOK:
      return sf::IntRect({120, 0}, pieceSize);
      break;
    case Piece::BLACK + Piece::KNIGHT:
      return sf::IntRect({180, 0}, pieceSize);
      break;
    case Piece::BLACK + Piece::BISHOP:
      return sf::IntRect({240, 0}, pieceSize);
      break;
    case Piece::BLACK + Piece::PAWN:
      return sf::IntRect({300, 0}, pieceSize);
      break;
    case Piece::WHITE + Piece::QUEEN:
      return sf::IntRect({0, 0}, pieceSize);
      break;
    case Piece::WHITE + Piece::KING:
      return sf::IntRect({60, 60}, pieceSize);
      break;
    case Piece::WHITE + Piece::ROOK:
      return sf::IntRect({120, 60}, pieceSize);
      break;
    case Piece::WHITE + Piece::KNIGHT:
      return sf::IntRect({180, 60}, pieceSize);
      break;
    case Piece::WHITE + Piece::BISHOP:
      return sf::IntRect({240, 60}, pieceSize);
      break;
    case Piece::WHITE + Piece::PAWN:
      return sf::IntRect({300, 60}, pieceSize);
      break;
    default:
      // How to error handle here?
      return sf::IntRect({360, 0}, pieceSize);
    }
  }
};
