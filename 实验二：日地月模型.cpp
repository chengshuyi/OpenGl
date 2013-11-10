////////////////////////////////////////////////////////////////////////////
//ʵ��Ҫ��(1)���OpenGL�еı任����                                     //
//          (2)���͸��ͶӰ��ƽ��ͶӰ�Ĳ�ͬ                               // 
//          (3)��Ӵ���ʵ��̫����������������˶�ģ��                     //
//          (4)�˽���Ȳ���                                               //
//          (5)ͨ���任�����۲��λ���뷽��                               //
//          (6)�������ģ��                                               //
////////////////////////////////////////////////////////////////////////////

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void Initial()
{
    glEnable(GL_DEPTH_TEST);	// ������Ȳ���
    glFrontFace(GL_CCW);		// ָ����ʱ���Ʒ���ʾ���������
    glEnable(GL_CULL_FACE);     //�����޳�Ч��   
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );	//����Ϊ��ɫ
}

void SetupRC(){

    //���ù�ԴLIGHT0�Ĳ���
    GLfloat light_diffuse[]={1.0f,1.0f,1.0f,1.0f};
    GLfloat light_ambient[]={0.0f,0.0f,0.0f,0.0f};
    GLfloat light_specular[]={1.0f,1.0f,1.0f,1.0f};
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);    //ɢ���
    glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);    //������
    glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);  //�����

    //�ǹ�Դ��Ч
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //ʹ����ɫ����
    glEnable(GL_COLOR_MATERIAL);

    //���ò��Ϸ�������
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
}
void ChangeSize(int w, int h)
{
    if(h == 0)	h = 1;

    // ���������ߴ�
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // �����޼��ռ�
    GLfloat fAspect;
    fAspect = (float)w/(float)h;
    gluPerspective(45.0, fAspect, 1.0, 500.0);
    /*
       if (w <= h) 
       glOrtho (-nRange, nRange, nRange*h/w, -nRange*h/w, -nRange*2.0f, nRange*2.0f);
       else 
       glOrtho (-nRange*w/h, nRange*w/h, nRange, -nRange, -nRange*2.0f, nRange*2.0f);
       */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void RenderScene(void)
{
    // ��ԭ�Ӻ���ת�ĽǶ�
    static float fElect1 = 0.0f,fElect2=0.0f;

    GLfloat position[]={0.0f,0.0f,0.0f,1.0f};

    //���ù�Դ��λ��
    //glLightfv(GL_LIGHT0,GL_POSITION,position);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ����ģ����ͼ����
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    //��Զ�ƶ�����
    glTranslatef(0.0f,0.0f,-300.0f);

    // ���ƺ�ɫ��̫��
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidSphere(40, 60, 60);
    glRotatef(fElect1,0.0f,1.0f,0.0f);
    glTranslatef(0.0f,0.0f,0.0f);
    // ��ǰ������ɫ��Ϊ��ɫ
    glColor3f(0.0f, 0.0f, 0.0f);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0,GL_POSITION,position);

    //������ɫ�ĵ���
    //���浱ǰ��ģ����ͼ����
    glPushMatrix();
    glColor3f(0.0f,0.0f,1.0f);
    glRotatef(fElect1, 0.0f, 1.0f, 0.0f);//��y����תһ���ĽǶ�
    glTranslatef(130.0f, 0.0f, 0.0f);//ƽ��һ�ξ���
    glutSolidSphere(15.0f, 60, 60);//��������


    // ���ƻ�ɫ������
    glPushMatrix();
    glColor3f(1.0f,1.0f,0.0f);
    glRotatef(fElect2, 0.0f, 1.0f, 0.0f);
    glTranslatef(20.0f, 0.0f, 0.0f);
    glutSolidSphere(8.0f, 60,60);
    glPopMatrix();

    // ����������
    //glPushMatrix();
    //glRotatef(-45.0f,0.0f, 0.0f, 1.0f);
    //glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
    //glTranslatef(0.0f, 0.0f, 60.0f);
    //glutSolidSphere(6.0f, 15, 15);
    //glPopMatrix();

    // ������ת����
    fElect1 += 2.0f;
    if(fElect1 > 360.0f)	fElect1 = 10.0f;
    fElect2+=20.0f;
    if(fElect2>360.0f){
        fElect2=10.0f;
    }
    glutSwapBuffers();
}

void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(100, TimerFunc, 1);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200,700);
    glutCreateWindow("�յ���ģ��");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutTimerFunc(500, TimerFunc, 1);

    SetupRC();

    Initial();
    glutMainLoop();

    return 0;
}
