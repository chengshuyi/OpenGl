#include <windows.h>
#include <gl/glut.h>
#include<gl/gl.h>
#include<gl/glu.h>

/* ��ʼ�� alpha �ںϵĲ��� */
void Initial(void)
{
	glEnable (GL_BLEND);
	//GL_SRC_ALPHA��ʾ��������ΪԴ��ɫ��Դalpha���
	//GL_ONE_MINUS_SRC_ALPHA��ʾ��������ΪĿ��ɫ�루1��Դalpha��ˣ�
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel (GL_FLAT);
	glClearColor (0.0, 0.0, 0.0, 0.0);
}

// ���ڴ�С�ı�ʱ���õĵǼǺ���
void ChangeSize(GLsizei w, GLsizei h)
{
	if(h == 0)		h = 1;
   	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
   	if (w <= h) 
		gluOrtho2D (0.0f, 1.0f, 0.0f, 1.0f*h/w);
    else 
		gluOrtho2D (0.0f, 1.0f*w/h, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
}

// �ڴ����л���ͼ��
void ReDraw(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor4f (1.0, 0.0, 0.0, 0.7);
	glRectf (0.25, 0.4, 0.75, 0.9);
	glColor4f (0.0, 1.0, 0.0, 0.5);
	glRectf (0.1, 0.1, 0.6, 0.6);
	glColor4f (0.0, 0.0, 1.0, 0.3);
	glRectf (0.4, 0.1, 0.9, 0.6);
	
	// ˢ��OpenGL�������
    glFlush();
}

void main(void)
   {
	//��ʼ��GLUT��OpenGL���ڵ���ʾģʽ
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 

	glutCreateWindow("��ɫ"); 
	glutDisplayFunc(ReDraw); // ���õ�ǰ���ڵ���ʾ�ص�����
    glutReshapeFunc(ChangeSize); // Ϊ��ǰ�������ô��������λص�����
   	
	// ���ڳ�ʼ��
    Initial();
	glutMainLoop(); //������GLUT�¼�����ѭ��
}
