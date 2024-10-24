#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
using namespace std;

int ax[100], ay[100];
int n = 3, bx, by, score = 0;

void gotoXY(int x, int y){
    static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
}

void ShowCur(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = {1, CursorVisibility};
    SetConsoleCursorInfo(handle, &cursor);
}

// ------------------------------------------------------------------

void vetuong(){
    for (int x=4; x<=55; x++){
        gotoXY(x,1);
        cout<< "_";
        gotoXY(x,25);
        cout<< "_";
    }
    for (int y=2; y<=25; y++){
        gotoXY(4,y);
        cout<< "|";
        gotoXY(55,y);
        cout<< "|";
    }
}

void taoran(){
    int x =30, y = 12;
    for (int i=0; i<n; i++){
        ax[i] = x;
        x--;
        ay[i] = y;
    }
}

void veran(){
    for (int i=0; i<n; i++){
        gotoXY(ax[i], ay[i]);
        if (i==0) 
            cout<< "+";
        else
            cout<< "o";
    }
}

void dichuyen(int x, int y){
    for (int i=n; i>0; i--){
        ax[i]=ax[i-1];
        ay[i]=ay[i-1];
    }
    ax[0]=x;
    ay[0]=y;
}

bool ktchamthan(){
	for (int i=1; i<n; i++)
		if (ax[i]==ax[0] && ay[i]==ay[0])
			return true;
	return false;
}

bool gameover(){
	if (ax[0] == 4 || ax[0] == 55 || ay[0] == 2 || ay[0] == 25 || ktchamthan()==true)
		return true;
	return false;
}

bool rantrenmoi(){
	for (int i=0; i<n; i++){
		if (ax[i]==bx && ay[i]==by)
			return true;
	}
	return false;
}


void taomoi(){
	do {
		bx = rand()%(54 - 5 + 1)+5;
		by = rand()%(24 - 3 +1)+3;
	} while (rantrenmoi() == true);
}

void vemoi(){
	gotoXY(bx, by);
	cout << "@";
}

bool kt(){
	if (ax[0] == bx && ay[0]==by)
		return true;
	return false;
}

void anmoi(){
	if (kt() == true) {
		n++;
		score ++;
		taomoi();
		vemoi();
	}	
}



int main(){
	srand((int) time(0));
    ShowCur(0);
        // setting
    system("cls");    
    vetuong();
    taoran();
    taomoi();
    vemoi();
    //   play
    int check = 2;   //  0 xuong    1 len   2 phai    3 trai
    int x = ax[0];
    int y= ay[0];
    while (true){
        //clear data cu
        gotoXY(ax[n],ay[n]);
        cout<<" ";
        // ve 
        veran();
        // dieu khien
        if (kbhit()){
            char c = getch();
            if (c==-32){
                c = getch();
                if (c==72 && check != 0)
                    check = 1;
                else
                    if (c==80 && check !=1)
                        check = 0;
                    else 
                        if (c==75 && check != 2)
                            check = 3;
                        else
                            if (c==77 && check != 3)
                                check = 2;
            }
        } 
        // di chuyen
        if (check ==2)
            x++;
        else
            if (check ==3)
                x--;
            else
                if (check ==1)
                    y--;
                else
                    if (check ==0)
                        y++;
        //  game over
        if (gameover()==true){
        	gotoXY(25, 14);
        	cout<< "<GAME OVER>";
        	break;
		}
        // xu ly
        anmoi();
        dichuyen(x,y);
        gotoXY(25,27);
        cout<<"SCORE: "<< score;
        // speed
        Sleep(107);
    }
    getch();
    return 0;
}

