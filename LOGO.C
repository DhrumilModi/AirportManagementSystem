#include<conio.h>
#include<graphics.h>
#include<stdio.h>


void main()
{
int gd=DETECT,gm,i=0;
initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
for(i=0;i<600;i++)
{
line(80+i,200,250+i,200);
line(150+i,240,200+i,240);
line(150+i,240,100+i,300);
line(200+i,240,100+i,300);
line(80+i,280,115+i,280);
line(132+i,280,250+i,280);
ellipse(250+i,240,270,90,80,40);
line(100+i,170,150+i,200);
line(100+i,170,200+i,200);
line(80+i,200,65+i,160);
arc(80+i,240,180,270,40);

line(40+i,240,40+i,160);
line(40+i,160,65+i,160);
ellipse(250+i,238,10,81,70,30);
line(261+i,233,320+i,233);
line(261+i,233,261+i,210);
rectangle(100+i,210,120+i,230);
rectangle(130+i,210,150+i,230);
rectangle(160+i,210,180+i,230);
rectangle(190+i,210,210+i,230);
rectangle(220+i,210,240+i,230);

line(0,459,679,459);
/*
rectangle(510-i,459,550-i,430) ;
rectangle(550-i,459,610-i,430);
line(530-i,410,550-i,430);
line(530-i,410,510-i,430);
line(590-i,410,610-i,430);
line(590-i,410,530-i,410);

rectangle(430-i,430,490-i,459);
rectangle(390-i,430,430-i,459);
line(410-i,410,430-i,430);
line(410-i,410,390-i,430);
line(410-i,410,470-i,410);
line(470-i,410,490-i,430);
*/
delay(1);
cleardevice();
}

//line(100,100,	200,300);
settextstyle(6,0,5);
delay(1000);
outtextxy(265,160,"Airline");delay(1000);
outtextxy(220,200,"Management");delay(1000);
outtextxy(255,240,"System");delay(1000);
getch();
}
