#include "pyramid_gl.h"
#include "object_gl.h"

#include "quad_gl.h"
#include "triangle_gl.h"

PyramidGL::PyramidGL() : ObjectGL()
{


	GLfloat size = 1.f;

	this->q1 = new QuadGL();
	this->q1->setColor(this->color[0], this->color[1], this->color[2]);
	this->q1->frontFaceMode = this->FaceMode;
	this->q1->backFaceMode = this->FaceMode;
	this->q1->translate(0.f, -sqrt(3) * size / 6.f, 0.f);
	this->q1->rotate(90.0f, 1.f, 0.f, 0.f);

	this->t1 = new TriangleGL();
	this->t1->setColor(this->color[0], this->color[1], this->color[2]);
	this->t1->frontFaceMode = this->FaceMode;
	this->t1->backFaceMode = this->FaceMode;
	this->t1->translate(0.0f, -0.052f, size/2.f - 0.17f);
	this->t1->rotate(-35.0f, 1.f, 0.f, 0.f);

	this->t2 = new TriangleGL();
	this->t2->setColor(this->color[0], this->color[1], this->color[2]);
	this->t2->frontFaceMode = this->FaceMode;
	this->t2->backFaceMode = this->FaceMode;
	this->t2->translate(0.0f, -0.052f, -(size / 2.f - 0.17f));
	this->t2->rotate(35.0f, 1.f, 0.f, 0.f);
	this->t2->rotate(-180.0f, 0.f, 1.f, 0.f);

	this->t3 = new TriangleGL();
	this->t3->setColor(this->color[0], this->color[1], this->color[2]);
	this->t3->frontFaceMode = this->FaceMode;
	this->t3->backFaceMode = this->FaceMode;
	this->t3->translate(-(size / 2.f - 0.17f), -0.052f, 0.0f);
	this->t3->rotate(-90.0f, 0.f, 1.f, 0.f);
	this->t3->rotate(-35.0f, 1.f, 0.f, 0.f);

	this->t4 = new TriangleGL();
	this->t4->setColor(this->color[0], this->color[1], this->color[2]);
	this->t4->frontFaceMode = this->FaceMode;
	this->t4->backFaceMode = this->FaceMode;
	this->t4->translate(size / 2.f - 0.17f, -0.052f, 0.0f);
	this->t4->rotate(90.0f, 0.f, 1.f, 0.f);
	this->t4->rotate(-35.0f, 1.f, 0.f, 0.f);
	

}
PyramidGL::~PyramidGL()
{

}
void PyramidGL::render()
{
	glPolygonMode(GL_FRONT, this->FaceMode);
	glPolygonMode(GL_BACK, this->FaceMode);
	//glPolygonMode(GL_BACK, GL_FILL);

	//glColor3f(this->color[0], this->color[1], this->color[2]);

	glPushMatrix();
	GLfloat *ptrM = glm::value_ptr(this->m);
	glMultMatrixf(ptrM);

	this->q1->setColor(this->color[0], this->color[1], this->color[2]);
	this->q1->render();
	this->t1->setColor(this->color[0], this->color[1], this->color[2]);
	this->t1->render();
	this->t2->setColor(this->color[0], this->color[1], this->color[2]);
	this->t2->render();
	this->t3->setColor(this->color[0], this->color[1], this->color[2]);
	this->t3->render();
	this->t4->setColor(this->color[0], this->color[1], this->color[2]);
	this->t4->render();
	

	glPopMatrix();
}