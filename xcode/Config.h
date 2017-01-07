
#pragma once

#include "cinder/Json.h"
#include "cinder/gl/Texture.h"
#include "cinder/Color.h"

struct GearData {
	ci::gl::TextureRef	mImageTex;
};

struct ColorData {
    std::string name;
    cinder::ColorA color;
};

struct PaletteData {
    std::string name;
    std::vector<ColorData> mColors;
};

class Config {
  public:

	// singleton access
	static Config* instance();

	void reload();
	const std::vector<GearData>&	getGearData() const	{ return mGears; }
    
    const std::vector<PaletteData>&   getPaletteData() const { return mPalettes; }

	ci::ImageSourceRef	getBackgroundImage() const;
	float getDecentSpeed() const;

  private:
	Config();

	void loadGearData();

	ci::JsonTree			mData;
	std::vector<GearData>	mGears;
    std::vector<PaletteData> mPalettes;
};
