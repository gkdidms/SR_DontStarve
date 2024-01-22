#pragma once
#include "Component.h"

BEGIN(Engine)

class CTerrainTex;
class CTransform;

class ENGINE_DLL CCalculator : public CComponent
{
private:
	explicit CCalculator(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CCalculator();

public:
	HRESULT		Ready_Calculator();
	_float		Compute_HeightOnTerrain(const _vec3* pPos, const _vec3* pTerrainVtxPos, const _ulong& dwCntX = VTXCNTX, const _ulong& dwCntZ = VTXCNTZ, const _ulong& dwVtxItv = VTXITV);

	_vec3		Picking_OnTerrain(HWND hWnd, 
		CTerrainTex* pTerrainBufferCom, 
		CTransform* pTerrainTransCom,
		const _ulong& dwCntX = VTXCNTX, 
		const _ulong& dwCntZ = VTXCNTZ);

public:
	static CCalculator*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	CComponent*				Clone(void);

private:
	virtual void	Free();
};

END