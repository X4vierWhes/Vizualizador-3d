/**********************************************************************************
// Pixel (Arquivo de Sombreamento)
//
// Criação:     22 Jul 2020
// Atualização: 08 Set 2023
// Compilador:  Direct3D Shader Compiler (FXC)
//
// Descrição:   Um pixel shader simples que apenas passa a cor do pixel
//              para frente sem realizar nenhuma modificação.
//
**********************************************************************************/

struct pixelIn
{
    float4 PosH  : SV_POSITION;
    float4 Color : COLOR;
};

float4 main(pixelIn pIn) : SV_TARGET
{
    return pIn.Color;
}