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
    for (int i = 0; i < steps; ++i) {
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

// Gotoxy
inline void gotoxy(int x, int y)
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

inline void color(int x)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

// Dibujar libreria
void dibujarLibreria(int x, int y)
{
    setTextColor(White);
    setTextColor(1);
    gotoxy(x, y);
    cout << "       .--.           .---.        .-.";
    gotoxy(x, y+1);
    cout << "   .---|--|   .-.     |   |  .---. |~|    .--.";
    gotoxy(x, y+2);
    cout << ".--|===|  |---|_|--.__|   |--|:::| |~|-==-|==|---.";
    gotoxy(x, y+3);
    cout << "|  |   |  |===| |~~|  |   |--|   |_|~|    |  |___|-.";
    gotoxy(x, y+4);
    cout << "|  |   |  |===| |==|  |   |  |:::|=| |    |  |---|=|";
    gotoxy(x, y+5);
    cout << "|  |   |  |   |_|__|  |   |__|   | | |    |  |___| |";
    gotoxy(x, y+6);
    cout << "|~~|===|--|===|~|~~|  |~~~|--|:::|=|~|----|==|---|=|";
    gotoxy(x, y+7);
    cout << "____________________________________________________";
}

// Dibujar el logo
void dibujarLetras(int x, int y)
{
    setTextColor(White);
    setTextColor(2);
    gotoxy(x, y);
    cout << "  _      _ _                   _          _____ _     _ _     _ _ ";
    gotoxy(x, y+1);
    cout << " | |    (_) |                 (_)        / ____| |   (_) |   | (_)";
    gotoxy(x, y+2);
    cout << " | |     _| |__  _ __ ___ _ __ _  __ _  | |  __| |__  _| |__ | |_ ";
    gotoxy(x, y+3);
    cout << " | |    | | '_ \\| '__/ _ \\ '__| |/ _` | | | |_ | '_ \\| | '_ \\| | |";
    gotoxy(x, y+4);
    cout << " | |____| | |_) | | |  __/ |  | | (_| | | |__| | | | | | |_) | | |";
    gotoxy(x, y+5);
    cout << " |______|_|_.__/|_|  \\___|_|  |_|\\__,_|  \\_____|_| |_|_|_.__/|_|_|";
    gotoxy(x, y+6);
    cout << " ___________________________________________________________________ ";
}

void dibujarPresionaTecla(int x, int y)
{
    setTextColor(White);
    gotoxy(x, y);
    cout << "Presiona una tecla para continuar...";
}
