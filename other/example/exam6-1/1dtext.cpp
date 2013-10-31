#include <GL/glut.h>
#include <math.h>
#ifndef M_PI
#  define M_PI 3.141592649
#endif /* !M_PI */

void Resize(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, (float)width / (float)height, 0.1, 1000.0);

    glMatrixMode(GL_MODELVIEW);
}

void Redraw(void)
{
    GLfloat x, y, z, th;
    static GLubyte roygbiv_image[8][3] =
        {
        { 0x3f, 0x00, 0x3f }, /* ������ɫ */
        { 0x7f, 0x00, 0x7f }, /* ����ɫ */
        { 0xbf, 0x00, 0xbf }, /* ���� */
        { 0x00, 0x00, 0xff }, /* ��ɫ */
        { 0x00, 0xff, 0x00 }, /* ��ɫ */
        { 0xff, 0xff, 0x00 }, /* ��ɫ */
        { 0xff, 0x7f, 0x00 }, /* ��ɫ */
        { 0xff, 0x00, 0x00 }  /* ��ɫ */
        };

    glClearColor(0.5, 0.5, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //��������Ŵ����С������ΪGL_LINEAR
	//��ʾʹ�����ʹ���������ص��ĸ����صļ�Ȩ��ֵ
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//����һά������ɫ����ΪRGB��
	//���Ϊ8���߽�Ϊ0��ʹ���޷�������
    glTexImage1D(GL_TEXTURE_1D, 0, 3, 8, 0, GL_RGB, GL_UNSIGNED_BYTE, roygbiv_image);
	//������������������ʹ������ͼ��
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    /* ���Ƶ���*/
    glDisable(GL_TEXTURE_1D);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glPushMatrix();
    glRotatef(10.0, 0.0, 1.0, 0.0);
    glTranslatef(0.0, -40.0, -100.0);

    glColor3f(0.0, 0.8, 0.0);
    glBegin(GL_POLYGON);
    for (th = 0.0; th < (2.0 * M_PI); th += (0.03125 * M_PI))
    {
        x = cos(th) * 200.0;
		z = sin(th) * 200.0;
		glVertex3f(x, 0.0, z);
    }
    glEnd();

    /* ���Ʋʺ� */
    glEnable(GL_TEXTURE_1D);
    glBegin(GL_QUAD_STRIP);
    for (th = 0.0; th <= M_PI; th += (0.03125 * M_PI))
    {
        x = cos(th) * 50.0;
		y = sin(th) * 50.0;
		z = -50.0;
		glTexCoord1f(0.0);
		glVertex3f(x, y, z);

        x = cos(th) * 55.0;
		y = sin(th) * 55.0;
		z = -50.0;
		glTexCoord1f(1.0);
		glVertex3f(x, y, z);
    }
    glEnd();

    glPopMatrix();
    glFlush();
}

int main(int  argc, char *argv[]) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(792, 573);
    glutCreateWindow("�ʺ�");
    glutReshapeFunc(Resize);
    glutDisplayFunc(Redraw);
    glutMainLoop();
    return (0);
}






