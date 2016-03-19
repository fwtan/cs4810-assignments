#include "image.h"
#include <stdlib.h>
#include <math.h>
// allows the use of min() and max() functions
#include <algorithm>
#include <iostream>
#include <stdio.h>
using namespace std;

// basic functions
template <class T>
static inline T EnforceRange(const T& x, const T& MaxValue) 
{
	return std::min(std::max(T(x), T(0)), T(MaxValue));
}


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
	int width  = outputImage.width();
	int height = outputImage.height();

	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			float rrn = 2 * noise * static_cast<float>(rand())/RAND_MAX - noise;
			float grn = 2 * noise * static_cast<float>(rand())/RAND_MAX - noise;
			float brn = 2 * noise * static_cast<float>(rand())/RAND_MAX - noise;

			float r = pixel(x, y).r;
			float g = pixel(x, y).g;
			float b = pixel(x, y).b;

			float nr = EnforceRange(r + rrn * 255.f, 255.f);
			float ng = EnforceRange(g + grn * 255.f, 255.f);
			float nb = EnforceRange(b + brn * 255.f, 255.f);

			outputImage.pixel(x, y).r = static_cast<unsigned char>(nr);
			outputImage.pixel(x, y).g = static_cast<unsigned char>(ng);
			outputImage.pixel(x, y).b = static_cast<unsigned char>(nb);
		}
	}

	return 1;
}

int Image32::Brighten(const float& brightness,Image32& outputImage) const
{
	int width  = outputImage.width();
	int height = outputImage.height();

	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			float r = pixel(x, y).r;
			float g = pixel(x, y).g;
			float b = pixel(x, y).b;

			r = EnforceRange(r * brightness, 255.f);
			g = EnforceRange(g * brightness, 255.f);
			b = EnforceRange(b * brightness, 255.f);

			outputImage.pixel(x, y).r = static_cast<unsigned char>(r);
			outputImage.pixel(x, y).g = static_cast<unsigned char>(g);
			outputImage.pixel(x, y).b = static_cast<unsigned char>(b);
		}
	}

    return 1;
}

int Image32::Luminance(Image32& outputImage) const
{
	int width  = outputImage.width();
	int height = outputImage.height();

	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			float r = pixel(x, y).r;
			float g = pixel(x, y).g;
			float b = pixel(x, y).b;

			float gray = 0.3f * r + 0.59f * g + 0.11f * b;

			outputImage.pixel(x, y).r = static_cast<unsigned char>(gray);
			outputImage.pixel(x, y).g = static_cast<unsigned char>(gray);
			outputImage.pixel(x, y).b = static_cast<unsigned char>(gray);
		}
	}

	return 1;
}

int Image32::Contrast(const float& contrast,Image32& outputImage) const
{
	int width  = outputImage.width();
	int height = outputImage.height();

	float mean_lum = 0;

	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			float r = pixel(x, y).r;
			float g = pixel(x, y).g;
			float b = pixel(x, y).b;

			mean_lum += 0.3f * r + 0.59f * g + 0.11f * b;
		}
	}

	mean_lum /= (width * height);

	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			float r = pixel(x, y).r;
			float g = pixel(x, y).g;
			float b = pixel(x, y).b;

			float cr = EnforceRange(contrast * (r - mean_lum) + mean_lum, 255.f);
			float cg = EnforceRange(contrast * (g - mean_lum) + mean_lum, 255.f);
			float cb = EnforceRange(contrast * (b - mean_lum) + mean_lum, 255.f);

			outputImage.pixel(x, y).r = static_cast<unsigned char>(cr);
			outputImage.pixel(x, y).g = static_cast<unsigned char>(cg);
			outputImage.pixel(x, y).b = static_cast<unsigned char>(cb);
		}
	}

	return 1;
}

