#pragma once

using namespace std;

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
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
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

// FUNCION PARA DIBUJAR LAS MATRICES
void setConsoleColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (color)
    {
    case 0:
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED); // Color blanco
        break;
    case 1:
        SetConsoleTextAttribute(hConsole, 0); // Color negro (Viene predeterminado)
        break;
    case 2:
        SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN); // Color amarillo
        break;
    case 3:
        SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN); // Color verde
        break;
    case 4:
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_RED);
        ; // Color magenta
        break;
    case 5:
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);
        ; // Color azul
        break;
    default:
        SetConsoleTextAttribute(hConsole, 7); // Color blanco (Viene predeterminado)
    }
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
    for (int i = 40; i < 81; i++)
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
    gotoxy(81, 3);
    cout << (char)187;
    gotoxy(81, 7);
    cout << (char)188;
    // Barras verticales
    for (int i = 4; i < 7; i++)
    {
        gotoxy(40, i);
        cout << (char)179;
        gotoxy(80, i);
        cout << (char)179;
    }
    // Conexión 1
    color(7);
    for (int i = 24; i < 40; i++)
    {
        gotoxy(i, 5);
        cout << (char)205;
    }
    for (int i = 81; i < 97; i++)
    {
        gotoxy(i, 5);
        cout << (char)205;
    }
    color(2);
    gotoxy(23,5);
    cout << (char)179;
    gotoxy(18,5);
    cout << (char)179;
    gotoxy(17,4);
    cout << (char)201;
    gotoxy(24,4);
    cout << (char)187;
    for(int i=18;i<24;i++){
        gotoxy(i,4);
        cout << (char)205;
    }
    gotoxy(17,6);
    cout << (char)200;
    gotoxy(24,6);
    cout << (char)188;
    for(int i=18;i<24;i++){
        gotoxy(i,6);
        cout << (char)205;
    }
    color(7);
    for(int i=7;i<9;i++){
        gotoxy(20,i);
        cout << (char)186;
    }
    

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