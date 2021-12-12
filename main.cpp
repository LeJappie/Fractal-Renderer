#include <iostream>
#include <complex>
#include <cmath>
#include "EasyBMP.hpp"
#include <limits>

using namespace std;

// Variables for rendering
bool fillInside = false;
int size = 2048;
int redBalance = 0;
int greenBalance = 0;
int blueBalance = 255;
int redScaling = 100;
int greenScaling = 100;
int blueScaling = 100;
// End of variables for rendering

// Variables for release
string name = "Fractal Renderer";
string version = "1.0";
string releaseDate = "12/12/2021";
string author = "Jappie";
// End of variables for release


int sequence(complex<double> c)
{
    complex<double> z = c;
    for (int i = 0; i <= 255; i++)
    {
        if (abs(z) > 2)
            return 255 - i;
        z = z*z + c;
    }
    if (fillInside)
        return 0;
    return 255;
}

void render()
{
    cout << "Starting render... This might take a while!" << endl;
    EasyBMP::Image img(size, size, "Fractal.bmp", EasyBMP::RGBColor(0, 0, 0));
    for (double i = 0; i < size; i++)
    { 
        for (double j = 0; j < size; j++)
        {
            double n = sequence(complex<double>((i-0.5*size)/(0.25*size), (j-0.5*size)/(0.25*size)));
            img.SetPixel(i, j, EasyBMP::RGBColor(redBalance/255 - redBalance/255 * pow(n, redScaling/10)/pow(255, redScaling/10-1),
                                                 greenBalance/255 - greenBalance/255 * pow(n, greenScaling/10)/pow(255, greenScaling/10-1),
                                                 blueBalance/255 - blueBalance/255 * pow(n, blueScaling/10)/pow(255, blueScaling/10-1)));
        }
        cout << "\r" << i+1 << " / " << size;
    }
    cout << endl << "Finalizing render..." << endl;
    img.Write();
    cout << "Render finished!" << endl;
}


void welcomeMessage()
{
    cout << name << " v" << version << " - " << releaseDate << endl
         << "© " << author << " 2021" << endl << endl;
}

void userInput()
{
    string userInput = "";
    while (userInput != "exit")
    {
        cout << "What do you want to do? Type \"help\" to see a list of commands:" << endl;
        userInput = "";
        cin >> userInput;
        cout << endl;
        if (userInput == "help")
        {
            cout << "===================================================" << endl
                 << "help: Show this menu"                                << endl
                 << "exit: Terminate the programme"                       << endl
                 << "size: Set the resolution of the render"              << endl
                 << "colourBalance: Set the colour balance of the render" << endl
                 << "colourScaling: Set the colour scaling of the render" << endl
                 << "render: Start the render"                            << endl
                 << "===================================================" << endl << endl;
        }
        else if (userInput == "size")
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Set the resolution of the render in pixels"  << endl
                 << "Large values may lead to long render times!" << endl << endl
                 << "Default: 2048"                               << endl
                 << "Current: " << size                           << endl << endl
                 << "Enter size: ";
            int newSize = 0;
            cin >> newSize;
            if (newSize <= 0)
                cout << "Invalid size!" << endl << endl;
            else
            {
                size = newSize;
                cout << endl << "size has been set to " << size << endl << endl;
            }
        }
        else if (userInput == "colourBalance")
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Set the colour balance of the render in RGB"                                      << endl
                 << "A higher value means that that colour will be more saturated"                     << endl << endl
                 << "Default:\tR: 0\tG: 0\tB: 255"                                                     << endl
                 << "Current:\tR: " << redBalance << "\tG: " << greenBalance << "\tB: " << blueBalance << endl << endl
                 << "Enter R: ";
            int newColour = 0;
            cin >> newColour;
            if (newColour < 0 || newColour > 255)
                cout << "Invalid colour!" << endl << endl;
            else
                redBalance = newColour;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            newColour = 0;
            cout << "Enter G: ";
            cin >> newColour;
            if (newColour < 0 || newColour > 255)
                cout << "Invalid colour!" << endl << endl;
            else
                greenBalance = newColour;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            newColour = 0;
            cout << "Enter B: ";
            cin >> newColour;
            if (newColour < 0 || newColour > 255)
                cout << "Invalid colour!" << endl << endl;
            else
                blueBalance = newColour;
            cout << "colourBalance has been set to:\tR: " << redBalance << "\tG: " << greenBalance << "\tB: " << blueBalance << endl << endl;
        }
        else if (userInput == "colourScaling")
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Set the colour scaling of the render in percentage (0-100)"                       << endl
                 << "A higher value means that that colour will fade less quickly"                     << endl << endl
                 << "Default:\tR: 100\tG: 100\tB: 100"                                                 << endl
                 << "Current:\tR: " << redScaling << "\tG: " << greenScaling << "\tB: " << blueScaling << endl << endl
                 << "Enter R: ";
            int newColour = 0;
            cin >> newColour;
            if (newColour < 0 || newColour > 100)
                cout << "Invalid percentage!" << endl << endl;
            else
                redScaling = newColour;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            newColour = 0;
            cout << "Enter G: ";
            cin >> newColour;
            if (newColour < 0 || newColour > 100)
                cout << "Invalid percentage!" << endl << endl;
            else
                greenScaling = newColour;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            newColour = 0;
            cout << "Enter B: ";
            cin >> newColour;
            if (newColour < 0 || newColour > 100)
                cout << "Invalid percentage!" << endl << endl;
            else
                blueScaling = newColour;
            cout << "colourScaling has been set to:\tR: " << redScaling << "\tG: " << greenScaling << "\tB: " << blueScaling << endl << endl;
        }
        else if (userInput == "render")
        {
            render();
            cout << endl << endl;
        }
        else if (userInput != "exit")
            cout << "Invalid input. Type \"help\" to see a list of commands" << endl << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


int main()
{
    welcomeMessage();
    userInput();
    return 0;
}