int Image32::Saturate(const float& saturation,Image32& outputImage) const
{
	int width  = outputImage.width();
	int height = outputImage.height();

	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			float r = pixel(x, y).r;
			float g = pixel(x, y).g;
			float b = pixel(x, y).b;

			float gray = 0.3f * r + 0.59f * g + 0.11f * b;

			float sr = EnforceRange(saturation * (r - gray) + gray, 255.f);
			float sg = EnforceRange(saturation * (g - gray) + gray, 255.f);
			float sb = EnforceRange(saturation * (b - gray) + gray, 255.f);

			outputImage.pixel(x, y).r = static_cast<unsigned char>(sr);
			outputImage.pixel(x, y).g = static_cast<unsigned char>(sg);
			outputImage.pixel(x, y).b = static_cast<unsigned char>(sb);
		}
	}

	return 1;
}

int Image32::Quantize(const int& bits,Image32& outputImage) const
{
	float scale  = pow(2, bits);
	float factor = 255.f/(scale - 1);

	int width  = outputImage.width();
	int height = outputImage.height();

	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			float r = pixel(x, y).r;
			float g = pixel(x, y).g;
			float b = pixel(x, y).b;

			float qr = floor(scale * r/256);
			float qg = floor(scale * g/256);
			float qb = floor(scale * b/256);

			qr = EnforceRange(qr * factor, 255.f);
			qg = EnforceRange(qg * factor, 255.f);
			qb = EnforceRange(qb * factor, 255.f);

			outputImage.pixel(x, y).r = static_cast<unsigned char>(qr);
			outputImage.pixel(x, y).g = static_cast<unsigned char>(qg);
			outputImage.pixel(x, y).b = static_cast<unsigned char>(qb);
		}
	}

	return 1;
}

int Image32::RandomDither(const int& bits,Image32& outputImage) const
{
	float scale  = pow(2, bits)-1;
	float factor = 255.f/(scale);
	float dither_lev = scale - 1;

	int width  = outputImage.width();
	int height = outputImage.height();

	float noise_level = 0.5f;

	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			float r = pixel(x, y).r;
			float g = pixel(x, y).g;
			float b = pixel(x, y).b;

			float nr = (2 * noise_level * static_cast<float>(rand())/RAND_MAX - noise_level);
			float ng = (2 * noise_level * static_cast<float>(rand())/RAND_MAX - noise_level);
			float nb = (2 * noise_level * static_cast<float>(rand())/RAND_MAX - noise_level);

			float qr = round(scale * (r/255 + nr/dither_lev));
			float qg = round(scale * (g/255 + ng/dither_lev));
			float qb = round(scale * (b/255 + nb/dither_lev));

			qr = EnforceRange(qr * factor, 255.f);
			qg = EnforceRange(qg * factor, 255.f);
			qb = EnforceRange(qb * factor, 255.f);

			outputImage.pixel(x, y).r = qr;
			outputImage.pixel(x, y).g = qg;
			outputImage.pixel(x, y).b = qb;
		}
	}

	return 1;
}
int Image32::OrderedDither2X2(const int& bits,Image32& outputImage) const
{
	float scale = pow(2, bits)-1;
	float factor = 255.f/scale;

	float thresholds[2][2];
	thresholds[0][0] = 1.f/5.f;
	thresholds[0][1] = 3.f/5.f;
	thresholds[1][0] = 4.f/5.f;
	thresholds[1][1] = 2.f/5.f;

	int width  = outputImage.width();
	int height = outputImage.height();

	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			int i = x % 2;
			int j = y % 2;

			float r = pixel(x, y).r;
			float g = pixel(x, y).g;
			float b = pixel(x, y).b;

			float cr = scale * r/255.f;
			float cg = scale * g/255.f;
			float cb = scale * b/255.f;

			float er = cr - floor(cr);
			float eg = cg - floor(cg);
			float eb = cb - floor(cb);

			if (er > thresholds[i][j])	cr = ceil(cr);
			else 						cr = floor(cr);

			if (eg > thresholds[i][j])	cg = ceil(cg);
			else 						cg = floor(cg);

			if (eb > thresholds[i][j])	cb = ceil(cb);
			else 						cb = floor(cb);

			cr = EnforceRange(cr * factor, 255.f);
			cg = EnforceRange(cg * factor, 255.f);
			cb = EnforceRange(cb * factor, 255.f);

			outputImage.pixel(x, y).r = static_cast<unsigned char>(cr);
			outputImage.pixel(x, y).g = static_cast<unsigned char>(cg);
			outputImage.pixel(x, y).b = static_cast<unsigned char>(cb);
		}
	}

	return 1;
}

