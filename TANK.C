#include <graphics.h>
#include <stdlib.h>
#include <conio.h>
#include <alloc.h>
#include <dos.h>
#include "key.h"

#define sc setcolor
#define sf setfillstyle

static void *tank,*mis;
main()
{
 int gd=DETECT,gm;
 initgraph(&gd,&gm,"");
 makedogu();
 game();
 closegraph();
}

makedogu()
{
/* Tank */
sf(1,12);bar(5,10,25,30);
sf(3,13);bar(0,12,5,19);
	 bar(0,21,5,28);
	 bar(25,12,30,19);
	 bar(25,21,30,28);
sf(5,2); bar(12,0,18,10);
tank=(void*)malloc(imagesize(0,0,30,30));
getimage(0,0,30,30,tank);
putimage(0,0,tank,XOR_PUT);

/* Missile */
sf(1,14);sc(14);
fillellipse(3,4,2,4);
bar(0,0,6,8);
mis=(void*)malloc(imagesize(0,0,6,8));
getimage(0,0,6,8,mis);
putimage(0,0,mis,XOR_PUT);
}

game()
{
 int x,y,xx,yy,ch,loop=1;
 x=305;
 y=225;
 putimage(x,y,tank,XOR_PUT);
 while(loop)
 {
  if((ch=getch())==0)ch=getch()<<8;
  xx=x;
  yy=y;
  switch(ch)
  {
   case ESC  :loop=0;break;
   case RIGHT:x=(x<605)?x+5:0;break;
   case LEFT :x=(x>0)?x-5:605;break;
   case DOWN : y=(y<445)?y+5:0;break;
   case UP   : y=(y>0)?y-5:445;break;
   case SPC  :shot(x,y);break;
   }
  putimage(xx,yy,tank,XOR_PUT);
  putimage(x,y,tank,XOR_PUT);
  }
 }

shot(x,y)
{
 int i;
 for(i=y-8;i>=0;i-=5)
 {
 putimage(x+12,i,mis,XOR_PUT);
 sound(i*10+100);
 delay(10);
 nosound();
 putimage(x+12,i,mis,XOR_PUT);
 }
 for(i=1;i<=50;i++)
 {
  sc(random(15)+1);
  line(x+2,0,random(20)+x+2,random(16));
  sound(i*50+50);
  delay(5);
  }
  nosound();
  sf(1,0);
  bar(x+2,0,x+22,15);
}
