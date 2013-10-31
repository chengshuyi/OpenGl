#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>
#define GL_PI 3.1415f

// ������ת����
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
// ָ���Ĳ���
BOOL bDepth = FALSE;

// ��ʼ��
void Initial()
{
	// ����ɫΪ��ɫ
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
	// ���õ�ǰ��ɫΪ��ɫ
	glColor3f(0.0f, 1.0f, 0.0f);
	// ��ɫ��ӰģʽΪƽ��ģʽ
	glShadeModel(GL_FLAT);
}

void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;
	if(h == 0)		h = 1;
	// ���������ߴ�
    glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// �����޼��ռ�
    if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ReDraw(void)
{
	GLfloat x,y,angle;   
	int iPivot = 1;	// ������ɫ�任��־

	// ��������Լ���Ȼ�����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(bDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
		
	// ���浱ǰ���󲢽�����ת
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	
	// ����׶�����������
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, 0.0f, 75.0f);
	for(angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f))
	{
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
		// ����ɫ�ں�ɫ����ɫ֮���л�
		if((iPivot %2) == 0)
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 0.0f, 0.0f);
		iPivot++;
		// ָ����һ����
		glVertex2f(x, y);
	}
	glEnd();
	
	// ����׶�׵�����
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0f, 0.0f);
	for(angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f))
	{
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
		if((iPivot %2) == 0)
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 0.0f, 0.0f);
		iPivot++;
		glVertex2f(x, y);
	}
	glEnd();
	// �ָ�����
	glPopMatrix();
	// ִ�л�������������ˢ����ˮ��
	glutSwapBuffers();
}

//��Ӧ��������ֱ���x���y����ʱ���˳ʱ����ת
void SpecialKeys(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)		xRot-= 5.0f;
	if(key == GLUT_KEY_DOWN)		xRot += 5.0f;
	if(key == GLUT_KEY_LEFT)		yRot -= 5.0f;
	if(key == GLUT_KEY_RIGHT)		yRot += 5.0f;
	if(xRot > 356.0f)	xRot = 0.0f;
	if(xRot < -1.0f)	xRot = 355.0f;
	if(yRot > 356.0f)	yRot = 0.0f;
	if(yRot < -1.0f)	yRot = 355.0f;

	glutPostRedisplay();
}

// �����Ҽ��˵�
void ProcessMenu(int value)
{
	switch(value)
		{
		case 1:
			bDepth = !bDepth;
			break;
		default:
			break;
		}
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Triangle Culling Example");
	//�����Ҽ��˵�
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("������Ȳ���",1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(ReDraw);
	Initial();
	glutMainLoop();
	return 0;
}
