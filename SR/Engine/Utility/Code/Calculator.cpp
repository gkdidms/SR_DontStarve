#include "..\..\Header\Calculator.h"

#include "Export_Utility.h"

CCalculator::CCalculator(LPDIRECT3DDEVICE9 pGraphicDev)
	:CComponent(pGraphicDev)
{
}

CCalculator::~CCalculator()
{
}

HRESULT CCalculator::Ready_Calculator()
{
	return S_OK;
}

_float CCalculator::Compute_HeightOnTerrain(const _vec3 * pPos,
											const _vec3 * pTerrainVtxPos,
											const _ulong & dwCntX, 
											const _ulong & dwCntZ,
											const _ulong& dwVtxItv)
{

	_ulong	dwIndex = _ulong(pPos->z / dwVtxItv) * dwCntX + _ulong(pPos->x / dwVtxItv);

	_float	fRatioX = _float(pPos->x - pTerrainVtxPos[dwIndex + dwCntX].x) / dwVtxItv;
	_float	fRatioZ = _float(pTerrainVtxPos[dwIndex + dwCntX].z - pPos->z) / dwVtxItv;

	D3DXPLANE	Plane;

	// ������ ��
	if (fRatioX > fRatioZ)
	{
		D3DXPlaneFromPoints(&Plane,
			&pTerrainVtxPos[dwIndex + dwCntX],
			&pTerrainVtxPos[dwIndex + dwCntX + 1],
			&pTerrainVtxPos[dwIndex + 1]);
	}
	 // ���� �Ʒ� 
	else
	{
		D3DXPlaneFromPoints(&Plane,
			&pTerrainVtxPos[dwIndex + dwCntX],
			&pTerrainVtxPos[dwIndex + 1],
			&pTerrainVtxPos[dwIndex]);
	}

	// Y = (-AX -CZ - D) / B


	return  (-Plane.a * pPos->x - Plane.c * pPos->z - Plane.d) / Plane.b;
}

_vec3 CCalculator::Picking_OnTerrain(HWND hWnd,
									CTerrainTex * pTerrainBufferCom,
									CTransform * pTerrainTransCom,
									const _ulong& dwCntX,
									const _ulong& dwCntZ)
{
	POINT		ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(hWnd, &ptMouse);

	// ����Ʈ -> ����

	D3DVIEWPORT9		ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));
	m_pGraphicDev->GetViewport(&ViewPort);

	_vec3		vMousePos;

	vMousePos.x = ptMouse.x / (ViewPort.Width * 0.5f) - 1.f;
	vMousePos.y = ptMouse.y / -(ViewPort.Height * 0.5f) + 1.f;

	vMousePos.z = 0.f;

	// ���� -> �佺���̽�
	_matrix	matProj;
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixInverse(&matProj, NULL, &matProj);
	D3DXVec3TransformCoord(&vMousePos, &vMousePos, &matProj);

	// �� �����̽� -> ����
	_matrix	matView;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, NULL, &matView);

	_vec3	vRayDir, vRayPos;

	vRayPos = { 0.f, 0.f, 0.f };
	vRayDir = vMousePos - vRayPos;

	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matView);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matView);

	// ���� -> ����
	_matrix		matWorld;
	pTerrainTransCom->Get_WorldMatrix(&matWorld);
	D3DXMatrixInverse(&matWorld, NULL, &matWorld);

	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matWorld);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matWorld);

	const _vec3*		pTerrainVtxPos = pTerrainBufferCom->Get_VtxPos();

	_ulong	dwVtxIdx[3]{};
	_float	fU(0.f), fV(0.f), fDist(0.f);

	for (_ulong i = 0; i < dwCntZ - 1; ++i)
	{
		for (_ulong j = 0; j < dwCntX - 1; ++j)
		{
			_ulong	dwIndex = i * dwCntX + j;

			// ������ ��

			dwVtxIdx[0] = dwIndex + dwCntX;
			dwVtxIdx[1] = dwIndex + dwCntX + 1;
			dwVtxIdx[2] = dwIndex + 1;

			if (D3DXIntersectTri(&pTerrainVtxPos[dwVtxIdx[1]], 
			&pTerrainVtxPos[dwVtxIdx[0]],
			&pTerrainVtxPos[dwVtxIdx[2]],
			&vRayPos, &vRayDir, 
			&fU, &fV, &fDist))
			{
				return _vec3(pTerrainVtxPos[dwVtxIdx[1]].x + fU * (pTerrainVtxPos[dwVtxIdx[0]].x - pTerrainVtxPos[dwVtxIdx[1]].x),
							0.f,
							pTerrainVtxPos[dwVtxIdx[1]].z + fV * (pTerrainVtxPos[dwVtxIdx[2]].z - pTerrainVtxPos[dwVtxIdx[0]].z));
			}

			// V1 + U(V2 - V1) + V(V3 - V1)

			// ���� �Ʒ�
			dwVtxIdx[0] = dwIndex + dwCntX;
			dwVtxIdx[1] = dwIndex + 1;
			dwVtxIdx[2] = dwIndex;

			if (D3DXIntersectTri(&pTerrainVtxPos[dwVtxIdx[2]],
				&pTerrainVtxPos[dwVtxIdx[1]],
				&pTerrainVtxPos[dwVtxIdx[0]],
				&vRayPos, &vRayDir,
				&fU, &fV, &fDist))
			{
				return _vec3(pTerrainVtxPos[dwVtxIdx[2]].x + fU * (pTerrainVtxPos[dwVtxIdx[1]].x - pTerrainVtxPos[dwVtxIdx[2]].x),
							 0.f,
							 pTerrainVtxPos[dwVtxIdx[2]].z + fV * (pTerrainVtxPos[dwVtxIdx[0]].z - pTerrainVtxPos[dwVtxIdx[2]].z));
			}
		}
	}



	return _vec3(0.f, 0.f, 0.f);
}

CCalculator * CCalculator::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCalculator*		pInstance = new CCalculator(pGraphicDev);

	if (FAILED(pInstance->Ready_Calculator()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Calculator Create Failed");
		return nullptr;
	}
	
	return pInstance;
}

CComponent * CCalculator::Clone(void)
{
	return new CCalculator(*this);
}

void CCalculator::Free()
{
	CComponent::Free();
}
