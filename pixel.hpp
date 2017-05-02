/*
________________________________________________________________________________________________________________________________________
||____________________________________________________________________________________________________________________________________||
||                                                                                                                                    ||
||                                                                                                                                    ||
||              Budapesti Műszaki és Gazdaságtudományi Egyetem, 2016-2017, Spring Semester                                            ||
||                                                                                                                                    ||
||                    BASICS OF PROGRAMMING 2 : FINAL PROJECT                                                                         ||
||                                                                                                                                    ||
||                                                                                                                                    ||
||                    BITMAP IMAGE TREATMENT USING C++                                                                                ||
||                                                                                                                                    ||
||                                                                                                                                    ||
||                                                    LAPORTE NATHAN CLAUDE                                                           ||
||                                                    Nept CODE : IBIS2E                                                              ||
||                                                    Ver. 1.10B April 2017                                                           ||
||                                                                                                                                    ||
||                                                                                                                                    ||
||                                                                                                                                    ||
||____________________________________________________________________________________________________________________________________||
________________________________________________________________________________________________________________________________________
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <typeinfo>
#define MAX_LENGTH 260 //260 is the longest string possible in windows.
using namespace std;

#pragma pack( 1) //Forces the memory alignement on 1bit (regular is on 4bits)

class picture //Represents a whole picture
{
protected:
  const char *fileIn;
  const char *fileOut;
  struct
  {
    unsigned char magicNumber[2]; //define the format type.
    unsigned int  size; //Size of the image
    int           reserved;
    unsigned int  offset; //Starting point of the pixel matrix
  }fileHeader ; //1st header containing file info
  struct
  {
    int   info_ize;
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
  } infoHeader; //Second header containing image info
  struct pixel// Its RGB values default pixels wil be black
  {
    unsigned char blue = 0;
    unsigned char green = 0;
    unsigned char red = 0;
  }; //In case of 24bits BMP We use a structure with the order BGR.
  vector<pixel> pixelTab; //The array of pixels.

public:

  picture(const char* filename);
  void addBorder(int size = 0, char r = 0, char b = 0, char g = 0); //Adds a border of the selected size and color to the image.
  void write(const char* filenameOut); // Write a new file.
  void greyScale(); // Transform the image into grey scale.
  void mozaik(int size); //Creates a mosaic effect with the image.
  void filter(int cmd); //Adds a filter tothe image.
  void sepia(); // Transform the image to Sepia.
};

class picturePalette : public picture //This is o be used with bmp files under 24bits color depth.
{
  protected :
  struct palette
  {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char reserved;
  }; //Adds a color palette to the image, which acts like an index for colors.
  vector<palette> paletteM;

  public :
  picturePalette(const char* filename);
  void write(const char* filenameOut);
  void convert();
};

void menu(); //first part of the menu
void menuOut(); //Last part of the menu where we can save