int Image32::FloydSteinbergDither(const int& bits,Image32& outputImage) const
{
	float weights[4] = {7.f/16.f, 3.f/16.f, 5.f/16.f, 1.f/16.f};

	float scale  = pow(2, bits);
	float factor = 255.f/(scale - 1);

	int width  = outputImage.width();
	int height = outputImage.height();

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			float r = pixel(x, y).r;
			float g = pixel(x, y).g;
			float b = pixel(x, y).b;

			float sr = floor(scale * r/256);
			float sg = floor(scale * g/256);
			float sb = floor(scale * b/256);

			float qr = floor(EnforceRange(sr * factor, 255.f));
			float qg = floor(EnforceRange(sg * factor, 255.f));
			float qb = floor(EnforceRange(sb * factor, 255.f));

			outputImage.pixel(x, y).r = static_cast<unsigned char>(qr);
			outputImage.pixel(x, y).g = static_cast<unsigned char>(qg);
			outputImage.pixel(x, y).b = static_cast<unsigned char>(qb);

			float er = r - qr;
			float eg = g - qg;
			float eb = b - qb;

			if (x < width - 1)
			{
				outputImage.pixel(x + 1, y).r = EnforceRange(outputImage.pixel(x + 1, y).r + er * weights[0], 255.f);
				outputImage.pixel(x + 1, y).g = EnforceRange(outputImage.pixel(x + 1, y).g + eg * weights[0], 255.f);
				outputImage.pixel(x + 1, y).b = EnforceRange(outputImage.pixel(x + 1, y).b + eb * weights[0], 255.f);

				if (y < height - 1)
				{
					outputImage.pixel(x + 1, y + 1).r = EnforceRange(outputImage.pixel(x + 1, y + 1).r + er * weights[3], 255.f);
					outputImage.pixel(x + 1, y + 1).g = EnforceRange(outputImage.pixel(x + 1, y + 1).g + eg * weights[3], 255.f);
					outputImage.pixel(x + 1, y + 1).b = EnforceRange(outputImage.pixel(x + 1, y + 1).b + eb * weights[3], 255.f);	
				}
			}

			if (y < height - 1)
			{
				outputImage.pixel(x, y + 1).r = EnforceRange(outputImage.pixel(x, y + 1).r + er * weights[2], 255.f);
				outputImage.pixel(x, y + 1).g = EnforceRange(outputImage.pixel(x, y + 1).g + eg * weights[2], 255.f);
				outputImage.pixel(x, y + 1).b = EnforceRange(outputImage.pixel(x, y + 1).b + eb * weights[2], 255.f);


				if (x > 1)
				{
					outputImage.pixel(x - 1, y + 1).r = EnforceRange(outputImage.pixel(x - 1, y + 1).r + er * weights[1], 255.f);
					outputImage.pixel(x - 1, y + 1).g = EnforceRange(outputImage.pixel(x - 1, y + 1).g + eg * weights[1], 255.f);
					outputImage.pixel(x - 1, y + 1).b = EnforceRange(outputImage.pixel(x - 1, y + 1).b + eb * weights[1], 255.f);			
				}
			}
		
		}
	}

	return 1;
}

int Image32::Blur3X3(Image32& outputImage) const
{
	float filter1D[9] = {1.f, 2.f, 1.f, 2.f, 4.f, 2.f, 1.f, 2.f, 1.f};

	int width  = outputImage.width();
	int height = outputImage.height();

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			float sum_r = 0;
			float sum_g = 0;
			float sum_b = 0;

			float sum_wei = 0;

			for (int oy = -1; oy <= 1 ; ++oy)
			{
				int ny = oy + y;
				if (ny < 0 || ny > height - 1)	continue;
				for (int ox = -1; ox <= 1; ++ox)
				{
					int nx = ox + x;
					if (nx < 0 || nx > width - 1)	continue; 

					float wei = filter1D[1 + ox + (1 + oy) * 3];

					sum_r += pixel(nx, ny).r * wei;
					sum_g += pixel(nx, ny).g * wei;
					sum_b += pixel(nx, ny).b * wei;

					sum_wei += wei;
				}
			}

			outputImage.pixel(x, y).r = static_cast<unsigned char>(EnforceRange(sum_r/sum_wei, 255.f));
			outputImage.pixel(x, y).g = static_cast<unsigned char>(EnforceRange(sum_g/sum_wei, 255.f));
			outputImage.pixel(x, y).b = static_cast<unsigned char>(EnforceRange(sum_b/sum_wei, 255.f));
		}
	}

	return 1;
}

