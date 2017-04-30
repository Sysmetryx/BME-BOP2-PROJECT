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
||                                                                                                      Ver. 1.10B March 2017         ||
||                                                                                                                                    ||
||                                                                                                                                    ||
||                                                                                                                                    ||
||____________________________________________________________________________________________________________________________________||
________________________________________________________________________________________________________________________________________
*/

#include "pixel.hpp"

using namespace std;


picture::picture(const char* filename){
    int i = 0;
    fileIn = filename;
    //fileOut = filenameOut;
//  Ouverture du ficher de lecture
    ifstream file;
    file.open(fileIn, ios::in | ios::binary);

    if(file.is_open()) { // file opened
//      Lecture des Headers
        file.read((char*) (&fileHeader), sizeof(fileHeader));
        file.read((char*) (&infoHeader), sizeof(infoHeader));

//      Variale temporaire pour stocker un pixel
        pixel tmp;

//      Lecture / Stockage / Ecriture des pixels
        for (i = 0; i < infoHeader.img_Width * infoHeader.img_Height; i++)
        {
            file.read((char*) (&tmp), sizeof(pixel));
            pixelTab.push_back(tmp);
        }

//      Fermeture des fichiers
        file.close();
    }
}

void picture::write(const char* filenameOut)
{
    int i = 0;
//  Ouverture du fichier de sortie
    ofstream file;
    file.open(filenameOut, ios::out | ios::binary);

    if(file.is_open())
    {
//      Ecriture des Headers
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
    /* note that for an image to appears correct, we use coefficients to colours, our eye is more sensitive to certain wavelength
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

void menuOut(picture pic)
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
void menu()
{
    system("cls");
    system("color 0B");
    cout << "Welcome to BitMAp editor" << endl << "Please, enter the name of a file to open :" << endl << "Exemple : 'Lena.bmp'"<<endl;
    char* filename = new char[MAX_LENGTH];
    cin >> filename;

    if( filename ==! "zz"){
        cout<< "Please, enter a valid file name."<< endl;
        menu();
    }
    else
    {
    picture pic(filename);
    int command = 0;
    while(command == 0)
    {   system("cls");
        cout <<"Welcome to BitMAp editor" << endl;
        cout << "Please, enter a command number : " << endl << "1: Add borders to the image." << endl << "2: Transform the image to greyscale." << endl <<"3: Create a mosaic with the image." << endl << "4: Save changes to the image" << endl << "5: Quit the program." << endl;
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

        case 4 :
        system("cls");
        cout << "Please, enter a name for the copied file : (ex : 'picture.bmp'" << endl;
        char* filenameOut;
        cin >> filenameOut;
        pic.write(filenameOut);
        cout << "Successfully saved, press any key to return to menu" << endl;
        system("pause");
        menu();
        break;

        case 5:
        break;
    }
    }

}


void picture::mozaik(int size)
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
          }

//        On recupère la moyenne de la zone de pixel
          red = red / (size * size);
          green = green / (size * size);
          blue = blue / (size * size);

//        On Re-ecrit le tableau avec la moyenne de chaque zone
          for(y = 0; y < size; y++)
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
          }
//        On re-initialize les valeurs des pixel de zone
          red = 0;
          blue = 0;
          green = 0;
        }
    }
}


int main()
{
    menu();
    return 0;
}
