/***************************************************************************
  This file is part of Project Apollo - NASSP
  Copyright 2004-2005

  ORBITER vessel module: Saturn V Module Parked/Docked mode

  Project Apollo is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Project Apollo is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Project Apollo; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See http://nassp.sourceforge.net/license/ for more details.

  **************************** Revision History ****************************
  *	$Log$
  *	Revision 1.1  2009/02/18 23:21:14  tschachim
  *	Moved files as proposed by Artlav.
  *	
  *	Revision 1.18  2008/04/11 11:49:10  tschachim
  *	Fixed BasicExcel for VC6, reduced VS2005 warnings, bugfixes.
  *	
  *	Revision 1.17  2008/01/23 01:40:07  lassombra
  *	Implemented timestep functions and event management
  *	
  *	Events for Saturns are now fully implemented
  *	
  *	Removed all hardcoded checklists from Saturns.
  *	
  *	Automatic Checklists are coded into an excel file.
  *	
  *	Added function to get the name of the active checklist.
  *	
  *	ChecklistController is now 100% ready for Saturn.
  *	
  *	Revision 1.16  2008/01/15 19:13:05  lassombra
  *	Implemented Vessel connector and Checklist Completion step.  The third button down on the left side completes the "current" step on the temporary MFD.
  *	
  *	Additionally made dummy checklists reference "Mission Timer Switch" so that the flashing function can be tested.
  *	
  *	Finally, updated the MFD demo to show one way to do a flashing switch, and a recommended deconstructor implementation.
  *	
  *	Revision 1.15  2008/01/14 01:17:01  movieman523
  *	Numerous changes to move payload creation from the CSM to SIVB.
  *	
  *	Revision 1.14  2008/01/12 04:14:10  movieman523
  *	Pass payload information to SIVB and have LEM use the fuel masses passed to it.
  *	
  *	Revision 1.13  2008/01/09 15:00:19  lassombra
  *	Added support for checklistController to save/load state.
  *	
  *	Added support for new scenario options LEMCHECK <lem checklist file and LEMCHECKAUTO <whether the lem should automatically execute checklists.
  *	
  *	Will document new options on the wiki
  *	
  *	Revision 1.12  2008/01/09 01:46:45  movieman523
  *	Added initial support for talking to checklist controller from MFD.
  *	
  *	Revision 1.11  2007/12/21 18:10:26  movieman523
  *	Revised docking connector code; checking in a working version prior to a rewrite to automate the docking process.
  *	
  *	Revision 1.10  2007/12/21 03:35:52  movieman523
  *	Fixed LEM initialisation bug.
  *	
  *	Revision 1.9  2007/12/21 01:00:09  movieman523
  *	Really basic Checklist MFD based on Project Apollo MFD, along with the various support functions required to make it work.
  *	
  *	Revision 1.8  2007/11/30 17:46:32  movieman523
  *	Implemented remaining meters as 0-5V voltmeters for now.
  *	
  *	Revision 1.7  2007/11/30 16:40:40  movieman523
  *	Revised LEM to use generic voltmeter and ammeter code. Note that the ED battery select switch needs to be implemented to fully support the voltmeter/ammeter now.
  *	
  *	Revision 1.6  2007/10/18 00:23:16  movieman523
  *	Primarily doxygen changes; minimal functional change.
  *	
  *	Revision 1.5  2007/06/06 15:02:08  tschachim
  *	OrbiterSound 3.5 support, various fixes and improvements.
  *	
  *	Revision 1.4  2007/04/23 10:44:35  tschachim
  *	Bugfix descent engine arm.
  *	
  *	Revision 1.3  2006/08/20 08:28:06  dseagrav
  *	LM Stage Switch actually causes staging (VERY INCOMPLETE), Incorrect "Ascent RCS" removed, ECA outputs forced to 24V during initialization to prevent IMU/LGC failure on scenario load, Valves closed by default, EDS saves RCS valve states, would you like fries with that?
  *	
  *	Revision 1.2  2006/08/18 05:45:01  dseagrav
  *	LM EDS now exists. Talkbacks wired to a power source will revert to BP when they lose power.
  *	
  *	Revision 1.1  2006/08/13 16:01:53  movieman523
  *	Renamed LEM. Think it all builds properly, I'm checking it in before the lightning knocks out the power here :).
  *	
  **************************************************************************/

// To force orbitersdk.h to use <fstream> in any compiler version
#pragma include_alias( <fstream.h>, <fstream> )
#include "Orbitersdk.h"
#include "stdio.h"
#include "math.h"
#include "OrbiterSoundSDK35.h"
#include "lmresource.h"

#include "nasspdefs.h"
#include "nasspsound.h"

#include "soundlib.h"
#include "toggleswitch.h"
#include "apolloguidance.h"
#include "LEMcomputer.h"
#include "dsky.h"
#include "IMU.h"

#include "LEM.h"
#include "tracer.h"
#include "papi.h"
#include "CollisionSDK/CollisionSDK.h"

#include "connector.h"

char trace_file[] = "ProjectApollo LM.log";


// ==============================================================
// Global parameters
// ==============================================================

static int refcount;

const double N   = 1.0;
const double kN  = 1000.0;
const double KGF = N*G;
const double SEC = 1.0*G;
const double KG  = 1.0;

const VECTOR3 OFS_STAGE1 =  { 0, 0, -8.935};
const VECTOR3 OFS_STAGE2 =  { 0, 0, 9.25-12.25};
const VECTOR3 OFS_STAGE21 =  { 1.85,1.85,24.5-12.25};
const VECTOR3 OFS_STAGE22 =  { -1.85,1.85,24.5-12.25};
const VECTOR3 OFS_STAGE23 =  { 1.85,-1.85,24.5-12.25};
const VECTOR3 OFS_STAGE24 =  { -1.85,-1.85,24.5-12.25};

