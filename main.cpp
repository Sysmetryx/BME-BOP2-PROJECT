/*
________________________________________________________________________________________________________________________________________
||____________________________________________________________________________________________________________________________________||
||                                                                                                                                    ||
||                                                                                                                                    ||
||                          Budapesti Műszaki és Gazdaságtudományi Egyetem, 2016-2017, Spring Semester                                ||
||                                                                                                                                    ||
||                                      BASICS OF PROGRAMMING 2 : FINAL PROJECT                                                       ||
||                                                                                                                                    ||
||                                                                                                                                    ||
||                                      BITMAP IMAGE TREATMENT USING C++                                                              ||
||                                                                                                                                    ||
||                                                                                                                                    ||
||                                                                                                      LAPORTE NATHAN CLAUDE         ||
||                                                                                                      Nept CODE : IBIS2E            ||
||                                                                                                      Ver. 1.05A March 2017         ||
||                                                                                                                                    ||
||                                                                                                                                    ||
||                                                                                                                                    ||
||____________________________________________________________________________________________________________________________________||
________________________________________________________________________________________________________________________________________
*/

#include "pixel.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;


picture::picture(const char* filename)
{
    FILE* in_file;
    in_file = fopen(filename, "rb");

    if(in_file != NULL)
    { // file opened
        fread(&fileHeader, sizeof(fileHeader), 1, in_file); //reading the FILEHEADER
        fread(&infoHeader, sizeof(infoHeader), 1, in_file); //reading the INFOHEADER
        matrix = (rgbr*) malloc((infoHeader.img_Width*infoHeader.img_Height)*sizeof(rgbr));
        std::cout << infoHeader.img_Width << std::endl;
        std::cout << infoHeader.img_Height << std::endl;
        std::cout << sizeof(rgbr) << std::endl;
        fread(&palette, sizeof(palette), 1, in_file);
        fread(&matrix, sizeof(matrix), 1, in_file);
        fclose(in_file);
     }
    else
    {
        std::cout << "The specified file cannot be loaded" << std::endl;
    }
}

void picture::img_copy(){
    FILE* out_file;
    out_file = fopen("copyfile.bmp", "w+b");
    fwrite(&fileHeader, sizeof(fileHeader), 1, out_file);
    fwrite(&infoHeader, sizeof(infoHeader), 1, out_file);
    fwrite(&palette, sizeof(palette), 1, out_file);
    fwrite(&matrix, sizeof(matrix), 1, out_file);
    fclose(out_file);
}


int main()
{
  picture test("lena.bmp");
  test.img_copy();
  return 0;
}

