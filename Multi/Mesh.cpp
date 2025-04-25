/**********************************************************************************
// Mesh (Código Fonte)
//
// Criação:     28 Abr 2016
// Atualização: 14 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Representa uma malha 3D
//
**********************************************************************************/

#include "Mesh.h"
#include "Engine.h"

// -------------------------------------------------------------------------------

Mesh::Mesh()
{
    vertexBufferUpload = nullptr;
    vertexBufferGPU = nullptr;
    ZeroMemory(&vertexBufferView, sizeof(D3D12_VERTEX_BUFFER_VIEW));
    vertexBufferSize = 0;
    vertexBufferStride = 0;

    indexBufferUpload = nullptr;
    indexBufferGPU = nullptr;
    ZeroMemory(&indexBufferView, sizeof(D3D12_INDEX_BUFFER_VIEW));
    indexBufferSize = 0;
    ZeroMemory(&indexFormat, sizeof(DXGI_FORMAT));

    cbufferHeap = nullptr;
    cbufferUpload = nullptr;
    cbufferData = nullptr;
    cbufferDescriptorSize = 0;
    cbufferElementSize = 0;
}

// -------------------------------------------------------------------------------

Mesh::~Mesh()
{
    if (vertexBufferUpload) vertexBufferUpload->Release();
    if (vertexBufferGPU) vertexBufferGPU->Release();
    if (indexBufferUpload) indexBufferUpload->Release();
    if (indexBufferGPU) indexBufferGPU->Release();

    if (cbufferUpload)
    {
        cbufferUpload->Unmap(0, nullptr);
        cbufferUpload->Release();
        cbufferHeap->Release();
    }
}

// -------------------------------------------------------------------------------

void Mesh::VertexBuffer(const void* vb, uint vbSize, uint vbStride)
{
    // guarda tamanho do buffer e vértice
    vertexBufferSize = vbSize;
    vertexBufferStride = vbStride;

    // aloca recursos para o vertex buffer
    Engine::graphics->Allocate(UPLOAD, vbSize, &vertexBufferUpload);
    Engine::graphics->Allocate(GPU, vbSize, &vertexBufferGPU);

    // copia vértices para o buffer da GPU usando o buffer de Upload
    Engine::graphics->Copy(vb, vbSize, vertexBufferUpload, vertexBufferGPU);
}

// -------------------------------------------------------------------------------

void Mesh::IndexBuffer(const void* ib, uint ibSize, DXGI_FORMAT ibFormat)
{
    // guarda tamanho do buffer e formato dos índices
    indexBufferSize = ibSize;
    indexFormat = ibFormat;

    // aloca recursos para o index buffer
    Engine::graphics->Allocate(UPLOAD, ibSize, &indexBufferUpload);
    Engine::graphics->Allocate(GPU, ibSize, &indexBufferGPU);

    // copia índices para o buffer da GPU usando o buffer de Upload
    Engine::graphics->Copy(ib, ibSize, indexBufferUpload, indexBufferGPU);
}

// -------------------------------------------------------------------------------

void Mesh::ConstantBuffer(uint objSize, uint objCount)
{
    // ---------------
    // Constant Buffer  
    // ---------------

    // o tamanho dos constant buffers precisam ser múltiplos 
    // do tamanho de alocação mínima do hardware (256 bytes)
    cbufferElementSize = (objSize + 255) & ~255;

    // aloca recursos para o constant buffer
    Engine::graphics->Allocate(CBUFFER, cbufferElementSize * objCount, &cbufferUpload);

    // mapeia memória do upload buffer para um endereço acessível pela CPU
    cbufferUpload->Map(0, nullptr, reinterpret_cast<void**>(&cbufferData));

    // ----------------
    // Descriptor Heaps 
    // ----------------

    // descritor do buffer constante
    D3D12_DESCRIPTOR_HEAP_DESC cbHeapDesc = {};
    cbHeapDesc.NumDescriptors = objCount;
    cbHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    cbHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

    // cria heap de descritores para buffer constante
    Engine::graphics->Device()->CreateDescriptorHeap(
        &cbHeapDesc, 
        IID_PPV_ARGS(&cbufferHeap));

    // tamanho de um descritor de constant buffer
    cbufferDescriptorSize = 
        Engine::graphics->Device()->GetDescriptorHandleIncrementSize(
            D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

    // precisa de um descritor para cada objeto
    for (uint i = 0; i < objCount; ++i)
    {
        // desloca para o endereço do i-ésimo objeto no buffer constante
        D3D12_GPU_VIRTUAL_ADDRESS cbAddress = cbufferUpload->GetGPUVirtualAddress();
        cbAddress += i * cbufferElementSize;

        // desloca para o endereço do i-ésimo objeto na heap de descritores
        D3D12_CPU_DESCRIPTOR_HANDLE handle = cbufferHeap->GetCPUDescriptorHandleForHeapStart();
        handle.ptr += i * cbufferDescriptorSize;

        // informações do constant buffer
        D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
        cbvDesc.BufferLocation = cbAddress;
        cbvDesc.SizeInBytes = cbufferElementSize;

        // cria uma view para o buffer constante
        Engine::graphics->Device()->CreateConstantBufferView(&cbvDesc, handle);
    }
}

// -------------------------------------------------------------------------------

void Mesh::CopyConstants(const void* cbData, uint cbIndex)
{
    memcpy(cbufferData + (cbIndex * cbufferElementSize), cbData, cbufferElementSize);
}

// -------------------------------------------------------------------------------

D3D12_VERTEX_BUFFER_VIEW* Mesh::VertexBufferView()
{
    vertexBufferView.BufferLocation = vertexBufferGPU->GetGPUVirtualAddress();
    vertexBufferView.StrideInBytes = vertexBufferStride;
    vertexBufferView.SizeInBytes = vertexBufferSize;

    return &vertexBufferView;
}

// -------------------------------------------------------------------------------

D3D12_INDEX_BUFFER_VIEW * Mesh::IndexBufferView()
{
    indexBufferView.BufferLocation = indexBufferGPU->GetGPUVirtualAddress();
    indexBufferView.Format = indexFormat;
    indexBufferView.SizeInBytes = indexBufferSize;

    return &indexBufferView;
}

// -------------------------------------------------------------------------------

ID3D12DescriptorHeap* Mesh::ConstantBufferHeap()
{
    return cbufferHeap;
}

// -------------------------------------------------------------------------------

D3D12_GPU_DESCRIPTOR_HANDLE Mesh::ConstantBufferHandle(uint cbIndex)
{
    D3D12_GPU_DESCRIPTOR_HANDLE handle = cbufferHeap->GetGPUDescriptorHandleForHeapStart();
    handle.ptr += cbIndex * cbufferDescriptorSize;
    return handle;
}

// -------------------------------------------------------------------------------