const int TO_EVA=1;


// Modif x15 to manage landing sound
#ifdef DIRECTSOUNDENABLED
static SoundEvent sevent        ;
static double NextEventTime = 0.0;
#endif

static GDIParams g_Param;

// ==============================================================
// API interface
// ==============================================================

BOOL WINAPI DllMain (HINSTANCE hModule,
					 DWORD ul_reason_for_call,
					 LPVOID lpReserved)
{
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		InitGParam(hModule);
		g_Param.hDLL = hModule; // DS20060413 Save for later
		InitCollisionSDK();
		break;

	case DLL_PROCESS_DETACH:
		FreeGParam();
		break;
	}
	return TRUE;
}

DLLCLBK VESSEL *ovcInit (OBJHANDLE hvessel, int flightmodel)

{
	LEM *lem;

	if (!refcount++) {
		LEMLoadMeshes();
	}
	
	// VESSELSOUND 

	lem = new LEM(hvessel, flightmodel);
	return static_cast<VESSEL *> (lem);
}

DLLCLBK void ovcExit (VESSEL *vessel)

{
	TRACESETUP("ovcExit LMPARKED");

	--refcount;

	if (!refcount) {
		TRACE("refcount == 0");

		//
		// This code could tidy up allocations when refcount == 0
		//

	}

	if (vessel) delete static_cast<LEM *> (vessel);
}

// Constructor
LEM::LEM(OBJHANDLE hObj, int fmodel) : Payload (hObj, fmodel), 
	
	CDRs28VBus("CDR-28V-Bus",NULL),
	LMPs28VBus("LMP-28V-Bus",NULL),
	ACBusA("AC-Bus-A",NULL),
	ACBusB("AC-Bus-B",NULL),
	dsky(soundlib, agc, 015),
	agc(soundlib, dsky, imu, Panelsdk),
	CSMToLEMPowerSource("CSMToLEMPower", Panelsdk),
	ACVoltsAttenuator("AC-Volts-Attenuator", 62.5, 125.0, 20.0, 40.0),
	EPSDCAmMeter(0, 120.0, 220.0, -50.0),
	EPSDCVoltMeter(20.0, 40.0, 215.0, -35.0),
	ComPitchMeter(0.0, 5.0, 220.0, -50.0),
	ComYawMeter(0.0, 5.0, 220.0, -50.0),
	Panel14SignalStrengthMeter(0.0, 5.0, 220.0, -50.0),
	RadarSignalStrengthMeter(0.0, 5.0, 220.0, -50.0),
	checkControl(soundlib),
	MFDToPanelConnector(MainPanel, checkControl),
	imu(agc, Panelsdk)

{
	dllhandle = g_Param.hDLL; // DS20060413 Save for later

	// VESSELSOUND initialisation
	soundlib.InitSoundLib(hObj, SOUND_DIRECTORY);

	// Force to NULL to avoid stupid VC++ optimization failure
	int x;
	for (x = 0; x < N_LEM_VALVES; x++){
		pLEMValves[x] = NULL;
		ValveState[x] = FALSE;
	}

	//
	// Do systems init first as other code may rely on some
	// of the variables it sets up.
	//
	SystemsInit();

	// Init further down
	Init();
}

LEM::~LEM()

{
#ifdef DIRECTSOUNDENABLED
    sevent.Stop();
	sevent.Done();
#endif

	// DS20060413 release DirectX stuff
	if(js_enabled > 0){
		// Release joysticks
		while(js_enabled > 0){
			js_enabled--;
			dx8_joystick[js_enabled]->Unacquire();
			dx8_joystick[js_enabled]->Release();
		}
		dx8ppv->Release();
		dx8ppv = NULL;
	}

}

void LEM::Init()

