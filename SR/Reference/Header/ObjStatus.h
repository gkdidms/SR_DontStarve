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
    // CComponent을(를) 통해 상속됨
    CComponent* Clone() override;
};

END