/*************************************************************************
Crytek Source File.
Copyright (C), Crytek Studios, 2001-2004.
-------------------------------------------------------------------------
$Id$
$DateTime$
Description: Rapid Fire Mode Implementation

-------------------------------------------------------------------------
History:
- 26:10:2005   14:15 : Created by M�rcio Martins

*************************************************************************/
#ifndef __RAPID_H__
#define __RAPID_H__

#if _MSC_VER > 1000
# pragma once
#endif


#include "Single.h"

class CRapidSharedData;

class CRapid : public CSingle
{
public:
	typedef struct SRapidParams
	{
		SRapidParams() { Reset(); };
		void Reset(const IItemParamsNode *params=0, bool defaultInit=true)
		{
			CItemParamReader reader(params);
			ResetValue(min_speed,	1.5f);
			ResetValue(max_speed,	3.0f);
			ResetValue(acceleration,	3.0f);
			ResetValue(deceleration,	-3.0f);
			ResetValue(barrel_attachment,	"");
			ResetValue(engine_attachment,	"");      
			ResetValue(camshake_rotate,	Vec3(0));
      ResetValue(camshake_shift,	Vec3(0));
			ResetValue(camshake_perShot,	0.0f);
		}

		void GetMemoryUsage(ICrySizer * s) const
		{
			s->Add(barrel_attachment);
			s->Add(engine_attachment);
		}

    Vec3 camshake_rotate;
    Vec3 camshake_shift;
    float camshake_perShot;
		float min_speed;
		float max_speed;
		float acceleration;
		float	deceleration;
		ItemString barrel_attachment;
		ItemString engine_attachment;		

	} SRapidParams;

	typedef struct SRapidActions
	{
		SRapidActions() { Reset(); };
		void Reset(const IItemParamsNode *params=0, bool defaultInit=true)
		{
			CItemParamReader reader(params);
			ResetValue(rapid_fire,"rapid_fire");
			ResetValue(blast,			"blast");
		}

		void GetMemoryUsage(ICrySizer * s) const
		{
			s->Add(rapid_fire);
			s->Add(blast);
		}

		ItemString rapid_fire;
		ItemString blast;

	} SRapidActions;

public:
	CRapid();
	virtual ~CRapid();

	// CSingle
	virtual void Update(float frameTime, uint32 frameId);

	virtual void ResetParams(const struct IItemParamsNode *params);
	virtual void PatchParams(const struct IItemParamsNode *patch);

	virtual void GetMemoryUsage(ICrySizer * s) const;

	virtual void Activate(bool activate);

	virtual void StartReload(int zoomed);

	virtual void StartFire();
	virtual void StopFire();
  virtual bool IsFiring() const { return m_firing || m_accelerating; };
	virtual bool IsSilenced() const { return false; } // compile fix, no guarantee of functionality

	virtual void NetStartFire();
	virtual void NetStopFire();

	virtual float GetSpinUpTime() const;
	virtual float GetSpinDownTime() const;

	virtual bool AllowZoom() const;

	virtual const char *GetType() const;
	virtual int PlayActionSAFlags(int flags) { return (flags | CItem::eIPAF_Animation) & ~CItem::eIPAF_Sound; };

	virtual void InitSharedParams();
	virtual void CacheSharedParamsPtr();
	// ~CSingle

protected:
	virtual void Accelerate(float acc);
	virtual void Firing(bool firing);
	virtual void UpdateRotation(float frameTime);
	virtual void UpdateSound(float frameTime);
  virtual void FinishDeceleration();

	float	m_speed;
	float	m_acceleration;
	float m_rotation_angle;
	
	bool	m_netshooting;

	bool	m_accelerating;
	bool	m_decelerating;

	uint32	m_soundId;
	uint32	m_spinUpSoundId;

	bool  m_startedToFire;

private:
	CRapidSharedData*	m_pShared;

};

class CRapidSharedData: public CSingleSharedData
{
public:
	CRapidSharedData(){};
	virtual ~CRapidSharedData(){};

	virtual const char* GetDataType() const { return "RapidData"; }
	virtual void GetMemoryUsage(ICrySizer* s) const
	{
		s->Add(*this);
		rapidactions.GetMemoryUsage(s);
		rapidparams.GetMemoryUsage(s);
		CSingleSharedData::GetMemoryUsage(s);
	}

	CRapid::SRapidActions rapidactions;
	CRapid::SRapidParams	rapidparams;
};
#endif