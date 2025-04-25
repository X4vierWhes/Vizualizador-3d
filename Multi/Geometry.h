/**********************************************************************************
// Geometry (Arquivo de Cabeçalho)
//
// Criação:     03 Fev 2013
// Atualização: 10 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Define vértices e índices para várias geometrias
//
**********************************************************************************/

#ifndef DXUT_GEOMETRY_H_
#define DXUT_GEOMETRY_H_

// -------------------------------------------------------------------------------

#include "Types.h"
#include <vector>
#include <DirectXMath.h>
#include <DirectXColors.h>
using namespace DirectX;
using std::vector;

// -------------------------------------------------------------------------------

struct Vertex
{
    XMFLOAT3 pos;
    XMFLOAT4 color;
};

// -------------------------------------------------------------------------------
// Geometry
// -------------------------------------------------------------------------------

struct Geometry
{
    vector<Vertex> vertices;                // vértices da geometria
    vector<uint>   indices;                 // índices da geometria

    void Subdivide();                       // subdivide triângulos

    // métodos inline
    const Vertex* VertexData() const        // retorna vértices da geometria
    { return vertices.data(); }
    
    const uint* IndexData() const           // retorna índices da geometria
    { return indices.data(); }
    
    uint VertexCount() const                // retorna número de vértices
    { return uint(vertices.size()); }
    
    uint IndexCount() const                 // retorna número de índices
    { return uint(indices.size()); }
};

// -------------------------------------------------------------------------------
// Box
// -------------------------------------------------------------------------------

struct Box : public Geometry
{
    Box(float width, float height, float depth);
};

// -------------------------------------------------------------------------------
// Cylinder
// -------------------------------------------------------------------------------

struct Cylinder : public Geometry
{
    Cylinder(float bottom, float top, float height, uint sliceCount, uint stackCount);
};

// -------------------------------------------------------------------------------
// Sphere
// -------------------------------------------------------------------------------

struct Sphere : public Geometry
{
    Sphere(float radius, uint sliceCount, uint stackCount);
};

// -------------------------------------------------------------------------------
// GeoSphere
// -------------------------------------------------------------------------------

struct GeoSphere : public Geometry
{
    GeoSphere(float radius, uint subdivisions);
};


// -------------------------------------------------------------------------------
// Grid
// -------------------------------------------------------------------------------

struct Grid : public Geometry
{
    Grid(float width, float depth, uint m, uint n);
};

// -------------------------------------------------------------------------------
// Quad
// -------------------------------------------------------------------------------

struct Quad : public Geometry
{
    Quad(float width, float height);
};

// -------------------------------------------------------------------------------

#endif
