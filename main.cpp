#include <iostream>
#include <vector>
#ifdef __APPLE__
#   include <OpenGL/opengl.h>
#   include <GLUT/glut.h>
#elif defined _WIN32
#   include <gl/glut.h>
#endif

//Обозначения клавиш
#define ESCAPE 27
#define ENTER 13


//Структура точки
typedef struct dot_type {
    dot_type(int x_t, int y_t):x(x_t),y(y_t) {
        color[0] = static_cast<unsigned char>(rand()%255);
        color[1] = static_cast<unsigned char>(rand()%255);
        color[2] = static_cast<unsigned char>(rand()%255);
    }
    int x, y;
    unsigned char color[3];
}dot;

typedef std::vector<dot> shape; //Фигура состаящая из точек

std::vector<shape> shapes; //Контейнер фигур

GLint Width = 512, Height = 512; //Размер окна

//Функция обработки графики (главная функция)
void Display()
{
    glClearColor(0, 0, 0, 1); //Цвет очистки экрана
    glClear(GL_COLOR_BUFFER_BIT); //Очистка экрана

    //Прорисовка фигур
    for (auto i : shapes) {
        glBegin(GL_POLYGON);
        for (dot j : i) {
            glVertex2f(j.x, j.y);
            glColor3ubv(j.color);
        }
        glEnd();
    }
    glFinish();
}

//При изменении размера окна
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

//Функция управления клавиатурой
void Keyboard( unsigned char key, int x, int y )
{
    //Елси нажат ESC - выходим
    //Если нажат ENTER - редактируем другую фигуру
    switch(key) {
        case ESCAPE:{
            exit(0);
            break;
        }
        case ENTER: {
            shape temp;
            shapes.push_back(temp);
            break;
        }
        default: {

        }
    }
}

//Функция управления мышью
void Mouse(int button, int state, int x, int y) {
    //Если контейнер пуст, не получиться обратиться к эелементу
    if (shapes.empty()) {
        shape temp;
        shapes.push_back(temp);
    }
    //Если нажата левая клавиша мыши
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        //Добавляем точку к "фигуре"
        shapes.back().push_back({x, Height-y});
        glutPostRedisplay();
    }
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);  //Инициализация API
    glutInitDisplayMode(GLUT_RGB); //Режим отображения
    glutInitWindowSize(Width, Height); //Размер экрана
    glutCreateWindow("Var 5"); //Заголовок окна
    glutDisplayFunc(Display); //Привязка функций-обработчиков
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(Mouse);
    glutMainLoop(); //Главная бесконечная функция

    exit(0); //Выход с освобождением памяти
}
