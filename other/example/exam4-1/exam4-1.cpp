#include <GL/glut.h>

GLenum DepthFunc = GL_LESS; /* ��ȶԱȺ��� */

//��ʼ������
void Initial(void)
{
    static float red_light[4]  = {  1.0,  0.0,  0.0,  1.0 };
    static float red_pos[4]    = {  1.0,  1.0,  1.0,  0.0 };
    static float blue_light[4] = {  0.0,  0.0,  1.0,  1.0 };
    static float blue_pos[4]   = { -1.0, -1.0, -1.0,  0.0 };
   
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, red_light);
    glLightfv(GL_LIGHT0, GL_POSITION, red_pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, blue_light);
    glLightfv(GL_LIGHT1, GL_POSITION, blue_pos);
}

void Resize(int width, int height) 
{
    /* ��������*/
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(22.5, (float)width / (float)height, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)   
{
    if (key == 'd' || key == 'D')
    {
		/* �л���ȶԱȺ��� */
        if (DepthFunc == GL_LESS)
            DepthFunc = GL_GREATER;
        else
            DepthFunc = GL_LESS;
        glutPostRedisplay();
    }
}

void Redraw(void)
{
    glShadeModel(GL_SMOOTH);
	
	//������Ȳ��Բ�������Ȳ��Ժ���
	glEnable(GL_DEPTH_TEST);
    glDepthFunc(DepthFunc); 
    //��ͬ����ȶԱȺ���ʹ�ò�ͬ�ĳ�ʼֵ
    if (DepthFunc == GL_LESS)
        glClearDepth(1.0);
    else
        glClearDepth(0.0);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(-1.0, 0.0, -20.0);
    glutSolidSphere(1.0, 36, 18);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.0, 0.0, -20.0);
    glRotatef(15.0, 0.0, 1.0, 0.0);
    glRotatef(15.0, 0.0, 0.0, 1.0);
    glutSolidCube(2.0);
    glPopMatrix();

	glFlush();
}

int main(int  argc, char *argv[]) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    //���鴰�ڵĳ�ʼ�ߴ�
	glutInitWindowSize(792, 573);
    glutCreateWindow("��Ȳ���");
    glutReshapeFunc(Resize);
    glutDisplayFunc(Redraw);
    glutKeyboardFunc(Keyboard);//������Ӧ�ص�����
	Initial();
    glutMainLoop();
    return (0);
}
