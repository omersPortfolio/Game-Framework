#include "GamePCH.h"
#include "Shapes.h"

const fw::VertexFormat meshAttribs_Human[] =
{
    fw::VertexFormat( -0.25f,  -0.25f,   0, 0 ),
    fw::VertexFormat(  0.25f,   0.25f,   0, 0 ),
    fw::VertexFormat(  0.25f,  -0.25f,   0, 0 ),
};
const int meshPrimType_Human = GL_TRIANGLES;
const int meshNumVerts_Human = sizeof(meshAttribs_Human) / sizeof(fw::VertexFormat);

const fw::VertexFormat meshAttribs_Enemy[] =
{
    fw::VertexFormat( 0.0f, 0.0f,   0,0 ),
};
const int meshPrimType_Enemy = GL_POINTS;
const int meshNumVerts_Enemy = sizeof(meshAttribs_Enemy) / sizeof(fw::VertexFormat);
