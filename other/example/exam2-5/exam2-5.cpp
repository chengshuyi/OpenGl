#include <windows.h>
#include <gl/gl.h>
//#include <gl/glu.h>
#include <gl/glut.h>
//#include <math.h>

// ��ת����
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

BOOL bWinding = TRUE;//ȷ��������Ʒ��ķ���

//��ʼ������
void SetupRC(void)
{
    // ���ô��ڱ�����ɫΪ��ɫ
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
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

// �ڴ����л���ͼ��
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// ��תͼ��
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glPointSize(5);
	glLineWidth(5);
	
	//���ö�����Ʒ��ķ�����˳ʱ�뻹����ʱ��
	if (bWinding) 
		glFrontFace(GL_CW);
	else
		glFrontFace(GL_CCW);

	glBegin(GL_TRIANGLES);//����������
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0, 60, 0);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-60, -60, 0);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(60, -60, 0);
	glEnd();

	glPopMatrix();

	// ˢ���������
	glutSwapBuffers();
}


void SpecialKeys(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)		xRot-= 5.0f;
	if(key == GLUT_KEY_DOWN)	xRot += 5.0f;
	if(key == GLUT_KEY_LEFT)	yRot -= 5.0f;
	if(key == GLUT_KEY_RIGHT)	yRot += 5.0f;

	if(xRot > 356.0f)	xRot = 0.0f;
	if(xRot < -1.0f)	xRot = 355.0f;
	if(yRot > 356.0f)	yRot = 0.0f;
	if(yRot < -1.0f)	yRot = 355.0f;

	// ˢ�´���
	glutPostRedisplay();
}

void ProcessMenu(int value)
{

	switch(value)
	{
		case 1:
			glPolygonMode(GL_FRONT,GL_FILL);;
			break;
		case 2:
			glPolygonMode(GL_FRONT,GL_LINE);
			break;
		case 3:
			glPolygonMode(GL_FRONT,GL_POINT);
			break;
		case 4:
			glPolygonMode(GL_FRONT,GL_FILL);
			break;
		case 5:
			glPolygonMode(GL_FRONT,GL_LINE);
			break;
		case 6:
			glPolygonMode(GL_FRONT,GL_POINT);
			break;
		case 7:
			glShadeModel(GL_FLAT);
			break;
		case 8:
			glShadeModel(GL_SMOOTH);
			break;
		case 9:
			bWinding = !bWinding;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	int nModeMenu;
	int nMainMenu;
	int nColorMenu;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	glutCreateWindow("�������ʾ");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	
	// �����˵�
	nModeMenu = glutCreateMenu(ProcessMenu);//�����˵�������˵��ص�����
	//��Ӳ˵��1��ʾѡ��˵���Ŀʱ���ݵĲ���ֵ
	glutAddMenuEntry("�����������ģʽ",1);
	glutAddMenuEntry("�����߿�ģ��",2);
	glutAddMenuEntry("�����ģʽ",3);
	glutAddMenuEntry("�����������ģʽ",4);
	glutAddMenuEntry("�����߿�ģ��",5);
	glutAddMenuEntry("�����ģʽ",6);

	nColorMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("ƽ������ģʽ",7);
	glutAddMenuEntry("�⻬����ģʽ",8);

	nMainMenu = glutCreateMenu(ProcessMenu);
	glutAddSubMenu("�����ģʽ", nModeMenu);
	glutAddSubMenu("��ɫģʽ", nColorMenu);
	glutAddMenuEntry("�ı��Ʒ�",9);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	SetupRC();
	glutMainLoop();

	return 0;
}