{
	RCS_Full=true;
	Eds=true;	
	toggleRCS =false;

	fdaiDisabled = false;
	fdaiSmooth = false;

	InitPanel();

	ABORT_IND=false;

	bToggleHatch=false;
	bModeDocked=false;
	bModeHover=false;
	HatchOpen=false;
	bManualSeparate=false;
	ToggleEva=false;
	CDREVA_IP=false;
	refcount = 0;
	viewpos = LMVIEW_LMP;
	startimer=false;
	ContactOK = false;
	stage = 0;
	status = 0;

	actualFUEL = 0.0;

	InVC = false;
	InPanel = false;
	PanelId = LMPANEL_MAIN;	// default panel
	CheckPanelIdInTimestep = false;
	InFOV = true;
	SaveFOV = 0;

	Crewed = true;
	AutoSlow = false;

	MissionTime = 0;
	FirstTimestep = true;

	SwitchFocusToLeva = 0;

	agc.ControlVessel(this);
	imu.SetVessel(this, TRUE);
	
	ph_Dsc = 0;
	ph_Asc = 0;
	ph_RCSA = 0;
	ph_RCSB = 0;

	DescentFuelMassKg = 8375.0;
	AscentFuelMassKg = 2345.0;

	Realism = REALISM_DEFAULT;
	ApolloNo = 0;
	Landed = false;

	LEMToCSMConnector.SetType(CSM_LEM_DOCKING);
	CSMToLEMPowerConnector.SetType(LEM_CSM_POWER);

	LEMToCSMConnector.AddTo(&CSMToLEMPowerConnector);
	CSMToLEMPowerSource.SetConnector(&CSMToLEMPowerConnector);

	//
	// Panel flash.
	//

	NextFlashUpdate = MINUS_INFINITY;
	PanelFlashOn = false;

	//
	// Default channel setup.
	//

	agc.SetInputChannelBit(030, 2, true);	// Descent stage attached.
	agc.SetInputChannelBit(030, 15, true);	// Temperature in limits.

	//
	// For now we'll turn on the mission timer. We don't yet have a switch to control
	// it.
	//

	MissionTimerDisplay.SetRunning(true);
	MissionTimerDisplay.SetEnabled(true);

	//
	// And Event Timer.
	//

	EventTimerDisplay.SetRunning(true);
	EventTimerDisplay.SetEnabled(true);

	//
	// Initial sound setup
	//

	soundlib.SoundOptionOnOff(PLAYCOUNTDOWNWHENTAKEOFF, FALSE);
	soundlib.SoundOptionOnOff(PLAYCABINAIRCONDITIONING, FALSE);
	soundlib.SoundOptionOnOff(DISPLAYTIMER, FALSE);
	/// \todo Disabled for now because of the LEVA and the descent stage vessel
	///		  Enable before CSM docking
	soundlib.SoundOptionOnOff(PLAYRADARBIP, FALSE);

	strncpy(AudioLanguage, "English", 64);
	soundlib.SetLanguage(AudioLanguage);
	SoundsLoaded = false;

	exhaustTex = oapiRegisterExhaustTexture("ProjectApollo/Exhaust_atrcs");

	//
	// Register visible connectors.
	//
	RegisterConnector(VIRTUAL_CONNECTOR_PORT, &MFDToPanelConnector);
	RegisterConnector(0, &LEMToCSMConnector);
}

void LEM::DoFirstTimestep()

{
	checkControl.linktoVessel(this);
	// Load sounds in case of dynamic creation, otherwise during clbkLoadStageEx
	if (!SoundsLoaded) {
		LoadDefaultSounds();
	}

#ifdef DIRECTSOUNDENABLED
	NextEventTime = 0.0;
#endif

	if (CabinFansActive()) {
		CabinFans.play(LOOP,255);
	}

	char VName10[256]="";

	strcpy (VName10, GetName()); strcat (VName10, "-LEVA");
	hLEVA=oapiGetVesselByName(VName10);
}

void LEM::LoadDefaultSounds()

{
    char buffers[80];

	soundlib.SetLanguage(AudioLanguage);
	sprintf(buffers, "Apollo%d", agc.GetApolloNo());
    soundlib.SetSoundLibMissionPath(buffers);

	//
	// load sounds now that the audio language has been set up.
	//

	soundlib.LoadMissionSound(LunarAscent, LUNARASCENT_SOUND, LUNARASCENT_SOUND);
	soundlib.LoadSound(StageS, "Stagesep.wav");
	soundlib.LoadMissionSound(Scontact, LUNARCONTACT_SOUND, LUNARCONTACT_SOUND);
	soundlib.LoadSound(Sclick, CLICK_SOUND, INTERNAL_ONLY);
	soundlib.LoadSound(Rclick, ROTARY_SOUND, INTERNAL_ONLY);
	soundlib.LoadSound(Bclick, "button.wav", INTERNAL_ONLY);
	soundlib.LoadSound(Gclick, "guard.wav", INTERNAL_ONLY);
	soundlib.LoadSound(CabinFans, "cabin.wav", INTERNAL_ONLY);
	soundlib.LoadSound(Vox, "vox.wav");
	soundlib.LoadSound(Afire, "des_abort.wav");

// MODIF X15 manage landing sound
#ifdef DIRECTSOUNDENABLED
    sevent.LoadMissionLandingSoundArray(soundlib,"sound.csv");
    sevent.InitDirectSound(soundlib);
#endif
	SoundsLoaded = true;
}

