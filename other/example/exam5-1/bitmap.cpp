#include <windows.h>
#include <gl/glut.h>
#include<gl/gl.h>
#include<gl/glu.h>

int        Width;  /* ���ڿ�� */
int        Height; /* ���ڸ߶� */
static GLubyte smiley[] = /* 16x16 Ц�� */
{
    0x03, 0xc0, 0, 0, /*                 ****                 */
    0x0f, 0xf0, 0, 0, /*               ********               */
    0x1e, 0x78, 0, 0, /*              ****  ****              */
    0x39, 0x9c, 0, 0, /*             ***  **  ***             */
    0x77, 0xee, 0, 0, /*            *** ****** ***            */
    0x6f, 0xf6, 0, 0, /*            ** ******** **            */
    0xff, 0xff, 0, 0, /*           ****************           */
    0xff, 0xff, 0, 0, /*           ****************           */
    0xff, 0xff, 0, 0, /*           ****************           */
    0xff, 0xff, 0, 0, /*           ****************           */
    0x73, 0xce, 0, 0, /*            ***  ****  ***            */
    0x73, 0xce, 0, 0, /*            ***  ****  ***            */
    0x3f, 0xfc, 0, 0, /*             ************             */
    0x1f, 0xf8, 0, 0, /*              **********              */
    0x0f, 0xf0, 0, 0, /*               ********               */
    0x03, 0xc0, 0, 0  /*                 ****                 */
};

//��ʼ������
void Initial(void)
{
     glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// ���ڴ�С�ı�ʱ���õĵǼǺ���
void ChangeSize(GLsizei w, GLsizei h)
{
	if(h == 0)		h = 1;
	
   	glViewport(0, 0, w, h);
	
	Width = w;
	Height = h;
	// ��������ϵͳ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho (0, w, 0, h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

// �ڴ����л���ͼ��
void ReDraw(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f (1.0, 0.0, 1.0);
	glRasterPos2i (100, 200);
	glBitmap (16, 16, 0.0, 0.0, 30.0, 30.0, smiley);
	glBitmap (16, 16, 0.0, 0.0, 0.0, 0.0, smiley);

	glColor3f (1.0, 1.0, 0.0);
	glRasterPos2i (150, 200);
	glBitmap (16, 16, 0.0, 0.0, 0.0, 0.0, smiley);

	glColor3f (0.0, 0.0, 1.0);
	int i;
	for(i=0;i<20;i++)
	{
		glRasterPos2i (rand()% Width, rand()%Height);
		glBitmap (16, 16, 0.0, 0.0, 0.0, 0.0, smiley);
	}
	// ˢ��OpenGL�������
    glFlush();
}

void main(void)
{
	//��ʼ��GLUT��OpenGL���ڵ���ʾģʽ
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutCreateWindow("λͼ"); 
	glutDisplayFunc(ReDraw); // ���õ�ǰ���ڵ���ʾ�ص�����
    glutReshapeFunc(ChangeSize); // Ϊ��ǰ�������ô��������λص�����
	// ���ڳ�ʼ��
    Initial();
	glutMainLoop(); //������GLUT�¼�����ѭ��
}
