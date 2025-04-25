/**********************************************************************************
// Mesh (Arquivo de Cabeçalho)
//
// Criação:     28 Abr 2016
// Atualização: 14 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Representa uma malha 3D
//
**********************************************************************************/

#ifndef DXUT_MESH_H_
#define DXUT_MESH_H_

// -------------------------------------------------------------------------------

#include "Types.h"
#include "Graphics.h"
#include <string>
#include <unordered_map>
using std::unordered_map;
using std::string;

// -------------------------------------------------------------------------------

struct SubMesh
{
    uint indexCount = 0;
    uint startIndex = 0;
    uint baseVertex = 0;
};

// -------------------------------------------------------------------------------

class Mesh
{
private:
    ID3D12Resource* vertexBufferUpload;                                     // buffer de Upload CPU -> GPU
    ID3D12Resource* vertexBufferGPU;                                        // buffer na GPU
    D3D12_VERTEX_BUFFER_VIEW vertexBufferView;                              // descritor do buffer de vértices
    uint vertexBufferSize;                                                  // tamanho do buffer de vértices
    uint vertexBufferStride;                                                // tamanho de um vértice
                                                                            
    ID3D12Resource* indexBufferUpload;                                      // buffer de Upload CPU -> GPU
    ID3D12Resource* indexBufferGPU;                                         // buffers na GPU
    D3D12_INDEX_BUFFER_VIEW indexBufferView;                                // descritor do buffer de índices
    uint indexBufferSize;                                                   // tamanho do buffer de índices
    DXGI_FORMAT indexFormat;                                                // formato do buffer de índices
                                                                            
    ID3D12DescriptorHeap* cbufferHeap;                                      // heap de descritores do buffer constante
    ID3D12Resource* cbufferUpload;                                          // buffer de Upload CPU -> GPU
    byte* cbufferData;                                                      // buffer na CPU
    uint cbufferDescriptorSize;                                             // tamanho do descritor 
    uint cbufferElementSize;                                                // tamanho de um elemento no buffer 
                                                                            
public:                                                                     
    unordered_map<string, SubMesh> SubMesh;                                 // uma malha pode armazenar múltiplas sub-malhas
                                                                            
    Mesh();                                                                 // construtor
    ~Mesh();                                                                // destrutor

    void VertexBuffer(const void* vb, uint vbSize, uint vbStride);          // aloca e copia vértices para vertex buffer 
    void IndexBuffer(const void* ib, uint ibSize, DXGI_FORMAT ibFormat);    // aloca e copia índices para index buffer 
    void ConstantBuffer(uint objSize, uint objCount = 1);                   // aloca constant buffer com tamanho solicitado
    void CopyConstants(const void* cbData, uint cbIndex = 0);               // copia dados para o constant buffer

    D3D12_VERTEX_BUFFER_VIEW * VertexBufferView();                          // retorna descritor (view) do Vertex Buffer
    D3D12_INDEX_BUFFER_VIEW * IndexBufferView();                            // retorna descritor (view) do Index Buffer
    ID3D12DescriptorHeap* ConstantBufferHeap();                             // retorna heap de descritores
    D3D12_GPU_DESCRIPTOR_HANDLE ConstantBufferHandle(uint cbIndex = 0);     // retorna handle de um descritor
};

// -------------------------------------------------------------------------------

#endif

