#include <windows.h>
#include <gl/glut.h>
#include<gl/gl.h>
#include<gl/glu.h>

int twin,qwin;

// ���ڴ�С�ı�ʱ���õĵǼǺ���
void ChangeSize(GLsizei w, GLsizei h)
{
	if(h == 0)		h = 1;
	
	// ���������ߴ�
   	glViewport(0, 0, w, h);
	
	// ��������ϵͳ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45.0f, (GLfloat)w/(GLfloat)h, 3.0f, 5.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -4.0f);
	glRotatef(15.0,1.0,1.0,0.0);
}

// �ڴ����л���ͼ��
void ReDrawt(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLineWidth(8.0f);
	glShadeModel(GL_FLAT);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glColor4f (0.0, 0.6, 1.0, 1.0);
	glutWireOctahedron();
    glFlush();
}

// �ڵڶ��������л���ͼ��
void ReDraww(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//ʹ�û�ϡ�������
	glEnable (GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glLineWidth(8.0f);
	glShadeModel(GL_FLAT);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glColor4f (0.0, 0.6, 1.0, 1.0);
	glutWireOctahedron();
    glFlush();
}

void main(void)
   {
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	twin = glutCreateWindow("ԭʼͼ��");
	glutDisplayFunc(ReDrawt); // ���õ�ǰ���ڵ���ʾ�ص�����
    glutReshapeFunc(ChangeSize); // Ϊ��ǰ�������ô��������λص�����
   	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(500, 500);
	qwin = glutCreateWindow("������");
	glutDisplayFunc(ReDraww); // ���õ�ǰ���ڵ���ʾ�ص�����
    glutReshapeFunc(ChangeSize); // Ϊ��ǰ�������ô��������λص�����

	glutMainLoop(); //������GLUT�¼�����ѭ��
}
