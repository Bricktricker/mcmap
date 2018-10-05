#pragma once
//C++ Header
#include <vector>
#include <fstream>
//My-Header
#include "PNGWriter.h"
#include "png.h"

class CachedPNGWriter : public PNGWriter
{
public:
	CachedPNGWriter(const size_t origW, const size_t origH);
	virtual ~CachedPNGWriter() = default;
	bool open(const size_t width, const size_t height) override; //creats imageBuffer
	bool addPart(const int startx, const int starty, const int width, const int height);
	virtual bool write(const std::string& path) override;
	uint8_t* getPixel(const size_t x, const size_t y) override;
	void discardPart();
	virtual bool compose(const std::string& path );

protected:

	struct ImagePart {
		int x, y, width, height;
		std::string filename;
		std::fstream file;
		png_structp pngPtr;
		png_infop pngInfo;

		ImagePart(const std::string& _file, const int _x, const int _y, const int _w, const int _h)
			: x(_x), y(_y), width(_w), height(_h), filename(_file), file{}, pngPtr(nullptr), pngInfo(nullptr) {}

		ImagePart(const ImagePart& part)
			: x(part.x), y(part.y), width(part.width), height(part.height), filename(part.filename), file{}, pngPtr(nullptr), pngInfo(nullptr) {}

		//Not needed
		ImagePart& operator=(const ImagePart& part) {
			this->x = part.x;
			this->y = part.y;
			this->width = part.width;
			this->height = part.height;
			this->filename = part.filename;
			if (part.file.is_open())
				file.open(filename);
			pngPtr = nullptr;
			pngInfo = nullptr;
			return *this;
		}
	};

	size_t m_currWidth;
	size_t m_currHeight;
	size_t m_origW;
	size_t m_origH;
	int offsetX;
	int offsetY;

	std::vector<ImagePart> m_partList;
	std::vector<uint8_t> m_buffer;
};
