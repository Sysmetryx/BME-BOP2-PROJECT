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
#define MAX_LENGTH 260
using namespace std;

#pragma pack( 1) //Force the memory alignement on 1bit (regular is on 4bits)

class picture
{
protected:
  const char *fileIn;
  const char *fileOut;
  struct // Its RGB values default pixels wil be black
  {
    unsigned char magicNumber[2]; //define the format type.
    unsigned int  size; //Size of the image
    int           reserved;
    unsigned int  offset; //Starting point of the pixel matrix
  }fileHeader ;
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
  } infoHeader;
  struct pixel// Its RGB values default pixels wil be black
  {
    unsigned char blue = 0;
    unsigned char green = 0;
    unsigned char red = 0;
  };


public:
  vector<pixel> pixelTab;
  picture(const char* filename);
  void addBorder(int size = 0, char r = 0, char b = 0, char g = 0);
  void write(const char* filenameOut);
  void greyScale();
  void mozaik(int size);
};


void menu();
void menuOut();
