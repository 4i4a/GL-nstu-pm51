#include <iostream>
#include <vector>
#ifdef __APPLE__
#   include <OpenGL/opengl.h>
#   include <GLUT/glut.h>
#elif defined _WIN32
#   include <gl/glut.h>
#endif

#define ESCAPE '\033'

typedef struct dot_type {
    dot_type(int x_t, int y_t):x(x_t),y(y_t) {
    }
    int x, y;
    unsigned char color[3] = {
        static_cast<unsigned char>(rand()%255),
        static_cast<unsigned char>(rand()%255),
        static_cast<unsigned char>(rand()%255)
    };
}dot;

std::vector<dot> vd;

GLint Width = 512, Height = 512;

void Display()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    for (dot j : vd) {
        glVertex2f(j.x, j.y);
        glColor3ubv(j.color);
    }
    glEnd();
    glFinish();
}
/* Функция вызывается при изменении размеров окна */
void Reshape(GLint w, GLint h)
{
    Width = w;
    Height = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
/* Функция обрабатывает сообщения от клавиатуры */
void Keyboard( unsigned char key, int x, int y )
{
    if( key == ESCAPE ) {
        exit(0);
    } else {
        std::cout << int(key);
    }
}

void Mouse(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        vd.push_back({x, Height-y});
        glutPostRedisplay();
    }
}

/* головная программа */
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(Width, Height);
    glutCreateWindow("Red square example");
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(Mouse);
    glutMainLoop();

    exit(0);
}
