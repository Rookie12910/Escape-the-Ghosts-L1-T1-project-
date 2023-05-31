#include "iGraphics.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define menu 1
#define playgame_1 2
#define playgame_2 3
#define gameover 4
#define howtoplay 5
#define Highscore 6
#define exitgame 7
#define rightside 1
#define leftside 2

int State = menu,mode=rightside;
char score[10];
char playername[100],name[100];
int len = 0;
int Score = 0,temp_score;
char run_r[3][10]= {"pr1.bmp","pr2.bmp","pr3.bmp"};
char run_l[3][10]= {"pl1.bmp","pl2.bmp","pl3.bmp"};
int r= 0,l=0;
int SCR,GHST;
char scr_0[10];
char scr_1[5];
char scr_2[5];
char scr_3[5];
char scr_4[5];

typedef struct
{
    char name[10];
    int scr;
}HighScore;
HighScore HS[5];

typedef struct
{
    int x;
    int y;
    int Count;
}character;

character player = {450,0};
character ghost1 ={420,580,0};
character ghost2 ={60,580,0};
character ghost3 ={800,580,0};

void  SCORE()
{
     if(State==playgame_2)
    {
        Score+=5;

    }
    else if(State==menu)
   {
       Score = 0;

   }

}

void HIGHSCORE()
{
    FILE *fp;
    fp = fopen("Highscore.txt","rb");
    for(int i=0;i<5;i++)
    {
        fscanf(fp,"%s %d",&HS[i].name,&HS[i].scr);
    }
    fclose(fp);
}

void score_sorting()
{
  HIGHSCORE();
        for(int i=0;i<5;i++)
        {
            if(temp_score>HS[i].scr)
            {
                for(int j =0;j<4-i; )
                {

                    HS[4-j].scr = HS[4-j-1].scr;
                    strcpy(HS[4-j].name,HS[4-j-1].name);
                    j++;

                }
                strcpy(HS[i].name,name);
                HS[i].scr = temp_score;
                temp_score = 0;
            }


        }
        FILE *fp;
        fp = fopen("Highscore.txt","wb");
        for(int i =0;i<5;i++)
        {
            fprintf(fp,"%s   %d\n",HS[i].name,HS[i].scr);
        }
        fclose(fp);

}





