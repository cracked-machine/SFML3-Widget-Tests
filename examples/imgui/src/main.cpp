
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <imgui.h>

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#include <Logging/BasicLogController.hpp>

int main()
{
  // Logging: make sure errors - exceptions and failed asserts - go to log file
  fclose( stderr );

  using Logger = ImGuiExample::Logging::BasicLogController;
  std::unique_ptr<Logger> logger{ std::make_unique<Logger>( "logger", "log.txt" ) };
  spdlog::set_level( spdlog::level::trace );

  SPDLOG_INFO( "Init" );

  sf::RenderWindow window( sf::VideoMode( { 640, 480 } ), "ImGui + SFML = <3" );
  window.setFramerateLimit( 60 );
  std::ignore = ImGui::SFML::Init( window );

  sf::CircleShape shape( 100.f );
  shape.setFillColor( sf::Color::Green );

  sf::Clock deltaClock;
  while ( window.isOpen() )
  {
    while ( const auto event = window.pollEvent() )
    {
      ImGui::SFML::ProcessEvent( window, *event );

      if ( event->is<sf::Event::Closed>() ) { window.close(); }
    }

    ImGui::SFML::Update( window, deltaClock.restart() );

    ImGui::ShowDemoWindow();

    ImGui::Begin( "Hello, world!" );
    ImGui::Button( "Look at this pretty button" );
    ImGui::End();

    window.clear();
    window.draw( shape );
    ImGui::SFML::Render( window );
    window.display();
  }

  ImGui::SFML::Shutdown();
}
