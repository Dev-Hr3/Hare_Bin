#pragma once

// bool GrannyMeshGetTextureAnimation(granny_mesh* pgrnMesh, float* puVelocity, float* pvVelocity);
// bool GrannyMeshIsTextureAnimation(granny_mesh* pgrnMesh);
bool GrannyMeshIsDeform(granny_mesh* pgrnMesh);

class CGraphicImage;

struct SMaterialData
{
	CGraphicImage * pImage;
	float fSpecularPower;
	BOOL isSpecularEnable;
	BYTE bSphereMapIndex;
};
//martysama0134's a288e6779da68f768431f9975e780da3
