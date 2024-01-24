#include "ObjStatus.h"

CObjStatus::CObjStatus()
{
}

CObjStatus::CObjStatus(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComponent(pGraphicDev)
{
}

CObjStatus::~CObjStatus()
{
}

CComponent* CObjStatus::Clone()
{
	return new CObjStatus(*this);
}
