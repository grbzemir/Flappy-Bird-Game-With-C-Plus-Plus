#include<iostream>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include <time.h>

#define EKRAN_GENISLIGI 90
#define EKRAN_YUKSEKLIGI 26
#define WIN_GENISLIGI 70
#define MENU_GENISLIGI 20
#define GAP_SIZE 7
#define PIPE_DIF 45

using namespace std;

 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int pipePozisyon[3];
int gapPozisyon[3];
int pipeBayrak[3];
char kus[2][6] = { '/','-','-','o','\\',' ','|','_','_','_',' ','>' };

int kusPozisyon = 6;
int score = 0;

void gotoxy(int x, int y)

{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) 

{
	
	if(size == 0)

		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
	
}

void cizEkran()

{ 
	
	for(int i=0; i<EKRAN_GENISLIGI; i++)

	{

		gotoxy(i,0); 
		cout<<"#";
		gotoxy(i,EKRAN_YUKSEKLIGI); 
		cout<<"#";
	}
	
	for(int i=0; i<EKRAN_YUKSEKLIGI; i++)

	{
		gotoxy(0,i);
		cout<<"#";	
		gotoxy(EKRAN_GENISLIGI,i); 
		cout<<"#";

	}

	for(int i=0; i<EKRAN_YUKSEKLIGI; i++)

	{

		gotoxy(WIN_GENISLIGI,i); 
		cout<<"#";

	}

}
void genPipe(int ind)

{

	gapPozisyon[ind] = 3 + rand()%14; 
}
void cizPipe(int index)

{
	if( pipeBayrak[index] == true )

	{

		for(int i=0; i<gapPozisyon[index]; i++)
	
		{

			gotoxy(WIN_GENISLIGI-pipePozisyon[index],i+1); 
			cout<<"###"; 
		}

		for(int i=gapPozisyon[index]+GAP_SIZE; i<EKRAN_YUKSEKLIGI-1; i++)

		{ 
			gotoxy(WIN_GENISLIGI-pipePozisyon[index],i+1); 
			cout<<"###"; 

		}

	} 

}

void silPipe(int index)

{
	if( pipeBayrak[index] == true )

	{
		for(int i=0; i<gapPozisyon[index]; i++)

		{ 
			gotoxy(WIN_GENISLIGI-pipePozisyon[index],i+1); 
			cout<<"   "; 

		}

		for(int i=gapPozisyon[index]+GAP_SIZE; i<EKRAN_YUKSEKLIGI-1; i++)

		{ 

			gotoxy(WIN_GENISLIGI-pipePozisyon[index],i+1); 
			cout<<"   "; 
		}

	}

}

void cizKus()

{
	for(int i=0; i<2; i++)
	
	{
		for(int j=0; j<6; j++)
		
		{


			gotoxy(j+2,i+kusPozisyon); 
			cout<<kus[i][j];
		}
	}
}
void silKus()

{
	for(int i=0; i<2; i++)

	{

		for(int j=0; j<6; j++)

		{

			gotoxy(j+2,i+kusPozisyon); 
			cout<<" ";
		}

	}


}

int carpisma()

{



	if( pipePozisyon[0] >= 61  )

	{

		if( kusPozisyon<gapPozisyon[0] || kusPozisyon >gapPozisyon[0]+GAP_SIZE )
		{
//			cout<< " HIT ";
//			getch();

			return 1;

		}

	}

	return 0;

}

void debug()

{
	
	//	gotoxy(EKRAN_GENISLIGI + 3, 4); cout<<"Pipe Pozisyon: "<<pipePozisyon[0];

	
}
void gameover()

{
	system("cls");
	cout<<endl;
	cout<<"\t\t--------------------------"<<endl;
	cout<<"\t\t-------- Game Over -------"<<endl;
	cout<<"\t\t--------------------------"<<endl<<endl;
	cout<<"\t\tMenuye Donmek Icin Herhangi Bir Tusa Basiniz.";
	getch();

}
void scoruGuncelle()

{

	gotoxy(WIN_GENISLIGI + 7, 5);
	cout<<"Score: "<<score<<endl;

}

void Bilgiler()

{
	
	system("cls");
	cout<<"Bilgiler";
	cout<<"\n----------------";
	cout<<"\n\nSpacebar = zipla";
	cout<<"\n\nHerhangi Bir Tusa Basarsaniz Menuye Donersiniz.";
	getch();
}

void Oyna()

{
	
	kusPozisyon = 6;
	score = 0;
	pipeBayrak[0] = 1; 
	pipeBayrak[1] = 0;
	pipePozisyon[0] = pipePozisyon[1] = 4;
	
	system("cls"); 
	cizEkran();
	genPipe(0);
	scoruGuncelle();
	
	gotoxy(WIN_GENISLIGI + 5, 2);cout<<"FLAPPY BIRD";
	gotoxy(WIN_GENISLIGI + 6, 4);cout<<"----------";
	gotoxy(WIN_GENISLIGI + 6, 6);cout<<"----------";
	gotoxy(WIN_GENISLIGI + 7, 12);cout<<"Control ";
	gotoxy(WIN_GENISLIGI + 7, 13);cout<<"-------- ";
	gotoxy(WIN_GENISLIGI + 2, 14);cout<<" Spacebar = jump";
	
	gotoxy(10, 5);
	cout<<"Baslamak Icin Herhangi Bir Tusa Basiniz.";
	getch();
	gotoxy(10, 5);
	cout<<"                      ";
	
	while(1)
	
	{
		 
		if(kbhit()) // klavyeden herhangi bir tusa basildi mi?

		{
			char ch = getch();

			if(ch==32)

			{
				if( kusPozisyon > 3 )
					kusPozisyon-=3;
			} 

			if(ch==27)
			
			{
				
				break;
			}


		}
		
		cizKus();
		cizPipe(0);
		cizPipe(1);
		debug();

		if( carpisma() == 1 )

		{

			gameover();
			return;

		}

		Sleep(100);
		silKus();
		silPipe(0);
		silPipe(1);
		kusPozisyon += 1;
		
		if( kusPozisyon > EKRAN_YUKSEKLIGI - 2 )

		{
			gameover();
			return;
		}
		
		if( pipeBayrak[0] == 1 )
			pipePozisyon[0] += 2;
		
		if( pipeBayrak[1] == 1 )
			pipePozisyon[1] += 2;
		
		if( pipePozisyon[0] >= 40 && pipePozisyon[0] < 42 )

		{

			pipeBayrak[1] = 1;
			pipePozisyon[1] = 4;
			genPipe(1);

		}

		if( pipePozisyon[0] > 68 )

		{
			score++;
			scoruGuncelle();
			pipeBayrak[1] = 0;
			pipePozisyon[0] = pipePozisyon[1];
			gapPozisyon[0] = gapPozisyon[1];
			
		}
		
	}
	 
}

int main()
{
	
	system("color 4");
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 
	
//	play();
	
	do
	
	{
		system("cls");
		gotoxy(10,5);cout<<" -------------------------- "; 
		gotoxy(10,6);cout<<" |      Flappy Bird       | "; 
		gotoxy(10,7);cout<<" --------------------------";
		gotoxy(10,9);cout<<"1. Oyunu Baslat";
		gotoxy(10,10);cout<<"2. Bilgiler";	 
		gotoxy(10,11);cout<<"3. Cikis";
		gotoxy(10,13); 
		cout<<"Seciminiz: ";
		char secim = getche();
		
		if( secim=='1') 
		Oyna();

		else if( secim=='2') 
		Bilgiler();

		else if( secim=='3') 
		exit(0);
		
	}


	while(1);
	
	return 0;


}
