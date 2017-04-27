#ifndef	SPHERE_GL_H
#define SPHERE_GL_H

#include "object_gl.h"

class SphereGL : public ObjectGL
{
private:
	GLfloat r;
	GLint sl, st;
public:
	int FaceMode;
public:
	SphereGL();
	~SphereGL();
	void render();
};

#endif
