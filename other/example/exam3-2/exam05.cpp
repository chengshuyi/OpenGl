#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

void SetupRC()
{
	glEnable(GL_DEPTH_TEST);	// ������Ȳ���
	glFrontFace(GL_CCW);		// ָ����ʱ���Ʒ���ʾ���������

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f );	//����Ϊ��ɫ
}

void ChangeSize(int w, int h)
{
	if(h == 0)	h = 1;

	// ���������ߴ�
    glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// �����޼��ռ�
	GLfloat fAspect;
	fAspect = (float)w/(float)h;
	gluPerspective(45.0, fAspect, 1.0, 500.0);
/*
	    if (w <= h) 
			glOrtho (-nRange, nRange, nRange*h/w, -nRange*h/w, -nRange*2.0f, nRange*2.0f);
		else 
			glOrtho (-nRange*w/h, nRange*w/h, nRange, -nRange, -nRange*2.0f, nRange*2.0f);
*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void RenderScene(void)
{
	// ��ԭ�Ӻ���ת�ĽǶ�
	static float fElect1 = 0.0f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ����ģ����ͼ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//��ͼ����z�Ḻ���ƶ�
	glTranslatef(0.0f, 0.0f, -250.0f);	

	// ���ƺ�ɫ��ԭ�Ӻ�
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(10.0f, 15, 15);

	// ��ǰ������ɫ��Ϊ��ɫ
	glColor3f(0.0f, 0.0f, 0.0f);

	//���Ƶ�һ������
	//���浱ǰ��ģ����ͼ����
	glPushMatrix();
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);//��y����תһ���ĽǶ�
	glTranslatef(90.0f, 0.0f, 0.0f);//ƽ��һ�ξ���
	glutSolidSphere(6.0f, 15, 15);//��������

	// �ָ�����
	glPopMatrix();

	// �ڶ�������
	glPushMatrix();
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(-70.0f, 0.0f, 0.0f);
	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();

	// ����������
	glPushMatrix();
	glRotatef(-45.0f,0.0f, 0.0f, 1.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 60.0f);
	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();

	// ������ת����
	fElect1 += 10.0f;
	if(fElect1 > 360.0f)	fElect1 = 10.0f;

	glutSwapBuffers();
}

void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(100, TimerFunc, 1);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("ԭ�Ӻ�ʾ��");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
    glutTimerFunc(500, TimerFunc, 1);

	SetupRC();
	glutMainLoop();

	return 0;
}
