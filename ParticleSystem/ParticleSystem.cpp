// ParticleSystem.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ParticleSystem_.h"

ParticleSystem_ particleSystem;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	particleSystem.render();
	glutSwapBuffers();
	glutPostRedisplay();
}

void mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Triangle demo");

	glewInit();
	particleSystem.initSystem();

	glutMouseFunc(mouseFunc);
	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}

