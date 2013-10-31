#include <windows.h>
#include <gl/glut.h>
#include<gl/gl.h>
#include<gl/glu.h>

GLfloat mat_ambient[]= { 0.1745f, 0.01175f, 0.01175f};
GLfloat mat_diffuse[]= { 0.61424f, 0.04136f, 0.04136f};
GLfloat mat_specular[] = { 0.727811f, 0.626959f, 0.626959f};
GLfloat light_ambient[]= { 0.1f, 0.1f, 0.1f, 0.0f };
GLfloat light_diffuse[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat light_position[] = { -10.0f, 0.0f, 5.0f, 0.0f };

GLfloat fogColorWhite[]={1.0f, 1.0f, 1.0f, 1.0f };
GLfloat fogColorGreen[]={0.0f, 1.0f, 0.0f, 1.0f };
float fogDensity = 0.02f;

//��ʼ������
void Initial(void)
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR,light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION,light_position);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.6*128);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glFrontFace(GL_CW);

	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, fogColorWhite);
	glFogf(GL_FOG_DENSITY, fogDensity);
	glFogf(GL_FOG_START, 0.0);
	glFogf(GL_FOG_END, 15.0);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
}

// ���ڴ�С�ı�ʱ���õĵǼǺ���
void ChangeSize(GLsizei w, GLsizei h)
{
	if(h == 0)		h = 1;
   	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100.0f, 1.0f, 1.0f, 20.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -15.5f);
}


// �ڴ����л���ͼ��
void ReDraw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(-4.0f, 4.0f, 0.0f);
	glRotatef(30.0f, 1.0f, 1.0f, 0.0f);
	glutSolidCone(1.0f, 50.0f, 20.0f, 20.0f);
	glPopMatrix();
	glutSwapBuffers();
}

static void Key(unsigned char key, int x, int y)
{
	switch(key){
		case '1':
				fogDensity *= 1.10;
				glFogi(GL_FOG_MODE, GL_EXP);
				glFogf(GL_FOG_DENSITY, fogDensity);//������Ũ��
				glutPostRedisplay();
		break;
		case '2':
				fogDensity /= 1.10;
				glFogi(GL_FOG_MODE, GL_EXP);
				glFogf(GL_FOG_DENSITY, fogDensity);//������Ũ��
				glutPostRedisplay();
		break;
		case '3':
				glFogi(GL_FOG_START, 0.0);
				glFogi(GL_FOG_END, 8.0);//�޸�������ʼ����ֹ��
				glutPostRedisplay();
		break;
		case '4':
				glFogi(GL_FOG_MODE, GL_EXP2);//�ı�������
				glutPostRedisplay();
		break;
		case '5':
				glFogi(GL_FOG_MODE, GL_LINEAR);//�ı�������
				glutPostRedisplay();
		break;
		case '6':
				glFogfv(GL_FOG_COLOR, fogColorGreen);//�ı������ɫ
				glutPostRedisplay();
		break;
		case '7':
				glFogfv(GL_FOG_COLOR, fogColorWhite);//�ı������ɫ
				glutPostRedisplay();
		break;
		default:
		break;
	}
}

void main(void)
{
	//��ʼ��GLUT��OpenGL���ڵ���ʾģʽ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
	glutInitWindowSize(300,300);
	glutInitWindowPosition(300,300);
	glutCreateWindow("��"); 
	glutDisplayFunc(ReDraw); // ���õ�ǰ���ڵ���ʾ�ص�����
    glutReshapeFunc(ChangeSize); // Ϊ��ǰ�������ô��������λص�����
   	glutKeyboardFunc(Key);

	// ���ڳ�ʼ��
    Initial();
	glutMainLoop(); //������GLUT�¼�����ѭ��
}