void LEM::AttitudeLaunch1()
{
	//Original code function by Richard Craig From MErcury Sample by Rob CONLEY
	// Modification for NASSP specific needs by JL Rocca-Serra
	VECTOR3 ang_vel;
	GetAngularVel(ang_vel);// gets current angular velocity for stabilizer and rate control
// variables to store each component deflection vector	
	VECTOR3 rollvectorl={0.0,0.0,0.0};
	VECTOR3 rollvectorr={0.0,0.0,0.0};
	VECTOR3 pitchvector={0.0,0.0,0.0};
	VECTOR3 yawvector={0.0,0.0,0.0};
	VECTOR3 yawvectorm={0.0,0.0,0.0};
	VECTOR3 pitchvectorm={0.0,0.0,0.0};
//************************************************************
// variables to store Manual control levels for each axis
	double tempP = 0.0;
	double tempY = 0.0;
	double tempR = 0.0; 
//************************************************************
// Variables to store correction factors for rate control
	double rollcorrect = 0.0;
	double yawcorrect= 0.0;
	double pitchcorrect = 0.0;
//************************************************************
// gets manual control levels in each axis, this code copied directly from Rob Conley's Mercury Atlas	
	if (GMBLswitch){
		tempP = GetManualControlLevel(THGROUP_ATT_PITCHDOWN, MANCTRL_ANYDEVICE, MANCTRL_ANYMODE) - GetManualControlLevel(THGROUP_ATT_PITCHUP, MANCTRL_ANYDEVICE, MANCTRL_ANYMODE);
	}
	if (GMBLswitch){
		tempR = GetManualControlLevel(THGROUP_ATT_BANKLEFT, MANCTRL_ANYDEVICE, MANCTRL_ANYMODE) - GetManualControlLevel(THGROUP_ATT_BANKRIGHT, MANCTRL_ANYDEVICE, MANCTRL_ANYMODE);
	}
	
	
	//sprintf (oapiDebugString(), "roll input: %f, roll vel: %f,pitch input: %f, pitch vel: %f", tempR, ang_vel.z,tempP, ang_vel.x);
	
//*************************************************************
//Creates correction factors for rate control in each axis as a function of input level
// and current angular velocity. Varies from 1 to 0 as angular velocity approaches command level
// multiplied by maximum rate desired
	if(tempR != 0.0)	{
		rollcorrect = (1/(fabs(tempR)*0.175))*((fabs(tempR)*0.175)-fabs(ang_vel.z));
			if((tempR > 0 && ang_vel.z > 0) || (tempR < 0 && ang_vel.z < 0))	{
						rollcorrect = 1;
					}
	}
	if(tempP != 0.0)	{
		pitchcorrect = (1/(fabs(tempP)*0.275))*((fabs(tempP)*0.275)-fabs(ang_vel.x));
		if((tempP > 0 && ang_vel.x > 0) || (tempP < 0 && ang_vel.x < 0))	{
						pitchcorrect = 1;
					}
	}
	
//*************************************************************	
// Create deflection vectors in each axis
	pitchvector = _V(0.0,0.0,0.05*tempP*pitchcorrect);
	pitchvectorm = _V(0.0,0.0,-0.2*tempP*pitchcorrect);
	yawvector = _V(0.05*tempY*yawcorrect,0.0,0.0);
	yawvectorm = _V(0.05*tempY*yawcorrect,0.0,0.0);
	rollvectorl = _V(0.0,0.60*tempR*rollcorrect,0.0);
	rollvectorr = _V(0.60*tempR*rollcorrect,0.0,0.0);

//*************************************************************
// create opposite vectors for "gyro stabilization" if command levels are 0
	if(tempP==0.0 && GMBLswitch) {
		pitchvectorm=_V(0.0,0.0,-0.8*ang_vel.x*3);
	}
	if(tempR==0.0 && GMBLswitch) {
		
		rollvectorr=_V(0.8*ang_vel.z*3,0.0,0.0);
	}
	
//**************************************************************	
// Sets thrust vectors by simply adding up all the axis deflection vectors and the 
// "neutral" default vector
	SetThrusterDir(th_hover[0],pitchvectorm+rollvectorr+_V( 0,1,0));//4
	SetThrusterDir(th_hover[1],pitchvectorm+rollvectorr+_V( 0,1,0));

//	sprintf (oapiDebugString(), "pitch vector: %f, roll vel: %f", tempP, ang_vel.z);

}

int LEM::clbkConsumeBufferedKey(DWORD key, bool down, char *keystate) {

	// rewrote to get key events rather than monitor key state - LazyD

	// DS20060404 Allow keys to control DSKY like in the CM
	if (KEYMOD_SHIFT(keystate)){
		// Do DSKY stuff
		if(down){
			switch(key){
				case OAPI_KEY_PRIOR:
					dsky.ResetPressed();
					break;
				case OAPI_KEY_NEXT:
					dsky.KeyRel();
					break;
				case OAPI_KEY_NUMPADENTER:
					dsky.EnterPressed();
					break;
				case OAPI_KEY_DIVIDE:
					dsky.VerbPressed();
					break;
				case OAPI_KEY_MULTIPLY:
					dsky.NounPressed();
					break;
				case OAPI_KEY_ADD:
					dsky.PlusPressed();
					break;
				case OAPI_KEY_SUBTRACT:
					dsky.MinusPressed();
					break;
				case OAPI_KEY_DECIMAL:
					dsky.ProgPressed();
					break;
				case OAPI_KEY_NUMPAD1:
					dsky.NumberPressed(1);
					break;
				case OAPI_KEY_NUMPAD2:
					dsky.NumberPressed(2);
					break;
				case OAPI_KEY_NUMPAD3:
					dsky.NumberPressed(3);
					break;
				case OAPI_KEY_NUMPAD4:
					dsky.NumberPressed(4);
					break;
				case OAPI_KEY_NUMPAD5:
					dsky.NumberPressed(5);
					break;
				case OAPI_KEY_NUMPAD6:
					dsky.NumberPressed(6);
					break;
				case OAPI_KEY_NUMPAD7:
					dsky.NumberPressed(7);
					break;
				case OAPI_KEY_NUMPAD8:
					dsky.NumberPressed(8);
					break;
				case OAPI_KEY_NUMPAD9:
					dsky.NumberPressed(9);
					break;
				case OAPI_KEY_NUMPAD0:
					dsky.NumberPressed(0);
					break;
			}
		}else{
			// KEY UP
			switch(key){
				case OAPI_KEY_DECIMAL:
					dsky.ProgReleased();
					break;
			}
		}
		return 0;
	}

	if (KEYMOD_SHIFT(keystate) || KEYMOD_CONTROL(keystate) || !down) {
		return 0; 
	}

	switch (key) {

	case OAPI_KEY_K:
		bToggleHatch = true;
		return 1;

	case OAPI_KEY_E:
		if (!Realism) {
			ToggleEva = true;
			return 1;
		}
		else {
			return 0;
		}

	case OAPI_KEY_6:
		viewpos = LMVIEW_CDR;
		SetView();
		return 1;

	case OAPI_KEY_7:
		viewpos = LMVIEW_LMP;
		SetView();
		return 1;

	//
	// Used by P64
	//


	case OAPI_KEY_COMMA:
		// move landing site left
		agc.RedesignateTarget(1,1.0);
		ButtonClick();
		return 1;

	case OAPI_KEY_PERIOD:
		// move landing site right
		agc.RedesignateTarget(1,-1.0);
		ButtonClick();
		return 1;

	case OAPI_KEY_HOME:
		//move the landing site downrange
		agc.RedesignateTarget(0,-1.0);
		ButtonClick();
		return 1;

	case OAPI_KEY_END:
		//move the landing site closer
		agc.RedesignateTarget(0,1.0);
		ButtonClick();
		return 1;

	//
	// Used by P66
	//

	case OAPI_KEY_MINUS:
		//increase descent rate
		agc.ChangeDescentRate(-0.3077);
		return 1;

	case OAPI_KEY_EQUALS:
		//decrease descent rate
		agc.ChangeDescentRate(0.3077);
		return 1;	
	}
	return 0;
}

