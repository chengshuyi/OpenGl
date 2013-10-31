////////////////////////////////////////////////////////////////////////////
//ʵ��Ҫ��(1)���glut������                                           //
//          (2)��ⴰ�ڵ������ı任                                       // 
//          (3)���OpenGLʵ�ֶ�����ԭ��                                   //   
//          (4)��Ӵ���ʵ���е�Bresenham�㷨��ֱ��                        //
//          (5)��Ӵ���ʵ�ָĽ�Bresenham�㷨��ֱ��                        //
//          (6)��Ӵ���ʵ��Բ�Ļ��ƣ������ʵ��Կ������ϵ�����޸ģ�       //
//          (7)�ʵ��޸Ĵ���ʵ�־��п�ȵ�ͼ�Σ���ˢ�ӻ�ˢ�ӣ�           //
////////////////////////////////////////////////////////////////////////////

#include <GL/glut.h>
#include "stdio.h"

int m_PointNumber = 0; //����ʱ���Ƶ����Ŀ
int m_DrawMode = 1;    //����ģʽ   1    DDA�㷨��ֱ��
//           2    �е�Bresenham�㷨��ֱ��
//           3    �Ľ�Bresenham�㷨��ֱ��
//           4    �˷ַ�����Բ
//           5    �ķַ�������Բ

//����������
void DrawCordinateLine(void)
{
	int i = 0 ;
	//������Ϊ��ɫ
	glColor3f(0.0f, 0.0f ,0.0f);
	glBegin(GL_LINES);
        for (i=10;i<=250;i=i+10)
		{
			glVertex2f((float)(i), 0.0f);
			glVertex2f((float)(i), 250.0f);
			glVertex2f(0.0f, (float)(i));
			glVertex2f(250.0f, (float)(i));
		}
	glEnd();
}

//����һ���㣬������һ�������α�ʾһ���㡣
void putpixel(GLsizei x, GLsizei y)
{
	glRectf(10*x,10*y,10*x+10,10*y+10);
}

///////////////////////////////////////////////////////////////////
//DDA�����㷨                                                    //
//����˵����x0,y0  �������                                      //  
//          x1,y1  �յ�����                                      // 
//          num    ɨ��ת��ʱ����㿪ʼ����ĵ����Ŀ�����ڶ���  //
/////////////////////////////////////////////////////////////////// 
void DDACreateLine(GLsizei x0, GLsizei y0, GLsizei x1, GLsizei y1, GLsizei num)
{
	//������ɫ
	glColor3f(1.0f,0.0f,0.0f);
	
	//�Ի��߶������п���
	if(num == 1)
		printf("DDA�����㷨����������\n");
	else if(num==0)
		return;

	//�����㷨��ʵ��
	GLsizei dx,dy,epsl,k;
	GLfloat x,y,xIncre,yIncre;

	dx = x1-x0;
	dy = y1-y0;
	x = x0;
	y = y0;

	if(abs(dx) > abs(dy)) epsl = abs(dx);
	else epsl = abs(dy);
	xIncre = (float)dx / epsl ;
	yIncre = (float)dy / epsl ;

	for(k = 0; k<=epsl; k++){
		putpixel((int)(x+0.5), (int)(y+0.5));
		if (k>=num-1) {
			printf("x=%f,y=%f,ȡ���� x=%d,y=%d\n", x, y, (int)(x+0.5),(int)(y+0.5));
			break;
		}
		x += xIncre;
		y += yIncre;

		if(x >= 25 || y >= 25) break;
	}
	
}

///////////////////////////////////////////////////////////////////
//�е�Bresenham�㷨��ֱ��(0<=k<=1)                               //
//����˵����x0,y0  �������                                      //  
//          x1,y1  �յ�����                                      // 
//          num    ɨ��ת��ʱ����㿪ʼ����ĵ����Ŀ�����ڶ���  //
/////////////////////////////////////////////////////////////////// 
void BresenhamLine(GLsizei x0, GLsizei y0, GLsizei x1, GLsizei y1, GLsizei num)
{
	glColor3f(1.0f,0.0f,0.0f);

	if(num == 1)
		printf("�е�Bresenham�㷨��ֱ�ߣ��������꼰�б�ʽ��ֵ\n");
	else if(num==0)
		return;
  
  //�����㷨��ʵ��
  GLsizei dx,dy,d,UpInce,DownInce,x,y,k;
  if(x0>x1){
    x=x1;x1=x0;x0=x;
    y=y1;y1=y0;y0=y;
  }
  x=x0;y=y0;
  dx=x1-x0;dy=y1-y0;
  d=dx-2*dy;
  UpInce=2*dx-2*dy;  DownInce=-2*dy;
  for(k=0;x<=x1;k++){
   putpixel(x,y);
    if (k>=num-1) {
      printf("x=%d,y=%d,ȡ���� x=%d,y=%d\n", x, y, (int)(x+0.5),(int)(y+0.5));
      break;
    }
  x++;
    if(d<0){
    y++;
      d+=UpInce;
    }
    else  d+=DownInce;
  }
  
}

