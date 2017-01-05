
#include "Config.h"

#include "cinder/app/App.h"
#include "cinder/Log.h"
#include "cinder/ImageIo.h"
#include "cinder/System.h"

using namespace std;
using namespace ci;

#define LOG_EXCEPTION( exc )	{ CI_LOG_E( "exception caught: " << System::demangleTypeName( typeid( exc ).name() ) << ", what: " << exc.what() ); }

Config::Config()
{
	reload();
}

void Config::reload()
{
	try {
		mData = JsonTree( app::loadAsset( "config.json" ) );

		loadGearData();

		CI_LOG_V( "successfully loaded config.json" );
	}
	catch( Exception &exc ) {
		LOG_EXCEPTION( exc );
	}
}

float Config::getDecentSpeed() const
{
	float result = 100;
	if( mData.hasChild( "decent-speed" ) )
		result = mData.getValueForKey<float>( "decent-speed" );

	return result;
}

ImageSourceRef Config::getBackgroundImage() const
{
	ImageSourceRef result;

	try {
		string imageName = mData.getValueForKey( "background" );
		result = loadImage( app::loadAsset( imageName ) );
	}
	catch( Exception &exc ) {
		LOG_EXCEPTION( exc );
	}

	return result;
}

void Config::loadGearData()
{
    cout << "seriously?";
	mGears.clear();

//	for( const auto &gear : mData["gears"] ) {
//		string imageFilename = gear.getValue();
//
//		auto tex = gl::Texture::create( loadImage( app::loadAsset( imageFilename ) ) );
//
//		mGears.push_back( GearData() );
//		mGears.back().mImageTex = tex;
//	}
    
   //auto colors = mData["colors"];
    
    cout << "...";
    
    mColors.clear();
    for( const auto &color: mData["colors"] ) {
       
        
        string colorName = color.getValueForKey("name");
        auto theColor = color["rgb"];
        int r = theColor[0].getValue<int>();
        int g = theColor[1].getValue<int>();
        int b = theColor[2].getValue<int>();
        mColors.push_back(ColorData());
        mColors.back().name = colorName;
        mColors.back().color = ColorA8u(r,g,b,255);
      //  mColors.back().color = ColorA(1,1,1,1);
        
        cout << r << "," << g << "," << b << "\n";
    }
}

// ----------------------------------------------------------------------------------------------------
// MARK: - Singleton Access
// ----------------------------------------------------------------------------------------------------

// static
Config* Config::instance()
{
	static Config sInstance;
	return &sInstance;
}
