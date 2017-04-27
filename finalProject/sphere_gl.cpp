#include "sphere_gl.h"
#include "object_gl.h"

SphereGL::SphereGL() : ObjectGL()
{


	GLfloat size = 1.f;

	this->r = size/2.f;
	this->sl = 40; 
	this->st = 40;

}
SphereGL::~SphereGL()
{

}
void SphereGL::render()
{
	//glPolygonMode(GL_FRONT, this->FaceMode);

	glColor3f(this->color[0], this->color[1], this->color[2]);

	glPushMatrix();
	GLfloat *ptrM = glm::value_ptr(this->m);
	glMultMatrixf(ptrM);

	if (this->FaceMode == GL_FILL){
		glutSolidSphere(this->r,this->sl,this->st);
	}
	else{
		glutWireSphere(this->r, this->sl, this->st);
	}

	glPopMatrix();
}