///////////////////////////////////////////////////////////////////
//�Ľ���Bresenham�㷨��ֱ��(0<=k<=1)                             //
//����˵����x0,y0  �������                                      //  
//          x1,y1  �յ�����                                      // 
//          num    ɨ��ת��ʱ����㿪ʼ����ĵ����Ŀ�����ڶ���  //
/////////////////////////////////////////////////////////////////// 
void Bresenham2Line(GLsizei x0, GLsizei y0, GLsizei x1, GLsizei y1, GLsizei num)
{
	glColor3f(1.0f,0.0f,0.0f);

	if(num == 1)
		printf("�Ľ���Bresenham�㷨��ֱ�ߣ��������꼰�б�ʽ��ֵ\n");
	else if(num==0)
		return;
  //�����㷨��ʵ��
  GLsizei x,y,dx,dy,e,k;
  dx=x1-x0;
  dy=y1-y0;
  e=-dx;x=x0;y=y0;
  for(k=0;x<=x1;k++){
    putpixel(x,y);  
    if(k>=num-1){
    
      printf("x=%d,y=%d,ȡ���� x=%d,y=%d\n", x, y, (int)(x+0.5),(int)(y+0.5));
      break;
    }
    x++;
    e=e+2*dy;
    if(e>0){
    y++;
    e=e-2*dx;
    }
  }
}

///////////////////////////////////////////////////////////////////
//Bresenham�㷨��Բ                                              //
//����˵����x,y    Բ������                                      //  
//          R      Բ�뾶                                        // 
//          num    ɨ��ת��ʱ����㿪ʼ����ĵ����Ŀ�����ڶ���  //
/////////////////////////////////////////////////////////////////// 
void BresenhamCircle(GLsizei x, GLsizei y, GLsizei R, GLsizei num)
{
	glColor3f(1.0f,0.0f,0.0f);

	if(num == 1)
		printf("Bresenham�㷨��Բ���������꼰�б�ʽ��ֵ\n");
  else if(num==0)
    return;
  

  //��Բ�㷨��ʵ��
   GLsizei x1,y1,d,k;
  x1=0;y1=R;d=1-R;
  for(k=0;x1<=y1;k++){
    putpixel(x1,y1);
    if(k>=num-1){
      printf("x=%d,y=%d,ȡ����x=%d,y=%d\n",x,y,(int)(x+0.5),(int)(y+0.5));
      break;
    }
   if(d<0) d+=2*x1+3;
    else{
      d+=2*(x1-y1)+5;
      y1--;
    }
    x1++;
  }
	

}

//��ʼ������
void Initial(void)
{
    // ���ô�����ɫΪ��ɫ
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// ���ڴ�С�ı�ʱ���õĵǼǺ���
void ChangeSize(GLsizei w, GLsizei h)
{

	if(h == 0)		h = 1;

	// ���������ߴ�
   	glViewport(0, 0, w, h);
	
	// ��������ϵͳ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// �����޼��ռ�ķ�Χ
   	if (w <= h) 
		glOrtho (0.0f, 250.0f, 0.0f, 250.0f*h/w, 1.0, -1.0);
    else 
		glOrtho (0.0f, 250.0f*w/h, 0.0f, 250.0f, 1.0, -1.0);

}

// �ڴ����л���ͼ��
void ReDraw(void)
{
	//�õ�ǰ����ɫ��䴰��
	glClear(GL_COLOR_BUFFER_BIT);

	//����������
	DrawCordinateLine();
	
	switch(m_DrawMode)
	{
	case 1:
		DDACreateLine(0,0,20,15,m_PointNumber);
		break;
	case 2:
		BresenhamLine(0,0,20,15,m_PointNumber);
		break;
	case 3:
		Bresenham2Line(1,1,8,6,m_PointNumber);
		break;
	case 4:
		BresenhamCircle(0,0,20,m_PointNumber);
		break;
	default:
		break;
	}

    glFlush();
}

//����ʱ��ص�����
void TimerFunc(int value)
{
	if(m_PointNumber == 0)
		value = 1;

	m_PointNumber = value;

	glutPostRedisplay();
	glutTimerFunc(500, TimerFunc, value+1);
}

//���ü��̻ص�����
void Keyboard(unsigned char key, int x, int y)   
{
    if (key == '1')     m_DrawMode = 1;
	if (key == '2')     m_DrawMode = 2;
	if (key == '3')     m_DrawMode = 3;
	if (key == '4')     m_DrawMode = 4;

	m_PointNumber = 0;
	glutPostRedisplay();
}

//void main(void)
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	//��ʼ��GLUT��OpenGL���ڵ���ʾģʽ
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(600,600);
	glutInitWindowPosition(100,100);

	glutCreateWindow("����ͼԪ���Ƴ���");	glutDisplayFunc(ReDraw); 
  glutReshapeFunc(ChangeSize); 
	glutKeyboardFunc(Keyboard);//������Ӧ�ص�����
	glutTimerFunc(500, TimerFunc, 1);

   	
	// ���ڳ�ʼ��
    Initial();
	glutMainLoop(); //������GLUT�¼�����ѭ��

	return 0;
}
