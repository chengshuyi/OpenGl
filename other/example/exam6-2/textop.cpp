#include <windows.h>
#include <gl/glut.h>
#include<gl/gl.h>
#include<gl/glu.h>

#define stripeImageWidth 64
GLubyte stripeImage[3*stripeImageWidth];
//��������ͼ��
void makeStripeImage(void)
{
	int j;
	for (j = 0; j < stripeImageWidth; j++)
	{
		stripeImage[3*j] = 255;
		stripeImage[3*j+1] =255-2*j;
		stripeImage[3*j+2] =255;
	}
}
/* �������� */
GLfloat sgenparams[] = {1.0, 1.0, 1.0, 0.0};

//��ʼ������
void Initial(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);

	makeStripeImage();
	//�����趨���ڴ��ж�ȡ����ͼ���ŵ���Ļ�ϵķ�ʽ
	//ָ���ڴ���ÿ����������ʼ������Ҫ��Ϊ�ֽ����У�1��
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//����������������������ǰ���Ⱥ���ɫ��Ϣ��ʹ֮��Ӧ����ͼ��
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//������תʹ���ظ���ʽ
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//��������Ŵ����С������ΪGL_LINEAR
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//��������
	glTexImage1D(GL_TEXTURE_1D, 0, 3, stripeImageWidth, 0, GL_RGB, GL_UNSIGNED_BYTE, stripeImage);

	//�����������������
	//ָ����ֵ�������ɲ���
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	//ָ�������������ɺ���,ϵ����sgenparamsָ��
	glTexGenfv(GL_S, GL_OBJECT_PLANE, sgenparams);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_1D);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glMaterialf (GL_FRONT, GL_SHININESS, 64.0);
}

// ���ڴ�С�ı�ʱ���õĵǼǺ���
void ChangeSize(GLsizei w, GLsizei h)
{
	if(h == 0)		h = 1;
	
	// ���������ߴ�
   	glViewport(0, 0, w, h);
	
	// ��������ϵͳ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// �����޼��ռ�ķ�Χ
   	if (w <= h) 
		glOrtho (-3.5f, 3.5f, -3.5f, 3.5f*h/w, -3.5, 3.5);
    else 
		glOrtho (-3.5f, 3.5f*w/h, -3.5f, 3.5f, -3.5, 3.5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// �ڴ����л���ͼ��
void ReDraw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix ();
	glRotatef(25.0, 1.0, 0.0, 0.0);
	glutSolidTeapot(1.5);
	glPopMatrix ();
	glFlush();
}

void main(void)
   {
	//��ʼ��GLUT��OpenGL���ڵ���ʾģʽ
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 

	glutCreateWindow("������"); 
	glutDisplayFunc(ReDraw); // ���õ�ǰ���ڵ���ʾ�ص�����
    glutReshapeFunc(ChangeSize); // Ϊ��ǰ�������ô��������λص�����
   	
	// ���ڳ�ʼ��
    Initial();
	glutMainLoop(); //������GLUT�¼�����ѭ��
}
