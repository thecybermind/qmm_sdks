/*
===========================================================================
Copyright (C) 2023 the OpenMoHAA team

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

// scriptmaster.h: Handle events, parse scripts, spawn at the beginning of the map

#pragma once

#include "class.h"
#include "listener.h"
#include "scriptvm.h"
#include <con_timer.h>

#define MAX_COMMANDS       20
#define MAX_EXECUTION_TIME 3000

void Showmenu(const str& name, qboolean bForce);
void Hidemenu(const str& name, qboolean bForce);

#define MAX_VAR_STACK 1024
#define MAX_FASTEVENT 10

class ScriptMaster : public Listener
{
    friend class ScriptThread;

public:
    // VM recursions
    int stackCount;

    // Global stack (not needed anymore)
#if 0
	ScriptVariable	avar_Stack[ MAX_VAR_STACK+1 ];	// Global variables stack
	Event			fastEvent[ MAX_FASTEVENT+1 ];	// Event that will be executed

	ScriptVariable	*pTop;							// Top variable on the stack
#endif

    // Command variables
    unsigned int cmdCount; // cmd count
    int          cmdTime;  // Elapsed VM execution time
    int          maxTime;  // Maximum VM execution time

    // Thread variables
    SafePtr<ScriptThread> m_PreviousThread; // parm.previousthread
    SafePtr<ScriptThread> m_CurrentThread;  // current running thread

    con_map<const_str, GameScript *> m_GameScripts; // compiled gamescripts

    // Miscellaneous
    Container<str>         m_menus;    // Script menus
    con_timer              timerList;  // waiting threads list
    con_arrayset<str, str> StringDict; // const strings (improve performance)
    int                    iPaused;    // num times paused

protected:
    static const char *ConstStrings[];

protected:
    void        InitConstStrings(void);
    void        CloseGameScript();
    GameScript *GetGameScriptInternal(str& filename);
    void        ExecuteRunning();
    void        Cache(Event *ev);
    void        RegisterAliasAndCache(Event *ev);
    void        RegisterAlias(Event *ev);

public:
    CLASS_PROTOTYPE(ScriptMaster);

    ScriptMaster();
    virtual ~ScriptMaster();

    //
    // Thread executions
    //
    ScriptThread *CreateThread(GameScript *scr, str label, Listener *self = NULL);
    ScriptThread *CreateThread(str filename, str label, Listener *self = NULL);
    void          ExecuteThread(GameScript *scr, str label = "");
    void          ExecuteThread(str filename, str label = "");
    void          ExecuteThread(GameScript *scr, str label, Event         &parms);
    void          ExecuteThread(str filename, str label, Event         &parms);
    ScriptThread *CreateScriptThread(ScriptClass *scriptClass, unsigned char *m_pCodePos);
    ScriptThread *CreateScriptThread(GameScript *scr, Listener *self, const_str label);
    ScriptThread *CreateScriptThread(GameScript *scr, Listener *self, str label);
    ScriptThread *CreateScriptThread(ScriptClass *scriptClass, const_str label);
    ScriptThread *CreateScriptThread(ScriptClass *scriptClass, str label);
    void          Reset(qboolean samemap = false);
    ScriptThread *PreviousThread(void);
    ScriptThread *CurrentThread(void);
    ScriptThread *CurrentScriptThread(void);
    ScriptClass  *CurrentScriptClass(void);

    GameScript *GetGameScript(const_str filename, qboolean recompile = false);
    GameScript *GetGameScript(str filename, qboolean recompile = false);
    GameScript *GetScript(const_str filename, qboolean recompile = false);
    GameScript *GetScript(str filename, qboolean recompile = false);

    void SetTime(int time);

    void      AddTiming(ScriptThread *thread, int time);
    void      RemoveTiming(ScriptThread *thread);
    const_str AddString(const char *s);
    const_str AddString(str& s);
    const_str GetString(const char *s);
    const_str GetString(str s);
    str     & GetString(const_str s);

    void ArchiveString(Archiver& arc, const_str& s);

    void Pause();
    void Unpause();
    void AllowPause(bool allow);
    void AddMenu(str name);
    void RemoveMenu(str name);
    void LoadMenus(void);
    void Archive(Archiver& arc) override;

    GameScript *GetTempScript(const char *data);

    void PrintStatus(void);
    void PrintThread(int iThreadNum);
};

extern Event EV_RegisterAlias;
extern Event EV_RegisterAliasAndCache;
extern Event EV_Cache;

extern qboolean disable_team_change;
extern qboolean disable_team_spectate;
extern str      vision_current;

extern Event EV_ScriptThread_Trace;
extern Event EV_ScriptThread_SightTrace;
extern Event EV_ScriptThread_VisionSetNaked;
extern Event EV_ScriptThread_CancelWaiting;

extern con_set<str, ScriptThreadLabel> m_scriptCmds;
extern ScriptMaster                    Director;

typedef enum scriptedEvType_e {
    SE_DEFAULT,
    SE_CONNECTED,
    SE_DISCONNECTED,
    SE_SPAWN,
    SE_DAMAGE,
    SE_KILL,
    SE_KEYPRESS,
    SE_INTERMISSION,
    SE_SERVERCOMMAND,
    SE_CHANGETEAM,
    SE_MAX

} scriptedEvType_t;

class ScriptEvent : public Class
{
public:
    ScriptThreadLabel label;

public:
    CLASS_PROTOTYPE(ScriptEvent);

    void Archive(Archiver& arc) override;

    bool IsRegistered(void);
    void Trigger(Event *ev);
};

inline void ScriptEvent::Archive(Archiver& arc)
{
    label.Archive(arc);
}

inline bool ScriptEvent::IsRegistered(void)
{
    return label.IsSet();
}

inline void ScriptEvent::Trigger(Event *ev)
{
    if (label.IsSet()) {
        label.Execute(NULL, ev);
    }

    delete ev;
}

extern ScriptEvent scriptedEvents[];
