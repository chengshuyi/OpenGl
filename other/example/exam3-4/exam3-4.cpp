#include <windows.h>
#include <gl/glut.h>
#include<gl/gl.h>
#include<gl/glu.h>

// ��ת����
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void SetupRC(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glShadeModel (GL_FLAT);
}

void ChangeSize(GLsizei w, GLsizei h)
{
	if(h == 0)		h = 1;
	
	// ���������ߴ�
   	glViewport(0, 0, w, h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// �����޼��ռ�ķ�Χ
    gluPerspective(60.0f, (GLfloat) w/(GLfloat) h, 1.0f, 20.0f);

    glMatrixMode(GL_MODELVIEW);
}

// �ڴ����л���ͼ��
void RenderScene(void)
{
	//����ü�ƽ�淽��ϵ��������ƽ�淽��Ϊx = 0
    GLdouble eqn[4] = {-1.0, 0.0, 0.0, 0.0};

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f (1.0f, 0.0f, 0.0f);

    glPushMatrix();

	//��z�Ḻ��ƽ��һ�ξ��룬��֤���õĹ۲�Ч��
    glTranslatef (0.0, 0.0, -5.0);

	//���òü�ƽ��
    glClipPlane (GL_CLIP_PLANE0, eqn);
    glEnable (GL_CLIP_PLANE0);

	//ʹ������ת
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    glutWireSphere(2.0f, 20 , 20);

    glPopMatrix();

    glFlush();
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

	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutCreateWindow("GLClipPlane"); 
	glutDisplayFunc(RenderScene); 
	glutSpecialFunc(SpecialKeys);
    glutReshapeFunc(ChangeSize); 
   	
    SetupRC();
	glutMainLoop();
	return 0;
}
