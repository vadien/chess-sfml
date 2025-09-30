#include "BoardDisplay.hpp"
#include "PlayerInput.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>
#include <ostream>

bool showSquareLabels = false;
float squareSize = 64;
int hoveredSquare = -1;
int selectedPiece = -1;
int heldPiece = -1;

void forcedMove(BoardDisplay &board, int startSquare, int endSquare) {
  // Any piece will currently 'take' any other piece.
  // FIXME: Pieces will take themselves!
  if (board.pieces[startSquare] == 0) {
    std::cout << "selectedPiece: " << selectedPiece << std::endl;
    return;
  }
  int i = board.pieces[startSquare];
  board.pieces[endSquare] = i;
  board.pieces[startSquare] = 0;
  std::cout << "Forced move: sq " << startSquare << " to sq " << endSquare
            << std::endl;
  std::cout << "startSquare should be " << board.pieces[startSquare]
            << ", endSquare should be " << board.pieces[endSquare] << std::endl;
  std::cout << "startSquare is now " << board.getPieces()[startSquare]
            << ", endSquare is now " << board.getPieces()[endSquare]
            << std::endl;
}

int main() {
  auto inputState = PlayerInput::None;
  auto window = sf::RenderWindow(sf::VideoMode({1280u, 720u}), "Chess in SFML");
  window.setFramerateLimit(60);
  if (!ImGui::SFML::Init(window)) {
    std::cout << "Imgui-SFML failed to init, exiting..." << std::endl;
    return -1;
  }
  BoardDisplay gameBoard = BoardDisplay();
  if (!gameBoard.texPieces.loadFromFile("assets/textures/pieces.png")) {
    std::cerr << "Could not load piece textures" << std::endl;
  }

  gameBoard.generateBoard();
  sf::Clock clock;
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      ImGui::SFML::ProcessEvent(window, *event);

      if (event->is<sf::Event::Closed>()) {
        window.close();
      }

      sf::Vector2f mousePos =
          window.mapPixelToCoords(sf::Mouse::getPosition(window));
      int square = gameBoard.tryGetSquareUnderMouse(mousePos);
      hoveredSquare = square;

      if (const auto *mouseClick =
              event->getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseClick->button == sf::Mouse::Button::Left) {
          if (ImGui::GetIO().WantCaptureMouse) {
            continue;
          }
          if (gameBoard.pieces[hoveredSquare] > 0) {
            heldPiece = hoveredSquare;
          }
        }
      }

      if (const auto *mouseRelease =
              event->getIf<sf::Event::MouseButtonReleased>()) {
        if (mouseRelease->button == sf::Mouse::Button::Left) {
          if (hoveredSquare != heldPiece && heldPiece != -1 &&
              hoveredSquare != -1) {
            forcedMove(gameBoard, heldPiece, hoveredSquare);
            selectedPiece = -1;
            std::cout << "Piece has been dragged to a new square, move made"
                      << std::endl;
          } else if (selectedPiece != -1 && hoveredSquare != -1) {
            forcedMove(gameBoard, selectedPiece, hoveredSquare);
            std::cout << "Clicked on new square with piece selected, move made"
                      << std::endl;
            selectedPiece = -1;
          } else if (selectedPiece == -1 && hoveredSquare == heldPiece &&
                     gameBoard.pieces[hoveredSquare] > 0) {
            selectedPiece = heldPiece;
            std::cout << "Clicked on piece with no piece selected" << std::endl;
          } else {
            selectedPiece = -1;
            std::cout << "Deselecting piece" << std::endl;
          }
          heldPiece = -1;
        }
      }
    }

    gameBoard.squareSize = squareSize;
    gameBoard.updateBoardDisplay(false,
                                 (heldPiece != -1 ? heldPiece : selectedPiece));
    gameBoard.updatePieceDisplay();
    ImGui::SFML::Update(window, clock.restart());

    ImGui::Begin("Board controls");
    // TODO: List all existing pieces
    // TODO: Add input field for FEN strings
    // TODO: Show current board as FEN string
    // TODO: Toggle board shading for legal move squares
    ImGui::Checkbox("Show Square Labels", &showSquareLabels);
    ImGui::BulletText("Hovered Square: %d", hoveredSquare);
    ImGui::BulletText("Selected Piece: %d", selectedPiece);
    ImGui::BulletText("Held Piece: %d", heldPiece);
    ImGui::ShowDemoWindow();
    ImGui::End();

    window.clear();
    for (auto s : gameBoard.getBoard()) {
      window.draw(s);
    }
    for (auto s : gameBoard.getPieceDisplay()) {
      window.draw(s);
    }
    if (showSquareLabels) {
      for (auto l : gameBoard.getSquareLabels()) {
        window.draw(l);
      }
    }
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();
}
