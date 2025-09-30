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
#include <vector>

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

  const std::vector<sf::RectangleShape> &getBoard() { return boardDisplay; }
  const std::vector<int> &getPieces() { return pieces; }
  const std::vector<sf::Sprite> &getPieceDisplay() { return pieceDisplay; }
  const std::vector<sf::Text> &getSquareLabels() { return squareLabels; }

  void generateBoard() {

    updateBoardDisplay(true);
    std::cout << "Board gen complete, now attempting pieces..." << std::endl;

    updatePieceDisplay(true);
    std::cout << "Piece textures loaded" << std::endl;
  }

  void updateBoardDisplay(bool initial = false, int highlightPiece = -1) {
    if (initial) {
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          // TODO: Make square size a variable
          sf::RectangleShape square({squareSize, squareSize});
          if ((i + j) % 2 == 0) {
            square.setOutlineColor(sf::Color(160, 111, 93));
            square.setFillColor(sf::Color(160, 111, 93));
          } else {
            square.setOutlineColor(sf::Color(235, 211, 187));
            square.setFillColor(sf::Color(235, 211, 187));
          }
          square.setOrigin({square.getPosition().x + squareSize / 2,
                            square.getPosition().y + squareSize / 2});
          square.setPosition(
              {(j + 2) * squareSize, 720 - (i + 2) * squareSize});
          boardDisplay.push_back(square);
          sf::Text squareLabel = sf::Text(font, std::to_string((i * 8) + j));
          squareLabel.setFillColor(sf::Color::Green);
          squareLabel.setOutlineColor(sf::Color::Green);
          squareLabel.setPosition(
              {square.getPosition().x - squareLabel.getLocalBounds().size.x / 2,
               square.getPosition().y -
                   squareLabel.getLocalBounds().size.y / 2});
          squareLabels.push_back(squareLabel);
        }
      }
    } else if (highlightPiece != -1) {
      boardDisplay[highlightPiece].setFillColor(sf::Color(160, 150, 60));

    } else {
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          if ((i + j) % 2 == 0) {
            boardDisplay[(i * 8) + j].setFillColor(sf::Color(160, 111, 93));
          } else {
            boardDisplay[(i * 8) + j].setFillColor(sf::Color(235, 211, 187));
          }
        }
      }
    }
  }

  void updatePieceDisplay(bool initial = false) {
    for (int i = 0; i < pieces.size(); i++) {
      if (initial) {
        sf::Sprite sprite(texPieces);
        sprite.setTextureRect(getPieceTexture(pieces[i]));
        sprite.setOrigin({squareSize / 2, squareSize / 2});
        sprite.setPosition(boardDisplay[i].getPosition());
        pieceDisplay.push_back(sprite);
      } else {
        pieceDisplay[i].setTextureRect(getPieceTexture(pieces[i]));
      }
    }
  }

  // TODO: Separate function for centre of square

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
      return sf::IntRect({0, 60}, pieceSize);
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
      return sf::IntRect({0, 0}, {1, 1});
    }
  }

  int tryGetSquareUnderMouse(sf::Vector2f mousePosition) {
    int i = 0;
    for (auto s : boardDisplay) {
      if (s.getGlobalBounds().contains(mousePosition)) {
        return i;
      }
      i++;
    }
    return -1;
  }
};
