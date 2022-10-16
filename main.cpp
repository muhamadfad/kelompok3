#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PI 3.14



//Deklarasi fungsi Mouse agar gambar 3d dapat diputar putar menggunakan Mouse
float xrot =0;
float yrot = 0;
float xdiff = 0;
float ydiff = 0;
bool mouseDown = false;

//DEKLARASI UNTUK MEMBUAT BENDA BERGERAK
int gerak = 0;
bool atas = true;


//Deklarasi pengaturan lembaran kerja agar Gambar 3d yang kita buat saat diputar atau di geser tidak kemana mana
void ukur(int lebar, int tinggi){
if(tinggi==0) tinggi=1;
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(45,lebar/tinggi, 5, 450);
glTranslatef(0,0,-400);// jarak object dari lembaran kerja
glMatrixMode(GL_MODELVIEW);
}
void myinit(void){
glClearColor (0.0, 0.0, 0.0, 0.0);

glMatrixMode(GL_PROJECTION);
glEnable(GL_DEPTH_TEST);

glMatrixMode(GL_MODELVIEW);
glPointSize(10.0);
glLineWidth(7.0f);
}

//Dan selanjutnya yaitu fungsi mouse
void idle()
{
if (!mouseDown)
{
xrot += 0.3;
yrot += 0.4;
}
glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
{
mouseDown = true;
xdiff = x - yrot;
ydiff = -y + xrot;
}
else
mouseDown = false;
}

void mouseMotion(int x, int y)
{
if(mouseDown)
{
yrot = x - xdiff;
xrot = y + ydiff;
glutPostRedisplay();
}
}

//Dibawah ini dimulai koding untuk membuat object
void tampilan(void){
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity();
gluLookAt(0,0,3,0,0,0,0,1,0);
glRotatef(xrot, 1, 0,0);
glRotatef(yrot, 0,1,0);
glPushMatrix();

glTranslatef( gerak, 0,0);//UNTUK MENGGERAKKAN BENDA
//KUBUS BAG 1
glBegin(GL_POLYGON);
glColor3f(0,0,0);
glVertex3f(-40,-40,40);
glVertex3f(40,-40,40);
glVertex3f(40,-40,-40);
glVertex3f(-40,-40,-40);
glEnd();
//KUBUS BAG 2
glBegin(GL_POLYGON);
glColor3f(0,0,0);
glVertex3f(40,-40,40);
glVertex3f(40,40,40);
glVertex3f(40,40,-40);
glVertex3f(40,-40,-40);
glEnd();
//KUBUS BAG 3
glBegin(GL_POLYGON);
glColor3f(0,0,0);
glVertex3f(-40,-40,40);
glVertex3f(-40,40,40);
glVertex3f(-40,40,-40);
glVertex3f(-40,-40,-40);
glEnd();
//KUBUS BAG 4
glBegin(GL_POLYGON);
glColor3f(0,0,0);
glVertex3f(-40,40,40);
glVertex3f(40,40,40);
glVertex3f(40,40,-40);
glVertex3f(-40,40,-40);
glEnd();
//KUBUS BAG 5
glBegin(GL_POLYGON);
glColor3f(0,0,0);
glVertex3f(-40,40,40);
glVertex3f(40,40,40);
glVertex3f(40,-40,40);
glVertex3f(-40,-40,40);
glEnd();
//KUBUS BAG 6
glBegin(GL_POLYGON);
glColor3f(0,0,0);
glVertex3f(-40,40,-40);
glVertex3f(40,40,-40);
glVertex3f(40,-40,-40);
glVertex3f(-40,-40,-40);
glEnd();

glPushMatrix();
glPopMatrix();
glutSwapBuffers();
}
void timer(int t)//UNTUK MENGGERAKKAN BENDA
{
    if (atas){
        gerak += 1;
    } else {
        gerak -= 1;
    }
    if (gerak > 20) {
        atas = false;
    } else if(gerak < -20){
        atas = true;
    }
 glutPostRedisplay();
//kecepatan mobil berbanding terbalik
//semakin besar nilai glutTimerFunc jika ingin mengganti kecepatan
//silahkan ganti angka 50 di bawah ini, misal 100 mobil akan semakin lambat
//dibawah 50 mobil akan semakin cepat
 glutTimerFunc(50,timer,0);
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(240, 80);
    glutInitWindowSize(750, 600);
    glutCreateWindow("MEMBUAT CPU");
    myinit();
    glClearColor(1.0,1.0,1.0,0.0);
    glutDisplayFunc(tampilan);
    glutTimerFunc(1,timer,0);//UNTUK MENGGERAKKAN BENDA
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
    glutReshapeFunc(ukur);
    glutMainLoop();
}
