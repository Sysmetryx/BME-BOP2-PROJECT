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
||                                                                                                      Ver. 1.5C March 2017         ||
||                                                                                                                                    ||
||                                                                                                                                    ||
||                                                                                                                                    ||
||____________________________________________________________________________________________________________________________________||
________________________________________________________________________________________________________________________________________
*/

#include "pixel.hpp"

picture::picture(const char* filename)//constructor of the object picture.
{
    int i = 0;
    fileIn = filename;
    ifstream file;
    file.open(fileIn, ios::in | ios::binary); // We open the selected file.
    if(file.is_open()) { // file opened
        file.read((char*) (&fileHeader), sizeof(fileHeader));//reading the first header.
        file.read((char*) (&infoHeader), sizeof(infoHeader));//reading the second header.
        pixel tmp; //temporary variable for pixel storage.
        for (i = 0; i < infoHeader.img_Width * infoHeader.img_Height; i++)
        {
            file.read((char*) (&tmp), sizeof(pixel)); //We read and load the pixels.
            pixelTab.push_back(tmp); //Add an element to the vector, so we use dynamic allocation.
        }
        file.close(); //closes the file.
    }
}

picturePalette::picturePalette(const char* filename) : picture(filename)//Constructor of the child class. Exactly the same, but with palette added.
{
    int i = 0;
    fileIn = filename;
    ifstream file;
    file.open(fileIn, ios::in | ios::binary);
    if(file.is_open()) { // file opened
        file.read((char*) (&fileHeader), sizeof(fileHeader));
        file.read((char*) (&infoHeader), sizeof(infoHeader));
        palette tmpP;
        for(int j = 0; j < infoHeader.color_Depth; j++)
        {
            file.read((char*) (&tmpP), sizeof(palette));
            paletteM.push_back(tmpP);
        }
        pixel tmp;
        for (i = 0; i < infoHeader.img_Width * infoHeader.img_Height; i++)
        {
            file.read((char*) (&tmp), sizeof(pixel));
            pixelTab.push_back(tmp);
        }
        file.close();
    }
}

void picturePalette::write(const char* filenameOut)//Used to save the file.
{
    int i = 0;
    ofstream file;
    file.open(filenameOut, ios::out | ios::binary); //Open / Create the output file.
    if(file.is_open())
    {
        file.write((char*) (&fileHeader), sizeof(fileHeader));//Writing of the first header
        file.write((char*) (&infoHeader), sizeof(infoHeader)); //Writing of the second header
        for(i = 0; i < infoHeader.color_Depth; i++)
        {
            file.write((char*) (&paletteM[i]), sizeof(palette));
        }
        for (i = 0; i < infoHeader.img_Width * infoHeader.img_Height; i++)
        {
            file.write((char *) (&pixelTab[i]), sizeof(pixel));
        }
    }
    cout << file.is_open() << endl;
    file.close();
}

void picture::write(const char* filenameOut)//Same function but without the palette being written.
{
    int i = 0;
    ofstream file;
    file.open(filenameOut, ios::out | ios::binary);
    if(file.is_open())
    {
        file.write((char*) (&fileHeader), sizeof(fileHeader));
        file.write((char*) (&infoHeader), sizeof(infoHeader));
        for (i = 0; i < infoHeader.img_Width * infoHeader.img_Height; i++)
        {
            file.write((char *) (&pixelTab[i]), sizeof(pixel));
        }
    }
    cout << file.is_open() << endl;
    file.close();
}

void picture::addBorder(int size, char r, char b, char g) //Add a border of the selected color and the selected width to the image.
{
    for (int i = 0; i < infoHeader.img_Width * infoHeader.img_Height; i++)
    {
        if(i < (infoHeader.img_Height * size) || i > infoHeader.img_Width * infoHeader.img_Height - (infoHeader.img_Height * size))
        {
            pixelTab[i].blue = b;
            pixelTab[i].red = r;
            pixelTab[i].green = g;
        }
        if (i % infoHeader.img_Width == 0 && i <= infoHeader.img_Width * infoHeader.img_Height - (infoHeader.img_Width * size) && i >= (infoHeader.img_Width * size))
        {
            for (int j = 0; j < size; j++)
            {
                pixelTab[i - j].blue = b;
                pixelTab[i - j].red = r;
                pixelTab[i - j].green = g;
                pixelTab[i + j].blue = b;
                pixelTab[i + j].red = r;
                pixelTab[i + j].green = g;
            }
        }
    }
}