/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{

      iClear();
      itoa(Score,score,10);

    if(State ==menu)
    {


        iShowBMP(0,0,"menu.bmp");

    }
    if(State==playgame_1)
    {
    iSetColor(255, 255, 255);
    iText(300,400,"Enter your name : ",GLUT_BITMAP_TIMES_ROMAN_24);
	iRectangle(300, 350, 250, 30);
	iText(310,360,playername,GLUT_BITMAP_HELVETICA_18);
    }
    else if(State==playgame_2)
    {
        iResumeTimer(GHST);
        iShowBMP(0,0,"back ground.bmp");
        iShowBMP(0,0,"brick.bmp");
        iShowBMP(0,50,"brick.bmp");
        iShowBMP(0,100,"brick.bmp");
        iShowBMP(850,0,"brick.bmp");
        iShowBMP(850,50,"brick.bmp");
        iShowBMP(850,100,"brick.bmp");
        iSetColor(255,0,0);
        iText(750,550,"SCORE : ",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(850,550,score,GLUT_BITMAP_TIMES_ROMAN_24);


        if(mode==rightside)
        {
            iShowBMP2(player.x,player.y,run_r[r],0);
        }
        else if(mode==leftside)
        {
            iShowBMP2(player.x,player.y,run_l[l],0);
        }

        iShowBMP2(ghost1.x,ghost1.y,"ghost1.bmp",0);
        iShowBMP2(ghost2.x,ghost2.y,"ghost2.bmp",0);
        iShowBMP2(ghost3.x,ghost3.y,"ghost3.bmp",0);

    }
    else if(State==gameover)
    {

        iShowBMP(0,0,"game over.bmp");
        iShowBMP(0,0,"brick.bmp");
        iShowBMP(0,50,"brick.bmp");
        iShowBMP(0,100,"brick.bmp");
        iShowBMP(850,0,"brick.bmp");
        iShowBMP(850,50,"brick.bmp");
        iShowBMP(850,100,"brick.bmp");
        if(mode==rightside)
        iShowBMP2( player.x,player.y,"prd.bmp",0);
        if(mode==leftside)
        iShowBMP2( player.x,player.y,"pld.bmp",0);
        iText(330,300,"YOUR SCORE : ",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(500,300,score,GLUT_BITMAP_TIMES_ROMAN_24);
        score_sorting();
   }
    else if(State==howtoplay)
    {
        iShowBMP(0,0,"how to play.bmp");
    }
    else if(State==Highscore)
    {
            iShowBMP(0,0,"high score.bmp");
            HIGHSCORE();
            itoa(HS[0].scr,scr_0,10);
            itoa(HS[1].scr,scr_1,10);
            itoa(HS[2].scr,scr_2,10);
            itoa(HS[3].scr,scr_3,10);
            itoa(HS[4].scr,scr_4,10);
            iSetColor(255,255,255);
            iText(300,400,HS[0].name,GLUT_BITMAP_TIMES_ROMAN_24);
            iText(500,400,scr_0,GLUT_BITMAP_TIMES_ROMAN_24);
            iText(300,350,HS[1].name,GLUT_BITMAP_TIMES_ROMAN_24);
            iText(500,350,scr_1,GLUT_BITMAP_TIMES_ROMAN_24);
            iText(300,300,HS[2].name,GLUT_BITMAP_TIMES_ROMAN_24);
            iText(500,300,scr_2,GLUT_BITMAP_TIMES_ROMAN_24);
            iText(300,250,HS[3].name,GLUT_BITMAP_TIMES_ROMAN_24);
            iText(500,250,scr_3,GLUT_BITMAP_TIMES_ROMAN_24);
            iText(300,200,HS[4].name,GLUT_BITMAP_TIMES_ROMAN_24);
            iText(500,200,scr_4,GLUT_BITMAP_TIMES_ROMAN_24);



    }
    else if(State==exitgame)
    {
        exit(0);
    }



}


/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{

}
/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(State==menu)
    {
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {


            if(mx>=312 && mx<=590 && my>=370 && my<=466)
                State = playgame_1;
            if(mx>=300 && mx<=610 && my>=250 && my<=350)
                State = howtoplay;
            if(mx>=305 && mx<=595 && my>=135 && my<=230)
                State = Highscore;
            if(mx>=315 && mx<=590 && my>=15 && my<=115)
                State = exitgame;







        }
        if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        {


        }
    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if(State == playgame_1)
	{
        if(key == '\r')
		{

			State = playgame_2;
			strcpy(name, playername);
			for(int i = 0; i < len; i++)
				playername[i] = '\0';
			    len = 0;

		}
		else
		{
			playername[len] = key;
			len++;
		}

	}

      if(State==Highscore && key=='\r')
      {
          State = menu;
      }

     if(State==gameover && key =='\r')
     {

        player.x=450,player.y=0;
        ghost1.x =420,ghost1.y=580;
        ghost2.x=60,ghost2.y=580;
        ghost3.x=840,ghost3.y=580;
        ghost1.Count = 0;
        ghost2.Count = 0;
        ghost3.Count = 0;
        State =menu;
        iResumeTimer(SCR);

     }
    if(State==howtoplay && key =='\r')
        State =menu;

}




/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)

{
    if(key==GLUT_KEY_END)
    {
        exit(0);
    }


    if(State==playgame_2)
    {
        if(player.x>50)
        {

            if(key == GLUT_KEY_LEFT)
            {
                mode = leftside;
                player.x=player.x-10;
                 l++;
                if(l>2)
                    l= 0;
            }
        }
        if(player.x<800)
        {
            if(key == GLUT_KEY_RIGHT)
            {
                mode =rightside;
                player.x=player.x+10;
                r++;
                if(r>2)
                    r= 0;
            }
        }
    }
}
void ghost()
{
    if(State ==playgame_2)
    {
        ghost1.y-=7+(ghost1.Count/3);
        if(ghost1.y<0)
        {
            ghost1.x+=150;
            ghost1.y=580;
            ghost1.Count++;
        }
        if(ghost1.x>760)
        {
            ghost1.x=100;
            ghost1.y=580;

        }
        ghost2.y-=10+ (ghost2.Count/4);
        if(ghost2.y<0)
        {
            ghost2.x+=200;
            ghost2.y=580;
            ghost2.Count++;
        }
        if(ghost2.x>760)
        {
            ghost2.x=20;
            ghost2.y=580;

        }
        ghost3.y-=15+ (ghost3.Count/5);
        if(ghost3.y<0)
        {
            ghost3.x-=250;
            ghost3.y=580;
            ghost3.Count++;
        }
        if(ghost3.x<30)
        {
            ghost3.x=800;
            ghost3.y=580;

        }

    }
    if((ghost1.x>=(player.x-75) && ghost1.x<=(player.x+54)) && (ghost1.y>=player.y && ghost1.y<=(player.y+60)))
    {
        State = gameover;
        temp_score = Score;
        iPauseTimer(GHST);
        iPauseTimer(SCR);

    }
    if((ghost2.x>=(player.x-50) && ghost2.x<=(player.x+54)) && (ghost2.y>=player.y && ghost2.y<=(player.y+60)))
    {

        State = gameover;
        temp_score = Score;
        iPauseTimer(GHST);
        iPauseTimer(SCR);

    }
    if((ghost3.x>=(player.x-50) && ghost3.x<=(player.x+54)) && (ghost3.y>=player.y && ghost3.y<=(player.y+60)))
    {

        State = gameover;
        temp_score = Score;
        iPauseTimer(GHST);
        iPauseTimer(SCR);

    }


}


int main()
{
    PlaySound("music.wav", NULL , SND_ASYNC | SND_LOOP);
    SCR=iSetTimer(2000,SCORE);
    GHST=iSetTimer(25,ghost);
    iInitialize(900, 600, "Escape the Ghosts");
    return 0;
}
