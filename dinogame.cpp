#include <iostream> 
#include <conio.h> 
#include <time.h>
#include <windows.h>

#define dinoPos 2
#define hurdlePos 74

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int dinoY;
int speed = 40;
int gameover = 0;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setcursor(bool visible, DWORD size){
    if (size == 0) {
        size = 20; // default cursor size Changing to numbers from 1 to 20, decreases cursor width
    }
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, & lpCursor);
}
 
void init() {
    system("cls"); 
    gameover = 0;
    gotoxy(3, 2); cout<<"SCORE : ";
    for (int i = 0; i < 79; i++){
    	gotoxy(1+i, 1); cout<<"ß";
    	gotoxy(1+i, 25); cout<<"ß";
	} 
}

void moveDino(int jump = 0) {
    static int foot = 0;

    if (jump == 0)
        dinoY = 0;
    else if (jump == 2)
        dinoY--;
    else dinoY++;

    gotoxy(dinoPos, 15 - dinoY);cout<<"                 ";
    gotoxy(dinoPos, 16 - dinoY);cout<<"         ÜÛßÛÛÛÛÜ";
    gotoxy(dinoPos, 17 - dinoY);cout<<"         ÛÛÛÛÛÛÛÛ";
    gotoxy(dinoPos, 18 - dinoY);cout<<"         ÛÛÛÛÛßßß";
    gotoxy(dinoPos, 19 - dinoY);cout<<" Û      ÜÛÛÛÛßßß ";
    gotoxy(dinoPos, 20 - dinoY);cout<<" ÛÛÜ  ÜÛÛÛÛÛÛÜÜÜ ";
    gotoxy(dinoPos, 21 - dinoY);cout<<" ßÛÛÛÛÛÛÛÛÛÛÛ  ß ";
    gotoxy(dinoPos, 22 - dinoY);cout<<"   ßÛÛÛÛÛÛÛß     ";
    gotoxy(dinoPos, 23 - dinoY);

    if (jump == 1 || jump == 2) {
        cout<<"    ÛÛß ßÛ       ";
        gotoxy(2, 24 - dinoY);
        cout<<"    ÛÜ   ÛÜ      ";
    } 
	else if (foot == 0) {
        cout<<"    ßÛÛß  ßßß    ";
        gotoxy(2, 24 - dinoY);
        cout<<"      ÛÜ         ";
        foot = !foot;
    } 
	else if (foot == 1) {
        cout<<"     ßÛÜ ßÛ      ";
        gotoxy(2, 24 - dinoY);
        cout<<"          ÛÜ     ";
        foot = !foot;
    }
    
    gotoxy(2, 25 - dinoY);
    if (jump == 0) {
        cout<<"ßßßßßßßßßßßßßßßßß";
    } else {
        cout<<"                ";
    } 
    Sleep(speed);
}
void drawHurdle() {
    static int plantX = 0;
	static int score = 0;
    if (plantX == 56 && dinoY < 4) {
        score = 0;
        speed = 40;
        gotoxy(36, 8);cout<<"Game Over";
        getch();
        gameover = 1; 
    }
    
    gotoxy(hurdlePos - plantX, 20);cout<<"| | ";
    gotoxy(hurdlePos - plantX, 21);cout<<"| | ";
    gotoxy(hurdlePos - plantX, 22);cout<<"|_| ";
    gotoxy(hurdlePos - plantX, 23);cout<<" |  ";
    gotoxy(hurdlePos - plantX, 24);cout<<" |  ";
     
    plantX++;
    
    if (plantX == 73) {
        plantX = 0;
        score++;
        gotoxy(11, 2);cout<<"     ";
        gotoxy(11, 2);cout<<score;
        if (speed > 20)
            speed--;
    }
}
void play(){ 
	system("cls");
    char ch;
    int i;
	init();
    while (true) {
        while (!kbhit()) {
            if( gameover==1 ){
            	return;
			}
			moveDino();
            drawHurdle();
        }
        ch = getch();
        if (ch == 32) {
        	i = 0;
            while( i < 12) {
                moveDino(1);
                drawHurdle();
                i++;
            }
            while(i > 0) {
                moveDino(2);
                drawHurdle();
                i--;
        	}
        }
		else if (ch == 'p'||ch=='P')
           getch();
		else if (ch == 27)
           break;
    }
}

void instructions() {
	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n1. Avoid hurdles by jumping";
	cout<<"\n2. Press 'Spacebar' to jump ";
	cout<<"\n3. Press 'p' to pause game ";
	cout<<"\n4. Press 'Escape' to exit from game";
	cout<<"\n\nPress any key to go back to menu";
	getch();
}

int main() {

    setcursor(0, 0);
    
    do{
		system("cls");
		gotoxy(10,5); cout<<" -------------------------- "; 
		gotoxy(10,6); cout<<" |        DINO RUN        | ";  
		gotoxy(10,7); cout<<" -------------------------- ";
		gotoxy(10,9); cout<<"1. Start Game";
		gotoxy(10,10); cout<<"2. Instructions";	 
		gotoxy(10,11); cout<<"3. Quit";
		gotoxy(10,13); cout<<"Select option: ";
		char op = getche();
		
		if( op=='1') play();
		else if( op=='2') instructions();
		else if( op=='3') exit(0);
		
	}while(1);
    
	return 0;
}
