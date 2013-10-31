#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>

GLint nNumPoints = 4;

GLfloat ctrlPoints[4][3]= {{  -4.0f, 0.0f, 0.0f},	// �յ�
							{ -6.0f, 4.0f, 0.0f},	// ���Ƶ�
							{  6.0f, -4.0f, 0.0f},	// ���Ƶ�
							{  4.0f, 0.0f, 0.0f }};	// �յ�

void DrawPoints(void)
{
	int i;	
	glPointSize(5.0f);
	glBegin(GL_POINTS);
		for(i = 0; i < nNumPoints; i++)
			glVertex2fv(ctrlPoints[i]);
	glEnd();
}

void Initial()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
	glColor3f(0.0f, 0.0f, 1.0f);	
	glLineWidth(2.0f);
}

void ReDraw(void)
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);

	glMap1f(GL_MAP1_VERTEX_3,	// ��������������
	0.0f,						// ������Сֵ
	100.0f,						// �������ֵ
	3,							// ���Ƶ����ݶ���֮�����Ŀ
	nNumPoints,					// ���Ƶ���Ŀ
	&ctrlPoints[0][0]);			// ������Ƶ������

	//������ְ��
	glEnable(GL_MAP1_VERTEX_3);

	// �������ϵĵ���������
	glBegin(GL_LINE_STRIP);
		for(i = 0; i <= 100; i++)
		{
			// ���㵱ǰ���ߵ������
			glEvalCoord1f((GLfloat) i); 
		}
	glEnd();

//	glMapGrid1d(100,0.0,100.0);
//	glEvalMesh1(GL_LINE,0,100);

	DrawPoints();
	glutSwapBuffers();
}

void ChangeSize(int w, int h)
{
	if(h == 0)		h = 1;
    glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10.0f, 10.0f, -10.0f, 10.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Bezier����");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(ReDraw);
	Initial();
	glutMainLoop();

	return 0;
}
