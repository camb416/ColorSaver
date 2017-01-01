#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ColorSaverApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void ColorSaverApp::setup()
{
}

void ColorSaverApp::mouseDown( MouseEvent event )
{
}

void ColorSaverApp::update()
{
}

void ColorSaverApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( ColorSaverApp, RendererGl )