int Image32::EdgeDetect3X3(Image32& outputImage) const
{
	float filter1D[9] = {-1.f, -1.f, -1.f, -1.f, 8.f, -1.f, -1.f, -1.f, -1.f};

	int width  = outputImage.width();
	int height = outputImage.height();

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			float sum_r = 0;
			float sum_g = 0;
			float sum_b = 0;

			for (int oy = -1; oy <= 1 ; ++oy)
			{
				int ny = oy + y;
				if (ny < 0 || ny > height - 1)	continue;
				for (int ox = -1; ox <= 1; ++ox)
				{
					int nx = ox + x;
					if (nx < 0 || nx > width - 1)	continue; 

					float wei = filter1D[1 + ox + (1 + oy) * 3];

					sum_r += pixel(nx, ny).r * wei;
					sum_g += pixel(nx, ny).g * wei;
					sum_b += pixel(nx, ny).b * wei;
				}
			}

			outputImage.pixel(x, y).r = static_cast<unsigned char>(EnforceRange(sum_r, 255.f));
			outputImage.pixel(x, y).g = static_cast<unsigned char>(EnforceRange(sum_g, 255.f));
			outputImage.pixel(x, y).b = static_cast<unsigned char>(EnforceRange(sum_b, 255.f));
		}
	}
	return 1;
}

int Image32::ScaleNearest(const float& scaleFactor,Image32& outputImage) const
{
	int src_width  = w;
	int src_height = h;

	int des_width  = scaleFactor * src_width;
	int des_height = scaleFactor * src_height;

	outputImage.setSize(des_width, des_height);

	for (int y = 0; y < des_height; ++y)
	{
		float sy = y/scaleFactor;
		if (sy < 0 || sy > src_height - 1) continue;
		for (int x = 0; x < des_width; ++x)
		{
			float sx = x/scaleFactor;
			if (sx < 0 || sx > src_width - 1) continue;
			outputImage.pixel(x, y) = NearestSample(sx, sy);
		}
	}

	return 1;
}

int Image32::ScaleBilinear(const float& scaleFactor,Image32& outputImage) const
{
	int src_width  = w;
	int src_height = h;

	int des_width  = scaleFactor * src_width;
	int des_height = scaleFactor * src_height;

	outputImage.setSize(des_width, des_height);

	for (int y = 0; y < des_height; ++y)
	{
		float sy = y/scaleFactor;
		if (sy < 0 || sy > src_height - 1) continue;
		for (int x = 0; x < des_width; ++x)
		{
			float sx = x/scaleFactor;
			if (sx < 0 || sx > src_width - 1) continue;
			outputImage.pixel(x, y) = BilinearSample(sx, sy);
		}
	}

	return 1;
}

int Image32::ScaleGaussian(const float& scaleFactor,Image32& outputImage) const
{
	int src_width  = w;
	int src_height = h;

	int des_width  = scaleFactor * src_width;
	int des_height = scaleFactor * src_height;

	outputImage.setSize(des_width, des_height);

	float radius   = 1.f;
	float variance = 0.25f;

	for (int y = 0; y < des_height; ++y)
	{
		float sy = y/scaleFactor;
		if (sy < 0 || sy > src_height - 1) continue;
		for (int x = 0; x < des_width; ++x)
		{
			float sx = x/scaleFactor;
			if (sx < 0 || sx > src_width - 1) continue;
			outputImage.pixel(x, y) = GaussianSample(sx, sy, variance, radius);
		}
	}

	return 1;
}

