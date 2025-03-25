#include <iostream>
#include <GL/glut.h>

float rotateAngle = 0.0f;
float scaleX = 1.0f, scaleY = 1.0f, scaleZ = 1.0f;
float shearXY = 0.0f;
bool reflectX = false;
bool rotating = true;
float translateX = 0.0f, translateY = 0.0f, translateZ = 0.0f;

enum Transformation {
    ROTATION,
    SCALING,
    SHEARING,
    REFLECTION,
    TRANSLATION,
    NONE
};

Transformation currentTransformation = ROTATION;

void drawColoredCube() {
    // Vertex coordinates for a cube
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
    };

    // Edge indices
    unsigned int indices[] = {
        0, 1, 1, 2, 2, 3, 3, 0, // Back face
        4, 5, 5, 6, 6, 7, 7, 4, // Front face
        0, 4, 1, 5, 2, 6, 3, 7  // Connecting edges
    };

    // Colors for each edge
    float colors[] = {
        1.0f, 0.0f, 0.0f, // Red
        0.0f, 1.0f, 0.0f, // Green
        0.0f, 0.0f, 1.0f, // Blue
        1.0f, 1.0f, 0.0f, // Yellow
        1.0f, 0.0f, 1.0f, // Magenta
        0.0f, 1.0f, 1.0f, // Cyan
        1.0f, 0.5f, 0.0f, // Orange
        0.5f, 0.0f, 1.0f, // Purple
        0.5f, 1.0f, 0.0f, // Lime
        0.0f, 0.5f, 1.0f, // Light Blue
        1.0f, 0.0f, 0.5f, // Pink
        0.0f, 1.0f, 0.5f  // Sea Green
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, indices);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);

    if (currentTransformation == TRANSLATION) {
        glTranslatef(translateX, translateY, translateZ);
    }

    if (currentTransformation == REFLECTION) {
        if (reflectX) {
            glScalef(-1.0f, 1.0f, 1.0f);
        }
    }

    glRotatef(rotateAngle, 1.0f, 1.0f, 1.0f);

    if (currentTransformation == SCALING) {
        glScalef(scaleX, scaleY, scaleZ);
    } else if (currentTransformation == SHEARING) {
        GLfloat shearMatrix[] = {
            1.0f, shearXY, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
        glMultMatrixf(shearMatrix);
    }

    drawColoredCube();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void init() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'r':
            rotating = !rotating;
            break;
        case 's':
            currentTransformation = SCALING;
            break;
        case 'h':
            currentTransformation = SHEARING;
            break;
        case 'f':
            currentTransformation = REFLECTION;
            break;
        case 'n':
            currentTransformation = NONE;
            break;
        case 't':
            currentTransformation = TRANSLATION;
            break;

        case '1':
            if (currentTransformation == SCALING) scaleX += 0.1f;
            break;
        case '2':
            if (currentTransformation == SCALING) scaleX -= 0.1f;
            break;
        case '3':
            if (currentTransformation == SCALING) scaleY += 0.1f;
            break;
        case '4':
            if (currentTransformation == SCALING) scaleY -= 0.1f;
            break;
        case '5':
            if (currentTransformation == SCALING) scaleZ += 0.1f;
            break;
        case '6':
            if (currentTransformation == SCALING) scaleZ -= 0.1f;
            break;

        case 'q':
            if (currentTransformation == SHEARING) shearXY += 0.1f;
            break;
        case 'w':
            if (currentTransformation == SHEARING) shearXY -= 0.1f;
            break;

        case 'z':
            if (currentTransformation == REFLECTION) reflectX = !reflectX;
            break;

        case 'i':
            if (currentTransformation == TRANSLATION) translateY += 0.1f;
            break;
        case 'k':
            if (currentTransformation == TRANSLATION) translateY -= 0.1f;
            break;
        case 'j':
            if (currentTransformation == TRANSLATION) translateX -= 0.1f;
            break;
        case 'l':
            if (currentTransformation == TRANSLATION) translateX += 0.1f;
            break;
        case 'u':
            if (currentTransformation == TRANSLATION) translateZ += 0.1f;
            break;
        case 'o':
            if (currentTransformation == TRANSLATION) translateZ -= 0.1f;
            break;
    }
    glutPostRedisplay();
}

void update(int value) {
    if (rotating) {
        rotateAngle += 1.0f;
        if (rotateAngle > 360.0f) {
            rotateAngle -= 360.0f;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);

    // Display transformation information in the terminal
    std::string message;
    switch (currentTransformation) {
        case ROTATION:
            message = "Rotation (r to toggle)";
            break;
        case SCALING:
            message = "Scaling (1/2/3/4/5/6 to adjust)";
            break;
        case SHEARING:
            message = "Shearing (q/w to adjust)";
            break;
        case REFLECTION:
            message = "Reflection (z to toggle X reflection)";
            break;
        case TRANSLATION:
            message = "Translation (i/k/j/l/u/o to adjust)";
            break;
        case NONE:
            message = "No Transformation";
            break;
    }
    std::cout << "\r" << message << std::flush; // Overwrite the previous message
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Transformations");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0);

    std::cout << "Controls:\n";
    std::cout << "r: Toggle Rotation\n";
    std::cout << "s: Scaling (1/2/3/4/5/6 to adjust)\n";
    std::cout << "h: Shearing (q/w to adjust)\n";
    std::cout << "f: Reflection (z to toggle X reflection)\n";
    std::cout << "t: Translation (i/k/j/l/u/o to adjust)\n";
    std::cout << "n: No transformation\n";

    glutMainLoop();
    return 0;
}
