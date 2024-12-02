#pragma once
#include <windows.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <sstream>

using namespace std;

// Función para configurar la consola en UTF-8
void configurarConsolaUtf8()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

// Función para mover el cursor a una posición específica en la consola
inline void gotoxy(int x, int y)
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

// Función para ocultar el cursor en la consola
inline void ocultarCursor()
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 50;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hCon, &cci);
}

// Función para obtener la posición actual del cursor en el eje X (columna) dentro de la consola
inline int whereX()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int column;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    column = csbi.dwCursorPosition.X;
    return column;
}

// Función para obtener la posición actual del cursor en el eje Y (fila) dentro de la consola
inline int whereY()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int row;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    row = csbi.dwCursorPosition.Y;
    return row;
}

/*
    Función que cambia el color de la consola
    @param x: color a cambiar
    0: Negro
    1: Azul
    2: Verde
    3: Aguamarina
    4: Rojo
    5: Púrpura
    6: Amarillo (marrón en sistemas antiguos)
    7: Blanco (gris en sistemas antiguos)
    8: Gris
    9: Azul claro
    10: Verde claro
    11: Aguamarina claro
    12: Rojo claro
    13: Púrpura claro
    14: Amarillo claro
    15: Blanco brillante
*/
inline void color(int x)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Obtener el atributo actual de la consola
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);

    // Extraer el color de fondo actual
    int backgroundColor = consoleInfo.wAttributes & 0xF0;

    // Combinar el color de texto deseado con el fondo actual
    SetConsoleTextAttribute(hConsole, x | backgroundColor);
}

// Enum para la función de abajo
enum ConsoleColor
{
    Black = 0,
    DarkGray = BACKGROUND_INTENSITY,
    Gray = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
    LightGray = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
    Blue = BACKGROUND_BLUE,
    Green = BACKGROUND_GREEN,
    Red = BACKGROUND_RED,
    Intensity = BACKGROUND_INTENSITY,
    White = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
};

// Cambia el color del fondo
void setConsoleBackground(ConsoleColor color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD cells = 0;
    DWORD written = 0;
    COORD homeCoords = {0, 0};

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    cells = csbi.dwSize.X * csbi.dwSize.Y;

    // Establecer el color de fondo
    FillConsoleOutputAttribute(hConsole, color, cells, homeCoords, &written);
    // Limpiar la consola
    FillConsoleOutputCharacter(hConsole, ' ', cells, homeCoords, &written);
    SetConsoleCursorPosition(hConsole, homeCoords);
}

// Ejecuta la gradiante
void ejecutarGradiente(int duracion)
{
    const int steps = 5;
    ConsoleColor colors[steps] = {White, LightGray, Gray, DarkGray, Black};

    /*
    for (int i = 0; i < steps; ++i) {
        setConsoleBackground(colors[i]);
        std::this_thread::sleep_for(std::chrono::milliseconds(duracion / steps));
    }*/

    // Recorre el array de Black a White
    for (int i = steps - 1; i >= 0; --i)
    {
        setConsoleBackground(colors[i]);
        std::this_thread::sleep_for(std::chrono::milliseconds(duracion / steps));
    }

    setConsoleBackground(White); // Resetea al color blanco
}

// Ejecuta la gradiante
void ejecutarGradienteDoble(int duracion)
{
    const int steps = 5;
    ConsoleColor colors[steps] = {White, LightGray, Gray, DarkGray, Black};

    // Recorre White a Black
    for (int i = 0; i < steps; ++i)
    {
        setConsoleBackground(colors[i]);
        std::this_thread::sleep_for(std::chrono::milliseconds(duracion / steps));
    }

    // Recorre el array de Black a White
    for (int i = steps - 1; i >= 0; --i)
    {
        setConsoleBackground(colors[i]);
        std::this_thread::sleep_for(std::chrono::milliseconds(duracion / steps));
    }

    setConsoleBackground(White); // Resetea al color blanco
}

// Cambia el color del texto, adaptándose al color del fondo
void setTextColor(int textColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Obtener el atributo actual de la consola
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);

    // Extraer el color de fondo actual
    int backgroundColor = consoleInfo.wAttributes & 0xF0;

    // Combinar el color de texto deseado con el fondo actual
    SetConsoleTextAttribute(hConsole, textColor | backgroundColor);
}