bool Image32::contain(const float& x, const float& y) const
{
	return (x >= 0 && y >= 0 && x < w && y < h);
}

int Image32::RotateNearest(const float& angle, Image32& outputImage) const
{
	float theta = 3.141592653 * angle/180.f;
	float cenx  = 0.5f * w;
	float ceny  = 0.5f * h;

	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			float ox = x - cenx;
			float oy = y - ceny;

			float u = cos(theta) * ox - sin(theta) * oy;
			float v = sin(theta) * ox + cos(theta) * oy;

			float su = u + cenx;
			float sv = v + ceny;

			if (contain(su, sv))
			{
				outputImage(x, y) = NearestSample(su, sv);
			}
			else
			{
				outputImage(x, y).r = 0;
				outputImage(x, y).g = 0;
				outputImage(x, y).b = 0;
			}
		}
	}

	return 1;
}

int Image32::RotateBilinear(const float& angle,Image32& outputImage) const
{
	float theta = 3.141592653 * angle/180.f;
	float cenx  = 0.5f * w;
	float ceny  = 0.5f * h;

	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			float ox = x - cenx;
			float oy = y - ceny;

			float u = cos(theta) * ox - sin(theta) * oy;
			float v = sin(theta) * ox + cos(theta) * oy;

			float su = u + cenx;
			float sv = v + ceny;

			if (contain(su, sv))
			{
				outputImage(x, y) = BilinearSample(su, sv);
			}
			else
			{
				outputImage(x, y).r = 0;
				outputImage(x, y).g = 0;
				outputImage(x, y).b = 0;
			}
		}
	}

	return 1;
}
	
int Image32::RotateGaussian(const float& angle,Image32& outputImage) const
{
	float theta = 3.141592653 * angle/180.f;
	float cenx  = 0.5f * w;
	float ceny  = 0.5f * h;

	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			float ox = x - cenx;
			float oy = y - ceny;

			float u = cos(theta) * ox - sin(theta) * oy;
			float v = sin(theta) * ox + cos(theta) * oy;

			float su = u + cenx;
			float sv = v + ceny;

			if (contain(su, sv))
			{
				outputImage(x, y) = GaussianSample(su, sv, 0.25f, 1.f);
			}
			else
			{
				outputImage(x, y).r = 0;
				outputImage(x, y).g = 0;
				outputImage(x, y).b = 0;
			}
		}
	}

	return 1;
}


int Image32::SetAlpha(const Image32& matte)
{
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			pixel(x,y).a = matte(x, y).r;
		}
	}

	return 1;
}

int Image32::Composite(const Image32& overlay,Image32& outputImage) const
{
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			float w = pixel(x,y).a/255.f;
			outputImage(x, y).r = EnforceRange(w * overlay(x,y).r + (1-w) * pixel(x,y).r, 255.f);
			outputImage(x, y).g = EnforceRange(w * overlay(x,y).g + (1-w) * pixel(x,y).g, 255.f);
			outputImage(x, y).b = EnforceRange(w * overlay(x,y).b + (1-w) * pixel(x,y).b, 255.f);
		}
	}
	return 1;
}

int Image32::CrossDissolve(const Image32& source,const Image32& destination,const float& blendWeight,Image32& outputImage)
{
	int width  = source.width();
	int height = source.height();

	float w = blendWeight;

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			outputImage(x, y).r = EnforceRange(w * destination(x,y).r + (1-w) * source(x,y).r, 255.f);
			outputImage(x, y).g = EnforceRange(w * destination(x,y).g + (1-w) * source(x,y).g, 255.f);
			outputImage(x, y).b = EnforceRange(w * destination(x,y).b + (1-w) * source(x,y).b, 255.f);
		}
	}

	return 1;
}

int Image32::Warp(const OrientedLineSegmentPairs& olsp, Image32& outputImage) const
{

	return 0;
}

