#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>

// ��ʼ��
void Initial()
{
	//����Ϊ��ɫ
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );	
}

void Drawquad(void)
{
	glBegin(GL_QUADS);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(80.0f, 0.0f);
		glVertex2f(80.0f, 80.0f);
		glVertex2f(0.0f, 80.0f);
	glEnd();
}

void ChangeSize(int w, int h)
{
	if(h == 0)		h = 1;
   	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// �����޼��ռ�ķ�Χ
   	if (w <= h) 
		glOrtho (0.0f, 300.0f, 0.0f, 300.0f*h/w, 1.0, -1.0);
    else 
		glOrtho (0.0f, 300.0f*w/h, 0.0f, 300.0f, 1.0, -1.0);
}

void ReDraw(void)
{
	glClear(GL_COLOR_BUFFER_BIT );
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//���ƺ�ɫ��������
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex2f(150.0f, 300.0f);
		glVertex2f(150.0f, 0.0f);
		glVertex2f(0.0f, 150.0f);
		glVertex2f(300.0f, 150.0f);
	glEnd();

	//������ʼͼ��
	glTranslatef( 150.0, 150.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	Drawquad();

//	glPushMatrix();
	// ���Ƴ���ת���ͼ��
	glRotatef( 135.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	Drawquad();

//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();

//	glPopMatrix();
	// ���Ƴ��ڶ�����ת���ͼ��
	glRotatef( 300.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	Drawquad();

	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("ͼ�α任");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(ReDraw);
	Initial();
	glutMainLoop();

	return 0;
}
