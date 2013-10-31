#include <windows.h>
#include <gl/glut.h>

// �������λ�úʹ�С
GLfloat x1 = 100.0f;
GLfloat y1 = 150.0f;
GLsizei rsize = 50;

// �仯�Ĳ���
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

// ���ڴ�С
GLfloat windowWidth;
GLfloat windowHeight;

//��ʼ������
void Initial(void)
{
    // ���ô�����ɫΪ��ɫ
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

// ���ڴ�С�ı�ʱ���õĵǼǺ���
void ChangeSize(GLsizei w, GLsizei h)
{
	if(h == 0)		h = 1;
	
	glViewport(0, 0, w, h);// ���������ߴ�
	
	// ��������ϵͳ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// �����޼��ռ�ķ�Χ
	if (w <= h) 
	{
		windowHeight = 250.0f*h/w;
		windowWidth = 250.0f;
	}
    else 
	{
		windowWidth = 250.0f*w/h;
		windowHeight = 250.0f;
	}

	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// �ڴ����л���ͼ��
void ReDraw(void)
{
	//�õ�ǰ����ɫ��䴰��
	glClear(GL_COLOR_BUFFER_BIT);
	
	// ���õ�ǰ�Ļ�ͼ��ͼRGB��ɫ
	glColor3f(1.0f, 0.0f, 0.0f);
	
	// ʹ�õ�ǰ��ɫ����һ�����ľ���
	glRectf(x1, y1, x1+rsize, y1+rsize);
	
	// ˢ��OpenGL�������
    glutSwapBuffers();
}

// ����ʱ��ص�����
void TimerFunction(int value)
{
	if(x1 > windowWidth-rsize || x1 < 0)	xstep = -xstep;
	if(y1 > windowHeight-rsize || y1 < 0)	ystep = -ystep;

	if(x1 > windowWidth-rsize)		x1 = windowWidth-rsize-1;
	if(y1 > windowHeight-rsize)		y1 = windowHeight-rsize-1;

	x1 += xstep;
	y1 += ystep;

	// ���������ػ�ͼ��
    glutPostRedisplay();
	glutTimerFunc(33,TimerFunction, 1);
}

// Main program entry point
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400,400);
	glutInitWindowPosition(100,100);
	glutCreateWindow("�ƶ��ľ���");
	glutDisplayFunc(ReDraw);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(33, TimerFunction, 1);

	Initial();
	glutMainLoop();

	return 0;
}