#include "cube_gl.h"
#include "object_gl.h"

#include "quad_gl.h"

CubeGL::CubeGL() : ObjectGL()
{
	
	
	GLfloat size = 1.f;

	this->q1 = new QuadGL();
	this->q1->setColor(this->color[0], this->color[1], this->color[2]);
	this->q1->frontFaceMode = this->FaceMode;
	this->q1->backFaceMode = this->FaceMode;
	this->q1->translate(0.f, 0.f, size / 2.f);
	

	this->q2 = new QuadGL();
	this->q2->setColor(this->color[0], this->color[1], this->color[2]);
	this->q2->frontFaceMode = this->FaceMode;
	this->q2->backFaceMode = this->FaceMode;
	this->q2->translate(0.f, 0.f, -size / 2.f);
	this->q2->rotate(-180.f, 0.f, 1.f, 0.f);

	this->q3 = new QuadGL();
	this->q3->setColor(this->color[0], this->color[1], this->color[2]);
	this->q3->frontFaceMode = this->FaceMode;
	this->q3->backFaceMode = this->FaceMode;
	this->q3->translate(-size / 2.f, 0.f, 0.f);
	this->q3->rotate(-90.0f, 0.f, 1.f, 0.f);

	this->q4 = new QuadGL();
	this->q4->setColor(this->color[0], this->color[1], this->color[2]);
	this->q4->frontFaceMode = this->FaceMode;
	this->q4->backFaceMode = this->FaceMode;
	this->q4->translate(size / 2.f, 0.f, 0.f);
	this->q4->rotate(90.0f, 0.f, 1.f, 0.f);

	this->q5 = new QuadGL();
	this->q5->setColor(this->color[0], this->color[1], this->color[2]);
	this->q5->frontFaceMode = this->FaceMode;
	this->q5->backFaceMode = this->FaceMode;
	this->q5->translate(0.f, -size / 2.f, 0.f);
	this->q5->rotate(90.0f, 1.f, 0.f, 0.f);

	this->q6 = new QuadGL();
	this->q6->setColor(this->color[0], this->color[1], this->color[2]);
	this->q6->frontFaceMode = this->FaceMode;
	this->q6->backFaceMode = this->FaceMode;
	this->q6->translate(0.f, size / 2.f, 0.f);
	this->q6->rotate(-90.0f, 1.f, 0.f, 0.f);
}
CubeGL::~CubeGL()
{

}
void CubeGL::render()
{
	glPolygonMode(GL_FRONT, this->FaceMode);
	glPolygonMode(GL_BACK, this->FaceMode);

	//glColor3f(this->color[0], this->color[1], this->color[2]);

	glPushMatrix();
	GLfloat *ptrM = glm::value_ptr(this->m);
	glMultMatrixf(ptrM);

	this->q1->setColor(this->color[0], this->color[1], this->color[2]);
	this->q1->render();
	this->q2->setColor(this->color[0], this->color[1], this->color[2]);
	this->q2->render();
	this->q3->setColor(this->color[0], this->color[1], this->color[2]);
	this->q3->render();
	this->q4->setColor(this->color[0], this->color[1], this->color[2]);
	this->q4->render();
	this->q5->setColor(this->color[0], this->color[1], this->color[2]);
	this->q5->render();
	this->q6->setColor(this->color[0], this->color[1], this->color[2]);
	this->q6->render();

	glPopMatrix();
}