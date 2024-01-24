#pragma once

#include "Camera.h"

class CDynamicCamera : public Engine::CCamera
{
private:
	explicit CDynamicCamera(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CDynamicCamera();

public:
	HRESULT Ready_GameObject(const _vec3* pEye,
		const _vec3* pAt,
		const _vec3* pUp,
		const _float& fFov,
		const _float& fAspect,
		const _float& fNear,
		const _float& fFar);

	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;

private:
	void		Key_Input(const _float& fTimeDelta);
	void		Mouse_Fix();
	void		Mouse_Move();

public:
	void		SetTarget(CGameObject* _targetObj) { m_pTarget = _targetObj; }

private:
	_bool		m_bFix = false;
	_bool		m_bCheck = false;
	CGameObject* m_pTarget = nullptr;


	_float	m_fAngle;		//����
	_float	m_fDistance;	//�Ÿ�
	_float	m_fHeight;		//����
	_bool	m_bkeyInput;
public:
	static CDynamicCamera* Create(LPDIRECT3DDEVICE9 pGraphicDev,
		const _vec3* pEye,
		const _vec3* pAt,
		const _vec3* pUp,
		const _float& fFov,
		const _float& fAspect,
		const _float& fNear,
		const _float& fFar);

private:
	virtual void Free();

};

