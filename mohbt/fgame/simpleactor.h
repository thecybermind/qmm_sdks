/*
===========================================================================
Copyright (C) 2015 the OpenMoHAA team

This file is part of OpenMoHAA source code.

OpenMoHAA source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

OpenMoHAA source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OpenMoHAA source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/

// simpleactor.h: Base class for character AI.

#pragma once

#include "weapon.h"
#include "sentient.h"
#include "container.h"
#include "stack.h"
#include "navigate.h"
#include "scriptmaster.h"
#include "characterstate.h"
#include "actorpath.h"

enum eEmotionMode {
    EMOTION_NONE,
    EMOTION_NEUTRAL,
    EMOTION_WORRY,
    EMOTION_PANIC,
    EMOTION_FEAR,
    EMOTION_DISGUST,
    EMOTION_ANGER,
    EMOTION_AIMING,
    EMOTION_DETERMINED,
    EMOTION_DEAD,
    EMOTION_CURIOUS
};

enum eAnimMode {
    ANIM_MODE_NONE,
    ANIM_MODE_NORMAL,
    ANIM_MODE_PATH,
    ANIM_MODE_PATH_GOAL,
    ANIM_MODE_DEST,
    ANIM_MODE_SCRIPTED,
    ANIM_MODE_NOCLIP,
    ANIM_MODE_FALLING_PATH,
    ANIM_MODE_FROZEN,
    ANIM_MODE_ATTACHED,
};

enum eAnimWeightType {
    ANIM_WEIGHT_NONE,
    ANIM_WEIGHT_MOTION,
    ANIM_WEIGHT_ACTION,
    ANIM_WEIGHT_CROSSBLEND_1,
    ANIM_WEIGHT_CROSSBLEND_2,
    ANIM_WEIGHT_CROSSBLEND_DIALOG,
    ANIM_WEIGHT_SAY,
    ANIM_WEIGHT_AIM,
    ANIM_WEIGHT_LASTFRAME,
};

class SimpleActor;

typedef SafePtr<SimpleActor> SimpleActorPtr;

class SimpleActor : public Sentient
{
public:
    int                   m_eAnimMode;
    ScriptThreadLabel     m_Anim;
    SafePtr<ScriptThread> m_pAnimThread;
    int                   m_eNextAnimMode;
    const_str             m_csNextAnimString;
    ScriptThreadLabel     m_NextAnimLabel;
    bool                  m_bNextForceStart;
    float                 m_fCrouchWeight;
    bool                  m_YawAchieved;
    float                 m_DesiredYaw;
    bool                  m_bHasDesiredLookDest;
    bool                  m_bHasDesiredLookAngles;
    Vector                m_vDesiredLookDest;
    Vector                m_DesiredLookAngles;
    Vector                m_DesiredGunDir;
    ActorPath             m_Path;
    float                 m_Dest[3];
    float                 m_NoClipDest[3];
    float                 path_failed_time;
    float                 m_fPathGoalTime;
    bool                  m_bStartPathGoalEndAnim;
    const_str             m_csPathGoalEndAnimScript;
    qboolean              m_walking;
    qboolean              m_groundPlane;
    vec3_t                m_groundPlaneNormal;
    Vector                watch_offset;
    bool                  m_bThink;
    int                   m_PainTime;
    eEmotionMode          m_eEmotionMode;
    float                 m_fAimLimit_up;
    float                 m_fAimLimit_down;
    int                   m_ChangeMotionAnimIndex;
    int                   m_ChangeActionAnimIndex;
    int                   m_ChangeSayAnimIndex;

protected:
    unsigned int m_weightType[MAX_FRAMEINFOS];
    float        m_weightBase[MAX_FRAMEINFOS];
    float        m_weightCrossBlend[MAX_FRAMEINFOS];
    bool         m_AnimMotionHigh;
    bool         m_AnimActionHigh;
    bool         m_AnimDialogHigh;

public:
    int               hit_obstacle_time;
    float             obstacle_vel[2];
    const_str         m_csAnimName;
    const_str         m_csSayAnim;
    const_str         m_csUpperAnim;
    const_str         m_csCurrentPosition;
    int               m_bPathErrorTime;
    class PathNode   *m_NearestNode;
    Vector            m_vNearestNodePos;
    short             m_bUpdateAnimDoneFlags;
    float             m_maxspeed;
    const_str         m_csMood;
    const_str         m_csIdleMood;
    int               m_iMotionSlot;
    int               m_iActionSlot;
    int               m_iSaySlot;
    bool              m_bLevelMotionAnim;
    bool              m_bLevelActionAnim;
    byte              m_bLevelSayAnim;
    byte              m_bNextLevelSayAnim;
    bool              m_bMotionAnimSet;
    bool              m_bActionAnimSet;
    bool              m_bSayAnimSet;
    bool              m_bAimAnimSet;
    int               m_iVoiceTime;
    bool              m_bDoAI;
    ScriptThreadLabel m_PainHandler;
    ScriptThreadLabel m_DeathHandler;
    ScriptThreadLabel m_AttackHandler;
    ScriptThreadLabel m_SniperHandler;
    float             m_fCrossblendTime;

public:
    CLASS_PROTOTYPE(SimpleActor);

    SimpleActor();
    ~SimpleActor();

    void         Archive(Archiver        &arc) override;
    virtual void SetMoveInfo(mmove_t *mm);
    virtual void GetMoveInfo(mmove_t *mm);
    bool         CanSeeFrom(vec3_t pos, Entity *ent);
    virtual bool CanTarget(void);
    virtual bool IsImmortal(void);
    bool         DoesTheoreticPathExist(Vector vDestPos, float fMaxPath);
    void
    SetPath(Vector vDestPos, const char *description, int iMaxDirtyTime, float *vLeashHome, float fLeashDistSquared);
    void                SetPath(SimpleEntity *pDestNode, const char *description, int iMaxDirtyTime);
    void                SetPathWithinDistance(Vector vDestPos, char *description, float fMaxPath, int iMaxDirtyTime);
    void                FindPathAway(vec3_t vAwayFrom, vec2_t vDirPreferred, float fMinSafeDist);
    void                ClearPath(void);
    bool                PathComplete(void) const;
    bool                PathExists(void) const;
    bool                PathIsValid(void) const;
    bool                PathAvoidsSquadMates(void) const;
    void                ShortenPathToAvoidSquadMates(void);
    PathInfo           *CurrentPathNode(void) const;
    PathInfo           *LastPathNode(void) const;
    float               PathDist(void) const;
    bool                PathHasCompleteLookahead(void) const;
    Vector              PathGoal(void) const;
    const float        *PathDelta(void) const;
    bool                PathGoalSlowdownStarted(void) const;
    void                SetDest(vec3_t dest);
    void                StopTurning(void);
    void                SetDesiredYaw(float yaw);
    void                SetDesiredYawDir(const vec2_t vec);
    void                SetDesiredYawDest(const vec3_t vec);
    void                UpdateEmotion(void);
    int                 GetEmotionAnim(void);
    int                 GetMotionSlot(int slot);
    int                 GetActionSlot(int slot);
    int                 GetSaySlot(void);
    void                StartCrossBlendAnimSlot(int slot);
    void                StartMotionAnimSlot(int slot, int anim, float weight);
    void                StartAimMotionAnimSlot(int slot, int anim);
    void                StartActionAnimSlot(int anim);
    void                StartSayAnimSlot(int anim);
    void                StartAimAnimSlot(int slot, int anim);
    void                SetBlendedWeight(int slot);
    void                EventSetAnimLength(Event *ev);
    void                UpdateNormalAnimSlot(int slot);
    void                UpdateCrossBlendAnimSlot(int slot);
    void                UpdateCrossBlendDialogAnimSlot(int slot);
    void                UpdateSayAnimSlot(int slot);
    void                UpdateLastFrameSlot(int slot);
    void                UpdateAnimSlot(int slot);
    void                StopAllAnimating(void);
    void                ChangeMotionAnim(void);
    void                ChangeActionAnim(void);
    void                ChangeSayAnim(void);
    void                StopAnimating(int slot);
    void                AnimFinished(int slot) override;
    void                UpdateAim(void);
    void                UpdateAimMotion(void);
    void                EventAIOn(Event *ev);
    void                EventAIOff(Event *ev);
    void                EventGetWeaponGroup(Event *ev);
    void                EventGetWeaponType(Event *ev);
    void                EventGetPainHandler(Event *ev);
    void                EventSetPainHandler(Event *ev);
    void                EventGetDeathHandler(Event *ev);
    void                EventSetDeathHandler(Event *ev);
    void                EventGetAttackHandler(Event *ev);
    void                EventSetAttackHandler(Event *ev);
    void                EventGetSniperHandler(Event *ev);
    void                EventSetSniperHandler(Event *ev);
    void                EventSetCrossblendTime(Event *ev);
    void                EventGetCrossblendTime(Event *ev);
    void                EventSetEmotion(Event *ev);
    void                EventGetPosition(Event *ev);
    void                EventSetPosition(Event *ev);
    void                EventGetAnimMode(Event *ev);
    void                EventSetAnimMode(Event *ev);
    void                EventSetAnimFinal(Event *ev);
    void                EventNoAnimLerp(Event *ev); // Added in 2.0
    const_str           GetRunAnim(void);
    const_str           GetWalkAnim(void);
    void                DesiredAnimation(int eAnimMode, const_str csAnimString);
    void                StartAnimation(int eAnimMode, const_str csAnimString);
    void                DesiredAnimation(int eAnimMode, ScriptThreadLabel AnimLabel);
    void                StartAnimation(int eAnimMode, ScriptThreadLabel AnimLabel);
    void                ContinueAnimationAllowNoPath(void);
    void                ContinueAnimation(void);
    void                SetPathGoalEndAnim(const_str csEndAnim);
    bool                UpdateSelectedAnimation(void);
    void                Anim_Attack(void);
    void                Anim_Suppress(void); // Added in 2.0
    void                Anim_Sniper(void);
    void                Anim_Aim(void);
    void                Anim_Shoot(void);
    void                Anim_Idle(void);
    void                Anim_Crouch(void);
    void                Anim_Prone(void);
    void                Anim_Stand(void);
    void                Anim_Cower(void);
    void                Anim_Killed(void);
    void                Anim_StartPain(void);
    void                Anim_Pain(void);
    void                Anim_CrouchRunTo(int eAnimMode);
    void                Anim_CrouchWalkTo(int eAnimMode);
    void                Anim_StandRunTo(int eAnimMode);
    void                Anim_StandWalkTo(int eAnimMode);
    void                Anim_RunTo(int eAnimMode);
    void                Anim_WalkTo(int eAnimMode);
    void                Anim_RunAwayFiring(int eAnimMode);
    void                Anim_RunToShooting(int eAnimMode);
    void                Anim_RunToAlarm(int eAnimMode);
    void                Anim_RunToCasual(int eAnimMode);
    void                Anim_RunToCover(int eAnimMode);
    void                Anim_RunToDanger(int eAnimMode);
    void                Anim_RunToDive(int eAnimMode);
    void                Anim_RunToFlee(int eAnimMode);
    void                Anim_RunToInOpen(int eAnimMode);
    void                Anim_Emotion(eEmotionMode eEmotMode);
    void                Anim_Say(const_str csSayAnimScript, int iMinTimeSinceLastSay, bool bCanInterrupt);
    void                Anim_FullBody(const_str csFullBodyAnim, int eAnimMode);
    virtual const char *DumpCallTrace(const char *pszFmt, ...) const;
};

inline void SimpleActor::StartAnimation(int eAnimMode, const_str csAnimString)
{
    m_eNextAnimMode    = eAnimMode;
    m_csNextAnimString = csAnimString;
    m_bNextForceStart  = true;
}

inline void SimpleActor::DesiredAnimation(int eAnimMode, const_str csAnimString)
{
    m_eNextAnimMode    = eAnimMode;
    m_csNextAnimString = csAnimString;
    m_bNextForceStart  = false;
}

inline void SimpleActor::StartAnimation(int eAnimMode, ScriptThreadLabel AnimLabel)
{
    m_eNextAnimMode    = eAnimMode;
    m_csNextAnimString = STRING_NULL;
    m_NextAnimLabel    = AnimLabel;
    m_bNextForceStart  = true;
}

inline void SimpleActor::DesiredAnimation(int eAnimMode, ScriptThreadLabel AnimLabel)
{
    m_eNextAnimMode    = eAnimMode;
    m_csNextAnimString = STRING_NULL;
    m_NextAnimLabel    = AnimLabel;
    m_bNextForceStart  = false;
}

inline void SimpleActor::ContinueAnimationAllowNoPath(void)
{
    if (m_eNextAnimMode < ANIM_MODE_NONE) {
        m_eNextAnimMode    = m_eAnimMode;
        m_csNextAnimString = STRING_NULL;
        m_NextAnimLabel    = m_Anim;
        m_bNextForceStart  = false;
    }
}

inline void SimpleActor::ContinueAnimation(void)
{
    ContinueAnimationAllowNoPath();

    if ((m_eNextAnimMode == ANIM_MODE_PATH || m_eNextAnimMode == ANIM_MODE_PATH_GOAL) && !PathExists()) {
        assert(!"ContinueAnimation() called on a pathed animation, but no path exists");
        Anim_Stand();
    }
}

inline void SimpleActor::SetPathGoalEndAnim(const_str csEndAnim)
{
    m_csPathGoalEndAnimScript = csEndAnim;
}

inline void SimpleActor::Archive(Archiver& arc)
{
    int i;

    Sentient::Archive(arc);

    arc.ArchiveInteger(&m_eAnimMode);
    m_Anim.Archive(arc);

    arc.ArchiveBool(&m_bHasDesiredLookDest);
    arc.ArchiveBool(&m_bHasDesiredLookAngles);
    arc.ArchiveVector(&m_vDesiredLookDest);
    arc.ArchiveVec3(m_DesiredLookAngles);
    arc.ArchiveVec3(m_DesiredGunDir);

    m_Path.Archive(arc);
    arc.ArchiveVec3(m_Dest);
    arc.ArchiveVec3(m_NoClipDest);

    arc.ArchiveFloat(&path_failed_time);
    arc.ArchiveFloat(&m_fPathGoalTime);
    arc.ArchiveBool(&m_bStartPathGoalEndAnim);
    Director.ArchiveString(arc, m_csPathGoalEndAnimScript);

    arc.ArchiveInteger(&m_eNextAnimMode);
    Director.ArchiveString(arc, m_csNextAnimString);
    m_NextAnimLabel.Archive(arc);
    arc.ArchiveBool(&m_bNextForceStart);

    arc.ArchiveBoolean(&m_walking);
    arc.ArchiveBoolean(&m_groundPlane);
    arc.ArchiveVec3(m_groundPlaneNormal);

    arc.ArchiveVector(&watch_offset);
    arc.ArchiveBool(&m_bThink);
    arc.ArchiveInteger(&m_PainTime);

    arc.ArchiveBool(&m_bAimAnimSet);
    arc.ArchiveBool(&m_bActionAnimSet);

    Director.ArchiveString(arc, m_csMood);
    Director.ArchiveString(arc, m_csIdleMood);

    ArchiveEnum(m_eEmotionMode, eEmotionMode);

    arc.ArchiveFloat(&m_fAimLimit_up);
    arc.ArchiveFloat(&m_fAimLimit_down);

    for (i = 0; i < MAX_FRAMEINFOS; i++) {
        arc.ArchiveUnsigned(&m_weightType[i]);
    }

    for (i = 0; i < MAX_FRAMEINFOS; i++) {
        arc.ArchiveFloat(&m_weightBase[i]);
    }

    for (i = 0; i < MAX_FRAMEINFOS; i++) {
        arc.ArchiveFloat(&m_weightCrossBlend[i]);
    }

    arc.ArchiveBool(&m_AnimMotionHigh);
    arc.ArchiveBool(&m_AnimActionHigh);
    arc.ArchiveBool(&m_AnimDialogHigh);

    arc.ArchiveVec2(obstacle_vel);

    Director.ArchiveString(arc, m_csCurrentPosition);

    arc.ArchiveBool(&m_bMotionAnimSet);
    arc.ArchiveBool(&m_bDoAI);

    arc.ArchiveFloat(&m_fCrossblendTime);

    arc.ArchiveSafePointer(&m_pAnimThread);

    arc.ArchiveBool(&m_YawAchieved);
    arc.ArchiveFloat(&m_DesiredYaw);

    arc.ArchiveInteger(&m_iVoiceTime);
    arc.ArchiveBool(&m_bSayAnimSet);

    arc.ArchiveInteger(&hit_obstacle_time);

    Director.ArchiveString(arc, m_csAnimName);

    arc.ArchiveInteger(&m_bPathErrorTime);
    arc.ArchiveInteger(&m_iMotionSlot);
    arc.ArchiveInteger(&m_iActionSlot);
    arc.ArchiveInteger(&m_iSaySlot);

    arc.ArchiveBool(&m_bLevelMotionAnim);
    arc.ArchiveBool(&m_bLevelActionAnim);
    arc.ArchiveByte(&m_bLevelSayAnim);
    arc.ArchiveByte(&m_bNextLevelSayAnim);

    Director.ArchiveString(arc, m_csSayAnim);
    Director.ArchiveString(arc, m_csUpperAnim);

    m_PainHandler.Archive(arc);
    m_DeathHandler.Archive(arc);
    m_AttackHandler.Archive(arc);
    m_SniperHandler.Archive(arc);

    arc.ArchiveObjectPointer((Class **)&m_NearestNode);
    arc.ArchiveVector(&m_vNearestNodePos);

    arc.ArchiveFloat(&m_fCrouchWeight);
    arc.ArchiveFloat(&m_maxspeed);
}

inline void SimpleActor::StopTurning(void)
{
    m_YawAchieved = true;
}

inline void SimpleActor::SetDesiredYaw(float yaw)
{
    m_YawAchieved = false;
    m_DesiredYaw  = yaw;
}

inline void SimpleActor::SetDesiredYawDir(const vec2_t vec)
{
    SetDesiredYaw(vectoyaw(vec));
}

inline void SimpleActor::SetDesiredYawDest(const vec3_t vec)
{
    vec2_t facedir;
    VectorSub2D(vec, origin, facedir);

    if (facedir[0] || facedir[1]) {
        SetDesiredYawDir(facedir);
    }
}

inline void SimpleActor::SetDest(vec3_t dest)
{
    VectorCopy(dest, m_Dest);
}
