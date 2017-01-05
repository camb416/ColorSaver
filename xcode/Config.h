
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

class Config {
  public:

	// singleton access
	static Config* instance();

	void reload();
	const std::vector<GearData>&	getGearData() const	{ return mGears; }
    
    const std::vector<ColorData>&   getColorData() const { return mColors; }

	ci::ImageSourceRef	getBackgroundImage() const;
	float getDecentSpeed() const;

  private:
	Config();

	void loadGearData();

	ci::JsonTree			mData;
	std::vector<GearData>	mGears;
    std::vector<ColorData> mColors;
};
