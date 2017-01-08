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

struct Circle{
    vec2 pos;
    vec2 origin;
    float size;
    Color color;
};

class ColorSaverApp : public App {
public:
    void setup() override;
    void mouseDown( MouseEvent event ) override;
    void mouseUp( MouseEvent event ) override;
    void update() override;
    void draw() override;
    
    static void prepare( Settings *settings );

    
private:
    params::InterfaceGlRef	mParams;
    ColorA					mColor;
    
    std::vector<PaletteData> mPalettes;
    
    int startFrame;
    
//    std::vector<Rectf*> mRectangles;
    std::vector<Circle*> mCircles;
    std::vector<Color*> mRectColors;
    
    bool isMouseDown;
    
    vector<string>			mEnumNames;
    int						mEnumSelection;
    
    void button();
    float mSpeed;
    float multiplier;
    float multiplierDest;
    ColorA bg;
    
};

void ColorSaverApp::button()
{
    mCircles.clear();
    console() << "Reset!" << endl;
    //mParams->setOptions( "text", "label=`Clicked!`" );
}

void ColorSaverApp::prepare(Settings *settings){
    settings->setWindowSize( 1280, 720 );
    settings->setHighDensityDisplayEnabled();
}

void ColorSaverApp::setup()
{
    Config::instance()->reload();
    
    isMouseDown = false;
    //  mRectangles.clear();
    multiplier = multiplierDest = 0.0f;
    
    bg = ColorA(0,0,0,1);
    
    
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
    for(int j = 0; j< numPalettes; j++){
        mParams->setOptions(mPalettes.at(j).name, "opened=false");

    }
    
    mParams->addParam("Background",&bg);
    mSpeed = 0.025f;
    // Setup some basic parameters.
    mParams->addParam( "Speed", &mSpeed ).min( 0.01f ).max( 0.1f ).keyIncr( "z" ).keyDecr( "Z" ).precision( 3).step( 0.002f );
    
    mParams->addButton( "Reset", bind( &ColorSaverApp::button, this ) );

    
    // Add an enum (list) selector.
    mEnumSelection = 0;
    
    
    
    
    
    //  auto imageSource = Config::instance()->getBackgroundImage();
    
    
    //cout << imageSource;
    
    
}

void ColorSaverApp::mouseDown( MouseEvent event )
{
    isMouseDown = true;
    multiplierDest = 0.0f;
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
    multiplierDest = 1.0f;
}

void ColorSaverApp::update()
{
    
    multiplier += (multiplierDest-multiplier)/4.0f;
    if(isMouseDown){
        
        Color color;
        
      //  color = mPalettes.at(0).mColors.at(randInt(mPalettes.at(0).mColors.size())).color;
      //  mRectColors.push_back(new Color(color));
        
        int howRandom = mPalettes.at(mEnumSelection).mColors.size();
        int thisRandom = randInt(howRandom);
        
        ivec2 mousePos = getMousePos()-getWindowPos()-(getWindowSize()/2);
        float x1 = (float)mousePos.x;
        float y1 = (float)mousePos.y;

        Circle * c = new Circle();
        c->pos = c->origin = vec2(x1,y1);
        c->size = randFloat()*(float)thisRandom*5.0f+5.0f;
        c->color = mPalettes.at(mEnumSelection).mColors.at(thisRandom).color;
        
        mCircles.push_back( c);
        
        startFrame = getElapsedFrames();
    } //else {
        for(int i=0;i<mCircles.size();i++){
            mCircles.at(i)->pos = cos(((float)(getElapsedFrames()-startFrame+(float)i)*mSpeed)*multiplier)*(1.0f) * mCircles.at(i)->origin;
        }
    //}
}

void ColorSaverApp::draw()
{
    gl::clear( bg );
    
    
    for(int i=0;i<mCircles.size();i++){
        gl::pushMatrices();
        gl::color( mCircles.at(i)->color );
        vec2 circlePos = mCircles.at(i)->pos;
        gl::translate(getWindowSize()/2);
        gl::drawSolidCircle(circlePos,mCircles.at(i)->size);
        
        // highlight
        //gl::color(ColorA(1,1,1,0.5f));
        //gl::drawSolidCircle(circlePos-mCircles.at(i)->size/3,mCircles.at(i)->size/2);
      
        gl::popMatrices();
    }
    
    
    // if( !mIsSelected ){
    
    mParams->draw();
    
}

//CINDER_APP( ColorSaverApp, RendererGl )
CINDER_APP( ColorSaverApp, RendererGl( RendererGl::Options().msaa( 4 ) ), ColorSaverApp::prepare )

