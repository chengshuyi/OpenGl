#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

// NURBS����ָ��
GLUnurbsObj *pNurb1 = NULL;
GLUnurbsObj *pNurb2 = NULL;

GLfloat ctrlPoints[5][5][3]= {
	{{-3,0.5,0},{-1,1.5,0},{-2,2,0},{1,-1,0},{-5,0,0}}, 
	{{-3,0.5,-1},{ -1,1.5,-1},{-2,2,-1},{1,-1,-1},{-5,0,-1}},
	{{-3,0.5,-2},{ -1,1.5,-2},{-2,2,-2},{1,-1,-2},{-5,0,-2}},
	{{-3,0.5,-3},{ -1,1.5,-3},{-2,2,-3},{1,-1,-3},{-5,0,-3}},
	{{-3,0.5,-4},{ -1,1.5,-4},{-2,2,-4},{1,-1,-4},{-5,0,-4}}};

GLfloat  mat_diffuse[] = {1.0f, 0.5f, 0.1f, 1.0f };
GLfloat  mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat  mat_shininess[] = { 100.0f };
GLfloat  light_position[] = { 0.0f, -10.0f, 0.0f, 1.0f};

GLfloat Knots[10] = {0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,1.0f};

int spin = 0;

void Initial()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_FRONT, GL_POSITION, light_position);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glEnable(GL_BLEND);

	glFrontFace(GL_CCW);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LINE_SMOOTH);

	pNurb1 = gluNewNurbsRenderer();
    gluNurbsProperty(pNurb1, GLU_SAMPLING_TOLERANCE, 25.0f);
	gluNurbsProperty(pNurb1, GLU_DISPLAY_MODE, (GLfloat)GLU_OUTLINE_POLYGON);

    pNurb2 = gluNewNurbsRenderer();
    gluNurbsProperty(pNurb2, GLU_SAMPLING_TOLERANCE, 25.0f);
	gluNurbsProperty(pNurb2, GLU_DISPLAY_MODE, (GLfloat)GLU_FILL);
}

static void Key(unsigned char key, int x, int y)
{
	switch(key){
		case 'd':
			spin = spin +1;
			glRotatef(spin, 1.0f, 1.0f, 0.0f);
			glutPostRedisplay();
			break;
		case 27:
			exit(0);
		default:
			break;
	}
}

void ReDraw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glRotatef(50.0f, 1.0f,1.0f,0.0f);

	//���Ƶ�һ������
	glPushMatrix();
	glTranslatef(1.0f,0.0f,0.0f);
    gluBeginSurface(pNurb1);
		gluNurbsSurface(pNurb1,	    // NURBS����ָ��
			10,                      // ������u�����ϵĽ����Ŀ
			Knots,		        	// ������u�����ϵ����Ľ��ֵ������	
			10,                      // ������v�����ϵĽ����Ŀ
			Knots,			        // ������v�����ϵ����Ľ��ֵ������
			5 * 3,			       	// ������u���������ڿ��Ƶ�֮���ƫ����
			3,					    // ������v���������ڿ��Ƶ�֮���ƫ����
			&ctrlPoints[0][0][0],   // ����������Ƶ������
			5,                      // ������u�����ϵĽ���
			5,					    // ������v�����ϵĽ���
			GL_MAP2_VERTEX_3);		// ���������
	gluEndSurface(pNurb1);
	glPopMatrix();

	//���Ƶڶ�������
	glPushMatrix();
	glTranslatef(7.0f,0.0f,0.0f);
    gluBeginSurface(pNurb2);
		gluNurbsSurface(pNurb2,	    // NURBS����ָ��
			10,                      // ������u�����ϵĽ����Ŀ
			Knots,		        	// ������u�����ϵ����Ľ��ֵ������	
			10,                      // ������v�����ϵĽ����Ŀ
			Knots,			        // ������v�����ϵ����Ľ��ֵ������
			5 * 3,			       	// ������u���������ڿ��Ƶ�֮���ƫ����
			3,					    // ������v���������ڿ��Ƶ�֮���ƫ����
			&ctrlPoints[0][0][0],   // ����������Ƶ������
			5,                      // ������u�����ϵĽ���
			5,					    // ������v�����ϵĽ���
			GL_MAP2_VERTEX_3);		// ���������
	gluEndSurface(pNurb2);
	glPopMatrix();
	
	glutSwapBuffers();
}

void ChangeSize(int w, int h)
{
	if(h == 0)		h = 1;

    glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective (50.0f, (GLdouble)w/(GLdouble)h, 1.0, 15.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    glTranslatef (0.0f, 0.0f, -9.0f);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600,400);
	glutInitWindowPosition(200,200);
	glutCreateWindow("NURBS����");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(ReDraw);
	glutKeyboardFunc(Key);
	Initial();
	glutMainLoop();
	return 0;
}
