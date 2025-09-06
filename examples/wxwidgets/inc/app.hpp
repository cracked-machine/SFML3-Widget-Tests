#ifndef __APP_HPP__
#define __APP_HPP__

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#include <Logging/BasicLogController.hpp>
#include <SFML/Window/WindowHandle.hpp>
#include <wx/wx.h>

class MyFrame : public wxFrame
{
public:
  wxButton *button;
  wxTextCtrl *textCtrl;

  MyFrame() : wxFrame( nullptr, wxID_ANY, "Hello wxWidgets World" )
  {
    // Simple vertical layout
    wxBoxSizer *sizer = new wxBoxSizer( wxVERTICAL );

    textCtrl = new wxTextCtrl( this, wxID_ANY, "Type here..." );
    button = new wxButton( this, wxID_ANY, "Click Me!" );

    sizer->Add( textCtrl, 0, wxALL | wxEXPAND, 5 );
    sizer->Add( button, 0, wxALL | wxEXPAND, 5 );

    SetSizer( sizer );

    // Bind button event
    button->Bind( wxEVT_BUTTON, &MyFrame::OnButtonClicked, this );
  }

  void OnButtonClicked( wxCommandEvent & )
  {
    wxMessageBox( "Button clicked! Text: " + textCtrl->GetValue(), "Info" );
  }
};

class MyApp : public wxApp
{
public:
  sf::RenderWindow *sf_window = nullptr;
  MyFrame *wx_frame = nullptr;

  virtual bool OnInit() override
  {
    using Logger = Logging::BasicLogController;
    std::unique_ptr<Logger> logger{ std::make_unique<Logger>( "logger", "log.txt" ) };
    spdlog::set_level( spdlog::level::trace );
    SPDLOG_INFO( "Init" );

    wx_frame = new MyFrame();
    wx_frame->Show();

    sf::WindowHandle wx_window_handle = wx_frame->GetHandle();
    sf_window = new sf::RenderWindow( wx_window_handle );

    Bind( wxEVT_IDLE, &MyApp::OnIdle, this );

    return true;
  }

  void OnIdle( wxIdleEvent & )
  {
    if ( !wx_frame->IsShown() )
    {
      sf_window->close();
      ExitMainLoop();
      return;
    }

    while ( const std::optional event = sf_window->pollEvent() )
    {
      if ( event->is<sf::Event::Closed>() ) { wx_frame->Close(); }
    }

    sf_window->clear( sf::Color::Black );
    sf::CircleShape shape( 50.f );
    shape.setFillColor( sf::Color( 100, 250, 50 ) );
    sf_window->draw( shape );
    sf_window->display();
  }
};

wxIMPLEMENT_APP( MyApp );

#endif // __APP_HPP__