// FUNCION PARA LIMPIAR EL ÁREA EN REEMPLAZO AL CLS
void limpiarArea(int x, int y, int width, int height)
{ // width= ancho && heigh= altura
    for (int i = 0; i < height; i++)
    {
        gotoxy(x, y + i);
        for (int j = 0; j < width; j++)
        {
            cout << " ";
        }
    }
}

// Funcion para dibujar un arte ASCII
void dibujarTitulo(int x, int y, int color, const string &titulo)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE)
    {
        cerr << "Error: no se pudo obtener el controlador de la consola.\n";
        return;
    }
    setTextColor(White);
    setTextColor(color);
    istringstream stream(titulo);
    string line;
    int offsetY = 0;

    while (getline(stream, line))
    {
        COORD pos = {static_cast<SHORT>(x), static_cast<SHORT>(y + offsetY)};
        SetConsoleCursorPosition(hConsole, pos);
        cout << line;
        offsetY++; // Incrementa en cada línea para mantener el arte alineado
    }
}

// Arte ASCII
string libros = R"(       
       .--.           .---.        .-.
   .---|--|   .-.     |   |  .---. |~|    .--.
.--|===|  |---|_|--.__|   |--|:::| |~|-==-|==|---.
|  |   |  |===| |~~|  |   |--|   |_|~|    |  |___|-.
|  |   |  |===| |==|  |   |  |:::|=| |    |  |---|=|
|  |   |  |   |_|__|  |   |__|   | | |    |  |___| |
|~~|===|--|===|~|~~|  |~~~|--|:::|=|~|----|==|---|=|
____________________________________________________
    )";

string letras = R"(  
  ____  _ _     _ _       _                    _____ _     _ _     _ _ 
 |  _ \(_) |   | (_)     | |                  / ____| |   (_) |   | (_)
 | |_) |_| |__ | |_  ___ | |_ ___  ___ __ _  | |  __| |__  _| |__ | |_ 
 |  _ <| | '_ \| | |/ _ \| __/ _ \/ __/ _` | | | |_ | '_ \| | '_ \| | |
 | |_) | | |_) | | | (_) | ||  __/ (_| (_| | | |__| | | | | | |_) | | |
 |____/|_|_.__/|_|_|\___/ \__\___|\___\__,_|  \_____|_| |_|_|_.__/|_|_|                                    
 ______________________________________________________________________                         
    )";

string carritoCompras = R"(        
        ____
       / __ \____
      //     |   \
     ||      |    |
     ||______|____|
      |            |
     (o)          (o))";

// Función para dibujar presionar la tecla
void dibujarPresionaTecla(int x, int y)
{
    setTextColor(White);
    gotoxy(x, y);
    cout << "Presiona una tecla para continuar...";
}

// Función para pausar
void pausa()
{
    getch();
}

// Función para limpiar la pantalla
void limpiarPantalla()
{
    system("CLS");
}

