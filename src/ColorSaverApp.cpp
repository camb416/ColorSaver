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
    
    std::vector<PaletteData> mPalettes;
    
    std::vector<Rectf*> mRectangles;
    std::vector<Color*> mRectColors;
    
    bool isMouseDown;
    
    vector<string>			mEnumNames;
    int						mEnumSelection;
    
};

void ColorSaverApp::setup()
{
    Config::instance()->reload();
    
    isMouseDown = false;
    //  mRectangles.clear();
    
    
    
    // Create the interface and give it a name.
    mParams = params::InterfaceGl::create( getWindow(), "App parameters", toPixels( ivec2( 200, 400 ) ) );
    
    
    
    
    mPalettes = Config::instance()->getPaletteData();
    
    int numPalettes = mPalettes.size();
    
    for(int j = 0; j< numPalettes; j++){
        mEnumNames.push_back(mPalettes.at(j).name);
    }
    
    mParams->addParam( "Palette", mEnumNames, &mEnumSelection )
    .keyDecr( "[" )
    .keyIncr( "]" )
    .updateFn( [this] { console() << "enum updated: " << mEnumNames[mEnumSelection] << endl; } );
    
    
    for(int j = 0; j< numPalettes; j++){
        int numColors = mPalettes.at(j).mColors.size();
        for(int i=0;i<numColors;i++){
            
            mParams->addParam( mPalettes.at(j).name + "_" + mPalettes.at(j).mColors.at(i).name, &mPalettes.at(j).mColors.at(i).color ).group( mPalettes.at(j).name ).label(mPalettes.at(j).mColors.at(i).name);
            
            
        }
    }
    // Add an enum (list) selector.
    mEnumSelection = 0;
    
    
    
    
    
    //  auto imageSource = Config::instance()->getBackgroundImage();
    
    
    //cout << imageSource;
    
    
}

void ColorSaverApp::mouseDown( MouseEvent event )
{
    isMouseDown = true;
    
//    Config::instance()->reload();
//    mPalettes = Config::instance()->getPaletteData();
//    
//    int numPalettes = mPalettes.size();
//    for(int j = 0; j< numPalettes; j++){
//        int numColors = mPalettes.at(j).mColors.size();
//        
//        for(int i=0;i<numColors;i++){
//            
//            mParams->addParam( mPalettes.at(j).mColors.at(i).name, &mPalettes.at(j).mColors.at(i).color ).group( mPalettes.at(j).name );
//            
//        }
//    }
}
void ColorSaverApp::mouseUp( MouseEvent event ){
    isMouseDown = false;
}

void ColorSaverApp::update()
{
    if(isMouseDown){
        
        Color color;
        
        color = mPalettes.at(0).mColors.at(randInt(mPalettes.at(0).mColors.size())).color;
        mRectColors.push_back(new Color(color));
        
        ivec2 mousePos = getMousePos()-getWindowPos();
        float x1 = (float)mousePos.x;
        float y1 = (float)mousePos.y;
        float x2 = x1 + 10;
        float y2 = y1 + 10;
        mRectangles.push_back( new Rectf( x1,y1,x2,y2 ));
    }
}

void ColorSaverApp::draw()
{
    gl::clear( Color( 0, 0, 0 ) );
    
    
    for(int i=0;i<mRectangles.size();i++){
        
        gl::color( *mRectColors.at(i) );
        gl::drawSolidRect(*mRectangles.at(i) );
    }
    
    
    // if( !mIsSelected ){
    
    mParams->draw();
    
}

CINDER_APP( ColorSaverApp, RendererGl )
