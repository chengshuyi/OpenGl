#include <windows.h>
#include <gl/glut.h>
#include<gl/gl.h>
//#include<gl/glu.h>

// �ڴ����л���ͼ��
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT); //�õ�ǰ����ɫ��䴰��
   	glColor3f(0.0f, 0.0f, 0.0f); //���õ�ǰ�Ļ�ͼ��ͼRGB��ɫ

//���Ʋ�ͬ��С�ĵ�
    GLfloat sizes[2];  //������Ƶ�ĳߴ緶Χ
	GLfloat step;      //������Ƶ�ߴ�Ĳ���
	GLfloat curSize;   //��ǰ���Ƶĵ�Ĵ�С
	glGetFloatv(GL_POINT_SIZE_RANGE,sizes);
	glGetFloatv(GL_POINT_SIZE_GRANULARITY,&step);

	curSize=sizes[0];
	
	for (int i=0;i<25;i++)
	{
		glPointSize(curSize);
        glBegin(GL_POINTS);
			glVertex3f(25.0+i*8,200.0,0.0);
		glEnd();
        curSize +=step*2;
	}

//����һ�����Ϊ5��ֱ��
	glLineWidth(5);
	glBegin(GL_LINES);
		glVertex3f(25.0,160.0,0.0);
		glVertex3f(225.0,160.0,0.0);
	glEnd();

//����һ������
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1,0x00FF);
	glBegin(GL_LINES);
		glVertex3f(25.0,120.0,0.0);
		glVertex3f(225.0,120.0,0.0);
	glEnd();

//����һ�����Ϊ3�ĵ㻮��
	glLineWidth(3);
	glLineStipple(1,0xFF0C);
	glBegin(GL_LINES);
		glVertex3f(25.0,80.0,0.0);
		glVertex3f(225.0,80.0,0.0);
	glEnd();

//�����ظ����ӻ��Ƶĵ㻮��
	glLineStipple(4,0xFF0C);
	glBegin(GL_LINES);
		glVertex3f(25.0,40.0,0.0);
		glVertex3f(225.0,40.0,0.0);
	glEnd();
	glDisable(GL_LINE_STIPPLE);

	glFlush();//ˢ��OpenGL�������
}

// ���ڴ�С�ı�ʱ���õĵǼǺ���
void ChangeSize(GLsizei w, GLsizei h)
{
	if(h == 0)		h = 1;
		
	glViewport(0, 0, w, h); //���������ߴ�

	// ��������ϵͳ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// �����޼��ռ�ķ�Χ
   		if (w <= h) 
			glOrtho (0.0f, 250.0f, 0.0f, 250.0f*h/w, 1.0, -1.0);
    	else 
			glOrtho (0.0f, 250.0f*w/h, 0.0f, 250.0f, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void SetupRC(void)
{
   	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // ���ô��ڵı���ɫ
}

void main(void)
{
	//��ʼ��GLUT��OpenGL���ڵ���ʾģʽ
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutCreateWindow("������"); 
	glutDisplayFunc(RenderScene); // ���õ�ǰ���ڵ���ʾ�ص�����
    glutReshapeFunc(ChangeSize); // Ϊ��ǰ�������ô��������λص�����

	SetupRC();
	glutMainLoop(); //������GLUT�¼�����ѭ��
}

