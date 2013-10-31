#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>

//��ʼ������
void SetupRC(void)
{
    // ���ô��ڱ�����ɫΪ��ɫ
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
}

//����������
void DrawTriangle(void)
{
	glBegin(GL_TRIANGLES);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(40.0f, 0.0f);
		glVertex2f(20.0f, 40.0f);
	glEnd();
}

void ChangeSize(int w, int h)
{
	if(h == 0)	h = 1;

    glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    if (w <= h) 
		glOrtho (-100.0f, 100.0f, -100.0f*h/w, 100.0f*h/w, -100.0f, 100.0f);
    else 
		glOrtho (-100.0f*w/h, 100.0f*w/h, -100.0f, 100.0f, -100.0f, 100.0f);

	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT );
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//���ƺ�ɫ��������
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex2f(-100.0f, 0.0f);
		glVertex2f(100.0f, 0.0f);
		glVertex2f(0.0f, -100.0f);
		glVertex2f(0.0f, 100.0f);
	glEnd();

	//������ʼ�ĺ�ɫ������
	glColor3f(1.0f, 0.0f, 0.0f);
	DrawTriangle();

	//������ʱ����ת200�Ƚǵ���ɫ������
	glRotatef(200.0f,0.0f,0.0f,1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	DrawTriangle();

	//������x�Ḻ��ƽ��40�Ļ�ɫ������
	glLoadIdentity();
	glTranslatef(-60.0f,0.0f,0.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	DrawTriangle();

	//������������Ϊ1.0,2.0,1.0����ɫ������
	glTranslatef(100.0f,10.0f,0.0f);
	glScalef(1.0f,2.0f,1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	DrawTriangle();

	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	glutCreateWindow("�任ʵ��");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	
	SetupRC();
	glutMainLoop();

	return 0;
}