//
// Timestep code.
//

void LEM::clbkPreStep (double simt, double simdt, double mjd) {

	if (CheckPanelIdInTimestep) {
		oapiSetPanel(PanelId);
		CheckPanelIdInTimestep = false;
	}
}


void LEM::clbkPostStep(double simt, double simdt, double mjd)

{
	if (FirstTimestep)
	{
		DoFirstTimestep();
		FirstTimestep = false;
		return;
	}

	//
	// Panel flash counter.
	//

	if (MissionTime >= NextFlashUpdate) {
		PanelFlashOn = !PanelFlashOn;
		NextFlashUpdate = MissionTime + 0.25;
	}

	//
	// If we switch focus to the astronaut immediately after creation, Orbitersound doesn't
	// play any sounds, or plays LEM sounds rather than astronauts sounds. We need to delay
	// the focus switch a few timesteps to allow it to initialise properly in the background.
	//

	if (SwitchFocusToLeva > 0 && hLEVA) {
		SwitchFocusToLeva--;
		if (!SwitchFocusToLeva) {
			oapiSetFocusObject(hLEVA);
		}
	}
	
	VECTOR3 RVEL = _V(0.0,0.0,0.0);
	GetRelativeVel(GetGravityRef(),RVEL);

	double deltat = oapiGetSimStep();

	MissionTime = MissionTime + deltat;
	SystemsTimestep(MissionTime, deltat);

	actualVEL = (sqrt(RVEL.x *RVEL.x + RVEL.y * RVEL.y + RVEL.z * RVEL.z)/1000*3600);
	actualALT = GetAltitude() ;
	if (actualALT < 1470){
		actualVEL = actualVEL-1470+actualALT;
	}
	if (GroundContact()){
	actualVEL =0;
	}
	if (status !=0 && Sswitch2){
				bManualSeparate = true;
	}
	actualFUEL = GetFuelMass()/GetMaxFuelMass()*100;	
	double dTime,aSpeed,DV,aALT,DVV,DVA;//aVAcc;aHAcc;ALTN1;SPEEDN1;aTime aVSpeed;
		aSpeed = actualVEL/3600*1000;
		aALT=actualALT;
		dTime=simt-aTime;
		if(dTime > 0.1){
			DV= aSpeed - SPEEDN1;
			aHAcc= (DV / dTime);
			DVV = aALT - ALTN1;
			aVSpeed = DVV / dTime;
			DVA = aVSpeed- VSPEEDN1;
			

			aVAcc=(DVA/ dTime);
			aTime = simt;
			VSPEEDN1 = aVSpeed;
			ALTN1 = aALT;
			SPEEDN1= aSpeed;
		}
	AttitudeLaunch1();
	if( toggleRCS){
			if(P44switch){
			SetAttitudeMode(2);
			toggleRCS =false;
			}
			else if (!P44switch){
			SetAttitudeMode(1);
			toggleRCS =false;
			}
		}
		if (GetAttitudeMode()==1){
		P44switch=false;
		}
		else if (GetAttitudeMode()==2 ){
		P44switch=true;
		}
	if(Sswitch1){
		Sswitch1=false;
		Undock(0);
		}

	if (stage == 0)	{
		if (EngineArmSwitch.IsDown()) { //  && !DESHE1switch && !DESHE2switch && ED1switch && ED2switch && ED5switch){
			SetThrusterResource(th_hover[0], ph_Dsc);
			SetThrusterResource(th_hover[1], ph_Dsc);
//TODOX15 is it useful to do it on every step ? surely no
			agc.SetInputChannelBit(030, 3, true);
		} else {
			SetThrusterResource(th_hover[0], NULL);
			SetThrusterResource(th_hover[1], NULL);
//TODOX15
			agc.SetInputChannelBit(030, 3, false);
		}
		

	}else if (stage == 1 || stage == 5)	{

		if (EngineArmSwitch.IsDown()) { // && !DESHE1switch && !DESHE2switch && ED1switch && ED2switch && ED5switch){
			SetThrusterResource(th_hover[0], ph_Dsc);
			SetThrusterResource(th_hover[1], ph_Dsc);
// TODOX15
			agc.SetInputChannelBit(030, 3, true);
		} else {
			SetThrusterResource(th_hover[0], NULL);
			SetThrusterResource(th_hover[1], NULL);
//TODOX15	
			agc.SetInputChannelBit(030, 3, false);
		}

		if (CDREVA_IP) {
			if(!hLEVA) {
				ToggleEVA();
			}
		}

		if (ToggleEva && GroundContact()){
			ToggleEVA();
		}
		
		if (bToggleHatch){
			VESSELSTATUS vs;
			GetStatus(vs);
			if (vs.status == 1){
				//PlayVesselWave(Scontact,NOLOOP,255);
				//SetLmVesselHoverStage2(vessel);
			}
			bToggleHatch=false;
		}

		double vsAlt = papiGetAltitude(this);
		if (!ContactOK && (GroundContact() || (vsAlt < 1.0))) {

#ifdef DIRECTSOUNDENABLED
			if (!sevent.isValid())
#endif
				Scontact.play();

			SetEngineLevel(ENGINE_HOVER,0);
			ContactOK = true;

			SetLmLandedMesh();
		}

		if (CPswitch && HATCHswitch && EVAswitch && GroundContact()){
			ToggleEva = true;
			EVAswitch = false;
		}
		//
		// This does an abort stage if the descent stage runs out of fuel,
		// probably should start P71
		//
		if (GetPropellantMass(ph_Dsc)<=50 && actualALT > 10){
			AbortStageSwitchLight = true;
			SeparateStage(stage);
			SetEngineLevel(ENGINE_HOVER,1);
			stage = 2;
			AbortFire();
			agc.SetInputChannelBit(030, 4, true); // Abort with ascent stage.
		}
		if (bManualSeparate && !startimer){
			VESSELSTATUS vs;
			GetStatus(vs);

			if (vs.status == 1){
				countdown=simt;
				LunarAscent.play(NOLOOP,200);
				startimer=true;
				//vessel->SetTouchdownPoints (_V(0,-0,10), _V(-1,-0,-10), _V(1,-0,-10));
			}
			else{
				SeparateStage(stage);
				stage = 2;
			}
		}
		if ((simt-(10+countdown))>=0 && startimer ){
			StartAscent();
		}
		//sprintf (oapiDebugString(),"FUEL %d",GetPropellantMass(ph_Dsc));
	}
	else if (stage == 2) {
		if (AscentEngineArmed()) {
			SetThrusterResource(th_hover[0], ph_Asc);
			SetThrusterResource(th_hover[1], ph_Asc);
			agc.SetInputChannelBit(030, 3, true);
		} else {
			SetThrusterResource(th_hover[0], NULL);
			SetThrusterResource(th_hover[1], NULL);
			agc.SetInputChannelBit(030, 3, false);
		}
	}
	else if (stage == 3){
		if (AscentEngineArmed()) {
			SetThrusterResource(th_hover[0], ph_Asc);
			SetThrusterResource(th_hover[1], ph_Asc);
			agc.SetInputChannelBit(030, 3, true);
		} else {
			SetThrusterResource(th_hover[0], NULL);
			SetThrusterResource(th_hover[1], NULL);
			agc.SetInputChannelBit(030, 3, false);
		}
	}
	else if (stage == 4)
	{	
	}

    // x15 landing sound management
#ifdef DIRECTSOUNDENABLED

    double     simtime       ;
	int        mode          ;
	double     timeremaining ;
	double     timeafterpdi  ;
	double     timetoapproach;
	char names [255]         ;
	int        todo          ;
	double     offset        ;
	int        newbuffer     ;

	
	if(simt >NextEventTime)
	{
        NextEventTime=simt+0.1;
	    agc.GetStatus(&simtime,&mode,&timeremaining,&timeafterpdi,&timetoapproach);
    	todo = sevent.play(soundlib,
			    this,
				names,
				&offset,
				&newbuffer,
		        simtime,
				MissionTime,
				mode,
				timeremaining,
				timeafterpdi,
				timetoapproach,
				NOLOOP,
				255);
        if (todo)
		{
           if(offset > 0.)
                sevent.PlaySound( names,newbuffer,offset);
		   else sevent.PlaySound( names,true,0);
		}
	} 
#endif
}

