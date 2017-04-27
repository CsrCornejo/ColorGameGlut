#ifndef PYRAMID_GL_H
#define PYRAMID_GL_H

#include "object_gl.h"
#include "quad_gl.h"
#include "triangle_gl.h"

class PyramidGL : public ObjectGL
{
private:
	QuadGL *q1;
	TriangleGL *t1, *t2, *t3, *t4;
public:
	int FaceMode;
public:
	PyramidGL();
	~PyramidGL();
	void render();
};

#endif