void picture::greyScale() //Transform a color image to a greyscale image.
{
    /* note that for an image to appears correctly, we use coefficients to colours, our eye is more sensitive to certain wavelength
    which is why we use the numbers below. These can be changed depending on the person and the image.*/
    float rweight = 0.2105;
    float gweight = 0.7152;
    float bweight = 0.0722;
    for(int i = 0; i < infoHeader.img_Width*infoHeader.img_Height; i++)
    {
        char btemp = pixelTab[i].blue;
        char gtemp = pixelTab[i].green;
        char rtemp = pixelTab[i].red;
        pixelTab[i].blue = floor(bweight*btemp) + floor(rweight*rtemp) + floor(gweight*gtemp);
        pixelTab[i].red = floor(bweight*btemp) + floor(rweight*rtemp) + floor(gweight*gtemp);
        pixelTab[i].green = floor(bweight*btemp) + floor(rweight*rtemp) + floor(gweight*gtemp);
    }
}

void menuOut(picture pic)//menu used to save
{
    system("cls");
    cout << "task completed, would you like to save ? (Y/N)" << endl;
    char comm;
    cin >> comm;
    if(comm == 'y' || comm == 'Y')
    {
        cout << "Please, enter a name for the copied file : (ex : 'picture.bmp'" << endl;
        char* filenameOut = new char[MAX_LENGTH];
        cin >> filenameOut;
        pic.write(filenameOut);
        cout << "File saved" << endl;
        system("pause");
        menu();
    }
    else if (comm == 'n' || comm =='N')
    {
        cout << "File not saved" << endl;
        system("pause");
        menu();
    }
    else
    {
        cout << "Please, enter a valid command." << endl;
        menuOut(pic);
    }
}
void menu()//Menu to select what effect to apply
{
    system("cls");
    system("color 0B");
    cout << "Welcome to BitMAp editor, do you wish to use a color palette ? (Y-N delaut : no)" << endl;
    char pal;
    cin >> pal;
    switch (pal){
        case 'y' :
            {
        cout << "Welcome to BitMAp editor" << endl << "Please, enter the name of a file to open :" << endl << "Exemple : 'Lena.bmp'"<<endl;
        char* filename1 = new char[MAX_LENGTH];
        cin >> filename1;
        picturePalette pic1(filename1);
        int command1;
            while(command1 == 0)
        {   system("cls");
            cout <<"Welcome to BitMAp editor" << endl;
            cout << "Please, enter a command number : " << endl << "1: Add borders to the image." << endl << "2: Transform the image to greyscale." << endl <<"3: Create a mosaic with the image." << endl << "4: Add a filter to the image."<< endl << "5: Convert the image to sepia."<< endl << "6: Save changes to the image" << endl << "7: Quit the program." << endl;
            cin >> command1;
        }
        switch (command1)
        {
            case 1 :
                {
                system("cls");
                cout << "please, enter the size :" << endl;
                int border_size;
                int rcomp;
                int gcomp;
                int bcomp;
                cin >> border_size;
                cout << "please, enter the red component (0 - 255) :" << endl;
                cin >> rcomp;
                cout << "please, enter the green component (0 - 255) :" << endl;
                cin >> gcomp;
                cout << "please, enter the blue component (0 - 255) :" << endl;
                cin >> bcomp;
                pic1.addBorder(border_size, (char)rcomp, (char)bcomp, (char)gcomp);
                menuOut(pic1);
                }
                break;

            case 2 :
                system("cls");
                pic1.greyScale();
                menuOut(pic1);
                break;

            case 3 :
                system("cls");
                cout << "Please enter a size for the mosaic (ex : 10)" << endl;
                int size;
                cin >> size;
                pic1.mozaik(size);
                menuOut(pic1);
                break;

            case 4:
                system("cls");
                cout << "Please, select a command for the filter :" << endl << "1: Add a filter with the selected rgb component." << endl << "2: Remove the selected rgb component." << endl;
                int cmd;
                cin >> cmd;
                pic1.filter(cmd);
                menuOut(pic1);
                break;

            case 5:
                system("cls");
                pic1.sepia();
                menuOut(pic1);
            break;

            case 6 :
                system("cls");
                cout << "Please, enter a name for the copied file : (ex : 'picture.bmp'" << endl;
                char* filenameOut;
                cin >> filenameOut;
                pic1.write(filenameOut);
                cout << "Successfully saved, press any key to return to menu" << endl;
                system("pause");
                menu();
            break;

            case 7:
            break;
        }
    }
        break;

        case 'n':
        {
        cout << "Welcome to BitMAp editor" << endl << "Please, enter the name of a file to open :" << endl << "Exemple : 'Lena.bmp'"<<endl;
        char* filename = new char[MAX_LENGTH];
        cin >> filename;
        picture pic(filename);
        int command = 0;
        while(command == 0)
        {
            system("cls");
            cout <<"Welcome to BitMAp editor" << endl;
            cout << "Please, enter a command number : " << endl << "1: Add borders to the image." << endl << "2: Transform the image to greyscale." << endl <<"3: Create a mosaic with the image." << endl << "4: Add a filter to the image."<< endl << "5: Convert the image to sepia."<< endl << "6: Save changes to the image" << endl << "7: Quit the program." << endl;
            cin >> command;
        }
        switch (command)
        {
            case 1 :
                system("cls");
                cout << "please, enter the size :" << endl;
                int border_size;
                int rcomp;
                int gcomp;
                int bcomp;
                cin >> border_size;
                cout << "please, enter the red component (0 - 255) :" << endl;
                cin >> rcomp;
                cout << "please, enter the green component (0 - 255) :" << endl;
                cin >> gcomp;
                cout << "please, enter the blue component (0 - 255) :" << endl;
                cin >> bcomp;
                pic.addBorder(border_size, (char)rcomp, (char)bcomp, (char)gcomp);
                menuOut(pic);
            break;

            case 2 :
                system("cls");
                pic.greyScale();
                menuOut(pic);
            break;

            case 3 :
                system("cls");
                cout << "Please enter a size for the mosaic (ex : 10)" << endl;
                int size;
                cin >> size;
                pic.mozaik(size);
                menuOut(pic);
            break;

            case 4:
                system("cls");
                cout << "Please, select a command for the filter :" << endl << "1: Add a filter with the selected rgb component." << endl << "2: Remove the selected rgb component." << endl;
                int cmd;
                cin >> cmd;
                pic.filter(cmd);
                menuOut(pic);
            break;

            case 5:
                system("cls");
                pic.sepia();
                menuOut(pic);
            break;

            case 6 :
                system("cls");
                cout << "Please, enter a name for the copied file : (ex : 'picture.bmp'" << endl;
                char* filenameOut;
                cin >> filenameOut;
                pic.write(filenameOut);
                cout << "Successfully saved, press any key to return to menu" << endl;
                system("pause");
                menu();
            break;

            case 7:
            break;
        }
        }
        break;
}
}