//
// Set GMBLswitch
//

void LEM::SetGimbal(bool setting)
{
	agc.SetInputChannelBit(032, 9, setting);
	GMBLswitch = setting;
}

//
// Get Mission Time
//

void LEM::GetMissionTime(double &Met)
{
	Met = MissionTime;
	return;
}

//
// Perform the stage separation as done when P12 is running and Abort Stage is pressed
//

void LEM::AbortStage()
{
	ButtonClick();
	AbortFire();
	AbortStageSwitchLight = true;
	SeparateStage(stage);
	SetThrusterResource(th_hover[0], ph_Asc);
	SetThrusterResource(th_hover[1], ph_Asc);
	stage = 2;
	startimer = false;
	AbortStageSwitchLight = true;
}

//
// Initiate ascent.
//

void LEM::StartAscent()

{
	SeparateStage(stage);
	stage = 2;
	SetEngineLevel(ENGINE_HOVER,1);
	startimer = false;

	LunarAscent.done();
}

typedef union {
	struct {
		unsigned MissionTimerRunning:1;
		unsigned MissionTimerEnabled:1;
		unsigned EventTimerRunning:1;
		unsigned EventTimerEnabled:1;
	} u;
	unsigned long word;
} LEMMainState;

//
// Scenario state functions.
//

void LEM::clbkLoadStateEx (FILEHANDLE scn, void *vs)

