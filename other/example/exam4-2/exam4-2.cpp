#include <GL/glut.h>

GLenum  DepthFunc = GL_LESS;  /* ��ȶԱȺ��� */
GLfloat	CuttingPlane = -22.0, /* �ü�ƽ��ľ��� */
	    CuttingDir   = 0.25;   /* �ü�ƽ������� */

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
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(22.5, (float)width / (float)height, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}							   

void Redraw(void)
{
    glShadeModel(GL_SMOOTH);

	//��Ȳ�������
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(DepthFunc); 
    if (DepthFunc == GL_LESS)
        glClearDepth(1.0);
    else
        glClearDepth(0.0);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

/*���òü�ƽ��*/
    
	//ָ�����Ƶ���ɫ���棬GL_NONE��ʾ����ɫ���汻д��
	glDrawBuffer(GL_NONE);

    glColor3i(0, 0, 0);
    glBegin(GL_POLYGON);
		glVertex3f(-100.0, 100.0, CuttingPlane);
		glVertex3f(100.0, 100.0, CuttingPlane);
		glVertex3f(100.0, -100.0, CuttingPlane);
		glVertex3f(-100.0, -100.0, CuttingPlane);
    glEnd();

	//ָ�����Ƶ���ɫ���棬
	//GL_BACK��ʾֻ�к���ͺ�����ɫ���汻д��
	//�����崰��ֻ����ǰ���棬˫���崰�ڰ���ǰ����ͺ󻺴�
    glDrawBuffer(GL_BACK);

/*��������*/
    glPushMatrix();
    glTranslatef(-1.0, 0.0, -20.0);
    glutSolidSphere(1.0, 18, 9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.0, 0.0, -20.0);
    glRotatef(15.0, 0.0, 1.0, 0.0);
    glRotatef(15.0, 0.0, 0.0, 1.0);
    glutSolidCube(2.0);
    glPopMatrix();

    glutSwapBuffers();
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
        Redraw();
    }
}

void Timer(int val)
{
    CuttingPlane += CuttingDir;

    if (CuttingPlane <= -22.0 || CuttingPlane >= -18.0)
        CuttingDir = -CuttingDir;

    Redraw();
    glutTimerFunc(250, Timer, 0);
}

int main(int  argc, char *argv[]) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(792, 573);
    glutCreateWindow("�ڵ�");
    glutReshapeFunc(Resize);
    glutDisplayFunc(Redraw);
    glutTimerFunc(25, Timer, 0);
    glutKeyboardFunc(Keyboard);
	Initial();
    glutMainLoop();
    return (0);
}
