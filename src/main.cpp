#include "BoardDisplay.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>

int main() {
  float squareSize = 64;
  auto window = sf::RenderWindow(sf::VideoMode({1280u, 720u}), "Chess in SFML");
  window.setFramerateLimit(60);
  if (!ImGui::SFML::Init(window)) {
    std::cout << "Imgui-SFML failed to init, exiting..." << std::endl;
    return -1;
  }
  BoardDisplay gameBoard = BoardDisplay();
  gameBoard.texPieces.loadFromFile("ChessPiecesArray.png");
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
    if (ImGui::Button("Reset board size")) {
      squareSize = 64.0f;
    }
    ImGui::SliderFloat("SliderFloat (0 -> 1)", &squareSize, 0.0f, 100.0f,
                       "%.0f");
    ImGui::ShowDemoWindow();
    ImGui::End();

    window.clear();
    for (auto s : gameBoard.getBoard()) {
      window.draw(s);
    }
    for (auto s : gameBoard.getPieces()) {
      window.draw(s);
    }
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();
}