{
	char *line;
	int	SwitchState;
	float ftcp;
	
	while (oapiReadScenario_nextline (scn, line)) {
        if (!strnicmp (line, "CONFIGURATION", 13)) {
            sscanf (line+13, "%d", &status);
		}
		else if (!strnicmp (line, "EVA", 3)) {
			CDREVA_IP = true;
		} 
		else if (!strnicmp (line, "CSWITCH", 7)) {
            SwitchState = 0;
			sscanf (line+7, "%d", &SwitchState);
			SetCSwitchState(SwitchState);
		} 
		else if (!strnicmp (line, "SSWITCH", 7)) {
            SwitchState = 0;
			sscanf (line+7, "%d", &SwitchState);
			SetSSwitchState(SwitchState);
		} 
		else if (!strnicmp (line, "LPSWITCH", 8)) {
            SwitchState = 0;
			sscanf (line+8, "%d", &SwitchState);
			SetLPSwitchState(SwitchState);
		} 
		else if (!strnicmp (line, "RPSWITCH", 8)) {
            SwitchState = 0;
			sscanf (line+8, "%d", &SwitchState);
			SetRPSwitchState(SwitchState);
		} 
		else if (!strnicmp(line, "MISSNTIME", 9)) {
            sscanf (line+9, "%f", &ftcp);
			MissionTime = ftcp;
		} 
		else if (!strnicmp(line, "MTD", 3)) {
            sscanf (line+3, "%f", &ftcp);
			MissionTimerDisplay.SetTime(ftcp);
		} 
		else if (!strnicmp(line, "ETD", 3)) {
            sscanf (line+3, "%f", &ftcp);
			EventTimerDisplay.SetTime(ftcp);
		}
		else if (!strnicmp(line, "UNMANNED", 8)) {
			int i;
			sscanf(line + 8, "%d", &i);
			Crewed = (i == 0);
		}
		else if (!strnicmp (line, "LANG", 4)) {
			strncpy (AudioLanguage, line + 5, 64);
		}
		else if (!strnicmp (line, "REALISM", 7)) {
			sscanf (line+7, "%d", &Realism);
		}
		else if (!strnicmp (line, "APOLLONO", 8)) {
			sscanf (line+8, "%d", &ApolloNo);
		}
		else if (!strnicmp (line, "LANDED", 6)) {
			sscanf (line+6, "%d", &Landed);
		}
		else if (!strnicmp(line, "DSCFUEL", 7)) {
			sscanf(line + 7, "%f", &ftcp);
			DescentFuelMassKg = ftcp;
		}
		else if (!strnicmp(line, "ASCFUEL", 7)) {
			sscanf(line + 7, "%f", &ftcp);
			AscentFuelMassKg = ftcp;
		}
		else if (!strnicmp (line, "FDAIDISABLED", 12)) {
			sscanf (line + 12, "%i", &fdaiDisabled);
		}
		else if (!strnicmp(line, DSKY_START_STRING, sizeof(DSKY_START_STRING))) {
			dsky.LoadState(scn, DSKY_END_STRING);
		}
		else if (!strnicmp(line, AGC_START_STRING, sizeof(AGC_START_STRING))) {
			agc.LoadState(scn);
		}
		else if (!strnicmp(line, IMU_START_STRING, sizeof(IMU_START_STRING))) {
			imu.LoadState(scn);
		}
		else if (!strnicmp (line, "ECA_1_START",sizeof("ECA_1_START"))) {
			ECA_1.LoadState(scn,"ECA_1_END");
		}
		else if (!strnicmp (line, "ECA_2_START",sizeof("ECA_2_START"))) {
			ECA_2.LoadState(scn,"ECA_2_END");
		}
		else if (!strnicmp (line, "PANEL_ID", 8)) { 
			sscanf (line+8, "%d", &PanelId);
		}
		else if (!strnicmp (line, "STATE", 5)) {
			LEMMainState state;
			sscanf (line+5, "%d", &state.word);

			MissionTimerDisplay.SetRunning(state.u.MissionTimerRunning != 0);
			MissionTimerDisplay.SetEnabled(state.u.MissionTimerEnabled != 0);
			EventTimerDisplay.SetRunning(state.u.EventTimerRunning != 0);
			EventTimerDisplay.SetEnabled(state.u.EventTimerEnabled != 0);
		} 
        else if (!strnicmp (line, PANELSWITCH_START_STRING, strlen(PANELSWITCH_START_STRING))) { 
			PSH.LoadState(scn);	
		}
		else if (!strnicmp (line, "LEM_EDS_START",sizeof("LEM_EDS_START"))) {
			eds.LoadState(scn,"LEM_EDS_END");
		}
        else if (!strnicmp (line, "<INTERNALS>", 11)) { //INTERNALS signals the PanelSDK part of the scenario
			Panelsdk.Load(scn);			//send the loading to the Panelsdk
		}
		else if (!strnicmp (line, ChecklistControllerStartString, strlen(ChecklistControllerStartString)))
		{
			checkControl.load(scn);
		}
		else 
		{
            ParseScenarioLineEx (line, vs);
        }
    }

	switch (status) {
	case 0:
		stage=0;
		SetLmVesselDockStage();
		break;

	case 1:
		stage=1;
		SetLmVesselHoverStage();

		if (CDREVA_IP){
			SetupEVA();
		}
		break;

	case 2:
		stage=2;
		SetLmAscentHoverStage();
		break;
	}

	//
	// Pass on the mission number and realism setting to the AGC.
	//

	agc.SetMissionInfo(ApolloNo, Realism);

	//
	// Load sounds, this is mandatory if loading in cockpit view, 
	// because OrbiterSound crashes when loading sounds during clbkLoadPanel
	//
	LoadDefaultSounds();

	// Also cause the AC busses to wire up
	switch(EPSInverterSwitch.GetState()){
		case THREEPOSSWITCH_UP:      // INV 2
			INV_1.active = 0;
			INV_2.active = 1; 
			ACBusA.WireTo(&AC_A_INV_2_FEED_CB);
			ACBusB.WireTo(&AC_B_INV_2_FEED_CB);
			break;
		case THREEPOSSWITCH_CENTER:  // INV 1
			INV_1.active = 1;
			INV_2.active = 0; 
			ACBusA.WireTo(&AC_A_INV_1_FEED_CB);
			ACBusB.WireTo(&AC_B_INV_1_FEED_CB);
			break;
		case THREEPOSSWITCH_DOWN:    // OFF	
			break;                   // Handled later
	}

}

