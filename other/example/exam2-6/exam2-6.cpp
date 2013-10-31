#include <windows.h>
#include <gl/gl.h>
//#include <gl/glu.h>
#include <gl/glut.h>
//#include <math.h>

// ��ת����
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

BOOL bDepth = FALSE;//��Ȳ��Կ���
BOOL bCull = FALSE;//�޳�����

//��ʼ������
void SetupRC(void)
{
    // ���ô��ڱ�����ɫΪ��ɫ
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
	glShadeModel(GL_FLAT);//ָ������ε���ӰģʽΪƽ������ģʽ
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
	//�����ɫ����Ȼ�����
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

	//�Ƿ�����Ȳ���
	if(bDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	//�Ƿ���޳�
	if(bCull)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	// ��תͼ��
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glFrontFace(GL_CW);//ָ��˳ʱ���Ʒ��Ķ����Ϊ���������

	//��������׶���������棬���ǵ���ɫ�ֱ�Ϊ�졢�̡���
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0, 0.0, 80.0);
		glVertex3f(0.0, 50.0, 0.0);
		glColor3f(1.0,0.0,0.0);
		glVertex3f(50.0, -50.0, 0.0);
		glColor3f(0.0,1.0,0.0);
		glVertex3f(-50.0, -50.0, 0.0);
		glColor3f(0.0,0.0,1.0);
		glVertex3f(0.0, 50.0, 0.0);
	glEnd();

	//��������׶�ĵ��棬����ɫΪ��ɫ
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0, 50.0, 0.0);
		glVertex3f(50.0, -50.0, 0.0);
		glColor3f(1.0,1.0,0.0);
		glVertex3f(-50.0, -50.0, 0.0);		
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
			bDepth = !bDepth;
			break;
		case 2:
			bCull = !bCull;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	glutCreateWindow("����׶");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	
	// �����Ҽ��˵�
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("��Ȳ���",1);
	glutAddMenuEntry("�޳�����",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	SetupRC();
	glutMainLoop();

	return 0;
}