int Image32::FunFilter(Image32& outputImage) const
{
	float cenx  = 0.5f * w;
	float ceny  = 0.5f * h;

	float theta = 256;

	for (int y = 0; y < h; ++y)
	{
		float dy = y - ceny;

		for (int x = 0; x < w; ++x)
		{
			float dx = x - cenx;

			float r = sqrt(dx * dx + dy * dy);
			float phi = 3.141592653 * r/theta;

			float su = dx * cos(phi) - dy * sin(phi) + cenx;
			float sv = dx * sin(phi) + dy * cos(phi) + ceny;

			if (contain(su, sv))
			{
				outputImage(x, y) = pixel(su, sv);
			}
		}
	}

	return 1;
}

int Image32::Crop(const int& x1,const int& y1,const int& x2,const int& y2,Image32& outputImage) const
{
	for (int y = y1; y <= y2; ++y)
	{
		for (int x = x1; x <= x2; ++x)
		{
			outputImage(x - x1, y - y1).r = pixel(x, y).r;
			outputImage(x - x1, y - y1).g = pixel(x, y).g;
			outputImage(x - x1, y - y1).b = pixel(x, y).b;
		}
	}

	return 1;
}

Pixel32 Image32::NearestSample(const float& x,const float& y) const
{
	Pixel32 s;
	s.r = pixel(x+0.5f, y+0.5f).r;
	s.g = pixel(x+0.5f, y+0.5f).g;
	s.b = pixel(x+0.5f, y+0.5f).b;

	return s;
}

Pixel32 Image32::BilinearSample(const float& x,const float& y) const
{
	int x1 = x;
	int x2 = x1 + 1;
	float dx = x - x1;

	int y1 = y;
	int y2 = y1 + 1;
	float dy = y - y1;

	float ir1 = (1 - dx) * pixel(x1, y1).r + dx * pixel(std::min(x1 + 1, w - 1), y1).r;
	float ir2 = (1 - dx) * pixel(x1, std::min(y1 + 1, h - 1)).r + dx * pixel(std::min(x1 + 1, w - 1), std::min(y1 + 1, h - 1)).r;
	float ir = EnforceRange((1 - dy) * ir1 + dy * ir2, 255.f);

	float ig1 = (1 - dx) * pixel(x1, y1).g + dx * pixel(std::min(x1 + 1, w - 1), y1).g;
	float ig2 = (1 - dx) * pixel(x1, std::min(y1 + 1, h - 1)).g + dx * pixel(std::min(x1 + 1, w - 1), std::min(y1 + 1, h - 1)).g;
	float ig = EnforceRange((1 - dy) * ig1 + dy * ig2, 255.f);

	float ib1 = (1 - dx) * pixel(x1, y1).b + dx * pixel(std::min(x1 + 1, w - 1), y1).b;
	float ib2 = (1 - dx) * pixel(x1, std::min(y1 + 1, h - 1)).b + dx * pixel(std::min(x1 + 1, w - 1), std::min(y1 + 1, h - 1)).b;
	float ib = EnforceRange((1 - dy) * ib1 + dy * ib2, 255.f);

	Pixel32 s;
	s.r = ir;
	s.g = ig;
	s.b = ib;

	return s;
}

Pixel32 Image32::GaussianSample(const float& x, const float& y, const float& variance, const float& radius) const
{
	float sum_r = 0;
	float sum_g = 0;
	float sum_b = 0;
	float sum_w = 0;

	for (int oy = -radius; oy <= radius; ++oy)
	{
		int ny = oy + y + 0.5;
		float dy = ny - y;
		if (ny < 0 || ny > h - 1)	continue;
		for (int ox = -radius; ox <= radius; ++ox)
		{
			int nx = ox + x + 0.5;
			float dx = nx - x;
			if (nx < 0 || nx > w - 1)	continue;

			float wei = exp(-0.5f * (dx * dx + dy * dy)/variance);

			sum_r += wei * pixel(nx, ny).r;
			sum_g += wei * pixel(nx, ny).g;
			sum_b += wei * pixel(nx, ny).b;

			sum_w += wei;
		}
	}

	Pixel32 s;

	s.r = EnforceRange(sum_r/sum_w, 255.f);
	s.g = EnforceRange(sum_g/sum_w, 255.f);
	s.b = EnforceRange(sum_b/sum_w, 255.f);

	return s;
}