void LEM::clbkSetClassCaps (FILEHANDLE cfg) {

	VSEnableCollisions(GetHandle(),"ProjectApollo");
	SetLmVesselDockStage();
}

void LEM::SetStateEx(const void *status)

{
	const VESSELSTATUS2 *vslm = static_cast<const VESSELSTATUS2 *> (status);

	DefSetStateEx(status);
}

void LEM::clbkSaveState (FILEHANDLE scn)

{
	SaveDefaultState (scn);	
	oapiWriteScenario_int (scn, "CONFIGURATION", status);
	if (CDREVA_IP){
		oapiWriteScenario_int (scn, "EVA", int(TO_EVA));
	}

	oapiWriteScenario_int (scn, "CSWITCH",  GetCSwitchState());
	oapiWriteScenario_int (scn, "SSWITCH",  GetSSwitchState());
	oapiWriteScenario_int (scn, "LPSWITCH",  GetLPSwitchState());
	oapiWriteScenario_int (scn, "RPSWITCH",  GetRPSwitchState());
	oapiWriteScenario_float (scn, "MISSNTIME", MissionTime);
	oapiWriteScenario_float (scn, "MTD", MissionTimerDisplay.GetTime());
	oapiWriteScenario_float (scn, "ETD", EventTimerDisplay.GetTime());
	oapiWriteScenario_string (scn, "LANG", AudioLanguage);
	oapiWriteScenario_int (scn, "PANEL_ID", PanelId);	

	if (Realism != REALISM_DEFAULT) {
		oapiWriteScenario_int (scn, "REALISM", Realism);
	}

	oapiWriteScenario_int (scn, "APOLLONO", ApolloNo);
	oapiWriteScenario_int (scn, "LANDED", Landed);
	oapiWriteScenario_int (scn, "FDAIDISABLED", fdaiDisabled);

	oapiWriteScenario_float (scn, "DSCFUEL", DescentFuelMassKg);
	oapiWriteScenario_float (scn, "ASCFUEL", AscentFuelMassKg);

	if (!Crewed) {
		oapiWriteScenario_int (scn, "UNMANNED", 1);
	}

	//
	// Main state flags are packed into a 32-bit value.
	//

	LEMMainState state;
	state.word = 0;

	state.u.MissionTimerRunning = MissionTimerDisplay.IsRunning();
	state.u.MissionTimerEnabled = MissionTimerDisplay.IsEnabled();
	state.u.EventTimerEnabled = EventTimerDisplay.IsEnabled();
	state.u.EventTimerRunning = EventTimerDisplay.IsRunning();

	oapiWriteScenario_int (scn, "STATE", state.word);

	dsky.SaveState(scn, DSKY_START_STRING, DSKY_END_STRING);
	agc.SaveState(scn);
	imu.SaveState(scn);

	//
	// Save the Panel SDK state.
	//

	Panelsdk.Save(scn);
	
	//
	// Save the state of the switches
	//

	PSH.SaveState(scn);	

	// Save ECAs
	ECA_1.SaveState(scn,"ECA_1_START","ECA_1_END");
	ECA_2.SaveState(scn,"ECA_2_START","ECA_2_END");

	// Save EDS
	eds.SaveState(scn,"LEM_EDS_START","LEM_EDS_END");
	checkControl.save(scn);
}

bool LEM::clbkLoadGenericCockpit ()

{
	SetCameraRotationRange(0.0, 0.0, 0.0, 0.0);
	SetCameraDefaultDirection(_V(0.0, 0.0, 1.0));

	InVC = false;
	InPanel = false;
	SetView();

	return true;
}

//
// Transfer important data from the CSM to the LEM when the LEM is first
// created.
//

bool LEM::SetupPayload(PayloadSettings &ls)

{
	char CSMName[64];

	MissionTime = ls.MissionTime;
	MissionTimerDisplay.SetTime(MissionTime);

	agc.SetDesiredLanding(ls.LandingLatitude, ls.LandingLongitude, ls.LandingAltitude);
	strncpy (AudioLanguage, ls.language, 64);
	strncpy (CSMName, ls.CSMName, 64);

	Crewed = ls.Crewed;
	AutoSlow = ls.AutoSlow;
	Realism = ls.Realism;
	ApolloNo = ls.MissionNo;

	DescentFuelMassKg = ls.DescentFuelKg;
	AscentFuelMassKg = ls.AscentFuelKg;

	agc.SetMissionInfo(ApolloNo, Realism, CSMName);
	agc.SetVirtualAGC(ls.Yaagc);

	// Initialize the checklist Controller in accordance with scenario settings.
	checkControl.init(ls.checklistFile);
	checkControl.autoExecute(ls.checkAutoExecute);
	// Sounds are initialized during the first timestep

	return true;
}

void LEM::PadLoad(unsigned int address, unsigned int value)

{ 
	agc.PadLoad(address, value);
 }


void LEM::SetRCSJet(int jet, bool fire) {
	/// \todo Only for the Virtual AGC for now
	if (agc.IsVirtualAGC()) {
		SetThrusterLevel(th_rcs[jet], fire);
	}
}


/// \todo Dirty Hack for the AGC++ attitude control, 
/// remove this and use I/O channels and pulsed thrusters 
/// identical to the VAGC instead

void LEM::SetRCSJetLevel(int jet, double level) {

	SetThrusterLevel(th_rcs[jet], level);
}
