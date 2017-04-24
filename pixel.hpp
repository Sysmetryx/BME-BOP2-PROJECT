
/*
________________________________________________________________________________________________________________________________________
||____________________________________________________________________________________________________________________________________||
||                                                                                                                                    ||
||																																	  ||
||							Budapesti Műszaki és Gazdaságtudományi Egyetem, 2016-2017, Spring Semester                                ||
||										                                                                                              ||
||										BASICS OF PROGRAMMING 2 : FINAL PROJECT														  ||
||																																	  ||
||																																	  ||
||										BITMAP IMAGE TREATMENT USING C++         													  ||
||																																      ||
||																																	  ||
||																										LAPORTE NATHAN CLAUDE         ||
||																										Nept CODE : IBIS2E	          ||
||																										Ver. 1.05A April 2017         ||
||                                                                                                                                    ||
||																																	  ||
||																																	  ||
||____________________________________________________________________________________________________________________________________||
________________________________________________________________________________________________________________________________________
*/

#include <iostream>
#include <vector>
#pragma pack(1)


typedef struct rgbr // Its RGB values default pixels wil be black
{
    char blue = 0;
    char green = 0;
    char red = 0;
    const char reserved = 0;
};

class picture //A Picture is a collection of pixels.
{
private:
	struct // Its RGB values default pixels wil be black
	{
    unsigned char magicNumber[2]; //define the format type.
    unsigned int size; //Size of the image
    unsigned short int id_one; //First id
    unsigned short int id_two; //second id
    unsigned int offset; //Starting point of the pixel matrix
	}fileHeader ;
  struct
  {
    int   info_Size;
    int   img_Width;
    int   img_Height;
    short biPlanes;//Number of color planes
    short bpp;
    int   compression;
    int   img_Size;
    int   xppm;//X pixels per meter
    int   yppm;//Y pixels per meter
    int   color_Depth;
    int   biClrImportant;//Number of important colors
  } infoHeader;
  struct
  {
   char p_blue;
   char p_green;
   char p_red;
   char p_reserved;
  }palette;
  rgbr* matrix; //ici, ça doit être img_width et img_height
public:
	picture(const char* filename);
	void img_copy();
};


