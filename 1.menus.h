void estructura_menu(){ 
    //Título
    color(4);
    gotoxy(52,5);
    cout<<"BIBLIOTECA GHIBLI";
    color(0);

    //Título
    //Barras horizontales
    color(4);
    for(int i=46;i<75;i++){
        gotoxy(i,3);
        cout<<(char)205;
        gotoxy(i,7);
        cout<<(char)205;
    }
    //Esquinas
    gotoxy(45,3);
    cout<<(char)218;
    gotoxy(45,7);
    cout<<(char)192;
    gotoxy(75,3);
    cout<<(char)191;
    gotoxy(75,7);
    cout<<(char)217;
    //Barras verticales
    for(int i=4;i<7;i++){
        gotoxy(45,i);
        cout<<(char)186;
        gotoxy(75,i);
        cout<<(char)186;
    }
    color(0);

    //Menú
    color(4);
    //Barras hoizontales
    for(int i=16;i<104;i++){
        gotoxy(i,9);
        cout<<(char)205;
        gotoxy(i,29);
        cout<<(char)205;
    }
    //Esquinas
    gotoxy(15,9);
    cout<<(char)201;
    gotoxy(15,29);
    cout<<(char)200;
    gotoxy(104,9);
    cout<<(char)187;
    gotoxy(104,29);
    cout<<(char)188;
    //Barras verticales
    for(int i=10;i<29;i++){
        gotoxy(15,i);
        cout<<(char)186;
        gotoxy(104,i);
        cout<<(char)186;
    }
    color(0);
    
    //Conexión título con menú
    color(4);
    gotoxy(49,7);
    cout<<(char)203;
    gotoxy(49,8);
    cout<<(char)186;
    gotoxy(49,9);
    cout<<(char)202;
    gotoxy(71,7);
    cout<<(char)203;
    gotoxy(71,8);
    cout<<(char)186;
    gotoxy(71,9);
    cout<<(char)202;
    color(0);

}