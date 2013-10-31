//GLRect.c
#include <windows.h>
#include <gl/glut.h>
#include<gl/gl.h>
#include<gl/glu.h>

// ����RenderScene�����ڴ����л�����Ҫ��ͼ��
void RenderScene(void)
{
	//�õ�ǰ���ɫ�����ɫ�����������趨���ڵı���ɫ
	glClear(GL_COLOR_BUFFER_BIT); 
	
		//���õ�ǰ��ͼʹ�õ�RGB��ɫ
   		glColor3f(1.0f, 0.0f, 0.0f); 

		//ʹ�õ�ǰ��ɫ����һ�����ľ���
	glRectf(100.0f, 150.0f, 150.0f, 100.0f); 
		
		//ˢ��OpenGL�������
		glFlush();
	}

// ����ChangeSize�Ǵ��ڴ�С�ı�ʱ���õĵǼǺ���
void ChangeSize(GLsizei w, GLsizei h)
	{
	if(h == 0)		h = 1;
		
		//���������ߴ�
	glViewport(0, 0, w, h); 

	// ��������ϵͳ��ʹͶӰ�任��λ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// �����޼��ռ�ķ�Χ
   		if (w <= h) 
			glOrtho (0.0f, 250.0f, 0.0f, 250.0f*h/w, 1.0f, -1.0f);
    	else 
			glOrtho (0.0f, 250.0f*w/h, 0.0f, 250.0f, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
}

//����SetupRC���ڳ�ʼ�������������ó�����Ⱦ״̬
void SetupRC(void)
{
	// ���ô��ڵ����ɫΪ��ɫ
   	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
}

void main(void)
   {
		//��ʼ��GLUT��OpenGL���ڵ���ʾģʽ
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 

// ����һ����ΪGLRect�Ĵ���
	glutCreateWindow("GLRect"); 

	// ���õ�ǰ���ڵ���ʾ�ص������ʹ��������λص�����
		glutDisplayFunc(RenderScene); 
    glutReshapeFunc(ChangeSize); 

   	 	SetupRC();

		//������GLUT�¼�����ѭ��
	glutMainLoop();
}