void picture::mozaik(int size)//Creates a mosaic.
{
    int i = 0, j = 0, x = 0, y = 0;
    int red;
    int blue;
    int green;
    for (i = 0; i < infoHeader.img_Height; i += size)
    {
       for(j = 0; j < infoHeader.img_Width; j += size)
        {
          for(y = 0; y < size; y++)
          {
            for(x = 0; x < size; x++)
            {
              int index = (i*infoHeader.img_Height)+(j + x)+(y * infoHeader.img_Width);
              if (index < infoHeader.img_Width * infoHeader.img_Height)
              {
              red += pixelTab[index].red;
              blue += pixelTab[index].blue;
              green += pixelTab[index].green;
              }
            }
          }//We get the average color of the pixel area.
          red = red / (size * size);
          green = green / (size * size);
          blue = blue / (size * size);
          for(y = 0; y < size; y++)//Rewriting the array with the selected average.
          {
            for(x = 0; x < size; x++)
            {
              int index = (i*infoHeader.img_Width)+(j + x)+(y * infoHeader.img_Width);
              if (index < infoHeader.img_Width * infoHeader.img_Height)
              {
              pixelTab[index].red = red;
              pixelTab[index].blue = blue;
              pixelTab[index].green = green;
              }
            }
          }//Re-initialize the values.
          red = 0;
          blue = 0;
          green = 0;
        }
    }
}

