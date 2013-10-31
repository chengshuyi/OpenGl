////////////////////////////////////////////////////////////////////////////
//ʵ��Ҫ��(1)���OpenGL�еı任����                                     //
//          (2)���͸��ͶӰ��ƽ��ͶӰ�Ĳ�ͬ                               // 
//          (3)��Ӵ���ʵ��̫����������������˶�ģ��                     //
//          (4)�˽���Ȳ���                                               //
//          (5)ͨ���任�����۲��λ���뷽��                               //
//          (6)�������ģ��                                               //
////////////////////////////////////////////////////////////////////////////

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void Initial()
{
	glEnable(GL_DEPTH_TEST);	// ������Ȳ���
	glFrontFace(GL_CCW);		// ָ����ʱ���Ʒ���ʾ���������

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );	//����Ϊ��ɫ
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
	static float fElect1 = 0.0f,fElect2=0.0f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ����ģ����ͼ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//��ͼ����z�Ḻ���ƶ�
	glTranslatef(0.0f, 0.0f, -250.0f);	

	// ���ƺ�ɫ��̫��
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(40, 60, 60);
  glRotatef(fElect1,0.0f,1.0f,0.0f);
  glTranslatef(0.0f,0.0f,0.0f);
	// ��ǰ������ɫ��Ϊ��ɫ
	glColor3f(0.0f, 0.0f, 0.0f);

	//������ɫ�ĵ���
	//���浱ǰ��ģ����ͼ����
	glPushMatrix();
  glColor3f(0.0f,0.0f,1.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);//��y����תһ���ĽǶ�
	glTranslatef(130.0f, 0.0f, 0.0f);//ƽ��һ�ξ���
	glutSolidSphere(10.0f, 60, 60);//��������


	// ���ƻ�ɫ������
  glPushMatrix();
  glColor3f(1.0f,1.0f,0.0f);
	glRotatef(fElect2, 0.0f, 1.0f, 0.0f);
	glTranslatef(20.0f, 0.0f, 0.0f);
	glutSolidSphere(6.0f, 60,60);
	glPopMatrix();

	// ����������
	//glPushMatrix();
	//glRotatef(-45.0f,0.0f, 0.0f, 1.0f);
	//glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	//glTranslatef(0.0f, 0.0f, 60.0f);
	//glutSolidSphere(6.0f, 15, 15);
	//glPopMatrix();

	// ������ת����
	fElect1 += 2.0f;
	if(fElect1 > 360.0f)	fElect1 = 10.0f;
  fElect2+=20.0f;
  if(fElect2>360.0f){
   fElect2=10.0f;
  }
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
  glutInitWindowSize(1200,700);
	glutCreateWindow("�յ���ģ��");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
  glutTimerFunc(500, TimerFunc, 1);

	Initial();
	glutMainLoop();

	return 0;
}
