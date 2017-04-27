#ifndef CUBE_GL_H
#define CUBE_GL_H

#include "object_gl.h"
#include "quad_gl.h"

class CubeGL : public ObjectGL
{
private:
	QuadGL *q1, *q2, *q3, *q4, *q5, *q6;
public:
	int FaceMode;
public:
	CubeGL();
	~CubeGL();
	void render();
};

#endif
