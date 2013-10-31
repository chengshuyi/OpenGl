#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>

// ��ת����
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

BOOL bColorMaterial = FALSE;//��ɫ����ģʽ

//��ʼ������
void SetupRC(void)
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f );
	glShadeModel(GL_FLAT);
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
	glEnable(GL_DEPTH_TEST);

	//���ù���
	glEnable(GL_LIGHTING);
	GLfloat ambient[]={0.8f, 0.8f, 0.8f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

	//���ò�������
	if(bColorMaterial)
	{
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	}
	else
	{

		glDisable(GL_COLOR_MATERIAL);
		GLfloat material_ambiemt[]={0.75f, 0.75f, 0.75f, 1.0f};
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,material_ambiemt);
	}

	// ��תͼ��
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glFrontFace(GL_CW);

	//��������׶
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
			bColorMaterial = FALSE;
			break;
		case 2:
			bColorMaterial = TRUE;
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
	glutCreateWindow("�ӹ��յ�����׶");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	
	// �����Ҽ��˵�
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("��ͨ����",1);
	glutAddMenuEntry("��ɫ���ٲ���",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	SetupRC();
	glutMainLoop();
	return 0;
}
