#include <windows.h>
#include <gl/glut.h>
#include<gl/gl.h>
#include<gl/glu.h>

void quads(void)
{
	glBegin (GL_QUADS);
		glColor3f (1.0, 1.0, 0.0);
		glVertex2f (10.0, 10.0);
		glColor3f(0.0,0.3,1.0);
		glVertex2f (30.0, 10.0);
		glColor3f(1.0,0.0,0.0);
		glVertex2f (30.0, 30.0);
		glColor3f(0.0,1.0,0.0);
		glVertex2f (10.0, 30.0);
	glEnd ();
}

//��ʼ������
void Initial(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// ���ڴ�С�ı�ʱ���õĵǼǺ���
void ChangeSize(GLsizei w, GLsizei h)
{
	if(h == 0)		h = 1;
	
   	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
   	if (w <= h) 
		gluOrtho2D (0.0f, 150.0f, 0.0f, 150.0f*h/w);
    else 
		gluOrtho2D (0.0f, 150.0f*w/h, 0.0f, 150.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// �ڴ����л���ͼ��
void ReDraw(void)
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	/* ����ԭʼͼ�� */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
    glTranslatef(10.0f, 100.0f,0.0f);
	quads();
	glPopMatrix();

	/* ����ͼ�� */
	glPushMatrix();
	for(i=0;i<5;i++)
	{
		glRasterPos2i( 20+i*30,10+i*20);
//		glPixelZoom(2.0,2.0);
		glCopyPixels(50,300,50,50,GL_COLOR);
	}
	glPopMatrix();
	// ˢ��OpenGL�������
    glFlush();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	//��ʼ��GLUT��OpenGL���ڵ���ʾģʽ
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); 
	glutInitWindowSize(500,400);
	glutInitWindowPosition(200,200);
	glutCreateWindow("���ش���");
	glutDisplayFunc(ReDraw); // ���õ�ǰ���ڵ���ʾ�ص�����
    glutReshapeFunc(ChangeSize); // Ϊ��ǰ�������ô��������λص�����
   	
	// ���ڳ�ʼ��
    Initial();
	glutMainLoop(); //������GLUT�¼�����ѭ��
	return 0;
}
