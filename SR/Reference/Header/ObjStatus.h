#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CObjStatus :
    public CComponent
{
private:
    explicit CObjStatus();
    explicit CObjStatus(LPDIRECT3DDEVICE9 pGraphicDev);
    virtual ~CObjStatus();
    // CComponent��(��) ���� ��ӵ�
    CComponent* Clone() override;
};

END