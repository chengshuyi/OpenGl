#include <windows.h>
#include <gl/glut.h>
#include<gl/gl.h>
#include<gl/glu.h>

/* �������� */
#define ImageWidth 64
#define ImageHeight 64
GLubyte Image[ImageWidth][ImageHeight][3];

void makeImage(void)
{
	int i, j, r,g,b;
	for (i = 0; i < ImageWidth; i++)
	{
		for (j = 0; j < ImageHeight; j++)
		{
			r=(i*j)%255;
			g=(4*i)%255;
			b=(4*j)%255;
			Image[i][j][0] = (GLubyte) r;
			Image[i][j][1] = (GLubyte) g;
			Image[i][j][2] = (GLubyte) b;
		}
	}
}

//��ʼ������
void Initial(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	makeImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	/* �������� */
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth,
	ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, &Image[0][0][0]);
	
	/* �����˲� */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	/* ˵��ӳ�䷽ʽ*/
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	
	/* ��������ӳ�� */
	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_FLAT);
}

// ���ڴ�С�ı�ʱ���õĵǼǺ���
void ChangeSize(GLsizei w, GLsizei h)
{
	if(h == 0)		h = 1;
   	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0*(GLfloat)w/(GLfloat)h, 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -3.6);
}

// �ڴ����л���ͼ��
void ReDraw(void)
{
	//�õ�ǰ����ɫ��䴰��
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* ����������������弸������ */
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
		glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, 1.0, 0.0);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -1.0, 0.0);

		glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
		glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
		glTexCoord2f(1.0, 1.0); glVertex3f(2.41421, 1.0, -1.41421);
		glTexCoord2f(1.0, 0.0); glVertex3f(2.41421, -1.0, -1.41421);
	glEnd();

// ˢ��OpenGL�������
	glFlush();
}

void main(void)
   {
	//��ʼ��GLUT��OpenGL���ڵ���ʾģʽ
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 

	glutCreateWindow("������ӳ��"); 
	glutDisplayFunc(ReDraw); // ���õ�ǰ���ڵ���ʾ�ص�����
    glutReshapeFunc(ChangeSize); // Ϊ��ǰ�������ô��������λص�����
   	
	// ���ڳ�ʼ��
    Initial();
	glutMainLoop(); //������GLUT�¼�����ѭ��
}
