#include "CUI.h"

CUI::CUI(LPDIRECT3DDEVICE9 pGraphicDev) : CGameObject(pGraphicDev)
{

}

CUI::~CUI()
{
}

HRESULT CUI::Ready_GameObject()
{
	return S_OK;
}

_int CUI::Update_GameObject(const _float& fTimeDelta)
{
	return 0;
}

void CUI::LateUpdate_GameObject()
{
	CGameObject::LateUpdate_GameObject();
}

void CUI::Free()
{
	CGameObject::Free();
}
