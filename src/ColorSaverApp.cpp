#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"

#include "cinder/Rand.h"
#include <string>

#include "Config.h"



using namespace ci;
using namespace ci::app;
using namespace std;

class ColorSaverApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
    void mouseUp( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
private:
    params::InterfaceGlRef	mParams;
    ColorA					mColor;
    
    std::vector<ColorData> mColors;
    
    std::vector<Rectf*> mRectangles;
    
    bool isMouseDown;

};

void ColorSaverApp::setup()
{
   // Config::instance()->reload();
   
    isMouseDown = false;
  //  mRectangles.clear();
    
    // Create the interface and give it a name.
   mParams = params::InterfaceGl::create( getWindow(), "App parameters", toPixels( ivec2( 200, 400 ) ) );
    
    
    
    mColors = Config::instance()->getColorData();
    
    int numColors = mColors.size();
    
    for(int i=0;i<numColors;i++){
        
       mParams->addParam( mColors.at(i).name, &mColors.at(i).color );

        
    }
 
   
  //  auto imageSource = Config::instance()->getBackgroundImage();

    
    //cout << imageSource;
    
    
}

void ColorSaverApp::mouseDown( MouseEvent event )
{
    isMouseDown = true;
    Config::instance()->reload();
    mColors = Config::instance()->getColorData();
    
    int numColors = mColors.size();
    
    for(int i=0;i<numColors;i++){
        
        mParams->addParam( mColors.at(i).name, &mColors.at(i).color );
        
        
    }
}
void ColorSaverApp::mouseUp( MouseEvent event ){
    isMouseDown = false;
}

void ColorSaverApp::update()
{
    if(isMouseDown){
        ivec2 mousePos = getMousePos();
        float x1 = randFloat(-.1,.1) + (float)mousePos.x;
        float y1 = randFloat(-.1,.1) + (float)mousePos.y;
        float x2 = x1 + 10;
        float y2 = y1 + 10;
        mRectangles.push_back( new Rectf( x1,y1,1,1 ));
    }
}

void ColorSaverApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );

    Color color = Color::gray( 0.34f );

    gl::color( color );
    for(int i=0;i<mRectangles.size();i++){
        gl::drawSolidRect(*mRectangles.at(i) );
    }
    
    
   // if( !mIsSelected ){
   
        mParams->draw();
    
}

CINDER_APP( ColorSaverApp, RendererGl )
