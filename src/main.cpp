#include "BoardDisplay.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>

int main() {
  bool showSquareLabels = false;
  float squareSize = 64;
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
    }

    gameBoard.squareSize = squareSize;
    ImGui::SFML::Update(window, clock.restart());

    ImGui::Begin("Board controls");
    // TODO: List all existing pieces
    // TODO: Add input field for FEN strings
    // TODO: Show current board as FEN string
    // TODO: Toggle board shading for legal move squares
    ImGui::Checkbox("Show Square Labels", &showSquareLabels);
    ImGui::ShowDemoWindow();
    ImGui::End();

    window.clear();
    for (auto s : gameBoard.getBoard()) {
      window.draw(s);
    }
    if (showSquareLabels) {
      for (auto l : gameBoard.getSquareLabels()) {
        window.draw(l);
      }
    }
    for (auto s : gameBoard.getPieces()) {
      window.draw(s);
    }
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();
}
