#include<stdio.h>
#include<stdbool.h>
#include<GL/glut.h>
#define outcode int
float xvmin=200,yvmin=200,xvmax=300,yvmax=300;
float xmin,ymin,xmax,ymax;
float x0,y0,x1,y1;
const int RIGHT=2;
const int LEFT=2;
const int TOP=8;
const int BOTTOM=4;
int computeoutcode(float x,float y);
void CSLCAD(float x0,float y0,float x1,float y1)
{
	int outcode0,outcode1,outcodeout;
	bool accept=false,done=false;
	outcode0=computeoutcode(x0,y0);
	outcode1=computeoutcode(x1,y1);
do
{
	if(outcode0==0 & outcode1==0)
	{
		accept=true;
		done=true;
	}
	else if(outcode0 & outcode1)
	done =true;
	else
	{
		double x,y;
		outcodeout=outcode0?outcode0:outcode1;
		if(outcodeout&TOP)
		{
			x=x0+(x1-x0)*(ymax-y0)/(y1-y0);
			y=ymax;
		}
		else if(outcodeout & BOTTOM)
		{
			x=x0+(x1-x0)*(ymin-y0)/(y1-y0);
			y=ymin;
		}
		else if(outcodeout & RIGHT)
		{
			y=x0+(x1-x0)*(xmax-x0)/(y1-y0);
			x=xmax;
		}
		else 
		{
			y=x0+(x1-x0)*(xmin-x0)/(y1-y0);
			x=xmin;
		}
		if(outcodeout==outcode0)
		{
			x0=x;
			y0=y;
			outcode0=computeoutcode(x0,y0);
		}
		else
		{
			x1=x;
			y1=y;
			outcode1=computeoutcode(x1,y1);
		}
	}
}while(!done);
if(accept)
{
	double Sx=(xvmax-xvmin)/(xmax-xmin);
	double Sy=(yvmax-yvmin)/(ymax-ymin);
	double vx0=xvmin+(x0-xmin)*Sx;
	double vy0=yvmin+(y0-xmin)*Sy;
	double vx1=xvmin+(x1-xmin)*Sx;
	double vy1=yvmin+(y1-xmin)*Sy;
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xvmin,yvmin);
	glVertex2f(xvmax,yvmin);
	glVertex2f(xvmax,yvmax);
	glVertex2f(xvmin,yvmax);
	glEnd();
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINES);
	glVertex2d(vx0,vy0);
	glVertex2d(vx1,vy1);
	glEnd();

}
}
int computeoutcode(float x, float y)
{
	int code=0;
	if(y>ymax)
	code=code|TOP;
	else if(y<ymin)
	code=code|BOTTOM;
	if(x>xmax)
	code=code|RIGHT;
	else if(x<xmin)
	code=code|LEFT;
	return code;
}
void drawline()
{
	glBegin(GL_LINES);
	glVertex2f(x0,y0);
	glVertex2f(x1,y1);
	glEnd();
}
void drawrect()
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin,ymin);
	glVertex2f(xmax,ymin);
	glVertex2f(xmax,ymax);
	glVertex2f(xmin,ymax);
	glEnd();
}
void display()
{
	glColor3f(1.0,0.0,0.0);
	drawline();
	glColor3f(0.0,0.0,1.0);
	drawrect();
	CSLCAD(x0,y0,x1,y1);
	glFlush();
}
void myinit()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,499.0,0.0,499.0);
}
int main(int argc,char*argv[])
{
printf("enter the end point of the clipping window");
scanf("%f%f%f%f",&xmin,&ymin,&xmax,&ymax);
printf("enter the end points");
scanf("%f%f%f%f",&x0,&y0,&x1,&y1);
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(500,500);
glutCreateWindow("COHEN SUTHERLAND LINE CLIPPING 4MT19CS173");
glutDisplayFunc(display);
myinit();
glutMainLoop();
return 0;
}
	
	
