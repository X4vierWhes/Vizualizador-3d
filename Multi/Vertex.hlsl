/**********************************************************************************
// Vertex (Arquivo de Sombreamento)
//
// Criação:     22 Jul 2020
// Atualização: 08 Set 2023
// Compilador:  Direct3D Shader Compiler (FXC)
//
// Descrição:   Um vertex shader que faz a transformação de vértices
//              a partir de uma matriz combinada WorldViewProj fornecida
//
**********************************************************************************/

cbuffer Object
{
    float4x4 WorldViewProj;
};

struct VertexIn
{
    float3 PosL  : POSITION;
    float4 Color : COLOR;
};

struct VertexOut
{
    float4 PosH  : SV_POSITION;
    float4 Color : COLOR;
};

VertexOut main(VertexIn vin)
{
    VertexOut vout;

    // transforma para espaço homogêneo de recorte
    vout.PosH = mul(float4(vin.PosL, 1.0f), WorldViewProj);

    // apenas passa a cor do vértice para o pixel shader
    vout.Color = vin.Color;

    return vout;
}