// Marcos de los menus
void estructura_menu()
{
    // Título
    color(7);
    gotoxy(52, 5);
    cout << "LIBRERIA GHIBLI";
    color(7);

    // Título
    // Barras horizontales
    color(2);
    for (int i = 40; i < 79; i++)
    {
        gotoxy(i, 3);
        cout << (char)205;
        gotoxy(i, 7);
        cout << (char)205;
    }
    // Esquinas
    gotoxy(39, 3);
    cout << (char)201;
    gotoxy(39, 7);
    cout << (char)200;
    gotoxy(79, 3);
    cout << (char)187;
    gotoxy(79, 7);
    cout << (char)188;
    // Barras verticales
    for (int i = 4; i < 7; i++)
    {
        gotoxy(40, i);
        cout << (char)179;
        gotoxy(78, i);
        cout << (char)179;
    }

    // Conexión 1
    color(7);
    for (int i = 24; i < 40; i++)
    {
        gotoxy(i, 5);
        cout << (char)205;
    }
    color(2);
    gotoxy(23, 5);
    cout << (char)179;
    gotoxy(18, 5);
    cout << (char)179;
    gotoxy(17, 4);
    cout << (char)201;
    gotoxy(24, 4);
    cout << (char)187;
    for (int i = 18; i < 24; i++)
    {
        gotoxy(i, 4);
        cout << (char)205;
    }
    gotoxy(17, 6);
    cout << (char)200;
    gotoxy(24, 6);
    cout << (char)188;
    for (int i = 18; i < 24; i++)
    {
        gotoxy(i, 6);
        cout << (char)205;
    }
    color(7);
    for (int i = 7; i < 9; i++)
    {
        gotoxy(20, i);
        cout << (char)186;
    }

    // Conexión 2
    for (int i = 79; i < 95; i++)
    {
        gotoxy(i, 5);
        cout << (char)205;
    }
    color(2);
    gotoxy(100, 5);
    cout << (char)179;
    gotoxy(95, 5);
    cout << (char)179;
    gotoxy(94, 4);
    cout << (char)201;
    gotoxy(101, 4);
    cout << (char)187;
    for (int i = 95; i < 101; i++)
    {
        gotoxy(i, 4);
        cout << (char)205;
    }
    gotoxy(94, 6);
    cout << (char)200;
    gotoxy(101, 6);
    cout << (char)188;
    for (int i = 95; i < 101; i++)
    {
        gotoxy(i, 6);
        cout << (char)205;
    }
    color(7);
    for (int i = 7; i < 9; i++)
    {
        gotoxy(98, i);
        cout << (char)186;
    }
    // Conexión 3
    gotoxy(58, 8);
    cout << (char)186;
    gotoxy(60, 8);
    cout << (char)186;
    gotoxy(42, 8);
    cout << (char)186;
    gotoxy(76, 8);
    cout << (char)186;

    // Menú
    color(2);
    // Barras hoizontales
    for (int i = 16; i < 104; i++)
    {
        gotoxy(i, 9);
        cout << (char)205;
        gotoxy(i, 29);
        cout << (char)205;
    }
    // Esquinas
    gotoxy(15, 9);
    cout << (char)201;
    gotoxy(15, 29);
    cout << (char)200;
    gotoxy(104, 9);
    cout << (char)187;
    gotoxy(104, 29);
    cout << (char)188;
    // Barras verticales
    for (int i = 10; i < 29; i++)
    {
        gotoxy(15, i);
        cout << (char)186;
        gotoxy(104, i);
        cout << (char)186;
        // contorno
        gotoxy(106, i + 1);
        cout << (char)186;
    }
    // Contorno de la ventana
    gotoxy(106, 10);
    cout << (char)187;
    gotoxy(105, 10);
    cout << (char)205;
    gotoxy(106, 30);
    cout << (char)188;
    for (int i = 16; i < 106; i++)
    {
        gotoxy(i, 30);
        cout << (char)205;
    }
    gotoxy(16, 30);
    cout << (char)200;
    color(7);
}

// Marcos de los menus
void estructura_menu2(int comX, int finX, int comY, int finY)
{
    // Menú
    setTextColor(White);
    setTextColor(2);
    // Barras hoizontales
    for (int i = comX; i < finX + 1; i++)
    {
        gotoxy(i, comY - 1);
        cout << (char)205;
        gotoxy(i, finY + 1);
        cout << (char)205;
    }
    // Esquinas
    gotoxy(comX - 1, comY - 1);
    cout << (char)201;
    gotoxy(comX - 1, finY + 1);
    cout << (char)200;
    gotoxy(finX + 1, comY - 1);
    cout << (char)187;
    gotoxy(finX + 1, finY + 1);
    cout << (char)188;
    // Barras verticales
    for (int i = comY; i < finY + 1; i++)
    {
        gotoxy(comX - 1, i);
        cout << (char)186;
        gotoxy(finX + 1, i);
        cout << (char)186;
    }
}

void dibujarTextoPuntos(int x, int y, string mensaje)
{
    const int maxPuntos = 3; // Número máximo de puntos a mostrar
    const int delay = 500;   // Tiempo de espera en milisegundos

    for (int i = 0; i < 6; ++i) // Hacerlo por 3 iteraciones
    {
        setTextColor(White);
        setTextColor(2);
        gotoxy(x,y);
        cout << mensaje;

        // Agregar puntos según la iteración
        for (int j = 0; j <= (i % (maxPuntos + 1)); ++j)
        {
            cout << ".";
        }

        cout.flush();                                        // Asegurarse de que se imprima inmediatamente
        this_thread::sleep_for(chrono::milliseconds(delay)); // Esperar un momento

        // Limpiar la línea después de cada iteración
        cout << "\r";
        cout << "            "; // Espacio en blanco para limpiar la línea
        cout << "\r";           // Regresar al principio de la línea
    }
}