void picture::filter(int cmd)//Add/Remove filter.
{
    int rfilter = 0;
    int gfilter = 0;
    int bfilter = 0;
    switch(cmd)
    {
        case 1 : //Adding a color filter to the image.
        system("cls");
        cout << "Please, select the red level for the filter" << endl;
        cin >> rfilter;
        cout << "Please, select the green level for the filter" << endl;
        cin >> gfilter;
        cout << "Please, select the breen level for the filter" << endl;
        cin >> bfilter;
        for (int i = 0; i < infoHeader.img_Height * infoHeader.img_Width; ++i)
        {

            if (rfilter + pixelTab[i].red > 255)
            {
                pixelTab[i].red = 255;
            }
            else if (rfilter > pixelTab[i].red)
            {
                pixelTab[i].red =  pixelTab[i].red + rfilter;
            }
            if (bfilter + pixelTab[i].blue > 255)
            {
                pixelTab[i].blue = 255;
            }
            else if (bfilter > pixelTab[i].blue)
            {
                pixelTab[i].blue =  pixelTab[i].blue + bfilter;
            }
            if (gfilter + pixelTab[i].green > 255)
            {
                pixelTab[i].green = 255;
            }
            else if (gfilter > pixelTab[i].green)
            {
                pixelTab[i].green =  pixelTab[i].green + gfilter;
            }
        }
        break;

        case 2 ://reoving the selected components.
        system("cls");
        cout << "Please, select the red level for the filter" << endl;
        cin >> rfilter;
        cout << "Please, select the green level for the filter" << endl;
        cin >> gfilter;
        cout << "Please, select the breen level for the filter" << endl;
        cin >> bfilter;
        for (int i = 0; i < infoHeader.img_Height * infoHeader.img_Width; ++i)
        {

            if (pixelTab[i].red - rfilter < 0)
            {
                pixelTab[i].red = 0;
            }
            else if (rfilter < pixelTab[i].red)
            {
                pixelTab[i].red =  pixelTab[i].red - rfilter;
            }
            if (pixelTab[i].blue - bfilter < 0)
            {
                pixelTab[i].blue = 0;
            }
            else if (bfilter < pixelTab[i].blue)
            {
                pixelTab[i].blue =  pixelTab[i].blue - bfilter;
            }
            if (pixelTab[i].green - gfilter < 0)
            {
                pixelTab[i].green = 0;
            }
            else if (gfilter < pixelTab[i].green)
            {
                pixelTab[i].green =  pixelTab[i].green - gfilter;
            }
        }
        break;
    }
}

void picture::sepia()//Transform to sepia
{
    /* as for the grey scale, we use coefficients to convert to sepia. Changing these will result in different variations. */
    for(int i = 0; i < infoHeader.img_Height * infoHeader.img_Width; i++)
    {
        unsigned char rtemp = pixelTab[i].red;
        unsigned char gtemp = pixelTab[i].green;
        unsigned char btemp = pixelTab[i].blue;
        if((rtemp * .393) + (gtemp *.769) + (btemp * .189) > 255)
        {
            pixelTab[i].red = 255;
        }
        else
        {
            pixelTab[i].red = (rtemp * .393) + (gtemp *.769) + (btemp * .189);
        }

        if((rtemp * .349) + (gtemp *.686) + (btemp * .168) > 255)
        {
            pixelTab[i].green = 255;
        }
        else
        {
            pixelTab[i].green = (rtemp * .349) + (gtemp *.686) + (btemp * .168);
        }
        if((rtemp * .272) + (gtemp *.534) + (btemp * .131) > 255)
        {
            pixelTab[i].blue = 255;
        }
        else
        {
            pixelTab[i].blue = (rtemp * .272) + (gtemp *.534) + (btemp * .131);
        }
    }
}

int main()
{
    menu();
    return 0;
}
