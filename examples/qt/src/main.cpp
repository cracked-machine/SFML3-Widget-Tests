
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>

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

  // create the window
  sf::RenderWindow window( sf::VideoMode( { 800, 600 } ), "My window" );

  // run the program as long as the window is open
  while ( window.isOpen() )
  {
    // check all the window's events that were triggered since the last iteration of the loop
    while ( const std::optional event = window.pollEvent() )
    {
      // "close requested" event: we close the window
      if ( event->is<sf::Event::Closed>() ) window.close();
    }

    // clear the window with black color
    window.clear( sf::Color::Black );

    sf::CircleShape shape( 50.f );

    // set the shape color to green
    shape.setFillColor( sf::Color( 100, 250, 50 ) );

    // end the current frame
    window.display();
  }
}
