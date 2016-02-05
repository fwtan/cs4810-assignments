#include "image.h"
#include <stdlib.h>
#include <math.h>

// allows the use of min() and max() functions
#include <algorithm>
#include <iostream>
#include <stdio.h>
using namespace std;


Pixel::Pixel(const Pixel32& p)
{
	r = p.r/255.f;
	g = p.g/255.f;
	b = p.b/255.f;
}

Pixel32::Pixel32(const Pixel& p)
{
	r = static_cast<unsigned char>(std::max(std::min(p.r * 255.f, 255.f), 0.f));
	g = static_cast<unsigned char>(std::max(std::min(p.g * 255.f, 255.f), 0.f));
	b = static_cast<unsigned char>(std::max(std::min(p.b * 255.f, 255.f), 0.f));
}

int Image32::AddRandomNoise(const float& noise,Image32& outputImage) const
{
	int width = outputImage.width();
	int height = outputImage.height();

	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			float rrn = 2 * noise * static_cast<float>(rand())/RAND_MAX - noise;
			float grn = 2 * noise * static_cast<float>(rand())/RAND_MAX - noise;
			float brn = 2 * noise * static_cast<float>(rand())/RAND_MAX - noise;

			float r = outputImage.pixel(x, y).r;
			float g = outputImage.pixel(x, y).g;
			float b = outputImage.pixel(x, y).b;

			float nr = std::max(std::min(r * (1 + rrn), 255.f), 0.f);
			float ng = std::max(std::min(g * (1 + grn), 255.f), 0.f);
			float nb = std::max(std::min(b * (1 + brn), 255.f), 0.f);

			outputImage.pixel(x, y).r = nr;
			outputImage.pixel(x, y).g = ng;
			outputImage.pixel(x, y).b = nb;
		}
	}

	return 0;
}

int Image32::Brighten(const float& brightness,Image32& outputImage) const
{
        return 0;
}

int Image32::Luminance(Image32& outputImage) const
{
	return 0;
}

int Image32::Contrast(const float& contrast,Image32& outputImage) const
{
	return 0;
}

int Image32::Saturate(const float& saturation,Image32& outputImage) const
{
	return 0;
}

int Image32::Quantize(const int& bits,Image32& outputImage) const
{
	float scale = pow(2, bits);
	float factor = 255.f/(scale - 1);

	int width = outputImage.width();
	int height = outputImage.height();

	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			float r = outputImage.pixel(x, y).r;
			float g = outputImage.pixel(x, y).g;
			float b = outputImage.pixel(x, y).b;

			float nr = floor(scale * r/256);
			float nb = floor(scale * g/256);
			float ng = floor(scale * b/256);

			nr = std::max(std::min(nr * factor, 255.f), 0.f);
			ng = std::max(std::min(ng * factor, 255.f), 0.f);
			nb = std::max(std::min(nb * factor, 255.f), 0.f);

			outputImage.pixel(x, y).r = nr;
			outputImage.pixel(x, y).g = ng;
			outputImage.pixel(x, y).b = nb;
		}
	}


	return 0;
}

int Image32::RandomDither(const int& bits,Image32& outputImage) const
{
	return 0;
}
int Image32::OrderedDither2X2(const int& bits,Image32& outputImage) const
{
	return 0;
}

int Image32::FloydSteinbergDither(const int& bits,Image32& outputImage) const
{
	return 0;
}

int Image32::Blur3X3(Image32& outputImage) const
{
	return 0;
}

int Image32::EdgeDetect3X3(Image32& outputImage) const
{
	return 0;
}
int Image32::ScaleNearest(const float& scaleFactor,Image32& outputImage) const
{
	return 0;
}

int Image32::ScaleBilinear(const float& scaleFactor,Image32& outputImage) const
{
	return 0;
}

int Image32::ScaleGaussian(const float& scaleFactor,Image32& outputImage) const
{
	return 0;
}

int Image32::RotateNearest(const float& angle,Image32& outputImage) const
{
	return 0;
}

int Image32::RotateBilinear(const float& angle,Image32& outputImage) const
{
	return 0;
}
	
int Image32::RotateGaussian(const float& angle,Image32& outputImage) const
{
	return 0;
}


int Image32::SetAlpha(const Image32& matte)
{
	return 0;
}

int Image32::Composite(const Image32& overlay,Image32& outputImage) const
{
	return 0;
}

int Image32::CrossDissolve(const Image32& source,const Image32& destination,const float& blendWeight,Image32& ouputImage)
{
	return 0;
}
int Image32::Warp(const OrientedLineSegmentPairs& olsp,Image32& outputImage) const
{
	return 0;
}

int Image32::FunFilter(Image32& outputImage) const
{
	return 0;
}

int Image32::Crop(const int& x1,const int& y1,const int& x2,const int& y2,Image32& outputImage) const
{
	return 0;
}

Pixel32 Image32::NearestSample(const float& x,const float& y) const
{
	return Pixel32();
}

Pixel32 Image32::BilinearSample(const float& x,const float& y) const
{
	return Pixel32();
}

Pixel32 Image32::GaussianSample(const float& x,const float& y,const float& variance,const float& radius) const
{
	return Pixel32();
}
