/**********************************************************************************
// Object (Arquivo de Cabeçalho)
//
// Criação:     14 Out 2022
// Atualização: 15 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Define armazenamento para objeto de uma cena
//
**********************************************************************************/

#ifndef DXUT_OBJECT_H_
#define DXUT_OBJECT_H_

#include "Types.h"
#include "Mesh.h"
#include <DirectXMath.h>
using DirectX::XMFLOAT4X4;

struct Object
{
	XMFLOAT4X4 world = {            // matriz de mundo
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f };

	uint cbIndex = -1;			    // índice para o constant buffer
	Mesh * mesh = nullptr;			// malha de vértices
	SubMesh submesh {};	            // informações da sub-malha
};

#endif
