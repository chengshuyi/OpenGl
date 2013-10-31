#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void Initial()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
	glEnable(GL_DEPTH_TEST);	
	glShadeModel(GL_SMOOTH);
}

void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;
	if(h == 0)	h = 1;

    glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ReDraw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    glPushMatrix();
   	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	//ǰ��
	glBegin(GL_POLYGON);
		// ��ɫ
		glColor3ub((GLubyte) 255, (GLubyte)255, (GLubyte)255);
		glVertex3f(50.0f,50.0f,50.0f);

		// ��ɫ
		glColor3ub((GLubyte) 255, (GLubyte)255, (GLubyte)0);
		glVertex3f(50.0f,-50.0f,50.0f);

		// ��ɫ
		glColor3ub((GLubyte) 255, (GLubyte)0, (GLubyte)0);
		glVertex3f(-50.0f,-50.0f,50.0f);

		// ���
		glColor3ub((GLubyte) 255, (GLubyte)0, (GLubyte)255);
		glVertex3f(-50.0f,50.0f,50.0f);
	glEnd();
	
	// ����
	glBegin(GL_POLYGON);
		// ��ɫ
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(50.0f,50.0f,-50.0f);

		// ��ɫ
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(50.0f,-50.0f,-50.0f);
		
		// ��ɫ
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-50.0f,-50.0f,-50.0f);

		// ��ɫ
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-50.0f,50.0f,-50.0f);
	glEnd();

	// ����
	glBegin(GL_POLYGON);
		// ��ɫ
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(50.0f,50.0f,-50.0f);

		// ��ɫ
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(50.0f,50.0f,50.0f);

		// ���
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-50.0f,50.0f,50.0f);

		// ��ɫ
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-50.0f,50.0f,-50.0f);
	glEnd();

	// ����
	glBegin(GL_POLYGON);
		// ��ɫ
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(50.0f,-50.0f,-50.0f);

		// ��ɫ
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(50.0f,-50.0f,50.0f);

		// ��ɫ
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-50.0f,-50.0f,50.0f);

		// ��ɫ
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-50.0f,-50.0f,-50.0f);
	glEnd();

	// �����
	glBegin(GL_POLYGON);
		// ��ɫ
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(50.0f,50.0f,50.0f);

		// ��ɫ
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(50.0f,50.0f,-50.0f);

		// ��ɫ
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(50.0f,-50.0f,-50.0f);

		// ��ɫ
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(50.0f,-50.0f,50.0f);
	glEnd();

	// �ұ���
	glBegin(GL_POLYGON);
		// ���
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-50.0f,50.0f,50.0f);

		// ��ɫ
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-50.0f,50.0f,-50.0f);

		// ��ɫ
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-50.0f,-50.0f,-50.0f);

		// ��ɫ
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-50.0f,-50.0f,50.0f);
	glEnd();

    glPopMatrix();

	glutSwapBuffers();
}

void SpecialKeys(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)		xRot-= 5.0f;
	if(key == GLUT_KEY_DOWN)	xRot += 5.0f;
	if(key == GLUT_KEY_LEFT)	yRot -= 5.0f;
	if(key == GLUT_KEY_RIGHT)	yRot += 5.0f;

	if(key > 356.0f)	xRot = 0.0f;
	if(key < -1.0f)		xRot = 355.0f;
	if(key > 356.0f)	yRot = 0.0f;
	if(key < -1.0f)		yRot = 355.0f;

	// ˢ�´���
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("��ɫ������");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(ReDraw);
	Initial();
	glutMainLoop();

	return 0;
}
