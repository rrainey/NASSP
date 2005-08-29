/***************************************************************************
  This file is part of Project Apollo - NASSP
  Copyright 2004-2005 Jean-Luc Rocca-Serra, Mark Grant

  ORBITER vessel module: generic Saturn base class
  Saturn CSM panel code

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
  *	Revision 1.74  2005/08/24 00:30:00  movieman523
  *	Revised CM RCS code, and removed a load of switches that aren't used anymore.
  *	
  *	Revision 1.73  2005/08/23 22:18:47  movieman523
  *	SPS switch now works.
  *	
  *	Revision 1.72  2005/08/23 20:13:12  movieman523
  *	Added RCS talkbacks and changed AGC to use octal addresses for EMEM.
  *	
  *	Revision 1.71  2005/08/23 03:20:00  flydba
  *	modified master alarm bitmap and correction of some switch positions
  *	
  *	Revision 1.70  2005/08/23 00:03:16  movieman523
  *	Removed agc_utilities.c, as we're not actually using any functions and it has socket code that has to be commented out with every update.
  *	
  *	Revision 1.69  2005/08/21 22:21:00  movieman523
  *	Fixed SM RCS and activated SIVB RCS at all times for now.
  *	
  *	Revision 1.68  2005/08/21 17:21:10  movieman523
  *	Added event timer display.
  *	
  *	Revision 1.67  2005/08/21 16:23:32  movieman523
  *	Added more alarms.
  *	
  *	Revision 1.66  2005/08/21 13:13:43  movieman523
  *	Wired in a few caution and warning lights.
  *	
  *	Revision 1.65  2005/08/21 11:51:59  movieman523
  *	Initial version of CSM caution and warning lights: light test switch now works.
  *	
  *	Revision 1.64  2005/08/20 17:21:25  movieman523
  *	Added dv Thrust switches.
  *	
  *	Revision 1.63  2005/08/20 11:14:52  movieman523
  *	Added Rot Contr Pwr switches and removed a number of old switches which aren't used anymore.
  *	
  *	Revision 1.62  2005/08/19 21:33:20  movieman523
  *	Added initial random failure support.
  *	
  *	Revision 1.61  2005/08/19 20:05:45  movieman523
  *	Added abort switches. Wired in Tower Jett switches and SIVB Sep switch.
  *	
  *	Revision 1.60  2005/08/19 18:38:13  movieman523
  *	Wired up parachute switches properly, and added 'Comp Acty' to CSM AGC.
  *	
  *	Revision 1.59  2005/08/19 14:04:34  tschachim
  *	Added missing DSKY display elements and a FDAI.
  *	
  *	Revision 1.58  2005/08/18 22:15:22  movieman523
  *	Wired up second DSKY, to accurately match the real hardware.
  *	
  *	Revision 1.57  2005/08/18 20:54:16  movieman523
  *	Added Main Release switch and wired it up to the parachutes.
  *	
  *	Revision 1.56  2005/08/18 19:12:21  movieman523
  *	Added Event Timer switches and null Event Timer class.
  *	
  *	Revision 1.55  2005/08/18 00:22:53  movieman523
  *	Wired in CM Uplink switch, removed some old code, added initial support for second DSKY.
  *	
  *	Revision 1.54  2005/08/17 22:54:26  movieman523
  *	Added ELS and CM RCS switches.
  *	
  *	Revision 1.53  2005/08/17 00:01:59  movieman523
  *	Added ECS indicator switch, revised state saving, revised Timestep code to pass in the delta-time so we don't need to keep calculating it.
  *	
  *	Revision 1.52  2005/08/16 20:55:23  movieman523
  *	Added first saturn-specific switch for Xlunar Inject.
  *	
  *	Revision 1.51  2005/08/16 18:54:30  movieman523
  *	Added Altimeter and launch vehicle switches.
  *	
  *	Revision 1.50  2005/08/16 01:37:23  movieman523
  *	Wired in RCS Indicators rotary switch, but the switch code seems to be broken at certain angles.
  *	
  *	Revision 1.49  2005/08/15 21:37:02  movieman523
  *	Added FDAI switches.
  *	
  *	Revision 1.48  2005/08/15 20:18:16  movieman523
  *	Made thrust meter work. Unfortunately on a real CSM it's not a thrust meter :).
  *	
  *	Revision 1.47  2005/08/15 19:47:08  movieman523
  *	Added BMAG switches.
  *	
  *	Revision 1.46  2005/08/15 19:25:03  movieman523
  *	Added CSM attitude control switches and removed old ones.
  *	
  *	Revision 1.45  2005/08/15 02:37:57  movieman523
  *	SM RCS is now wired up.
  *	
  *	Revision 1.44  2005/08/14 00:45:55  movieman523
  *	Added second master alarm light.
  *	
  *	Revision 1.43  2005/08/13 22:24:20  movieman523
  *	Added the master alarm rendeing to CSM.
  *	
  *	Revision 1.42  2005/08/13 20:20:17  movieman523
  *	Created MissionTimer class and wired it into the LEM and CSM.
  *	
  *	Revision 1.41  2005/08/13 16:41:15  movieman523
  *	Fully wired up the CSM caution and warning switches.
  *	
  *	Revision 1.40  2005/08/13 14:59:24  movieman523
  *	Added initial null implementation of CSM caution and warning system, and removed 'master alarm' flag from Saturn class.
  *	
  *	Revision 1.39  2005/08/13 14:21:36  movieman523
  *	Added beginnings of caution and warning system.
  *	
  *	Revision 1.38  2005/08/13 11:48:26  movieman523
  *	Added remaining caution and warning switches to CSM (currently not wired up to anything).
  *	
  *	Revision 1.37  2005/08/13 00:43:50  movieman523
  *	Added more caution and warning switches.
  *	
  *	Revision 1.36  2005/08/13 00:09:43  movieman523
  *	Added IMU Cage switch
  *	
  *	Revision 1.35  2005/08/12 23:15:49  movieman523
  *	Added switches to update mission time display.
  *	
  *	Revision 1.34  2005/08/11 01:27:26  movieman523
  *	Added initial Virtual AGC support.
  *	
  *	Revision 1.33  2005/08/10 21:54:04  movieman523
  *	Initial IMU implementation based on 'Virtual Apollo' code.
  *	
  *	Revision 1.32  2005/08/08 20:33:00  movieman523
  *	Added initial support for offsetting the mission timer and event timer from MissionTime: the real timers could be adjusted using the switches on the control panel (which aren't wired up yet), and the event timer would reset to zero on an abort.
  *	
  *	Revision 1.31  2005/08/05 13:14:25  tschachim
  *	Minor fixes
  *	
  *	Revision 1.30  2005/08/04 01:06:04  flydba
  *	*** empty log message ***
  *	
  *	Revision 1.29  2005/07/30 16:12:13  tschachim
  *	Bugfix O2 FLOW meter
  *	
  *	Revision 1.28  2005/07/19 16:25:43  tschachim
  *	New switches
  *	
  *	Revision 1.27  2005/07/06 22:11:31  tschachim
  *	Finished SequencerSwitchesRow, no functionality yet
  *	
  *	Revision 1.26  2005/07/05 17:56:59  tschachim
  *	Fixed some switches because of spring-load
  *	
  *	Revision 1.25  2005/06/06 12:31:29  tschachim
  *	New switches, PanelSwitchScenarioHandler
  *	
  *	Revision 1.24  2005/05/26 15:58:40  tschachim
  *	New fuel cell displays and controls
  *	Some code moved for better readability
  *	
  *	Revision 1.23  2005/05/12 00:26:58  movieman523
  *	Added O2 tank quantity failure on Apollo 13.
  *	
  *	Revision 1.22  2005/05/05 21:40:56  tschachim
  *	Introduced cryo fans, fuel cell indicators and cabin indicators
  *	
  *	Revision 1.21  2005/04/22 16:01:54  tschachim
  *	Removed fuel cell test-code
  *	
  *	Revision 1.20  2005/04/22 14:10:03  tschachim
  *	PanelSDK introduced
  *	Panel id defines
  *	New switches and indicators
  *	ToggleSwitch.Init changed
  *	SwitchListener introduced
  *	
  *	Revision 1.19  2005/04/16 00:14:10  tschachim
  *	fixed dsky keyboard and g&n panel lights
  *	
  *	Revision 1.18  2005/04/10 19:27:04  flydba
  *	*** empty log message ***
  *	
  *	Revision 1.17  2005/04/10 16:01:40  flydba
  *	*** empty log message ***
  *	
  *	Revision 1.16  2005/04/10 14:29:41  flydba
  *	*** empty log message ***
  *	
  *	Revision 1.15  2005/04/10 03:00:47  flydba
  *	*** empty log message ***
  *	
  *	Revision 1.14  2005/04/10 01:52:04  flydba
  *	*** empty log message ***
  *	
  *	Revision 1.13  2005/04/01 15:32:51  tschachim
  *	Added RCSIndicatorsSwitch
  *	
  *	Revision 1.12  2005/03/16 19:40:42  tschachim
  *	Rechanged MFDSPEC lines as in revision 1.2
  *	
  *	Revision 1.11  2005/03/16 16:04:58  yogenfrutz
  *	changed for splitted csm panel (resolves ATI bug)
  *	
  *	Revision 1.10  2005/03/16 13:39:06  yogenfrutz
  *	changed position of docking panel MFD by 1pixel lower and 1 pixel right for better look
  *	
  *	Revision 1.9  2005/03/14 17:46:27  yogenfrutz
  *	Added changes for "light off" docking panel MFD,yogenfrutz
  *	
  *	Revision 1.8  2005/03/13 21:23:02  chode99
  *	G-gauge displays the new calculation of g (aZAcc).
  *	
  *	Revision 1.7  2005/03/11 17:54:00  tschachim
  *	Introduced GuardedToggleSwitch and GuardedThreePosSwitch
  *	
  *	Revision 1.6  2005/03/10 19:06:24  tschachim
  *	fixed "one pixel" bug
  *	
  *	Revision 1.5  2005/03/09 22:09:02  tschachim
  *	Docking panel camera without changing direction from Yogenfrutz
  *	Switchable docking panel MFD
  *	
  *	Revision 1.4  2005/03/05 02:03:40  tschachim
  *	Docking MFD is now the right MFD,
  *	button click sound added
  *	
  *	Revision 1.3  2005/03/03 18:00:18  tschachim
  *	docking panel and MFD
  *	
  *	Revision 1.2  2005/03/02 01:19:03  chode99
  *	Changed MFDSPEC lines to be same size as LM, and added button definitions, like the LM.
  *	For some unknown reason, this seems to prevent the CTDs that were occuring when issuing certain MFD commands.
  *	
  *	Revision 1.1  2005/02/11 12:54:07  tschachim
  *	Initial version
  *	
  **************************************************************************/

#include "Orbitersdk.h"
#include <stdio.h>
#include <math.h>
#include "OrbiterSoundSDK3.h"
#include "soundlib.h"

#include "resource.h"

#define LOADBMP(id) (LoadBitmap (g_Param.hDLL, MAKEINTRESOURCE (id)))

#include "nasspdefs.h"
#include "nasspsound.h"

#include "toggleswitch.h"
#include "apolloguidance.h"
#include "dsky.h"
#include "csmcomputer.h"
#include "IMU.h"

#include "saturn.h"

extern GDIParams g_Param;

void BaseInit() {

	// need to init device-dependent resources here in case the screen mode has changed
	g_Param.col[2] = oapiGetColour(154, 154, 154);
	g_Param.col[3] = oapiGetColour(3, 3, 3);
	g_Param.col[4] = oapiGetColour(255, 0, 255);
	g_Param.col[5] = oapiGetColour(255, 0, 255);
}

//Needle function by Rob Conley from Mercury code
void DrawNeedle (HDC hDC, int x, int y, double rad, double angle, HPEN pen0, HPEN pen1)
{
	double dx = rad * cos(angle), dy = rad * sin(angle);
	HGDIOBJ oldObj;

	oldObj = SelectObject (hDC, pen1);
	MoveToEx (hDC, x, y, 0); LineTo (hDC, x + (int)(0.85*dx+0.5), y - (int)(0.85*dy+0.5));
	SelectObject (hDC, oldObj);
	oldObj = SelectObject (hDC, pen0);
	MoveToEx (hDC, x, y, 0); LineTo (hDC, x + (int)(dx+0.5), y - (int)(dy+0.5));
	SelectObject (hDC, oldObj);
}

void Saturn::RedrawPanel_G (SURFHANDLE surf)
{
	double alpha;
	double range;

	alpha = aZAcc/G;

	//sprintf(oapiDebugString(), "Accel %f", alpha);
	if (alpha > 15)
		alpha = 15;
	if (alpha < -1)
		alpha = -1;

	range = 235 * RAD;
	range = range / 15;
	alpha = 15 - alpha;
	HDC hDC = oapiGetDC (surf);
	DrawNeedle (hDC, 27, 27, 26.0, (alpha*range)-50*RAD, g_Param.pen[2], g_Param.pen[3] );//(alpha * range)
	oapiReleaseDC (surf, hDC);

	oapiBlt (surf, srf[15], 0, 0, 0, 0, 56, 57, SURF_PREDEF_CK);
}

void Saturn::RedrawPanel_Thrust (SURFHANDLE surf)
{
	double alpha;
	double range;

	//
	// MUSTFIX
	//
	// Note: on a real Saturn, this _ISN'T_ a thrust meter! It shows pressure at the top of the LET, or
	// SPS combustion chamber pressure.
	//

	alpha = GetEngineLevel(ENGINE_MAIN) * 100 * ThrustAdjust;

	if (alpha > 100)
		alpha = 100;

	range = 270 * RAD;
	range = range / 100;
	alpha = 100 - alpha;
	HDC hDC = oapiGetDC (surf);
	DrawNeedle (hDC, 48, 45, 20.0, (alpha*range)-45*RAD, g_Param.pen[4], g_Param.pen[4]);//(alpha * range)
	oapiReleaseDC (surf, hDC);

	oapiBlt (surf, srf[SRF_THRUSTMETER], 0, 0, 0, 0, 95, 91, SURF_PREDEF_CK);
}

// Altimeter Needle function by Rob Conley from Mercury code, Heavily modified to have non linear gauge range... :):)

void Saturn::RedrawPanel_Alt (SURFHANDLE surf)
{
	double alpha;
	double range;

	alpha = GetAltitude();
	alpha = alpha / 0.305;

#define ALTIMETER_X_CENTER	68
#define ALTIMETER_Y_CENTER	69
#define ALTIMETER_RADIUS		52.0

	//sprintf(oapiDebugString(), "altitude %f", alpha);
	if (alpha > 50000) alpha = 50000;

	if (alpha < 4001){
		range = 120 * RAD;
		range = range / 4000;
		alpha = 4000 - alpha;
		HDC hDC = oapiGetDC (surf);
		DrawNeedle (hDC, ALTIMETER_X_CENTER, ALTIMETER_Y_CENTER, ALTIMETER_RADIUS, (alpha*range)+150*RAD, g_Param.pen[4], g_Param.pen[4]);//(alpha * range)
		oapiReleaseDC (surf, hDC);
	}
	else if (alpha > 4001 && alpha < 6001){
		range = 35 * RAD;
		range = range / 2000;
		alpha = 2000 - alpha;
		HDC hDC = oapiGetDC (surf);
		DrawNeedle (hDC, ALTIMETER_X_CENTER, ALTIMETER_Y_CENTER, ALTIMETER_RADIUS, (alpha*range)+185*RAD, g_Param.pen[4], g_Param.pen[4]);//(alpha * range)
		oapiReleaseDC (surf, hDC);
	}
	else if (alpha > 6001 && alpha < 8001){
		range = 25 * RAD;
		range = range / 2000;
		alpha = 2000 - alpha;
		HDC hDC = oapiGetDC (surf);
		DrawNeedle (hDC, ALTIMETER_X_CENTER, ALTIMETER_Y_CENTER, ALTIMETER_RADIUS, (alpha*range)+165*RAD, g_Param.pen[4], g_Param.pen[4]);//(alpha * range)
		oapiReleaseDC (surf, hDC);
	}
	else if (alpha > 8001 && alpha < 10001){
		range = 20 * RAD;
		range = range / 2000;
		alpha = 2000 - alpha;
		HDC hDC = oapiGetDC (surf);
		DrawNeedle (hDC, ALTIMETER_X_CENTER, ALTIMETER_Y_CENTER, ALTIMETER_RADIUS, (alpha*range)+150*RAD, g_Param.pen[4], g_Param.pen[4]);//(alpha * range)
		oapiReleaseDC (surf, hDC);
	}
	else if (alpha > 10001 && alpha < 20001){
		range = 55 * RAD;
		range = range / 10000;
		alpha = 10000 - alpha;
		HDC hDC = oapiGetDC (surf);
		DrawNeedle (hDC, ALTIMETER_X_CENTER, ALTIMETER_Y_CENTER, ALTIMETER_RADIUS, (alpha*range)+70*RAD, g_Param.pen[4], g_Param.pen[4]);//(alpha * range)
		oapiReleaseDC (surf, hDC);
	}
	else if (alpha > 20001 && alpha < 40001){
		range = 65 * RAD;
		range = range / 20000;
		alpha = 20000 - alpha;
		HDC hDC = oapiGetDC (surf);
		DrawNeedle (hDC, ALTIMETER_X_CENTER, ALTIMETER_Y_CENTER, ALTIMETER_RADIUS, (alpha*range)+15*RAD, g_Param.pen[4], g_Param.pen[4]);//(alpha * range)
		oapiReleaseDC (surf, hDC);
	}
	else {
		range = 20 * RAD;
		range = range / 10000;
		alpha = 10000 - alpha;
		HDC hDC = oapiGetDC (surf);
		DrawNeedle (hDC, ALTIMETER_X_CENTER, ALTIMETER_Y_CENTER, ALTIMETER_RADIUS, (alpha*range)+10*RAD, g_Param.pen[4], g_Param.pen[4]);//(alpha * range)
		oapiReleaseDC (surf, hDC);
	}
	oapiBlt (surf, srf[SRF_ALTIMETER], 0, 0, 0, 0, 137, 139, SURF_PREDEF_CK);
}

void Saturn::RedrawPanel_MFDButton(SURFHANDLE surf, int mfd, int side, int xoffset, int yoffset) {

	HDC hDC = oapiGetDC (surf);
	SelectObject (hDC, g_Param.font[2]);
	SetTextColor (hDC, RGB(196, 196, 196));
	SetTextAlign (hDC, TA_CENTER);
	SetBkMode (hDC, TRANSPARENT);
	const char *label;
	for (int bt = 0; bt < 6; bt++) {
		if (label = oapiMFDButtonLabel (mfd, bt+side*6))
			TextOut (hDC, 10 + xoffset, 3 + 31 * bt + yoffset, label, strlen(label));
		else break;
	}
	oapiReleaseDC (surf, hDC);
}

void Saturn::RedrawPanel_SuitCabinDeltaPMeter (SURFHANDLE surf) {

	AtmosStatus atm;
	GetAtmosStatus(atm);

	// Suit cabin pressure difference
	double scdp = (atm.SuitReturnPressurePSI - atm.CabinPressurePSI) * (INH2O / PSI);

	//
	// Limit needle to the meter.
	//

	if (scdp > 5.5)	scdp = 5.5;
	if (scdp < -5.5) scdp = -5.5;

	scdp = (scdp / 5.0) * 60.0;

	// O2 main regulator output flow 
	double cf = atm.CabinRegulatorFlowLBH + atm.O2DemandFlowLBH + atm.DirectO2FlowLBH;

	//
	// Limit needle to the meter.
	//

	if (cf < 0.1) cf = 0.1;
	if (cf > 1.1) cf = 1.1;

	cf = (cf - .6) / .4 * 60.0;

	HDC hDC = oapiGetDC (surf);
	DrawNeedle (hDC,  0, 22, 20.0, scdp * RAD, g_Param.pen[4], g_Param.pen[4]);
	DrawNeedle (hDC, 45, 22, 20.0, (180.0 - cf) * RAD, g_Param.pen[4], g_Param.pen[4]);
	oapiReleaseDC (surf, hDC);

	oapiBlt (surf, srf[SRF_SUITCABINDELTAPMETER], 0, 13, 0, 0, 46, 18, SURF_PREDEF_CK);
}

void Saturn::RedrawPanel_SuitComprDeltaPMeter (SURFHANDLE surf) {

	// O2 main regulator output flow 
	// TODO: Is this the correct flow for that meter? No documentation found yet...
	AtmosStatus atm;
	GetAtmosStatus(atm);

	double cf = atm.CabinRegulatorFlowLBH + atm.O2DemandFlowLBH + atm.DirectO2FlowLBH;
	cf = (cf - .6) / .4 * 60.0;
	if (cf > 90) cf = 90;
	if (cf < -90) cf = -90;
	
	// Suit compressor pressure difference
	double scdp = (atm.SuitPressurePSI - atm.SuitReturnPressurePSI);
	scdp = (scdp - .5) / .5 * 60.0;
	if (scdp > 90) scdp = 90;
	if (scdp < -90) scdp = -90;

	HDC hDC = oapiGetDC (surf);
	DrawNeedle (hDC,  0, 22, 20.0, cf * RAD, g_Param.pen[4], g_Param.pen[4]);
	DrawNeedle (hDC, 45, 22, 20.0, (180.0 - scdp) * RAD, g_Param.pen[4], g_Param.pen[4]);
	oapiReleaseDC (surf, hDC);
}

void Saturn::RedrawPanel_O2CryoTankPressureIndicator(SURFHANDLE surf, SURFHANDLE needle, double value, int xOffset, int xNeedle) {

	if (value < 100.0)
		oapiBlt(surf, needle, xOffset, 110, xNeedle, 0, 10, 10, SURF_PREDEF_CK);

	else if (value <= 500.0) 
		oapiBlt(surf, needle, xOffset, 110 - (int)((value - 100.0) * 0.065), xNeedle, 0, 10, 10, SURF_PREDEF_CK);

	else if (value <= 850.0)
		oapiBlt(surf, needle, xOffset, 84 - (int)((value - 500.0) * 0.07714), xNeedle, 0, 10, 10, SURF_PREDEF_CK);

	else if (value <= 900.0)
		oapiBlt(surf, needle, xOffset, 57 - (int)((value - 850.0) * 0.38), xNeedle, 0, 10, 10, SURF_PREDEF_CK);

	else if (value <= 950.0)
		oapiBlt(surf, needle, xOffset, 38 - (int)((value - 900.0) * 0.42), xNeedle, 0, 10, 10, SURF_PREDEF_CK);

	else if (value <= 1050.0)
		oapiBlt(surf, needle, xOffset, 17 - (int)((value - 950.0) * 0.13), xNeedle, 0, 10, 10, SURF_PREDEF_CK);

	else
		oapiBlt(surf, needle, xOffset, 4, xNeedle, 0, 10, 10, SURF_PREDEF_CK);

}

void Saturn::RedrawPanel_CryoTankIndicators(SURFHANDLE surf) {

	TankPressures press;

	GetTankPressures(press);

	// H2Tank1 pressure
	double value = press.H2Tank1PressurePSI;
	if (value < 0.0) value = 0.0;
	if (value > 400.0) value = 400.0;
	oapiBlt(surf, srf[SRF_NEEDLE],  0, (110 - (int)(value / 400.0 * 104.0)), 0, 0, 10, 10, SURF_PREDEF_CK);

	// H2Tank2 pressure
	value = press.H2Tank2PressurePSI;
	if (value < 0.0) value = 0.0;
	if (value > 400.0) value = 400.0;
	oapiBlt(surf, srf[SRF_NEEDLE], 53, (110 - (int)(value / 400.0 * 104.0)), 10, 0, 10, 10, SURF_PREDEF_CK);

	// O2Tank1 / O2SurgeTank pressure
	if (O2PressIndSwitch)  
		value = press.O2Tank1PressurePSI;
	else
		value = *(double*) Panelsdk.GetPointerByString("HYDRAULIC:O2SURGETANK:PRESS") * PSI;
	RedrawPanel_O2CryoTankPressureIndicator(surf, srf[SRF_NEEDLE], value, 86, 0);

	// O2Tank2 pressure
	value = press.O2Tank2PressurePSI;
	RedrawPanel_O2CryoTankPressureIndicator(surf, srf[SRF_NEEDLE], value, 139, 10);

	// H2Tank1 quantity
	value = *(double*) Panelsdk.GetPointerByString("HYDRAULIC:H2TANK1:MASS") / CSM_H2TANK_CAPACITY ;
	if (value < 0.0) value = 0.0;
	if (value > 1.0) value = 1.0;
	oapiBlt(surf, srf[SRF_NEEDLE],  172, (110 - (int)(value * 104.0)), 0, 0, 10, 10, SURF_PREDEF_CK);

	// H2Tank2 quantity
	value = *(double*) Panelsdk.GetPointerByString("HYDRAULIC:H2TANK2:MASS") / CSM_H2TANK_CAPACITY ;
	if (value < 0.0) value = 0.0;
	if (value > 1.0) value = 1.0;
	oapiBlt(surf, srf[SRF_NEEDLE],  225, (110 - (int)(value * 104.0)), 10, 0, 10, 10, SURF_PREDEF_CK);

	// O2Tank1 quantity
	value = *(double*) Panelsdk.GetPointerByString("HYDRAULIC:O2TANK1:MASS") / CSM_O2TANK_CAPACITY ;
	if (value < 0.0) value = 0.0;
	if (value > 1.0) value = 1.0;
	oapiBlt(surf, srf[SRF_NEEDLE],  258, (110 - (int)(value * 104.0)), 0, 0, 10, 10, SURF_PREDEF_CK);

	// O2Tank2 quantity
	value = *(double*) Panelsdk.GetPointerByString("HYDRAULIC:O2TANK2:MASS") / CSM_O2TANK_CAPACITY ;
	if (value < 0.0) value = 0.0;
	if (value > 1.0) value = 1.0;

	//
	// Apollo 13 O2 tank 2 quantity display failed offscale high around 46:45.
	//

#define O2FAILURETIME	(46.0 * 3600.0 + 45.0 * 60.0)

	if (ApolloNo == 13) {
		if (MissionTime >= (O2FAILURETIME + 5.0)) {
			value = 1.05;
		}
		else if (MissionTime >= O2FAILURETIME) {
			value += (1.05 - value) * ((MissionTime - O2FAILURETIME) / 5.0);
		}
	}
	oapiBlt(surf, srf[SRF_NEEDLE],  311, (110 - (int)(value * 104.0)), 10, 0, 10, 10, SURF_PREDEF_CK);
}

void Saturn::RedrawPanel_CabinIndicators (SURFHANDLE surf) {

	AtmosStatus atm;
	GetAtmosStatus(atm);

	// Suit temperature
	double value = KelvinToFahrenheit(atm.SuitTempK);
	if (value < 20.0) value = 20.0;
	if (value > 95.0) value = 95.0;
	oapiBlt(surf, srf[SRF_NEEDLE],  1, (110 - (int)((value - 20.0) / 75.0 * 104.0)), 0, 0, 10, 10, SURF_PREDEF_CK);

	// Cabin temperature
	value = KelvinToFahrenheit(atm.CabinTempK);
	if (value < 40.0) value = 40.0;
	if (value > 120.0) value = 120.0;
	oapiBlt(surf, srf[SRF_NEEDLE],  53, (110 - (int)((value - 40.0) / 80.0 * 104.0)), 10, 0, 10, 10, SURF_PREDEF_CK);

	// Suit pressure
	value = atm.SuitReturnPressurePSI;
	if (value < 0.0) value = 0.0;
	if (value > 16.0) value = 16.0;
	if (value < 6.0)
		oapiBlt(surf, srf[SRF_NEEDLE],  101, (108 - (int)(value / 6.0 * 55.0)), 0, 0, 10, 10, SURF_PREDEF_CK);
	else
		oapiBlt(surf, srf[SRF_NEEDLE],  101, (53 - (int)((value - 6.0) / 10.0 * 45.0)), 0, 0, 10, 10, SURF_PREDEF_CK);

	// Cabin pressure
	value = atm.CabinPressurePSI;
	if (value < 0.0) value = 0.0;
	if (value > 16.0) value = 16.0;
	if (value < 6.0)
		oapiBlt(surf, srf[SRF_NEEDLE],  153, (108 - (int)(value / 6.0 * 55.0)), 10, 0, 10, 10, SURF_PREDEF_CK);
	else
		oapiBlt(surf, srf[SRF_NEEDLE],  153, (53 - (int)((value - 6.0) / 10.0 * 45.0)), 10, 0, 10, 10, SURF_PREDEF_CK);

	// Suit CO2 partial pressure
	value = atm.SuitCO2MMHG;
	if (value < 0.0) value = 0.0;
	if (value > 30.0) value = 30.0;	
	if (value < 10.0)
		oapiBlt(surf, srf[SRF_NEEDLE],  215, (109 - (int)(value / 10.0 * 55.0)), 10, 0, 10, 10, SURF_PREDEF_CK);
	else if (value < 15.0)
		oapiBlt(surf, srf[SRF_NEEDLE],  215, (54 - (int)((value - 10.0) / 5.0 * 19.0)), 10, 0, 10, 10, SURF_PREDEF_CK);
	else if (value < 20.0)
		oapiBlt(surf, srf[SRF_NEEDLE],  215, (35 - (int)((value - 15.0) / 5.0 * 15.0)), 10, 0, 10, 10, SURF_PREDEF_CK);
	else
		oapiBlt(surf, srf[SRF_NEEDLE],  215, (20 - (int)((value - 20.0) / 10.0 * 14.0)), 10, 0, 10, 10, SURF_PREDEF_CK);

}

void Saturn::RedrawPanel_FuelCellIndicators (SURFHANDLE surf) {

	double h2flow, o2flow, temp, condenserTemp;

	// read values of the selected fuel cell
	if (FuelCellIndicatorsSwitch == 1) {
		h2flow = *(double*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL1:H2FLOW") * LBH;
		o2flow = *(double*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL1:O2FLOW") * LBH;
		temp = KelvinToFahrenheit(*(double*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL1:TEMP"));
		condenserTemp = KelvinToFahrenheit(*(double*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL1:CONDENSERTEMP"));

	} else if (FuelCellIndicatorsSwitch == 2) {
		h2flow = *(double*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL2:H2FLOW") * LBH;
		o2flow = *(double*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL2:O2FLOW") * LBH;
		temp = KelvinToFahrenheit(*(double*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL2:TEMP"));
		condenserTemp = KelvinToFahrenheit(*(double*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL2:CONDENSERTEMP"));

	} else {
		h2flow = *(double*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL3:H2FLOW") * LBH;
		o2flow = *(double*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL3:O2FLOW") * LBH;
		temp = KelvinToFahrenheit(*(double*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL3:TEMP"));
		condenserTemp = KelvinToFahrenheit(*(double*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL3:CONDENSERTEMP"));
	}

	// Fuel Cell H2 flow
	if (h2flow < 0.0) h2flow = 0.0;
	if (h2flow > 0.2) h2flow = 0.2;
	if (h2flow < 0.05)
		oapiBlt(surf, srf[SRF_NEEDLE],  0, (111 - (int)(h2flow / 0.05 * 21.0)), 0, 0, 10, 10, SURF_PREDEF_CK);
	else if (h2flow < 0.15)
		oapiBlt(surf, srf[SRF_NEEDLE],  0, (90 - (int)((h2flow - 0.05) / 0.1 * 65.0)), 0, 0, 10, 10, SURF_PREDEF_CK);
	else
		oapiBlt(surf, srf[SRF_NEEDLE],  0, (25 - (int)((h2flow - 0.15) / 0.05 * 21.0)), 0, 0, 10, 10, SURF_PREDEF_CK);

	// Fuel Cell O2 flow
	if (o2flow < 0.0) o2flow = 0.0;
	if (o2flow > 1.6) o2flow = 1.6;
	if (o2flow < 0.4)
		oapiBlt(surf, srf[SRF_NEEDLE],  53, (111 - (int)(o2flow / 0.4 * 21.0)), 10, 0, 10, 10, SURF_PREDEF_CK);
	else if (o2flow < 1.2)
		oapiBlt(surf, srf[SRF_NEEDLE],  53, (90 - (int)((o2flow - 0.4) / 0.8 * 65.0)), 10, 0, 10, 10, SURF_PREDEF_CK);
	else
		oapiBlt(surf, srf[SRF_NEEDLE],  53, (25 - (int)((o2flow - 1.2) / 0.4 * 21.0)), 10, 0, 10, 10, SURF_PREDEF_CK);

	// Fuel Cell skin temperature
	if (temp < 100.0) temp = 100.0;
	if (temp > 550.0) temp = 550.0;
	if (temp < 400.0)
		oapiBlt(surf, srf[SRF_NEEDLE],  86, (109 - (int)((temp - 100.0) / 300.0 * 53.0)), 0, 0, 10, 10, SURF_PREDEF_CK);
	else if (temp < 500.0)
		oapiBlt(surf, srf[SRF_NEEDLE],  86, (56 - (int)((temp - 400.0) / 100.0 * 40.0)), 0, 0, 10, 10, SURF_PREDEF_CK);
	else
		oapiBlt(surf, srf[SRF_NEEDLE],  86, (16 - (int)((temp - 500.0) / 50.0 * 12.0)), 0, 0, 10, 10, SURF_PREDEF_CK);

	// Fuel Cell condenser exhaust temperature
	if (condenserTemp < 150.0) condenserTemp = 150.0;
	if (condenserTemp > 250.0) condenserTemp = 250.0;
	oapiBlt(surf, srf[SRF_NEEDLE],  139, (109 - (int)((condenserTemp - 150.0) / 100.0 * 103.0)), 10, 0, 10, 10, SURF_PREDEF_CK);
}


//
// Free all allocated surfaces.
//

void Saturn::ReleaseSurfaces ()
{
	for (int i = 0; i < nsurf; i++) {
		if (srf[i]) {
			oapiDestroySurface (srf[i]);
			srf[i] = 0;
		}
	}
}

//
// Load all the surfaces and initialise the panel.
//

void Saturn::InitPanel (int panel)

{
// Panel dependency temporary disabled because of the new panels	
/*	switch (panel) {

	case 0:// ilumination panel left
    case 2:
    case 4://added for splitted panel
		srf[0] = oapiCreateSurface (LOADBMP (IDB_ILMFCSM));
		srf[1] = oapiCreateSurface (LOADBMP (IDB_ILMINDICATORS1));
		srf[2] = oapiCreateSurface (LOADBMP (IDB_NEEDLE1));
		srf[3] = oapiCreateSurface (LOADBMP (IDB_HORIZON));
		srf[4] = oapiCreateSurface (LOADBMP (IDB_DIGITAL));
		srf[5] = oapiCreateSurface (LOADBMP (IDB_HORIZON2));
		srf[6] = oapiCreateSurface (LOADBMP (IDB_ILMSWITCHUP));
		srf[7] = oapiCreateSurface (LOADBMP (IDB_ILMSWLEVER));
		srf[8] = oapiCreateSurface (LOADBMP (IDB_ILMSECSWITCH));
		srf[9] = oapiCreateSurface (LOADBMP (IDB_ILMABORT));
		srf[10] = oapiCreateSurface (LOADBMP (IDB_ILMANNUN));
		srf[11] = oapiCreateSurface (LOADBMP (IDB_ILMLAUNCH));
		srf[12] = oapiCreateSurface (LOADBMP (IDB_ILM_LV_ENG));
		srf[13] = oapiCreateSurface (LOADBMP (IDB_ILMLIGHTS2));
		srf[14] = oapiCreateSurface (LOADBMP (IDB_ANLG_ALT));
		srf[15] = oapiCreateSurface (LOADBMP (IDB_ANLG_GMETER));
		srf[16] = oapiCreateSurface (LOADBMP (IDB_THRUST));
		srf[17] = oapiCreateSurface (LOADBMP (IDB_ILMGUARDSWITCH));
		srf[18] = oapiCreateSurface (LOADBMP (IDB_ILMMASTER_ALARM));
		srf[19] = oapiCreateSurface (LOADBMP (IDB_MASTER_ALARM_BRIGHT));
		//srf[20] = oapiCreateSurface (LOADBMP (IDB_BUTTON));
		srf[SRF_DSKY] = oapiCreateSurface (LOADBMP (IDB_ILMDSKY_LIGHTS));
		srf[SRF_ALLROUND] = oapiCreateSurface (LOADBMP (IDB_ILMALLROUND));
		srf[23] = oapiCreateSurface (LOADBMP (IDB_ILMTHREEPOSSWITCH));
		srf[24] = oapiCreateSurface (LOADBMP (IDB_MFDFRAME_ILM));
		srf[25] = oapiCreateSurface (LOADBMP (IDB_MFDPOWER_ILM));
		srf[26] = oapiCreateSurface (LOADBMP (IDB_DOCKINGSWITCHES_ILM));
		oapiSetSurfaceColourKey (srf[2], g_Param.col[4]);
		oapiSetSurfaceColourKey (srf[3], 0);
		oapiSetSurfaceColourKey (srf[5], g_Param.col[5]);
		oapiSetSurfaceColourKey (srf[14], g_Param.col[4]);
		oapiSetSurfaceColourKey (srf[15], g_Param.col[4]);
		oapiSetSurfaceColourKey (srf[16], g_Param.col[4]);
		oapiSetSurfaceColourKey (srf[SRF_ALLROUND], g_Param.col[4]);
		break;

	case 1: // panel
	case 3:
    case 5://added for splitted panel
*/
	
		//
		// I'm pretty sure that some of these bitmaps aren't used anymore.
		// We need to go through these and delete the unused ones at some
		// point, and remove them from the resource.rc file so as not to
		// bloat the DLL.
		//

		srf[0]							= oapiCreateSurface (LOADBMP (IDB_FCSM));
		srf[SRF_INDICATOR]				= oapiCreateSurface (LOADBMP (IDB_INDICATOR));
		srf[SRF_NEEDLE]					= oapiCreateSurface (LOADBMP (IDB_NEEDLE));
		srf[3]							= oapiCreateSurface (LOADBMP (IDB_HORIZON));
		srf[SRF_DIGITAL]				= oapiCreateSurface (LOADBMP (IDB_DIGITAL));
		srf[5]							= oapiCreateSurface (LOADBMP (IDB_HORIZON2));
		srf[SRF_SWITCHUP]				= oapiCreateSurface (LOADBMP (IDB_SWITCHUP));
		srf[SRF_SWITCHLEVER]			= oapiCreateSurface (LOADBMP (IDB_SWLEVER));
		srf[SRF_SWITCHGUARDS]			= oapiCreateSurface (LOADBMP (IDB_SWITCHGUARDS));
		srf[SRF_ABORT]					= oapiCreateSurface (LOADBMP (IDB_ABORT));
		srf[10]							= oapiCreateSurface (LOADBMP (IDB_ANNUN));
		srf[11]							= oapiCreateSurface (LOADBMP (IDB_LAUNCH));
		srf[12]							= oapiCreateSurface (LOADBMP (IDB_LV_ENG));
		srf[13]							= oapiCreateSurface (LOADBMP (IDB_LIGHTS2));
		srf[SRF_ALTIMETER]				= oapiCreateSurface (LOADBMP (IDB_ANLG_ALT));
		srf[15]							= oapiCreateSurface (LOADBMP (IDB_ANLG_GMETER));
		srf[SRF_THRUSTMETER]			= oapiCreateSurface (LOADBMP (IDB_THRUST));
		srf[SRF_SEQUENCERSWITCHES]		= oapiCreateSurface (LOADBMP (IDB_SEQUENCERSWITCHES));
		srf[18]							= oapiCreateSurface (LOADBMP (IDB_MASTER_ALARM));
		srf[SRF_MASTERALARM_BRIGHT]		= oapiCreateSurface (LOADBMP (IDB_MASTER_ALARM_BRIGHT));
		srf[SRF_DSKY]					= oapiCreateSurface (LOADBMP (IDB_DSKY_LIGHTS));
		srf[SRF_ALLROUND]				= oapiCreateSurface (LOADBMP (IDB_ALLROUND));
		srf[SRF_THREEPOSSWITCH]			= oapiCreateSurface (LOADBMP (IDB_THREEPOSSWITCH));
		srf[24]							= oapiCreateSurface (LOADBMP (IDB_MFDFRAME));
		srf[25]							= oapiCreateSurface (LOADBMP (IDB_MFDPOWER));
		srf[26]							= oapiCreateSurface (LOADBMP (IDB_DOCKINGSWITCHES));
		srf[SRF_ROTATIONALSWITCH]		= oapiCreateSurface (LOADBMP (IDB_ROTATIONALSWITCH));
		srf[SRF_SUITCABINDELTAPMETER]	= oapiCreateSurface (LOADBMP (IDB_SUITCABINDELTAPMETER));
		srf[SRF_THREEPOSSWITCH305]		= oapiCreateSurface (LOADBMP (IDB_THREEPOSSWITCH305));
		srf[SRF_DSKYDISP]       		= oapiCreateSurface (LOADBMP (IDB_DSKY_DISP));
		srf[SRF_FDAI]	        		= oapiCreateSurface (LOADBMP (IDB_FDAI));
		srf[SRF_FDAIROLL]       		= oapiCreateSurface (LOADBMP (IDB_FDAI_ROLL));
		srf[SRF_CWSLIGHTS]       		= oapiCreateSurface (LOADBMP (IDB_CWS_LIGHTS));
		srf[SRF_EVENT_TIMER_DIGITS]    	= oapiCreateSurface (LOADBMP (IDB_EVENT_TIMER));
		srf[SRF_DSKYKEY]		    	= oapiCreateSurface (LOADBMP (IDB_DSKY_KEY));

		oapiSetSurfaceColourKey (srf[SRF_NEEDLE],				g_Param.col[4]);
		oapiSetSurfaceColourKey (srf[3],						0);
		oapiSetSurfaceColourKey (srf[5],						g_Param.col[5]);
		oapiSetSurfaceColourKey (srf[SRF_SWITCHLEVER],			g_Param.col[4]);
		oapiSetSurfaceColourKey (srf[SRF_SWITCHUP],				g_Param.col[4]);
		oapiSetSurfaceColourKey (srf[SRF_SWITCHGUARDS],			g_Param.col[4]);
		oapiSetSurfaceColourKey (srf[SRF_ALTIMETER],			g_Param.col[4]);
		oapiSetSurfaceColourKey (srf[15],						g_Param.col[4]);
		oapiSetSurfaceColourKey (srf[SRF_THRUSTMETER],			g_Param.col[4]);
		oapiSetSurfaceColourKey (srf[SRF_SEQUENCERSWITCHES],	g_Param.col[4]);
		oapiSetSurfaceColourKey (srf[SRF_ALLROUND],				g_Param.col[4]);
		oapiSetSurfaceColourKey (srf[SRF_THREEPOSSWITCH],		g_Param.col[4]);
		oapiSetSurfaceColourKey (srf[SRF_ROTATIONALSWITCH],		g_Param.col[4]);
		oapiSetSurfaceColourKey (srf[SRF_SUITCABINDELTAPMETER],	g_Param.col[4]);
		oapiSetSurfaceColourKey (srf[SRF_THREEPOSSWITCH305],	g_Param.col[4]);
		oapiSetSurfaceColourKey (srf[SRF_DSKYDISP],				g_Param.col[4]);
		oapiSetSurfaceColourKey (srf[SRF_FDAI],					g_Param.col[4]);
		oapiSetSurfaceColourKey (srf[SRF_FDAIROLL],				g_Param.col[4]);
/*		break;
	}
*/
	SetSwitches(panel);
}

bool Saturn::clbkLoadPanel (int id) {

	static HBITMAP hBmpMain = 0;
	static HBITMAP hBmpLeft = 0;
	static HBITMAP hBmpRight = 0;
	static HBITMAP hBmpLower = 0;
	static HBITMAP hBmpHatch = 0;
	static HBITMAP hBmpRNDZ_Left = 0;
	static HBITMAP hBmpRNDZ_Right = 0;
	static bool recursion;

	// avoid recursive calls
	if (recursion) return true;
	recursion = true;

	if (!InPanel && id != PanelId) {
		// sometimes clbkLoadPanel is called inside oapiSetPanel, 
		// sometimes not, so ignore the recursive call
		oapiSetPanel(PanelId);
		id = PanelId;
	}
	recursion = false;

	ReleaseSurfaces();
	HBITMAP hBmp;

	//
	// Should we display a panel for unmanned flights?
	//

	if (!Crewed)
		return false;

	switch(id) {
	case SATPANEL_LOWER:
//		if (!hBmpLower)
			hBmpLower = LoadBitmap (g_Param.hDLL, MAKEINTRESOURCE (IDB_CSM_LOWER_PANEL));
		hBmp = hBmpLower;
		oapiSetPanelNeighbours(-1, -1, SATPANEL_MAIN, -1);
		break;

	case SATPANEL_MAIN:
//		if (!hBmpMain)
			hBmpMain = LoadBitmap (g_Param.hDLL, MAKEINTRESOURCE (IDB_CSM_MAIN_PANEL));
		hBmp = hBmpMain;
		oapiSetPanelNeighbours(SATPANEL_LEFT, SATPANEL_RIGHT, SATPANEL_HATCH_WINDOW, SATPANEL_LOWER);

		break;

	case SATPANEL_LEFT:
//		if (!hBmpLeft)
			hBmpLeft = LoadBitmap (g_Param.hDLL, MAKEINTRESOURCE (IDB_CSM_LEFT_PANEL));
		hBmp = hBmpLeft;
		oapiSetPanelNeighbours(-1, SATPANEL_MAIN, -1, -1);

		break;

	case SATPANEL_RIGHT:
//		if (!hBmpRight)
			hBmpRight = LoadBitmap (g_Param.hDLL, MAKEINTRESOURCE (IDB_CSM_RIGHT_PANEL));
		hBmp = hBmpRight;
		oapiSetPanelNeighbours(SATPANEL_MAIN, -1, -1, -1);
		break;

	case SATPANEL_LEFT_RNDZ_WINDOW:
//		if (!hBmpRNDZ_Left)
			hBmpRNDZ_Left = LoadBitmap (g_Param.hDLL, MAKEINTRESOURCE (IDB_CSM_LEFT_RNDZ_WINDOW));
		hBmp = hBmpRNDZ_Left;
		oapiSetPanelNeighbours(-1, SATPANEL_HATCH_WINDOW, -1, SATPANEL_MAIN);
		break;

	case SATPANEL_RIGHT_RNDZ_WINDOW:
//		if (!hBmpRNDZ_Right)
			hBmpRNDZ_Right = LoadBitmap (g_Param.hDLL, MAKEINTRESOURCE (IDB_CSM_RIGHT_RNDZ_WINDOW));
		hBmp = hBmpRNDZ_Right;
		oapiSetPanelNeighbours(SATPANEL_HATCH_WINDOW, -1, -1, SATPANEL_MAIN);
		break;

	case SATPANEL_HATCH_WINDOW:
//		if (!hBmpHatch)
			hBmpHatch = LoadBitmap (g_Param.hDLL, MAKEINTRESOURCE (IDB_CSM_HATCH_WINDOW));
		hBmp = hBmpHatch;
		oapiSetPanelNeighbours(SATPANEL_LEFT_RNDZ_WINDOW, SATPANEL_RIGHT_RNDZ_WINDOW, -1, SATPANEL_MAIN);
		break;

	}

//old areas as backup and reference to create the new panel areas

		//MFDSPEC mfds_left_l  = {{1012, 770, 1290, 1048}, 6, 6, 41, 27};
		//MFDSPEC mfds_right_l = {{1305, 770, 1583, 1048}, 6, 6, 41, 27};
		//MFDSPEC mfds_left_r  = {{253, 770, 531, 1048}, 6, 6, 41, 27};
		//MFDSPEC mfds_right_r = {{546, 770, 824, 1048}, 6, 6, 41, 27};

		//MFDSPEC mfds_dock = {{893, 627, 1112, 842}, 6, 6, 31, 31};;

		//oapiRegisterMFD (MFD_LEFT,  mfds_left_l);
		//oapiRegisterMFD (MFD_RIGHT, mfds_right_l);

        //oapiRegisterPanelArea (AID_ALTITUDE1,							_R( 547, 425,  643,  440), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_GMETER,                              _R( 301, 491,  357,  548), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_HORIZON,								_R( 853, 294,  949,  390), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE);
		//oapiRegisterPanelArea (AID_HORIZON2,							_R( 440, 537,  536,  633), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE);
		//oapiRegisterPanelArea (AID_SWITCH_HUD,                          _R( 194, 585,  329,  617), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_SM_RCS_PANEL1,                       _R( 138, 656,  232,  689), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_P12_SWITCH,							_R( 332, 585,  361,  617), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_P13,							        _R( 234, 656,  295,  689), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_SM_RCS_MODE,                         _R( 298, 656,  360,  689), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_SPS_GIMBAL_SWITCHES,                 _R( 343, 905,  487,  937), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_TLI_SWITCH,							_R( 847, 903,  870,  923), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_SPS,									_R( 221, 821,  251,  860), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_SC_SWITCH,                           _R( 285, 745,  308,  765), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_ROT_PWR,								_R( 216, 745,  239,  765), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_P17,                                 _R( 523, 912,  546,  932), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_P18,                                 _R( 588, 912,  611,  932), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_CM_RCS_LOGIC,                        _R( 616, 905,  645,  937), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_CMD_SWITCH,                          _R( 651, 899,  676,  944), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_CMP_SWITCH,                          _R( 684, 899,  709,  944), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_FCSM_SWITCH,                         _R( 515, 970,  584,  1004), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_P19,                                 _R( 247, 970,  436,  1002), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_DIRECT_ULLAGE_THRUST_ON_LIGHT,		_R( 273, 808,  303,  878), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_LIGHTS_LAUNCHER,						_R( 612, 727,  718,  817), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_LV_TANK_GAUGES,                      _R( 466, 728,  589,  807), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_SWITCH_JET,                          _R( 841, 739,  964,  784), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_EDS,                                 _R( 808, 752,  831,  772), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_DOCKING_PROBE_SWITCH,				_R(1029, 171, 1055,  280), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_P21,                                 _R(1061, 241, 1236,  273), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_CSM_SIVB_SEP_SWITCH,                 _R( 595, 825,  664,  856), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_LEM_POWER_SWITCH,					_R(1258, 248, 1281,  268), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_SIVB_LEM_SEP_SWITCH,					_R( 968, 739,  994,  785), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_P22,									_R(1045, 470, 1106,  501), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_P23,									_R(1146, 476, 1169,  507), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_P24,									_R(1047, 567, 1172,  609), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_P25,									_R(1047, 664, 1108,  705), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_P27,									_R(1502, 398, 1848,  429), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_P28,									_R(1324, 586, 1625,  695), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_P29,									_R(1620, 735, 1681,  766), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_P30,									_R(1766, 894, 1827,  925), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_CABIN_PRESS,							_R(1629, 664, 1729,  695), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_FUEL_CELL_RADIATORS,					_R(2089, 438, 2182,  516), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_P31,									_R(2090, 550, 2181,  672), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_P32,									_R(2294, 648, 2317,  668), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_P33,									_R(1987, 743, 2074,  775), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_P34,									_R(2301, 750, 2324,  770), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_FUEL_CELL_SWITCHES,					_R(2077, 701, 2285,  775), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_P35,									_R(1923, 814, 2281,  921), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_P36,									_R(1923, 963, 2326,  994), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_CABIN_FAN_SWITCHES,					_R(1417, 398, 1490,  430), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_CW,									_R(1141, 109, 1490,  194), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_SMRCS_FUEL,                          _R(1034, 328, 1146,  417), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_SPS_FUEL,                            _R(1920, 279, 2027,  367), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_EMS_SWITCH,							_R( 437, 333,  467,  364), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_BUS_PANEL,							_R(2361, 814, 2488,  994), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_05G_LIGHT,							_R( 561, 387,  585,  401), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_SPS_LIGHT,							_R( 604, 387,  628,  401), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_SPS_INJ_VLV,							_R(1924, 425, 2065,  457), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_AUTO_LIGHT,							_R( 464, 969,  480,  995), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_CMRCS_HE_DUMP_SWITCH,				_R( 666, 825,  734,  855), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_BUS_LIGHT,							_R(2445, 635, 2461,  651), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_CABIN_LIGHT,							_R(1781, 595, 1797,  611), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_CABIN_GAUGES,						_R(1693, 483, 1857,  571), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_EMS_KNOB,							_R( 442, 248,  510,  316), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_EMS_DISPLAY,							_R( 545, 264,  647,  369), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,PANEL_MAP_BACKGROUND);
        //oapiRegisterMFD (MFD_RIGHT, mfds_dock);	// MFD_USER1
		//oapiRegisterPanelArea (AID_MFDDOCK,	        _R( 851,  613, 1152      ,  864     ), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_MFDDOCK_POWER,   _R( 635,  845,  655      ,  860     ), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND);
		//oapiRegisterPanelArea (AID_SM_RCS_MODE,     _R( 719,  791,  719 + 133,  791 + 73), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND);		
	
	switch (id) {
	
	case SATPANEL_LOWER: // guidance & navigation lower equipment bay
		oapiRegisterPanelBackground (hBmp, PANEL_ATTACH_TOP|PANEL_ATTACH_BOTTOM|PANEL_ATTACH_LEFT|PANEL_MOVEOUT_RIGHT, g_Param.col[4]);
		
		//
		// Lower panel uses the second DSKY.
		//

		oapiRegisterPanelArea (AID_DSKY2_DISPLAY,								_R(1582,  341, 1687,  517), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,					PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_DSKY2_LIGHTS,								_R(1438,  346, 1540,  466), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,				PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_DSKY2_KEY,			                        _R(1418,  536, 1705,  657), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN|PANEL_MOUSE_UP,	PANEL_MAP_BACKGROUND);
		
		oapiRegisterPanelArea (AID_MASTER_ALARM3,								_R(1084,  607, 1129,  643), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,					PANEL_MAP_BACKGROUND);
		
		SetCameraDefaultDirection(_V(0.0, 0.0, 1.0));
		break;    
	
	case SATPANEL_MAIN: // main instrument panel
		oapiRegisterPanelBackground (hBmp, PANEL_ATTACH_TOP|PANEL_ATTACH_BOTTOM|PANEL_ATTACH_LEFT|PANEL_MOVEOUT_RIGHT, g_Param.col[4]);
		
		oapiRegisterPanelArea (AID_ABORT_BUTTON,								_R( 862,  600,  924,  631), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,					PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_SEQUENCERSWITCHES,							_R( 802,  918,  990, 1100), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN|PANEL_MOUSE_UP,   PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_LV_ENGINE_LIGHTS,							_R( 843,  735,  944,  879), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,					PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_SEPARATIONSWITCHES,		    				_R(1087,  942, 1340, 1004), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN|PANEL_MOUSE_UP,	PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_SUITCABINDELTAPMETER,	    				_R(1445,  106, 1491,  150), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,				PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_MISSION_CLOCK,								_R(1835,  305, 1973,  324), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,				PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_CYROTANKSWITCHES,        					_R(1912,  490, 2488,  520), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,					PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_CYROTANKINDICATORS,        					_R(2173,  315, 2495,  439), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,				PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_SUITCOMPRDELTAPMETER,       					_R(2069,  726, 2115,  770), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,				PANEL_MAP_BACKGROUND);		
		oapiRegisterPanelArea (AID_CABININDICATORS,        						_R(2278,  593, 2504,  717), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,				PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_FUELCELLINDICATORS,		    				_R(2763,  319, 2913,  443), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,				PANEL_MAP_BACKGROUND);		
		oapiRegisterPanelArea (AID_FUELCELLPHRADTEMPINDICATORS,	  				_R(2822,  490, 3019,  513), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,				PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_FUELCELLRADIATORSINDICATORS,    				_R(2822,  539, 2931,  562), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,				PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_FUELCELLRADIATORSSWITCHES,    				_R(2816,  607, 2937,  637), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN|PANEL_MOUSE_UP,	PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_FUELCELLINDICATORSSWITCH,    				_R(3030,  630, 3114,  714), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,					PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_FUELCELLHEATERSSWITCHES,	    				_R(2817,  695, 2938,  725), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,					PANEL_MAP_BACKGROUND);		
		oapiRegisterPanelArea (AID_FUELCELLPURGESWITCHES,	    				_R(2815,  817, 3123,  846), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,					PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_FUELCELLREACTANTSINDICATORS,    				_R(2823,  893, 3061,  917), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,				PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_FUELCELLREACTANTSSWITCHES,    				_R(2757,  955, 3131,  984), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN|PANEL_MOUSE_UP,	PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_FUELCELLLATCHSWITCHES,	    				_R(2593, 1251, 2670, 1280), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,					PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_SBAND_NORMAL_SWITCHES,						_R(2593, 1050, 2858, 1079), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,					PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_CAUTIONWARNING_SWITCHES,						_R(1908,  400, 2140,  434), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN|PANEL_MOUSE_UP,	PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_MISSION_TIMER_SWITCHES,						_R(2019,  299, 2139,  328), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN|PANEL_MOUSE_UP,	PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_IMU_CAGE_SWITCH,								_R( 290, 1244,  324, 1305), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,					PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_MASTER_ALARM,								_R( 464,  497,  509,  533), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,					PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_MASTER_ALARM2,								_R(2960,  652, 3005,  688), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,					PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_SMRCS_HELIUM1_SWITCHES,						_R(1585,  430, 1748,  459), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN|PANEL_MOUSE_UP,	PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_SMRCS_HELIUM2_SWITCHES,						_R(1411,  571, 1748,  632), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN|PANEL_MOUSE_UP,	PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_PRIM_PRPLNT_SWITCHES,						_R(1411,  718, 1748,  747), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN|PANEL_MOUSE_UP,	PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_SEC_PRPLT_SWITCHES,							_R(1411,  848, 1748,  877), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN|PANEL_MOUSE_UP,	PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_ATTITUDE_CONTROL_SWITCHES,					_R( 190,  838,  482,  867), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,					PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_BMAG_SWITCHES,								_R( 125, 1036,  258, 1065), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,					PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_THRUSTMETER,									_R( 498,  920,  593, 1011), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,				PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_ENTRY_MODE_SWITCH,							_R( 593,  402,  628,  432), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN|PANEL_MOUSE_UP,	PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_CMC_SWITCH,									_R( 343,  635,  377,  664), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN|PANEL_MOUSE_UP,	PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_FDAI_SWITCHES,								_R( 265,  742,  484,  771), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN|PANEL_MOUSE_UP,	PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_RCS_INDICATORS,								_R(1788,  448, 1875,  535), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,					PANEL_MAP_BACKGROUND);		
		oapiRegisterPanelArea (AID_LV_SWITCHES,									_R(1044, 1145, 1173, 1206), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN|PANEL_MOUSE_UP,	PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_ALTIMETER,									_R( 836,   85,  973,  222), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,				PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_ECS_INDICATOR_SWITCH,						_R(1788,  585, 1875,  673), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,					PANEL_MAP_BACKGROUND);		
		oapiRegisterPanelArea (AID_ELS_SWITCHES,								_R( 702, 1157,  956, 1218), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,					PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_EVENT_TIMER_SWITCHES,						_R( 701, 1260,  950, 1289), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN|PANEL_MOUSE_UP,	PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_MAIN_RELEASE_SWITCH,							_R(1043, 1235, 1077, 1296), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN|PANEL_MOUSE_UP,	PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_ABORT_ROW,									_R(1042, 1034, 1293, 1095), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN|PANEL_MOUSE_UP,	PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_ROT_PWR,										_R( 104,  948,  324,  977), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN|PANEL_MOUSE_UP,	PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_dVTHRUST_SWITCHES,							_R( 443, 1053,  571, 1114), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN|PANEL_MOUSE_UP,	PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_CWS_LIGHTS_LEFT,								_R(1540,   97, 1752,  205), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,				PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_CWS_LIGHTS_RIGHT,							_R(1795,   97, 2008,  205), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,				PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_EVENT_TIMER,									_R( 866,  670,  937,  688), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,				PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_RCS_HELIUM1_TALKBACK,						_R(1590,  367, 1742,  392), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,				PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_RCS_HELIUM2_TALKBACK,						_R(1590,  525, 1742,  550), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,				PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_RCS_PROP1_TALKBACK,							_R(1590,  658, 1742,  683), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,				PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_RCS_PROP2_TALKBACK,							_R(1502,  791, 1742,  816), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,				PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_SPS,											_R( 300, 1053,  338, 1115), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,					PANEL_MAP_BACKGROUND);

		//
		// display & keyboard (DSKY):
		//
		// Main panel uses the main DSKY.
		//

		oapiRegisterPanelArea (AID_DSKY_DISPLAY,								_R(1239,  589, 1344,  765), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,					PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_DSKY_LIGHTS,									_R(1095,  594, 1197,  714), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE,				PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_DSKY_KEY,			                        _R(1075,  784, 1363,  905), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN|PANEL_MOUSE_UP,	PANEL_MAP_BACKGROUND);

		// FDAI
		fdaiRight.RegisterMe(AID_FDAI_RIGHT, 1120, 314);
		hBmpFDAIRollIndicator = LoadBitmap(g_Param.hDLL, MAKEINTRESOURCE (IDB_FDAI_ROLLINDICATOR));
		
		SetCameraDefaultDirection(_V(0.0, 0.0, 1.0));
		break;    

	case SATPANEL_LEFT: // left instrument panel
		oapiRegisterPanelBackground (hBmp,PANEL_ATTACH_TOP|PANEL_ATTACH_BOTTOM|PANEL_ATTACH_LEFT|PANEL_MOVEOUT_RIGHT,  g_Param.col[4]);
		
		//new areas to be added soon...
		
		SetCameraDefaultDirection(_V(-1.0, 0.0, 0.0)); 
		break;    

	case SATPANEL_RIGHT: // right instrument panel
		oapiRegisterPanelBackground (hBmp,PANEL_ATTACH_TOP|PANEL_ATTACH_BOTTOM|PANEL_ATTACH_LEFT|PANEL_MOVEOUT_RIGHT,  g_Param.col[4]);
		
		oapiRegisterPanelArea (AID_FUELCELLPUMPSSWITCHES,      					_R( 451,  881,  680,  910), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,					PANEL_MAP_BACKGROUND);
		oapiRegisterPanelArea (AID_SUITCOMPRESSORSWITCHES,      				_R( 965, 1428, 1041, 1519), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_DOWN,					PANEL_MAP_BACKGROUND);
		
		SetCameraDefaultDirection(_V(1.0, 0.0, 0.0));
		break;    

	case SATPANEL_LEFT_RNDZ_WINDOW: // left rendezvous window
		oapiRegisterPanelBackground (hBmp,PANEL_ATTACH_TOP|PANEL_ATTACH_BOTTOM|PANEL_ATTACH_LEFT|PANEL_MOVEOUT_RIGHT,  g_Param.col[4]);
		
		//the new animated COAS has to be added soon...

		SetCameraDefaultDirection(_V(0.0, 0.0, 1.0));
		break;    

	case SATPANEL_RIGHT_RNDZ_WINDOW: // right rendezvous window
		oapiRegisterPanelBackground (hBmp,PANEL_ATTACH_TOP|PANEL_ATTACH_BOTTOM|PANEL_ATTACH_LEFT|PANEL_MOVEOUT_RIGHT,  g_Param.col[4]);
		
		SetCameraDefaultDirection(_V(0.0, 0.0, 1.0));
		break;    

	case SATPANEL_HATCH_WINDOW: // hatch window
		oapiRegisterPanelBackground (hBmp,PANEL_ATTACH_TOP|PANEL_ATTACH_BOTTOM|PANEL_ATTACH_LEFT|PANEL_MOVEOUT_RIGHT,  g_Param.col[4]);
		
		SetCameraDefaultDirection(_V(0.0, 0.0, 1.0)); // TODO
		break;    	
	}

	InitPanel (id);

	SetCameraRotationRange(0.0, 0.0, 0.0, 0.0);

	InVC = false;
	InPanel = true;
	PanelId = id;
	SetView();

	return hBmp != NULL;
}

//
// Wire up all the control panel switches. Note that this can
// be called multiple times, so be sure to initialise all the panel
// and row variables at the start of the function to reset internal
// state..
//

void Saturn::SetSwitches(int panel) {

	MainPanel.Init(0, this, &soundlib, this);

	// SATPANEL_MAIN
	SequencerSwitchesRow.Init(AID_SEQUENCERSWITCHES, MainPanel);
	LiftoffNoAutoAbortSwitch.Init     ( 20,   3, 39, 38, srf[SRF_SEQUENCERSWITCHES], SequencerSwitchesRow, 0, 81);
	LiftoffNoAutoAbortSwitch.InitGuard(  0,   1, 92, 40, srf[SRF_SEQUENCERSWITCHES]);
	LesMotorFireSwitch.Init			  ( 20,  49, 39, 38, srf[SRF_SEQUENCERSWITCHES], SequencerSwitchesRow, 0, 119);
	LesMotorFireSwitch.InitGuard      (  0,  47, 92, 40, srf[SRF_SEQUENCERSWITCHES]);
	CanardDeploySwitch.Init           ( 20,  95, 39, 38, srf[SRF_SEQUENCERSWITCHES], SequencerSwitchesRow, 0, 157);
	CanardDeploySwitch.InitGuard      (  0,  93, 92, 40, srf[SRF_SEQUENCERSWITCHES]);
	CsmLvSepSwitch.Init				  ( 20, 141, 39, 38, srf[SRF_SEQUENCERSWITCHES], SequencerSwitchesRow, 0, 195);
	CsmLvSepSwitch.InitGuard		  (  0, 139, 92, 40, srf[SRF_SEQUENCERSWITCHES]);
	ApexCoverJettSwitch.Init          (127,   3, 39, 38, srf[SRF_SEQUENCERSWITCHES], SequencerSwitchesRow, 0, 233);
	ApexCoverJettSwitch.InitGuard     ( 94,   1, 92, 40, srf[SRF_SEQUENCERSWITCHES], 0, 40);
	DrogueDeploySwitch.Init			  (127,  49, 39, 38, srf[SRF_SEQUENCERSWITCHES], SequencerSwitchesRow, 0, 271);
	DrogueDeploySwitch.InitGuard      ( 94,  47, 92, 40, srf[SRF_SEQUENCERSWITCHES], 0, 40);
	MainDeploySwitch.Init             (127,  95, 39, 38, srf[SRF_SEQUENCERSWITCHES], SequencerSwitchesRow, 0, 309);
	MainDeploySwitch.InitGuard        ( 94,  93, 92, 40, srf[SRF_SEQUENCERSWITCHES], 0, 40);		
	CmRcsHeDumpSwitch.Init			  (127, 141, 39, 38, srf[SRF_SEQUENCERSWITCHES], SequencerSwitchesRow, 0, 347);
	CmRcsHeDumpSwitch.InitGuard		  ( 94, 139, 92, 40, srf[SRF_SEQUENCERSWITCHES], 0, 40);
	 
	SeparationSwitchesRow.Init(AID_SEPARATIONSWITCHES, MainPanel);
	EDSSwitch.Init				  (  0,	16, 34, 29, srf[SRF_SWITCHUP], SeparationSwitchesRow); 
	CsmLmFinalSep1Switch.Init	  ( 43, 19, 34, 29, srf[SRF_SWITCHUP], SeparationSwitchesRow); 
	CsmLmFinalSep1Switch.InitGuard( 43,  0, 34, 61, srf[SRF_SWITCHGUARDS]);
	CsmLmFinalSep2Switch.Init	  ( 87, 19, 34, 29, srf[SRF_SWITCHUP], SeparationSwitchesRow); 
	CsmLmFinalSep2Switch.InitGuard( 87,  0, 34, 61, srf[SRF_SWITCHGUARDS]);
	CmSmSep1Switch.Init			  (131, 19, 34, 29, srf[SRF_SWITCHUP], SeparationSwitchesRow); 
	CmSmSep1Switch.InitGuard      (131,  0, 34, 61, srf[SRF_SWITCHGUARDS], 68);
	CmSmSep1Switch.SetFailed(SwitchFail.u.SMJett1Fail != 0);
	CmSmSep2Switch.Init			  (175, 19, 34, 29, srf[SRF_SWITCHUP], SeparationSwitchesRow); 
	CmSmSep2Switch.InitGuard      (175,  0, 34, 61, srf[SRF_SWITCHGUARDS], 68);
	CmSmSep2Switch.SetFailed(SwitchFail.u.SMJett2Fail != 0);
	SivbLmSepSwitch.Init		  (219, 19, 34, 29, srf[SRF_SWITCHUP], SeparationSwitchesRow); 
	SivbLmSepSwitch.InitGuard     (219,  0, 34, 61, srf[SRF_SWITCHGUARDS]);

	CryoTankSwitchesRow.Init(AID_CYROTANKSWITCHES, MainPanel);
	CabinFan1Switch.Init (  0, 0, 34, 29, srf[SRF_SWITCHUP],       CryoTankSwitchesRow); 
	CabinFan2Switch.Init ( 59, 0, 34, 29, srf[SRF_SWITCHUP],       CryoTankSwitchesRow);
	H2Heater1Switch.Init (114, 0, 34, 29, srf[SRF_THREEPOSSWITCH], CryoTankSwitchesRow);
	H2Heater2Switch.Init (157, 0, 34, 29, srf[SRF_THREEPOSSWITCH], CryoTankSwitchesRow);
	O2Heater1Switch.Init (200, 0, 34, 29, srf[SRF_THREEPOSSWITCH], CryoTankSwitchesRow);
	O2Heater2Switch.Init (250, 0, 34, 29, srf[SRF_THREEPOSSWITCH], CryoTankSwitchesRow);
	O2PressIndSwitch.Init(293, 0, 34, 29, srf[SRF_SWITCHUP],       CryoTankSwitchesRow); 
	H2Fan1Switch.Init    (349, 0, 34, 29, srf[SRF_THREEPOSSWITCH], CryoTankSwitchesRow);
	H2Fan2Switch.Init    (413, 0, 34, 29, srf[SRF_THREEPOSSWITCH], CryoTankSwitchesRow);
	O2Fan1Switch.Init    (478, 0, 34, 29, srf[SRF_THREEPOSSWITCH], CryoTankSwitchesRow);
	O2Fan2Switch.Init    (541, 0, 34, 29, srf[SRF_THREEPOSSWITCH], CryoTankSwitchesRow);

	//
	// SM RCS Helium 1
	//

	SMRCSHelium1Row.Init(AID_SMRCS_HELIUM1_SWITCHES, MainPanel);
	SMRCSHelium1ASwitch.Init (0, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SMRCSHelium1Row, this, CSM_He1_TANKA_VALVE, &SMRCSHelium1ATalkback);
	SMRCSHelium1BSwitch.Init (43, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SMRCSHelium1Row, this, CSM_He1_TANKB_VALVE, &SMRCSHelium1BTalkback);
	SMRCSHelium1CSwitch.Init (86, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SMRCSHelium1Row, this, CSM_He1_TANKC_VALVE, &SMRCSHelium1CTalkback);
	SMRCSHelium1DSwitch.Init (129, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SMRCSHelium1Row, this, CSM_He1_TANKD_VALVE, &SMRCSHelium1DTalkback);

	SMRCSHelium1TalkbackRow.Init(AID_RCS_HELIUM1_TALKBACK, MainPanel);
	SMRCSHelium1ATalkback.Init(0, 0, 23, 23, srf[SRF_INDICATOR], SMRCSHelium1TalkbackRow);
	SMRCSHelium1BTalkback.Init(43, 0, 23, 23, srf[SRF_INDICATOR], SMRCSHelium1TalkbackRow);
	SMRCSHelium1CTalkback.Init(86, 0, 23, 23, srf[SRF_INDICATOR], SMRCSHelium1TalkbackRow);
	SMRCSHelium1DTalkback.Init(129, 0, 23, 23, srf[SRF_INDICATOR], SMRCSHelium1TalkbackRow);

	//
	// SM RCS Helium 2
	//

	SMRCSHelium2Row.Init(AID_SMRCS_HELIUM2_SWITCHES, MainPanel);
	SMRCSHelium2ASwitch.Init (174, 16, 34, 29, srf[SRF_THREEPOSSWITCH], SMRCSHelium2Row, this, CSM_He2_TANKA_VALVE, &SMRCSHelium2ATalkback);
	SMRCSHelium2BSwitch.Init (217, 16, 34, 29, srf[SRF_THREEPOSSWITCH], SMRCSHelium2Row, this, CSM_He2_TANKB_VALVE, &SMRCSHelium2BTalkback);
	SMRCSHelium2CSwitch.Init (260, 16, 34, 29, srf[SRF_THREEPOSSWITCH], SMRCSHelium2Row, this, CSM_He2_TANKC_VALVE, &SMRCSHelium2CTalkback);
	SMRCSHelium2DSwitch.Init (303, 16, 34, 29, srf[SRF_THREEPOSSWITCH], SMRCSHelium2Row, this, CSM_He2_TANKD_VALVE, &SMRCSHelium2DTalkback);

	CMUplinkSwitch.Init(0, 16, 34, 29, srf[SRF_SWITCHUP], SMRCSHelium2Row, &agc);
	CMUplinkSwitch.SetChannelData(33, 10, false);	// Down is 'Block Uplink Input'
	IUUplinkSwitch.Init(43, 16, 34, 29, srf[SRF_SWITCHUP], SMRCSHelium2Row);
	CMRCSPressSwitch.Init(87, 19, 34, 29, srf[SRF_SWITCHUP], SMRCSHelium2Row);
	CMRCSPressSwitch.InitGuard(87, 0, 34, 61, srf[SRF_SWITCHGUARDS]);
	SMRCSIndSwitch.Init(131, 16, 34, 29, srf[SRF_SWITCHUP], SMRCSHelium2Row);

	SMRCSHelium2TalkbackRow.Init(AID_RCS_HELIUM2_TALKBACK, MainPanel);
	SMRCSHelium2ATalkback.Init(0, 0, 23, 23, srf[SRF_INDICATOR], SMRCSHelium2TalkbackRow);
	SMRCSHelium2BTalkback.Init(43, 0, 23, 23, srf[SRF_INDICATOR], SMRCSHelium2TalkbackRow);
	SMRCSHelium2CTalkback.Init(86, 0, 23, 23, srf[SRF_INDICATOR], SMRCSHelium2TalkbackRow);
	SMRCSHelium2DTalkback.Init(129, 0, 23, 23, srf[SRF_INDICATOR], SMRCSHelium2TalkbackRow);

	//
	// SM RCS Primary Propellant.
	//

	SMRCSProp1Row.Init(AID_PRIM_PRPLNT_SWITCHES, MainPanel);

	SMRCSHeaterASwitch.Init (2, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SMRCSProp1Row);
	SMRCSHeaterBSwitch.Init (45, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SMRCSProp1Row);
	SMRCSHeaterCSwitch.Init (88, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SMRCSProp1Row);
	SMRCSHeaterDSwitch.Init (131, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SMRCSProp1Row);

	SMRCSProp1ASwitch.Init (174, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SMRCSProp1Row, this, CSM_PRIPROP_TANKA_VALVE, &SMRCSProp1ATalkback);
	SMRCSProp1BSwitch.Init (217, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SMRCSProp1Row, this, CSM_PRIPROP_TANKB_VALVE, &SMRCSProp1BTalkback);
	SMRCSProp1CSwitch.Init (260, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SMRCSProp1Row, this, CSM_PRIPROP_TANKC_VALVE, &SMRCSProp1CTalkback);
	SMRCSProp1DSwitch.Init (303, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SMRCSProp1Row, this, CSM_PRIPROP_TANKD_VALVE, &SMRCSProp1DTalkback);

	SMRCSProp1TalkbackRow.Init(AID_RCS_PROP1_TALKBACK, MainPanel);
	SMRCSProp1ATalkback.Init(0, 0, 23, 23, srf[SRF_INDICATOR], SMRCSProp1TalkbackRow);
	SMRCSProp1BTalkback.Init(43, 0, 23, 23, srf[SRF_INDICATOR], SMRCSProp1TalkbackRow);
	SMRCSProp1CTalkback.Init(86, 0, 23, 23, srf[SRF_INDICATOR], SMRCSProp1TalkbackRow);
	SMRCSProp1DTalkback.Init(129, 0, 23, 23, srf[SRF_INDICATOR], SMRCSProp1TalkbackRow);

	//
	// SM RCS Secondary Propellant.
	//

	SMRCSProp2Row.Init(AID_SEC_PRPLT_SWITCHES, MainPanel);

	RCSCMDSwitch.Init (2, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SMRCSProp2Row);
	RCSTrnfrSwitch.Init (45, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SMRCSProp2Row);
	CMRCSIsolate1.Init (88, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SMRCSProp2Row, this, CM_RCSPROP_TANKA_VALVE, &CMRCSIsolate1Talkback);
	CMRCSIsolate2.Init (131, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SMRCSProp2Row, this, CM_RCSPROP_TANKB_VALVE, &CMRCSIsolate2Talkback);

	SMRCSProp2ASwitch.Init (174, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SMRCSProp2Row, this, CSM_SECPROP_TANKA_VALVE, &SMRCSProp2ATalkback);
	SMRCSProp2BSwitch.Init (217, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SMRCSProp2Row, this, CSM_SECPROP_TANKB_VALVE, &SMRCSProp2BTalkback);
	SMRCSProp2CSwitch.Init (260, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SMRCSProp2Row, this, CSM_SECPROP_TANKC_VALVE, &SMRCSProp2CTalkback);
	SMRCSProp2DSwitch.Init (303, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SMRCSProp2Row, this, CSM_SECPROP_TANKD_VALVE, &SMRCSProp2DTalkback);

	SMRCSProp2TalkbackRow.Init(AID_RCS_PROP2_TALKBACK, MainPanel);
	SMRCSProp2ATalkback.Init(85, 0, 23, 23, srf[SRF_INDICATOR], SMRCSProp2TalkbackRow);
	SMRCSProp2BTalkback.Init(128, 0, 23, 23, srf[SRF_INDICATOR], SMRCSProp2TalkbackRow);
	SMRCSProp2CTalkback.Init(171, 0, 23, 23, srf[SRF_INDICATOR], SMRCSProp2TalkbackRow);
	SMRCSProp2DTalkback.Init(214, 0, 23, 23, srf[SRF_INDICATOR], SMRCSProp2TalkbackRow);

	CMRCSIsolate1Talkback.Init(0, 0, 23, 23, srf[SRF_INDICATOR], SMRCSProp2TalkbackRow);
	CMRCSIsolate2Talkback.Init(43, 0, 23, 23, srf[SRF_INDICATOR], SMRCSProp2TalkbackRow);

	//
	// Attitude control, etc.
	//

	AttitudeControlRow.Init(AID_ATTITUDE_CONTROL_SWITCHES, MainPanel);
	ManualAttRollSwitch.Init(0, 0, 34, 29, srf[SRF_THREEPOSSWITCH], AttitudeControlRow);
	ManualAttPitchSwitch.Init(43, 0, 34, 29, srf[SRF_THREEPOSSWITCH], AttitudeControlRow);
	ManualAttYawSwitch.Init(86, 0, 34, 29, srf[SRF_THREEPOSSWITCH], AttitudeControlRow);
	LimitCycleSwitch.Init(129, 0, 34, 29, srf[SRF_SWITCHUP], AttitudeControlRow);
	AttDeadbandSwitch.Init(172, 0, 34, 29, srf[SRF_SWITCHUP], AttitudeControlRow);
	AttRateSwitch.Init(215, 0, 34, 29, srf[SRF_SWITCHUP], AttitudeControlRow);
	TransContrSwitch.Init(258, 0, 34, 29, srf[SRF_SWITCHUP], AttitudeControlRow);

	//
	// BMAG
	//

	BMAGRow.Init(AID_BMAG_SWITCHES, MainPanel);
	BMAGRollSwitch.Init(0, 0, 34, 29, srf[SRF_THREEPOSSWITCH], BMAGRow);
	BMAGPitchSwitch.Init(49, 0, 34, 29, srf[SRF_THREEPOSSWITCH], BMAGRow);
	BMAGYawSwitch.Init(99, 0, 34, 29, srf[SRF_THREEPOSSWITCH], BMAGRow);

	//
	// Entry mode.
	//

	EntryModeRow.Init(AID_ENTRY_MODE_SWITCH, MainPanel);
	EntryModeSwitch.Init(0, 0, 34, 29, srf[SRF_THREEPOSSWITCH], EntryModeRow);

	//
	// CMC Att switch.
	//

	CMCAttRow.Init(AID_CMC_SWITCH, MainPanel);
	CMCAttSwitch.Init(0, 0, 34, 29, srf[SRF_SWITCHUP], CMCAttRow);

	//
	// FDAI switches.
	//

	FDAISwitchesRow.Init(AID_FDAI_SWITCHES, MainPanel);
	FDAIScaleSwitch.Init(0, 0, 34, 29, srf[SRF_THREEPOSSWITCH], FDAISwitchesRow);
	FDAISourceSwitch.Init(43, 0, 34, 29, srf[SRF_THREEPOSSWITCH], FDAISwitchesRow);
	FDAISelectSwitch.Init(142, 0, 34, 29, srf[SRF_THREEPOSSWITCH], FDAISwitchesRow);
	FDAIAttSetSwitch.Init(185, 0, 34, 29, srf[SRF_SWITCHUP], FDAISwitchesRow);

	//
	// Caution and Warning switches.
	//

	CautionWarningRow.Init(AID_CAUTIONWARNING_SWITCHES, MainPanel);
	MissionTimerSwitch.Init(190, 0, 34, 29, srf[SRF_THREEPOSSWITCH], CautionWarningRow, &MissionTimerDisplay);
	CautionWarningModeSwitch.Init(7, 0, 34, 29, srf[SRF_THREEPOSSWITCH], CautionWarningRow, &cws);
	CautionWarningCMCSMSwitch.Init(55, 0, 34, 29, srf[SRF_SWITCHUP], CautionWarningRow, &cws);
	CautionWarningPowerSwitch.Init(104, 0, 34, 29, srf[SRF_THREEPOSSWITCH], CautionWarningRow, &cws);
	CautionWarningLightTestSwitch.Init(147, 0, 34, 29, srf[SRF_THREEPOSSWITCH], CautionWarningRow, &cws);

	//
	// Mission Timer switches.
	//

	MissionTimerSwitchesRow.Init(AID_MISSION_TIMER_SWITCHES, MainPanel);
	MissionTimerHoursSwitch.Init(0, 0, 34, 29, srf[SRF_THREEPOSSWITCH], MissionTimerSwitchesRow, TIME_UPDATE_HOURS, &MissionTimerDisplay);
	MissionTimerMinutesSwitch.Init(43, 0, 34, 29, srf[SRF_THREEPOSSWITCH], MissionTimerSwitchesRow, TIME_UPDATE_MINUTES, &MissionTimerDisplay);
	MissionTimerSecondsSwitch.Init(86, 0, 34, 29, srf[SRF_THREEPOSSWITCH], MissionTimerSwitchesRow, TIME_UPDATE_SECONDS, &MissionTimerDisplay);

	//
	// IMU Cage switch.
	//

	IMUCageSwitchRow.Init(AID_IMU_CAGE_SWITCH, MainPanel);
	IMUGuardedCageSwitch.Init(0, 19, 34, 29, srf[SRF_SWITCHUP], IMUCageSwitchRow, &imu);
	IMUGuardedCageSwitch.InitGuard(0, 0, 34, 61, srf[SRF_SWITCHGUARDS]);

	//
	// RCS Indicators rotary switch.
	//

	RCSIndicatorsSwitchRow.Init(AID_RCS_INDICATORS, MainPanel);
	RCSIndicatorsSwitch.Init(0, 0, 84, 84, srf[SRF_ROTATIONALSWITCH], RCSIndicatorsSwitchRow);

	//
	// ECS Indicators rotary switch.
	//

	ECSIndicatorsSwitchRow.Init(AID_ECS_INDICATOR_SWITCH, MainPanel);
	ECSIndicatorsSwitch.Init(0, 0, 84, 84, srf[SRF_ROTATIONALSWITCH], ECSIndicatorsSwitchRow);

	//
	// LV switches.
	//

	LVRow.Init(AID_LV_SWITCHES, MainPanel);
	LVGuidanceSwitch.Init(0, 19, 34, 29, srf[SRF_SWITCHUP], LVRow);
	SIISIVBSepSwitch.Init(47, 19, 34, 29, srf[SRF_SWITCHUP], LVRow);
	SIISIVBSepSwitch.InitGuard(47, 0, 34, 61, srf[SRF_SWITCHGUARDS]);
	TLIEnableSwitch.Init(95, 16, 34, 29, srf[SRF_SWITCHUP], LVRow, this);

	//
	// ELS Switches.
	//

	ELSRow.Init(AID_ELS_SWITCHES, MainPanel);
	CGSwitch.Init(0, 16, 34, 29, srf[SRF_SWITCHUP], ELSRow, &agc);
	CGSwitch.SetChannelData(32, 11, true);	// LM Attached flag.
	ELSLogicSwitch.Init(44, 19, 34, 29, srf[SRF_SWITCHUP], ELSRow);
	ELSLogicSwitch.InitGuard(44, 0, 34, 61, srf[SRF_SWITCHGUARDS]);
	ELSAutoSwitch.Init(88, 16, 34, 29, srf[SRF_SWITCHUP], ELSRow);
	CMRCSLogicSwitch.Init(131, 16, 34, 29, srf[SRF_SWITCHUP], ELSRow);
	CMPropDumpSwitch.Init(175, 19, 34, 29, srf[SRF_SWITCHUP], ELSRow);
	CMPropDumpSwitch.InitGuard(175, 0, 34, 61, srf[SRF_SWITCHGUARDS]);
	CPPropPurgeSwitch.Init(220, 19, 34, 29, srf[SRF_SWITCHUP], ELSRow);
	CPPropPurgeSwitch.InitGuard(220, 0, 34, 61, srf[SRF_SWITCHGUARDS]);

	//
	// Event Timer Switches
	//

	EventTimerRow.Init(AID_EVENT_TIMER_SWITCHES, MainPanel);
	FCSMSPSASwitch.Init(0, 0, 34, 29, srf[SRF_SWITCHUP], EventTimerRow);
	FCSMSPSBSwitch.Init(43, 0, 34, 29, srf[SRF_SWITCHUP], EventTimerRow);
	EventTimerUpDownSwitch.Init(86, 0, 34, 29, srf[SRF_THREEPOSSWITCH], EventTimerRow, &EventTimerDisplay);
	EventTimerControlSwitch.Init(129, 0, 34, 29, srf[SRF_THREEPOSSWITCH], EventTimerRow, &EventTimerDisplay);
	EventTimerMinutesSwitch.Init(172, 0, 34, 29, srf[SRF_THREEPOSSWITCH], EventTimerRow, TIME_UPDATE_MINUTES, &EventTimerDisplay);
	EventTimerSecondsSwitch.Init(215, 0, 34, 29, srf[SRF_THREEPOSSWITCH], EventTimerRow, TIME_UPDATE_SECONDS, &EventTimerDisplay);

	//
	// Main chute release.
	//

	MainReleaseRow.Init(AID_MAIN_RELEASE_SWITCH, MainPanel);
	MainReleaseSwitch.Init(0, 19, 34, 29, srf[SRF_SWITCHUP], MainReleaseRow);
	MainReleaseSwitch.InitGuard(0, 0, 34, 61, srf[SRF_SWITCHGUARDS]);

	//
	// Abort switches.
	//

	AbortRow.Init(AID_ABORT_ROW, MainPanel);
	PropDumpAutoSwitch.Init(0, 16, 34, 29, srf[SRF_SWITCHUP], AbortRow);
	TwoEngineOutAutoSwitch.Init(49, 16, 34, 29, srf[SRF_SWITCHUP], AbortRow);
	LVRateAutoSwitch.Init(110, 16, 34, 29, srf[SRF_SWITCHUP], AbortRow);
	TowerJett1Switch.Init(169, 19, 34, 29, srf[SRF_SWITCHUP], AbortRow);
	TowerJett1Switch.InitGuard(169, 0, 34, 61, srf[SRF_SWITCHGUARDS]);
	TowerJett1Switch.SetFailed(SwitchFail.u.TowerJett1Fail != 0);
	TowerJett2Switch.Init(217, 19, 34, 29, srf[SRF_SWITCHUP], AbortRow);
	TowerJett2Switch.InitGuard(217, 0, 34, 61, srf[SRF_SWITCHGUARDS]);
	TowerJett2Switch.SetFailed(SwitchFail.u.TowerJett2Fail != 0);

	//
	// Rotational controller power switches.
	//

	RotContrPowerRow.Init(AID_ROT_PWR, MainPanel);
	RotPowerNormal1Switch.Init(0, 0, 34, 29, srf[SRF_THREEPOSSWITCH], RotContrPowerRow);
	RotPowerNormal2Switch.Init(59, 0, 34, 29, srf[SRF_THREEPOSSWITCH], RotContrPowerRow);
	RotPowerDirect1Switch.Init(118, 0, 34, 29, srf[SRF_THREEPOSSWITCH], RotContrPowerRow);
	RotPowerDirect2Switch.Init(186, 0, 34, 29, srf[SRF_THREEPOSSWITCH], RotContrPowerRow);

	//
	// dV Thrust switches.
	//

	dvThrustRow.Init(AID_dVTHRUST_SWITCHES, MainPanel);
	dVThrust1Switch.Init(0, 19, 34, 29, srf[SRF_SWITCHUP], dvThrustRow);
	dVThrust1Switch.InitGuard(0, 0, 34, 61, srf[SRF_SWITCHGUARDS]);
	dVThrust2Switch.Init(94, 19, 34, 29, srf[SRF_SWITCHUP], dvThrustRow);
	dVThrust2Switch.InitGuard(94, 0, 34, 61, srf[SRF_SWITCHGUARDS]);

	//
	// Fuel Cell Switches.
	//

	FuelCellPhRadTempIndicatorsRow.Init(AID_FUELCELLPHRADTEMPINDICATORS, MainPanel);
	FuelCellPhIndicator.Init     (  0, 0, 23, 23, srf[SRF_INDICATOR], FuelCellPhRadTempIndicatorsRow);
	FuelCellRadTempIndicator.Init(174, 0, 23, 23, srf[SRF_INDICATOR], FuelCellPhRadTempIndicatorsRow);

	FuelCellRadiatorsIndicatorsRow.Init(AID_FUELCELLRADIATORSINDICATORS, MainPanel);
	FuelCellRadiators1Indicator.Init( 0, 0, 23, 23, srf[SRF_INDICATOR], FuelCellRadiatorsIndicatorsRow);
	FuelCellRadiators2Indicator.Init(43, 0, 23, 23, srf[SRF_INDICATOR], FuelCellRadiatorsIndicatorsRow);
	FuelCellRadiators3Indicator.Init(86, 0, 23, 23, srf[SRF_INDICATOR], FuelCellRadiatorsIndicatorsRow);
	
	FuelCellRadiatorsSwitchesRow.Init(AID_FUELCELLRADIATORSSWITCHES, MainPanel); 
	FuelCellRadiators1Switch.Init( 0, 0, 34, 29, srf[SRF_THREEPOSSWITCH], FuelCellRadiatorsSwitchesRow); 
	FuelCellRadiators2Switch.Init(43, 0, 34, 29, srf[SRF_THREEPOSSWITCH], FuelCellRadiatorsSwitchesRow); 
	FuelCellRadiators3Switch.Init(86, 0, 34, 29, srf[SRF_THREEPOSSWITCH], FuelCellRadiatorsSwitchesRow); 

	FuelCellIndicatorsSwitchRow.Init(AID_FUELCELLINDICATORSSWITCH, MainPanel);
	FuelCellIndicatorsSwitch.Init(0, 0, 84, 84, srf[SRF_ROTATIONALSWITCH], FuelCellIndicatorsSwitchRow);

	FuelCellHeatersSwitchesRow.Init(AID_FUELCELLHEATERSSWITCHES, MainPanel);
	FuelCellHeater1Switch.Init( 0, 0, 34, 29, srf[SRF_SWITCHUP], FuelCellHeatersSwitchesRow); 
	FuelCellHeater2Switch.Init(43, 0, 34, 29, srf[SRF_SWITCHUP], FuelCellHeatersSwitchesRow); 
	FuelCellHeater3Switch.Init(86, 0, 34, 29, srf[SRF_SWITCHUP], FuelCellHeatersSwitchesRow); 

	FuelCellPurgeSwitchesRow.Init(AID_FUELCELLPURGESWITCHES, MainPanel);
	FuelCellPurge1Switch.Init( 0, 0, 34, 29, srf[SRF_THREEPOSSWITCH], FuelCellPurgeSwitchesRow); 
	FuelCellPurge2Switch.Init(43, 0, 34, 29, srf[SRF_THREEPOSSWITCH], FuelCellPurgeSwitchesRow); 
	FuelCellPurge3Switch.Init(86, 0, 34, 29, srf[SRF_THREEPOSSWITCH], FuelCellPurgeSwitchesRow); 

	FuelCellReactantsIndicatorsRow.Init(AID_FUELCELLREACTANTSINDICATORS, MainPanel);
	FuelCellReactants1Indicator.Init( 0, 0, 23, 23, srf[SRF_INDICATOR], FuelCellReactantsIndicatorsRow);
	FuelCellReactants2Indicator.Init(43, 0, 23, 23, srf[SRF_INDICATOR], FuelCellReactantsIndicatorsRow);
	FuelCellReactants3Indicator.Init(86, 0, 23, 23, srf[SRF_INDICATOR], FuelCellReactantsIndicatorsRow);

	FuelCellReactantsSwitchesRow.Init(AID_FUELCELLREACTANTSSWITCHES, MainPanel); 
	FuelCellReactants1Switch.Init( 43, 0, 34, 29, srf[SRF_THREEPOSSWITCH], FuelCellReactantsSwitchesRow); 
	FuelCellReactants2Switch.Init( 86, 0, 34, 29, srf[SRF_THREEPOSSWITCH], FuelCellReactantsSwitchesRow); 
	FuelCellReactants3Switch.Init(129, 0, 34, 29, srf[SRF_THREEPOSSWITCH], FuelCellReactantsSwitchesRow); 

	FuelCellLatchSwitchesRow.Init(AID_FUELCELLLATCHSWITCHES, MainPanel);
	FCReacsValvesSwitch.Init( 0, 0, 34, 29, srf[SRF_SWITCHUP], FuelCellLatchSwitchesRow); 
	H2PurgeLineSwitch.Init  (43, 0, 34, 29, srf[SRF_SWITCHUP], FuelCellLatchSwitchesRow); 


	SBandNormalSwitchesRow.Init(AID_SBAND_NORMAL_SWITCHES, MainPanel);
	SBandNormalXPDRSwitch.Init(		  0, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SBandNormalSwitchesRow);
	SBandNormalPwrAmpl1Switch.Init(  43, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SBandNormalSwitchesRow);
	SBandNormalPwrAmpl2Switch.Init(  86, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SBandNormalSwitchesRow);
	SBandNormalMode1Switch.Init(	145, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SBandNormalSwitchesRow);
	SBandNormalMode2Switch.Init(	188, 0, 34, 29, srf[SRF_THREEPOSSWITCH], SBandNormalSwitchesRow);
	SBandNormalMode3Switch.Init(	231, 0, 34, 29, srf[SRF_SWITCHUP],		 SBandNormalSwitchesRow);

	
	// SATPANEL_RIGHT
	FuelCellPumpsSwitchesRow.Init(AID_FUELCELLPUMPSSWITCHES, MainPanel);
	FuelCellPumps1Switch.Init(  0, 0, 34, 29, srf[SRF_THREEPOSSWITCH], FuelCellPumpsSwitchesRow); 
	FuelCellPumps2Switch.Init( 65, 0, 34, 29, srf[SRF_THREEPOSSWITCH], FuelCellPumpsSwitchesRow); 
	FuelCellPumps3Switch.Init(130, 0, 34, 29, srf[SRF_THREEPOSSWITCH], FuelCellPumpsSwitchesRow); 

	SuitCompressorSwitchesRow.Init(AID_SUITCOMPRESSORSWITCHES, MainPanel);
	SuitCompressor1Switch.Init(  0, 58, 34, 33, srf[SRF_THREEPOSSWITCH305], SuitCompressorSwitchesRow); 
	SuitCompressor2Switch.Init( 42,  0, 34, 33, srf[SRF_THREEPOSSWITCH305], SuitCompressorSwitchesRow); 

	SPSRow.Init(AID_SPS, MainPanel);
	SPSswitch.Init(0, 0, 38, 48, srf[SRF_SWITCHLEVER], SPSRow, this);

	// old stuff

	//EDSRow.Init(AID_EDS, MainPanel);
	LPRow.Init(AID_SWITCH_PANEL_LEFT, MainPanel);

	SRP1Row.Init(AID_SM_RCS_PANEL1, MainPanel);
	P14Row.Init(AID_SM_RCS_MODE, MainPanel);
	P15Row.Init(AID_SPS_GIMBAL_SWITCHES, MainPanel);

	P28Row.Init(AID_P28, MainPanel);
	P31Row.Init(AID_P31, MainPanel);
	P35Row.Init(AID_P35, MainPanel);
	P36Row.Init(AID_P36, MainPanel);
	P37Row.Init(AID_BUS_PANEL, MainPanel);

	EMS1Row.Init(AID_EMS_SWITCH, MainPanel);

	LPSRow.Init(AID_LEM_POWER_SWITCH, MainPanel);

	//EDSswitch.Init(0, 0, 23, 20, srf[6], EDSRow);

	if (panel == SATPANEL_LEFT_RNDZ_WINDOW) {
		LPswitch5.Init(87, 33, 23, 20, srf[6], P14Row);
	} else {
		LPswitch5.Init( 36, 7, 23, 20, srf[6], P14Row);
	}

	LPswitch6.Init( 45, 7, 23, 20, srf[6], P15Row);
	LPswitch7.Init(119, 7, 23, 20, srf[6], P15Row);

	P231switch.Init( 10, 6, 23, 20, srf[23], P28Row);
	P232switch.Init( 48, 6, 23, 20, srf[23], P28Row);
	P233switch.Init( 85, 6, 23, 20, srf[23], P28Row);
	P234switch.Init(122, 6, 23, 20, srf[23], P28Row);
	P235switch.Init(154, 6, 23, 20, srf[23], P28Row);
	P236switch.Init(  4, 84, 23, 20, srf[23], P28Row);
	P237switch.Init( 36, 84, 23, 20, srf[23], P28Row);
	P238switch.Init( 68, 84, 23, 20, srf[23], P28Row);
	P239switch.Init(100, 84, 23, 20, srf[23], P28Row);
	P240switch.Init(132, 84, 23, 20, srf[23], P28Row);
	P241switch.Init(168, 84, 23, 20, srf[23], P28Row);
	P242switch.Init(204, 84, 23, 20, srf[23], P28Row);
	P243switch.Init(236, 84, 23, 20, srf[23], P28Row);
	P244switch.Init(275, 84, 23, 20, srf[23], P28Row);

	P31switch.Init( 3,  8, 23, 20, srf[6], P31Row);
	P32switch.Init(35,  8, 23, 20, srf[6], P31Row);
	P33switch.Init(67,  8, 23, 20, srf[6], P31Row);
	P34switch.Init( 2, 98, 23, 20, srf[23], P31Row);
	P35switch.Init(33, 98, 23, 20, srf[23], P31Row);
	P36switch.Init(66, 98, 23, 20, srf[23], P31Row);

	P311switch.Init(  3, 6, 23, 20, srf[23], P35Row);
	P312switch.Init( 36, 6, 23, 20, srf[23], P35Row);
	P313switch.Init( 67, 6, 23, 20, srf[23], P35Row);
	P314switch.Init(112, 6, 23, 20, srf[23], P35Row);
	P315switch.Init(143, 6, 23, 20, srf[23], P35Row);
	P316switch.Init(175, 6, 23, 20, srf[23], P35Row);
	P317switch.Init(214, 6, 23, 20, srf[23], P35Row);
	P318switch.Init(254, 6, 23, 20, srf[23], P35Row);
	P319switch.Init(293, 6, 23, 20, srf[23], P35Row);
	P320switch.Init(333, 6, 23, 20, srf[23], P35Row);
	P321switch.Init(  3, 84, 23, 20, srf[23], P35Row);
	P322switch.Init( 35, 84, 23, 20, srf[23], P35Row);
	P323switch.Init(185, 82, 23, 20, srf[23], P35Row);
	P324switch.Init(224, 82, 23, 20, srf[23], P35Row);
	P325switch.Init(261, 82, 23, 20, srf[23], P35Row);
	P326switch.Init(293, 82, 23, 20, srf[23], P35Row);
	P327switch.Init(325, 82, 23, 20, srf[23], P35Row);

	P328switch.Init(  4, 6, 23, 20, srf[6], P36Row);
	P329switch.Init( 35, 6, 23, 20, srf[6], P36Row);
	P330switch.Init(185, 6, 23, 20, srf[23], P36Row);
	P331switch.Init(218, 6, 23, 20, srf[23], P36Row);
	P332switch.Init(249, 6, 23, 20, srf[23], P36Row);
	P333switch.Init(282, 6, 23, 20, srf[23], P36Row);
	P334switch.Init(313, 6, 23, 20, srf[23], P36Row);
	P335switch.Init(345, 6, 23, 20, srf[23], P36Row);
	P336switch.Init(377, 6, 23, 20, srf[23], P36Row);

	P337switch.Init( 3,   6, 23, 20, srf[23], P37Row);
	P338switch.Init(50,   6, 23, 20, srf[23], P37Row);
	P339switch.Init(96,   6, 23, 20, srf[23], P37Row);
	P340switch.Init( 3,  81, 23, 20, srf[23], P37Row);
	P341switch.Init(35,  81, 23, 20, srf[23], P37Row);
	P342switch.Init(67,  81, 23, 20, srf[23], P37Row);
	P343switch.Init(99,  81, 23, 20, srf[23], P37Row);
	P344switch.Init( 3, 155, 23, 20, srf[23], P37Row);
	P345switch.Init(35, 155, 23, 20, srf[23], P37Row);
	P346switch.Init(67, 155, 23, 20, srf[23], P37Row);
	P347switch.Init(99, 155, 23, 20, srf[23], P37Row);

	EMSswitch.Init(4, 6, 23, 20, srf[23], EMS1Row);

	RPswitch15.Init(0, 0, 23, 20, srf[23], LPSRow);
}

void SetupgParam(HINSTANCE hModule) {

	g_Param.hDLL = hModule;

	//
	// allocate GDI resources
	//

	g_Param.font[0]  = CreateFont (-13, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, "Arial");
	g_Param.font[1]  = CreateFont (-10, 0, 0, 0, 400, 0, 0, 0, 0, 0, 0, 0, 0, "Arial");
	g_Param.font[2]  = CreateFont (-8, 0, 0, 0, 400, 0, 0, 0, 0, 0, 0, 0, 0, "Arial");
	g_Param.brush[0] = CreateSolidBrush (RGB(0,255,0));    // green
	g_Param.brush[1] = CreateSolidBrush (RGB(255,0,0));    // red
	g_Param.brush[2] = CreateSolidBrush (RGB(154,154,154));  // Grey
	g_Param.brush[3] = CreateSolidBrush (RGB(3,3,3));  // Black
	g_Param.pen[0] = CreatePen (PS_SOLID, 1, RGB(224, 224, 224));
	g_Param.pen[1] = CreatePen (PS_SOLID, 3, RGB(164, 164, 164));
	g_Param.pen[2] = CreatePen (PS_SOLID, 1, RGB( 77,  77,  77));
	g_Param.pen[3] = CreatePen (PS_SOLID, 3, RGB( 77,  77,  77));
	g_Param.pen[4] = CreatePen (PS_SOLID, 3, RGB(  0,   0,   0));
}

void DeletegParam() {

	int i;

	//
	// deallocate GDI resources
	//

	for (i = 0; i < 3; i++) DeleteObject (g_Param.font[i]);
	for (i = 0; i < 4; i++) DeleteObject (g_Param.brush[i]);
	for (i = 0; i < 5; i++) DeleteObject (g_Param.pen[i]);
}

bool Saturn::clbkPanelMouseEvent (int id, int event, int mx, int my)

{
	static int ctrl = 0;

	if (MainPanel.CheckMouseClick(id, event, mx, my))
		return true;

	switch (id) {
	case AID_MASTER_ALARM:
	case AID_MASTER_ALARM2:
	case AID_MASTER_ALARM3:
		StopMasterAlarm();
		ButtonClick();
		return true;

	case AID_DSKY_KEY:
		if (event & PANEL_MOUSE_LBDOWN) {
			dsky.ProcessKeyPress(mx, my);
		} else if (event & PANEL_MOUSE_LBUP) {
			dsky.ProcessKeyRelease(mx, my);
		}
		return true;

	case AID_DSKY2_KEY:
		if (event & PANEL_MOUSE_LBDOWN) {
			dsky2.ProcessKeyPress(mx, my);
		} else if (event & PANEL_MOUSE_LBUP) {
			dsky2.ProcessKeyRelease(mx, my);
		}
		return true;

	case AID_CMD_SWITCH:
		if(event & PANEL_MOUSE_RBDOWN){
			if(mx <25 ){
				CMDCswitch = !CMDCswitch;
				GuardClick();
			}
		}else if(event & PANEL_MOUSE_LBDOWN){
			if(mx <25 && CMDCswitch){
				if(my >16 && my <27 && !CMDswitch){
					CMDswitch = true;
					SwitchClick();
				}else if(my >27 && my <37 && CMDswitch && CMDCswitch){
					CMDswitch = false;
					SwitchClick();
				}
			}
		}
		return true;

	case AID_CMP_SWITCH:
		if(event & PANEL_MOUSE_RBDOWN){
			if(mx <25 ){
				CMPCswitch = !CMPCswitch;
				GuardClick();
			}
		}else if(event & PANEL_MOUSE_LBDOWN){
			if(mx <25 && CMPCswitch){
				if(my >16 && my <27 && !CMPswitch){
					CMPswitch = true;
					SwitchClick();
				}else if(my >27 && my <37 && CMPswitch && CMPCswitch){
					CMPswitch = false;
					SwitchClick();
				}
			}
		}
		return true;

	case AID_CABIN_PRESS:
		if (my >=6 && my <=16 ){
			if (mx >38 && mx < 62 && !RPswitch13){
				SwitchClick();
				RPswitch13=true;
			}else if (mx >5 && mx < 29 && !RPswitch14){
				SwitchClick();
				RPswitch14=true;
			}
		}else if (my >=16 && my <=27 ){
			if (mx >38 && mx < 62 && RPswitch13 ){
				SwitchClick();
				RPswitch13=false;
			}else if (mx >5 && mx < 29 && RPswitch14){
				SwitchClick();
				RPswitch14=false;
			}
		}

			return true;

	case AID_DOCKING_PROBE_SWITCH:
		if(event & PANEL_MOUSE_RBDOWN){
			if(mx <25 ){
				DPCswitch = !DPCswitch;
				GuardClick();
			}
		}else if(event & PANEL_MOUSE_LBDOWN){
			if(mx <25 && DPCswitch){
				if(my >80 && my <91 && !DPswitch){
					DPswitch = true;
					SwitchClick();
					ProbeSound();
				}else if(my >91 && my <101 && DPswitch && DPCswitch){
					DPswitch = false;
					SwitchClick();
				}
			}
		}
		return true;

	case AID_SC_SWITCH:
		if (my >=0 && my <=10 ){
			if (mx > 7 && mx < 18 && !SCswitch){
				SwitchClick();
				SCswitch=true;
			}
			}else if (my >=10 && my <=20 ){
				if (mx >7 && mx < 18 && SCswitch){
				SwitchClick();
				SCswitch=false;
				}
			}
		return true;

	case AID_ABORT_BUTTON:
		if (mx > 1 && mx < 62 && my > 1 && my < 31){
			bAbort =true;
			ButtonClick();
		}
		return true;

	case AID_EMS_KNOB:
		if (my >=1 && my <=34 ){
			if (mx > 1 && mx < 67 && !EMSKswitch){
				SwitchClick();
				EMSKswitch=true;
			}
		}
		else if (my >=34 && my <=67 ){
			if (mx > 1 && mx < 67 && EMSKswitch){
				SwitchClick();
				EMSKswitch=false;
			}
		}
		return true;

	case AID_MFDDOCK:
		if (oapiGetMFDMode(MFD_RIGHT) != MFD_NONE) {	// MFD_USER1
			if (my > 234 && my < 249) {	//&& event == PANEL_MOUSE_LBDOWN
				if (mx > 47 && mx < 68) {
					ButtonClick();
					oapiToggleMFD_on (MFD_RIGHT);	// MFD_USER1
				} else if (mx > 208 && mx < 229) {
					ButtonClick();
					oapiSendMFDKey (MFD_RIGHT, OAPI_KEY_F1);		// MFD_USER1
				} else if (mx > 239 && mx < 252) {
					ButtonClick();
					oapiSendMFDKey (MFD_RIGHT, OAPI_KEY_GRAVE);		// MFD_USER1
				}
			} else if (mx > 5 && mx < 26 && my > 38 && my < 208) {
				if ((my - 38) % 31 < 14) {
					int bt = (my - 38) / 31 + 0;
					ButtonClick();
					oapiProcessMFDButton (MFD_RIGHT, bt, event);	// MFD_USER1
				}
			} else if (mx > 273 && mx < 294 && my > 38 && my < 208) {
				if ((my - 38) % 31 < 14) {
					int bt = (my - 38) / 31 + 6;
					ButtonClick();
					oapiProcessMFDButton (MFD_RIGHT, bt, event);	// MFD_USER1
				}
			}
		}
		return true;

	case AID_MFDDOCK_POWER:
		if (oapiGetMFDMode(MFD_RIGHT) == MFD_NONE) {	// MFD_USER1
			ButtonClick();
			oapiToggleMFD_on (MFD_RIGHT);	// MFD_USER1
		}
		return true;
		break;
	}
	return false;
}


//#include "PanelSDK/Internals/Esystems.h"

void Saturn::PanelSwitchToggled(ToggleSwitch *s) {

	if (s == &CabinFan1Switch || s == &CabinFan2Switch) {
		if (CabinFansActive()) {
			CabinFanSound();
		} else {
			StopCabinFanSound();
		}

		// TEST
		/*if (s == &CabinFan1Switch) {
			int *pump = (int*) Panelsdk.GetPointerByString("ELECTRIC:TESTHEATER:PUMP");
			if (CabinFan1Switch.IsUp())
				*pump = SP_PUMP_ON;
			else
				*pump = SP_PUMP_OFF;
		}

		if (s == &CabinFan2Switch) {
			int *pump = (int*) Panelsdk.GetPointerByString("HYDRAULIC:TESTEXCHANGER:PUMP");
			if (CabinFan2Switch.IsUp())
				*pump = SP_PUMP_ON;
			else
				*pump = SP_PUMP_OFF;
		}
		*/
		/*
			FCell *fc = (FCell *) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL1");
			if (CabinFan1Switch) {
				fc->PLOAD(20.0);
			} else {
				fc->PUNLOAD(20.0);
			}
		}

		if (s == &CabinFan2Switch) {
			FCell *fc = (FCell *) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL2");
			if (CabinFan2Switch) {
				fc->PLOAD(40.0);
			} else {
				fc->PUNLOAD(40.0);
			}
		}*/

	} else if (s == &O2Heater1Switch) {
		CryoTankHeaterSwitchToggled(s, 
			(int*) Panelsdk.GetPointerByString("ELECTRIC:O2TANK1HEATER:PUMP"));

	} else if (s == &O2Heater2Switch) {
		CryoTankHeaterSwitchToggled(s, 
			(int*) Panelsdk.GetPointerByString("ELECTRIC:O2TANK2HEATER:PUMP"));

	} else if (s == &H2Heater1Switch) {
		CryoTankHeaterSwitchToggled(s, 
			(int*) Panelsdk.GetPointerByString("ELECTRIC:H2TANK1HEATER:PUMP"));

	} else if (s == &H2Heater2Switch) {
		CryoTankHeaterSwitchToggled(s, 
			(int*) Panelsdk.GetPointerByString("ELECTRIC:H2TANK2HEATER:PUMP"));

	} else if (s == &O2Fan1Switch) {
		CryoTankHeaterSwitchToggled(s, 
			(int*) Panelsdk.GetPointerByString("ELECTRIC:O2TANK1FAN:PUMP"));

	} else if (s == &O2Fan2Switch) {
		CryoTankHeaterSwitchToggled(s, 
			(int*) Panelsdk.GetPointerByString("ELECTRIC:O2TANK2FAN:PUMP"));

	} else if (s == &H2Fan1Switch) {
		CryoTankHeaterSwitchToggled(s, 
			(int*) Panelsdk.GetPointerByString("ELECTRIC:H2TANK1FAN:PUMP"));

	} else if (s == &H2Fan2Switch) {
		CryoTankHeaterSwitchToggled(s, 
			(int*) Panelsdk.GetPointerByString("ELECTRIC:H2TANK2FAN:PUMP"));


	} else if (s == &FuelCellRadiators1Switch) {
		if (FuelCellRadiators1Switch.IsUp())
			FuelCellCoolingBypass(1, false);
		else if (FuelCellRadiators1Switch.IsDown())
			FuelCellCoolingBypass(1, true);

	} else if (s == &FuelCellRadiators2Switch) {
		if (FuelCellRadiators2Switch.IsUp())
			FuelCellCoolingBypass(2, false);
		else if (FuelCellRadiators2Switch.IsDown())
			FuelCellCoolingBypass(2, true);

	} else if (s == &FuelCellRadiators3Switch) {
		if (FuelCellRadiators3Switch.IsUp())
			FuelCellCoolingBypass(3, false);
		else if (FuelCellRadiators3Switch.IsDown())
			FuelCellCoolingBypass(3, true);
		

	} else if (s == &FuelCellHeater1Switch) {
		FuelCellHeaterSwitchToggled(s, 
			(int*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL1HEATER:PUMP"));

	} else if (s == &FuelCellHeater2Switch) {
		FuelCellHeaterSwitchToggled(s, 
			(int*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL2HEATER:PUMP"));

	} else if (s == &FuelCellHeater3Switch) {
		FuelCellHeaterSwitchToggled(s, 
			(int*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL3HEATER:PUMP"));


	} else if (s == &FuelCellPurge1Switch || s == &FuelCellPurge2Switch || s == &FuelCellPurge3Switch || s == &H2PurgeLineSwitch) {
		if (s == &FuelCellPurge1Switch || s == &H2PurgeLineSwitch) {
			FuelCellPurgeSwitchToggled(&FuelCellPurge1Switch, 
				(int*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL1:PURGE"));		
		} 
		if (s == &FuelCellPurge2Switch || s == &H2PurgeLineSwitch) {
			FuelCellPurgeSwitchToggled(&FuelCellPurge2Switch, 
				(int*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL2:PURGE"));		
		} 
		if (s == &FuelCellPurge3Switch || s == &H2PurgeLineSwitch) {
			FuelCellPurgeSwitchToggled(&FuelCellPurge3Switch, 
				(int*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL3:PURGE"));
		}


	} else if (s == &FuelCellReactants1Switch) {
		FuelCellReactantsSwitchToggled(s, 
			(int*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL1:START"));
	
	} else if (s == &FuelCellReactants2Switch) {
		FuelCellReactantsSwitchToggled(s, 
			(int*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL2:START"));
	
	} else if (s == &FuelCellReactants3Switch) {
		FuelCellReactantsSwitchToggled(s, 
			(int*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL3:START"));


	} else if (s == &FuelCellPumps1Switch) {
		FuelCellPumpsSwitchToggled(s, 
			(int*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL1COOLING:PUMP"));
		
	} else if (s == &FuelCellPumps2Switch) {
		FuelCellPumpsSwitchToggled(s, 
			(int*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL2COOLING:PUMP"));

	} else if (s == &FuelCellPumps3Switch) {
		FuelCellPumpsSwitchToggled(s, 
			(int*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL3COOLING:PUMP"));

		
	} else if (s == &SuitCompressor1Switch || s == & SuitCompressor2Switch) {
		int *pump = (int*) Panelsdk.GetPointerByString("ELECTRIC:SUITCOMPRESSORCO2ABSORBER:PUMP");
		// No busses at the moment
		if (SuitCompressor1Switch.IsCenter() && SuitCompressor2Switch.IsCenter())
			*pump = SP_PUMP_OFF;
		else
			*pump = SP_PUMP_AUTO;
	}
}

void Saturn::PanelIndicatorSwitchStateRequested(IndicatorSwitch *s) {

	double *running;

	if (s == &FuelCellPhIndicator) {
		FuelCellPhIndicator = true;	// Not simulated at the moment

	} else if (s == &FuelCellRadTempIndicator) {
		double *temp;
		if (FuelCellIndicatorsSwitch == 1)
			temp = (double*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL1COOLING:TEMP");
		else if (FuelCellIndicatorsSwitch == 2)
			temp = (double*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL2COOLING:TEMP");
		else if (FuelCellIndicatorsSwitch == 3)
			temp = (double*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL3COOLING:TEMP");

		if (KelvinToFahrenheit(*temp) <= -30.0)	// indication if temperature below -30�F 
			FuelCellRadTempIndicator = false;
		else
			FuelCellRadTempIndicator = true;
			

	} else if (s == &FuelCellRadiators1Indicator) {
		FuelCellRadiators1Indicator = !FuelCellCoolingBypassed(1);

	} else if (s == &FuelCellRadiators2Indicator) {
		FuelCellRadiators2Indicator = !FuelCellCoolingBypassed(2);

	} else if (s == &FuelCellRadiators3Indicator) {
		FuelCellRadiators3Indicator = !FuelCellCoolingBypassed(3);


	} else if (s == &FuelCellReactants1Indicator) {
		running = (double*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL1:RUNNING");
		if (*running) FuelCellReactants1Indicator = false; 
		         else FuelCellReactants1Indicator = true;

	} else if (s == &FuelCellReactants2Indicator) {
		running = (double*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL2:RUNNING");
		if (*running) FuelCellReactants2Indicator = false; 
		         else FuelCellReactants2Indicator = true;

	} else if (s == &FuelCellReactants3Indicator) {
		running = (double*) Panelsdk.GetPointerByString("ELECTRIC:FUELCELL3:RUNNING");
		if (*running) FuelCellReactants3Indicator = false; 
		         else FuelCellReactants3Indicator = true;
	
	} 
}

void Saturn::CryoTankHeaterSwitchToggled(ToggleSwitch *s, int *pump) {

	if (s->IsUp())
		*pump = SP_PUMP_AUTO;
	else if (s->IsCenter())
		*pump = SP_PUMP_OFF;
	else if (s->IsDown())
		*pump = SP_PUMP_ON;
}

void Saturn::FuelCellHeaterSwitchToggled(ToggleSwitch *s, int *pump) {

	if (s->IsUp())
		*pump = SP_PUMP_AUTO;
	else 
		*pump = SP_PUMP_OFF;
}

void Saturn::FuelCellReactantsSwitchToggled(ToggleSwitch *s, int *start) {

	// Is the reactants valve latched?
	if (!FCReacsValvesSwitch) return;

	if (s->IsUp())
		*start = SP_FUELCELL_START;
	else if (s->IsCenter())
		*start = SP_FUELCELL_NONE;
	else if (s->IsDown())
		*start = SP_FUELCELL_STOP;
}

void Saturn::FuelCellPurgeSwitchToggled(ToggleSwitch *s, int *start) {

	if (s->IsUp()) {
		if (H2PurgeLineSwitch.GetState())
			*start = SP_FUELCELL_H2PURGE;
		else 
			*start = SP_FUELCELL_NOPURGE;
	} else if (s->IsCenter())
		*start = SP_FUELCELL_NOPURGE;
	else if (s->IsDown())
		*start = SP_FUELCELL_O2PURGE;
}

void Saturn::FuelCellPumpsSwitchToggled(ToggleSwitch *s, int *pump) {

	// No busses at the moment
	if (s->IsUp() || s->IsDown())
		*pump = SP_PUMP_AUTO;
	else if (s->IsCenter())
		*pump = SP_PUMP_OFF;
}

void Saturn::SwitchClick()

{
	Sclick.play(NOLOOP,255);
}

void Saturn::ButtonClick()

{
	Bclick.play(NOLOOP,255);
}

void Saturn::GuardClick()

{
	Gclick.play(NOLOOP,255);
}

void Saturn::ProbeSound()

{
	Psound.play(NOLOOP,255);
}

void Saturn::CabinFanSound()

{
	CabinFans.play(LOOP,255);
}

void Saturn::StopCabinFanSound()

{
	CabinFans.stop();
}

//
// Signal a master alarm until reset.
//

void Saturn::MasterAlarm()

{
	//
	// Enable master alarm.
	//

	cws.SetMasterAlarm(true);
}

//
// And stop it.
//

void Saturn::StopMasterAlarm()

{
	SMasterAlarm.stop();
	cws.SetMasterAlarm(false);
}

bool Saturn::clbkPanelRedrawEvent(int id, int event, SURFHANDLE surf) 

{
	int Curdigit, Curdigit2;

	//
	// Note: if you crash in this function with a NULL surf handle, odds are you screwed up
	// the region definition so maxX < minX or maxY < minY.
	//

	//
	// Special handling illuminated "sequencer switches"
	//

	if (LAUNCHIND[0]){
		if (EDSSwitch.GetState())
			LiftoffNoAutoAbortSwitch.SetOffset(78, 81);
		else
			LiftoffNoAutoAbortSwitch.SetOffset(234, 81);

	} else {
		LiftoffNoAutoAbortSwitch.SetOffset(0, 81);
	}

	//
	// Special handling for docking panel
	//

	if (id == AID_SM_RCS_MODE) {
		if (PanelId == SATPANEL_LEFT_RNDZ_WINDOW) {
			if (oapiGetMFDMode(MFD_RIGHT) != MFD_NONE) {	// MFD_USER1
				oapiBlt(surf, srf[26], 0, 0, 0, 0, 133, 73);
				LPswitch5.SetVisible(true);
			} else {
				LPswitch5.SetVisible(false);
			}
		} else {
			LPswitch5.SetVisible(true);
		}

	}

	//
	// Process all the generic switches.
	//

	if (MainPanel.DrawRow(id, surf))
		return true;

	//
	// Now special case the rest.
	//

	switch (id) {
	case AID_DSKY_LIGHTS:
		dsky.RenderLights(surf, srf[SRF_DSKY]);
		return true;

	case AID_DSKY_DISPLAY:
		dsky.RenderData(surf, srf[SRF_DIGITAL], srf[SRF_DSKYDISP]);
		return true;

	case AID_DSKY_KEY:
		dsky.RenderKeys(surf, srf[SRF_DSKYKEY]);
		return true;

	case AID_FDAI_RIGHT:
		fdaiRight.PaintMe(imu.GetTotalAttitude(), surf, srf[SRF_FDAI], srf[SRF_FDAIROLL], hBmpFDAIRollIndicator);
		return true;

	case AID_DSKY2_LIGHTS:
		dsky2.RenderLights(surf, srf[SRF_DSKY]);
		return true;

	case AID_DSKY2_DISPLAY:
		dsky2.RenderData(surf, srf[SRF_DIGITAL], srf[SRF_DSKYDISP]);
		return true;

	case AID_DSKY2_KEY:
		dsky2.RenderKeys(surf, srf[SRF_DSKYKEY]);
		return true;

	case AID_ABORT_BUTTON:
		if (ABORT_IND) {
			oapiBlt(surf,srf[SRF_ABORT], 0, 0, 62, 0, 62, 31);
		} 
		else {
			oapiBlt(surf,srf[SRF_ABORT], 0, 0, 0, 0, 62, 31);
		}
		return true;

	case AID_SUITCABINDELTAPMETER:
		RedrawPanel_SuitCabinDeltaPMeter(surf);

	case AID_CYROTANKINDICATORS:
		RedrawPanel_CryoTankIndicators(surf);
		return true;

	case AID_SUITCOMPRDELTAPMETER:
		RedrawPanel_SuitComprDeltaPMeter(surf);
		return true;

	case AID_CABININDICATORS:
		RedrawPanel_CabinIndicators(surf);
		return true;

	case AID_FUELCELLINDICATORS:
		RedrawPanel_FuelCellIndicators(surf);
		return true;

	case AID_LV_ENGINE_LIGHTS:
		if (ENGIND[0]) {
			oapiBlt(surf,srf[12],55,44,55,44,27,27);
		} else {
			oapiBlt(surf,srf[12],55,44,157,44,27,27);
		}
		if (ENGIND[1]) {
			oapiBlt(surf,srf[12],55,98,55,98,27,27);
		} else {
			oapiBlt(surf,srf[12],55,98,157,98,27,27);
		}
		if (ENGIND[2]) {
			oapiBlt(surf,srf[12],20,98,20,98,27,27);
		} else {
			oapiBlt(surf,srf[12],20,98,122,98,27,27);
		}
		if (ENGIND[3]) {
			oapiBlt(surf,srf[12],20,44,20,44,27,27);
		} else {
			oapiBlt(surf,srf[12],20,44,122,44,27,27);
		}
		if (ENGIND[4]) {
			oapiBlt(surf,srf[12],37,71,37,71,27,27);
		} else {
			oapiBlt(surf,srf[12],37,71,140,71,27,27);
		}
		if (ENGIND[5]) {
			oapiBlt(surf,srf[12],6,4,6,4,27,27);
		} else {
			oapiBlt(surf,srf[12],6,4,108,4,27,27);
		}
		if (SIISepState) {
			oapiBlt(surf,srf[12],37,4,37,4,27,27);
		} else {
			oapiBlt(surf,srf[12],37,4,139,4,27,27);
		}
		if (AutopilotLight) {
			oapiBlt(surf,srf[12],69,4,69,4,27,27);
		} else {
			oapiBlt(surf,srf[12],69,4,171,4,27,27);
		}
		return true;

	case AID_MISSION_CLOCK:
		MissionTimerDisplay.Render(surf, srf[SRF_DIGITAL]);
		return true;

	case AID_EVENT_TIMER:
		EventTimerDisplay.Render(surf, srf[SRF_EVENT_TIMER_DIGITS]);
		return true;

	case AID_ALTIMETER:
		RedrawPanel_Alt(surf);
		return true;

	case AID_GMETER  :
		RedrawPanel_G(surf);
		return true;

	case AID_THRUSTMETER  :
		RedrawPanel_Thrust(surf);
		return true;

	//
	// old stuff
	//

	case AID_CMD_SWITCH:
			if(CMDCswitch){
			oapiBlt(surf,srf[8],0,0,25,0,25,45);
			if(CMDswitch){
				oapiBlt(surf,srf[6],1,16,0,0,23,20);
			}else{
				oapiBlt(surf,srf[6],1,16,23,0,23,20);
			}
		}else{
			oapiBlt(surf,srf[8],0,0,0,0,25,45);
			CMDswitch=false;
		}
		return true;

	case AID_CMP_SWITCH:
			if(CMPCswitch){
			oapiBlt(surf,srf[8],0,0,25,0,25,45);
			if(CMPswitch){
				oapiBlt(surf,srf[6],1,16,0,0,23,20);
			}else{
				oapiBlt(surf,srf[6],1,16,23,0,23,20);
			}
		}else{
			oapiBlt(surf,srf[8],0,0,0,0,25,45);
			CMPswitch=false;
		}
		return true;

	case AID_DOCKING_PROBE_SWITCH:
			if(DPCswitch){
			oapiBlt(surf,srf[8],0,64,125,0,25,45);
			oapiBlt(surf,srf[13],7,0,0,0,19,20);
			oapiBlt(surf,srf[13],7,21,0,0,19,20);
			if(DPswitch){
				oapiBlt(surf,srf[6],1,80,0,0,23,20);
				oapiBlt(surf,srf[13],7,0,38,0,19,20);
				oapiBlt(surf,srf[13],7,21,38,0,19,20);
			}else{
				oapiBlt(surf,srf[6],1,80,23,0,23,20);
				oapiBlt(surf,srf[13],7,0,0,0,19,20);
				oapiBlt(surf,srf[13],7,21,0,0,19,20);
			}
		}else{
			oapiBlt(surf,srf[8],0,64,100,0,25,45);
			oapiBlt(surf,srf[13],7,0,0,0,19,20);
			oapiBlt(surf,srf[13],7,21,0,0,19,20);
			DPswitch=false;
		}
		return true;

	case AID_GAUGES1:
		double DispValue;
		if (!ph_sps){
			if(stage < CSM_LEM_STAGE){
				DispValue = 1;
			}else{
				DispValue = 0;
			}
		}else{
			DispValue = GetPropellantMass(ph_sps)/20500;
		}
		oapiBlt(surf,srf[2],0,(90-(int)(DispValue*90.0)),0,0,6,4);//
		oapiBlt(surf,srf[2],31,(90-(int)(DispValue*90.0)),10,0,6,4);//
		if (!ph_rcs0){
			if(stage < CSM_LEM_STAGE){
				DispValue = 1;
			}else{
				DispValue = 0;
			}
		}else{
			DispValue = GetPropellantMass(ph_rcs0)/500;
		}
		oapiBlt(surf,srf[2],65,(90-(int)(DispValue*90.0)),0,0,6,4);//
		if (!ph_rcs1){
			if(stage < CM_ENTRY_STAGE){
				DispValue = 1;
			}else{
				DispValue = 0;
			}
		}else{
		DispValue = GetPropellantMass(ph_rcs1)/500;
		}
		oapiBlt(surf,srf[2],96,(int)(90-(DispValue*90.0)),10,0,6,4);//
		return true;

	case AID_LV_TANK_GAUGES:
		if (!ph_2nd){
			if(stage < LAUNCH_STAGE_SIVB){
				DispValue = 1;
			}else{
				DispValue = 0;
			}
		}else{
			DispValue = GetPropellantMass(ph_2nd)/SII_FuelMass;
		}
		oapiBlt(surf,srf[2],11,(67-(int)(DispValue*67.0))+3,8,0,7,7, SURF_PREDEF_CK);//
		oapiBlt(surf,srf[2],21,(67-(int)(DispValue*67.0))+3,0,0,7,7, SURF_PREDEF_CK);//
		if (!ph_3rd){
			if(stage < LAUNCH_STAGE_SIVB){
				DispValue = 1;
			}else{
				DispValue = 0;
			}
		}else{
			DispValue = GetPropellantMass(ph_3rd)/S4B_FuelMass;
		}
		oapiBlt(surf,srf[2],39,(67-(int)(DispValue*67.0))+3,8,0,7,7, SURF_PREDEF_CK);//
		oapiBlt(surf,srf[2],49,(67-(int)(DispValue*67.0))+3,0,0,7,7, SURF_PREDEF_CK);//
		oapiBlt(surf,srf[2],67,(67-(int)(DispValue*67.0))+3,8,0,7,7, SURF_PREDEF_CK);//
		oapiBlt(surf,srf[2],77,(67-(int)(DispValue*67.0))+3,0,0,7,7, SURF_PREDEF_CK);//
		oapiBlt(surf,srf[2],96,(67-(int)(DispValue*67.0))+3,8,0,7,7, SURF_PREDEF_CK);//
		oapiBlt(surf,srf[2],105,(67-(int)(DispValue*67.0))+3,0,0,7,7, SURF_PREDEF_CK);//
		return true;

	case AID_SMRCS_FUEL:
		if (!ph_rcs0){
			if(stage < CSM_LEM_STAGE){
				DispValue = 1;
			}else{
				DispValue = 0;
			}
		}else{
			DispValue = GetPropellantMass(ph_rcs0)/500;
		}
		oapiBlt(surf,srf[2],  0,(38-(int)(DispValue*38.0))+40,0,0,7,7, SURF_PREDEF_CK);//
		oapiBlt(surf,srf[2], 36,(60-(int)(DispValue*60.0))+17,8,0,7,7, SURF_PREDEF_CK);//
		oapiBlt(surf,srf[2], 67,(75-(int)(DispValue*75.0))+ 2,0,0,7,7, SURF_PREDEF_CK);//
		oapiBlt(surf,srf[2],104,(75-(int)(DispValue*75.0))+ 2,8,0,7,7, SURF_PREDEF_CK);//
		return true;

	case AID_SPS_FUEL:
		if (!ph_sps){
			if(stage < CSM_LEM_STAGE){
				DispValue = 1;
			}else{
				DispValue = 0;
			}
		}else{
			DispValue = GetPropellantMass(ph_sps)/20500;
		}
		oapiBlt(surf,srf[2],  0,(40-(int)(DispValue*40.0))+40,0,0,7,7, SURF_PREDEF_CK);//
		oapiBlt(surf,srf[2], 36,(63-(int)(DispValue*63.0))+17,8,0,7,7, SURF_PREDEF_CK);//
		oapiBlt(surf,srf[2], 64,(78-(int)(DispValue*78.0))+ 2,0,0,7,7, SURF_PREDEF_CK);//
		oapiBlt(surf,srf[2],100,(78-(int)(DispValue*78.0))+ 2,8,0,7,7, SURF_PREDEF_CK);//
		return true;

	case AID_ALTITUDE1:
		int TmpALT;
		double tmpALTdec;
		int tmpalt2;
		if (actualALT > 999999){
		actualALT = actualALT /1000000;
		oapiBlt(surf,srf[SRF_DIGITAL],85,0,130,0,10,15);
		}else if (actualALT > 9999){
		actualALT =actualALT /1000;
		oapiBlt(surf,srf[SRF_DIGITAL],85,0,120,0,10,15);
		}

		TmpALT = (int)actualALT;
		tmpALTdec = actualALT-TmpALT;
		tmpalt2 = (int)(tmpALTdec *100.0);

		Curdigit=(int)actualALT/10000;
		oapiBlt(surf,srf[SRF_DIGITAL],0,0,10*Curdigit,0,10,15);
		Curdigit=(int)actualALT/1000;
		Curdigit2=(int)actualALT/10000;
		oapiBlt(surf,srf[SRF_DIGITAL],10,0,10*(Curdigit-(Curdigit2*10)),0,10,15);
		Curdigit=(int)actualALT/100;
		Curdigit2=(int)actualALT/1000;
		oapiBlt(surf,srf[SRF_DIGITAL],20,0,10*(Curdigit-(Curdigit2*10)),0,10,15);
		Curdigit=(int)actualALT/10;
		Curdigit2=(int)actualALT/100;
		oapiBlt(surf,srf[SRF_DIGITAL],30,0,10*(Curdigit-(Curdigit2*10)),0,10,15);
		Curdigit=(int)actualALT;
		Curdigit2=(int)actualALT/10;
		oapiBlt(surf,srf[SRF_DIGITAL],40,0,10*(Curdigit-(Curdigit2*10)),0,10,15);
		oapiBlt(surf,srf[SRF_DIGITAL],50,11,140,8,10,4);//dot display

		Curdigit=tmpalt2/10 ;
		Curdigit2=tmpalt2 /100;
		oapiBlt(surf,srf[SRF_DIGITAL],60,0,10*(Curdigit-(Curdigit2*10)),0,10,15);
		Curdigit=tmpalt2 ;
		Curdigit2=tmpalt2 /10;
		oapiBlt(surf,srf[SRF_DIGITAL],70,0,10*(Curdigit-(Curdigit2*10)),0,10,15);
		return true;

	case AID_SC_SWITCH:
		if(SCswitch){
			oapiBlt(surf,srf[6],0,0,0,0,23,20);
		}
		else{
			oapiBlt(surf,srf[6],0,0,23,0,23,20);
		}
		return true;

	case AID_CABIN_PRESS:
		if(RPswitch13){
			oapiBlt(surf,srf[6],38,6,0,0,23,20);
		}else{
			oapiBlt(surf,srf[6],38,6,23,0,23,20);
		}
		if(RPswitch14){
			oapiBlt(surf,srf[6],5,6,0,0,23,20);
		}else{
			oapiBlt(surf,srf[6],5,6,23,0,23,20);
		}
		return true;

#if 0
	case AID_05G_LIGHT:
		if(P115switch){
			oapiBlt(surf,srf[SRF_ALLROUND],0,0,600,68,24,13);
		}else{
			oapiBlt(surf,srf[SRF_ALLROUND],0,0,600,82,24,13);
		}
		return true;
#endif

	case AID_SPS_LIGHT:
		if(SPSswitch.IsUp()){
			oapiBlt(surf,srf[SRF_ALLROUND],0,0,625,68,24,13);
		}else{
			oapiBlt(surf,srf[SRF_ALLROUND],0,0,625,82,24,13);
		}
		return true;

	case AID_SPS_INJ_VLV:
		if(SPSswitch.IsUp()){
			oapiBlt(surf,srf[SRF_ALLROUND],0,0,0,168,141,32);
		}else{
			oapiBlt(surf,srf[SRF_ALLROUND],0,0,0,135,141,32);
		}
		return true;

	case AID_EMS_KNOB:
		if(EMSKswitch){
			oapiBlt(surf,srf[SRF_ALLROUND],0,0,516,0,67,67);
		}else{
			oapiBlt(surf,srf[SRF_ALLROUND],0,0,583,0,67,67);
		}
		return true;

	case AID_EMS_DISPLAY:
		if(EMSKswitch){
			oapiBlt(surf,srf[SRF_ALLROUND],0,0,651,0,100,104);
		}
		return true;

	case AID_MASTER_ALARM:
	case AID_MASTER_ALARM2:
	case AID_MASTER_ALARM3:
		cws.RenderMasterAlarm(surf, srf[SRF_MASTERALARM_BRIGHT]);
		return true;

	case AID_CWS_LIGHTS_LEFT:
		cws.RenderLights(surf, srf[SRF_CWSLIGHTS], true);
		return true;

	case AID_CWS_LIGHTS_RIGHT:
		cws.RenderLights(surf, srf[SRF_CWSLIGHTS], false);
		return true;

	case AID_DIRECT_ULLAGE_THRUST_ON_LIGHT:
		if (LAUNCHIND[6]){
			oapiBlt(surf,srf[10],3,3,27,0,26,26);
		}else{
			oapiBlt(surf,srf[10],3,3,0,0,26,26);
		}
		if (LAUNCHIND[7]){
			oapiBlt(surf,srf[10],3,42,27,27,26,26);
		}else{
			oapiBlt(surf,srf[10],3,42,0,27,26,26);
		}
		return true;

	case AID_MFDDOCK:
		if (oapiGetMFDMode(MFD_RIGHT) != MFD_NONE) {	// MFD_USER1
			oapiBlt(surf,srf[24], 0, 0, 0, 0, 301, 251);

			RedrawPanel_MFDButton (surf, MFD_RIGHT, 0, 7, 38);	// MFD_USER1
			RedrawPanel_MFDButton (surf, MFD_RIGHT, 1, 274, 38);	// MFD_USER1
		}
		return true;

	case AID_MFDDOCK_POWER:
		if (oapiGetMFDMode(MFD_RIGHT) == MFD_NONE) {	// MFD_USER1
			oapiBlt(surf, srf[25], 0, 0, 0, 0, 20, 15);
		}
		return true;
	}
	return false;
}

void Saturn::clbkMFDMode (int mfd, int mode) {

	switch (mfd) {
	case MFD_RIGHT:		// MFD_USER1
		oapiTriggerPanelRedrawArea (SATPANEL_LEFT_RNDZ_WINDOW, AID_MFDDOCK);
		break;
	}
}

//
// Set switches to default state.
//

void Saturn::InitSwitches() {

	LiftoffNoAutoAbortSwitch.Register(PSH, "LiftoffNoAutoAbortSwitch", false, false);
	LesMotorFireSwitch.Register(PSH, "LesMotorFireSwitch", false, false);
	CanardDeploySwitch.Register(PSH, "CanardDeploySwitch", false, false);
	CsmLvSepSwitch = false;						// saved in SSwitchState.Sswitch5
	CsmLvSepSwitch.SetGuardState(false);		// saved in CSwitchState.Cswitch5
	ApexCoverJettSwitch.Register(PSH, "ApexCoverJettSwitch", false, false);
	DrogueDeploySwitch.Register(PSH, "DrogueDeploySwitch", false, false);
	MainDeploySwitch.Register(PSH, "MainDeploySwitch", false, false);
	CmRcsHeDumpSwitch = false;					// saved in SSwitchState.CMRHDswitch
	CmRcsHeDumpSwitch.SetGuardState(false);		// saved in CSwitchState.CMRHGswitch

	EDSSwitch = true;							// saved in LPSwitchState.EDSswitch
	CsmLmFinalSep1Switch = false;				// saved in SSwitchState.Sswitch1
	CsmLmFinalSep1Switch.SetGuardState(false);	// saved in CSwitchState.Cswitch1
	CsmLmFinalSep1Switch.SetSpringLoaded(SPRINGLOADEDSWITCH_DOWN);
	CsmLmFinalSep2Switch = false;				// saved in SSwitchState.Sswitch2
	CsmLmFinalSep2Switch.SetGuardState(false);	// saved in CSwitchState.Cswitch2
	CsmLmFinalSep2Switch.SetSpringLoaded(SPRINGLOADEDSWITCH_DOWN);
	CmSmSep1Switch = false;						// saved in SSwitchState.Sswitch3
	CmSmSep1Switch.SetGuardState(false);		// saved in CSwitchState.Cswitch3
	CmSmSep1Switch.SetSpringLoaded(SPRINGLOADEDSWITCH_DOWN);
	CmSmSep2Switch = false;						// saved in SSwitchState.Sswitch4
	CmSmSep2Switch.SetGuardState(false);		// saved in CSwitchState.Cswitch4
	CmSmSep2Switch.SetSpringLoaded(SPRINGLOADEDSWITCH_DOWN);
	SivbLmSepSwitch = false;					// saved in RPSwitchState.RPswitch16
	SivbLmSepSwitch.SetGuardState(false);		// saved in RPSwitchState.RPCswitch
	SivbLmSepSwitch.SetSpringLoaded(SPRINGLOADEDSWITCH_DOWN);

	MissionTimerSwitch.Register(PSH, "MissionTimerSwitch", THREEPOSSWITCH_CENTER);
	CautionWarningModeSwitch.Register(PSH, "CautionWarningModeSwitch", THREEPOSSWITCH_UP);
	CautionWarningCMCSMSwitch.Register(PSH, "CautionWarningCMCSMSwitch", 1);
	CautionWarningPowerSwitch.Register(PSH, "CautionWarningPowerSwitch", THREEPOSSWITCH_UP);
	CautionWarningLightTestSwitch.Register(PSH, "CautionWarningLightTestSwitch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);

	CabinFan1Switch = false;					// saved in CP2SwitchState.CFswitch1
	CabinFan2Switch = false;					// saved in CP2SwitchState.CFswitch2
	H2Heater1Switch.Register(PSH, "H2Heater1Switch", THREEPOSSWITCH_UP);
	H2Heater2Switch.Register(PSH, "H2Heater2Switch", THREEPOSSWITCH_UP);
	O2Heater1Switch.Register(PSH, "O2Heater1Switch", THREEPOSSWITCH_UP);
	O2Heater2Switch.Register(PSH, "O2Heater2Switch", THREEPOSSWITCH_UP);
	O2PressIndSwitch.Register(PSH, "O2PressIndSwitch", true);
	H2Fan1Switch.Register(PSH, "H2Fan1Switch", THREEPOSSWITCH_UP);
	H2Fan2Switch.Register(PSH, "H2Fan2Switch", THREEPOSSWITCH_UP);
	O2Fan1Switch.Register(PSH, "O2Fan1Switch", THREEPOSSWITCH_UP);
	O2Fan2Switch.Register(PSH, "O2Fan2Switch", THREEPOSSWITCH_UP);

	FuelCellPhIndicator.Register(PSH, "FuelCellPhIndicator", false);
	FuelCellRadTempIndicator.Register(PSH, "FuelCellRadTempIndicator", false);

	FuelCellRadiators1Indicator.Register(PSH, "FuelCellRadiators1Indicator", false);
	FuelCellRadiators2Indicator.Register(PSH, "FuelCellRadiators2Indicator", false);
	FuelCellRadiators3Indicator.Register(PSH, "FuelCellRadiators3Indicator", false);
	FuelCellRadiators1Switch.Register(PSH, "FuelCellRadiators1Switch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER); 
	FuelCellRadiators2Switch.Register(PSH, "FuelCellRadiators2Switch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER); 
	FuelCellRadiators3Switch.Register(PSH, "FuelCellRadiators3Switch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER); 

	FuelCellIndicatorsSwitch.AddPosition(1, 330);
	FuelCellIndicatorsSwitch.AddPosition(2,   0);
	FuelCellIndicatorsSwitch.AddPosition(3,  30);
	FuelCellIndicatorsSwitch.Register(PSH, "FuelCellIndicatorsSwitch", 1);

	FuelCellHeater1Switch.Register(PSH, "FuelCellHeater1Switch", true);
	FuelCellHeater2Switch.Register(PSH, "FuelCellHeater2Switch", true);
	FuelCellHeater3Switch.Register(PSH, "FuelCellHeater3Switch", true);

	FuelCellPurge1Switch.Register(PSH, "FuelCellPurge1Switch", THREEPOSSWITCH_CENTER);
	FuelCellPurge2Switch.Register(PSH, "FuelCellPurge2Switch", THREEPOSSWITCH_CENTER);
	FuelCellPurge3Switch.Register(PSH, "FuelCellPurge3Switch", THREEPOSSWITCH_CENTER);

	FuelCellReactants1Indicator.Register(PSH, "FuelCellReactants1Indicator", false);
	FuelCellReactants2Indicator.Register(PSH, "FuelCellReactants2Indicator", false);
	FuelCellReactants3Indicator.Register(PSH, "FuelCellReactants3Indicator", false);
	FuelCellReactants1Switch.Register(PSH, "FuelCellReactants1Switch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);
	FuelCellReactants2Switch.Register(PSH, "FuelCellReactants2Switch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);
	FuelCellReactants3Switch.Register(PSH, "FuelCellReactants3Switch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);

	FCReacsValvesSwitch.Register(PSH, "FCReacsValvesSwitch", true);
	H2PurgeLineSwitch.Register  (PSH, "H2PurgeLineSwitch",   false);

	FuelCellPumps1Switch.Register(PSH, "FuelCellPumps1Switch", THREEPOSSWITCH_UP); 
	FuelCellPumps2Switch.Register(PSH, "FuelCellPumps2Switch", THREEPOSSWITCH_UP); 
	FuelCellPumps3Switch.Register(PSH, "FuelCellPumps3Switch", THREEPOSSWITCH_UP); 

	SuitCompressor1Switch.Register(PSH, "SuitCompressor1Switch", THREEPOSSWITCH_CENTER);   
	SuitCompressor2Switch.Register(PSH, "SuitCompressor2Switch", THREEPOSSWITCH_CENTER);   
	
	SBandNormalXPDRSwitch.Register(PSH, "SBandNormalXPDRSwitch", THREEPOSSWITCH_CENTER);
	SBandNormalPwrAmpl1Switch.Register(PSH, "SBandNormalPwrAmpl1Switch", THREEPOSSWITCH_CENTER);
	SBandNormalPwrAmpl2Switch.Register(PSH, "SBandNormalPwrAmpl2Switch", THREEPOSSWITCH_CENTER);
	SBandNormalMode1Switch.Register(PSH, "SBandNormalMode1Switch", THREEPOSSWITCH_CENTER);
	SBandNormalMode2Switch.Register(PSH, "SBandNormalMode2Switch", THREEPOSSWITCH_CENTER);
	SBandNormalMode3Switch.Register(PSH, "SBandNormalMode3Switch", false);

	MissionTimerHoursSwitch.Register(PSH, "MissionTimerHoursSwitch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);
	MissionTimerMinutesSwitch.Register(PSH, "MissionTimerMinutesSwitch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);
	MissionTimerSecondsSwitch.Register(PSH, "MissionTimerSecondsSwitch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);

	SMRCSHelium1ASwitch.Register(PSH, "SMRCSHelium1ASwitch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);
	SMRCSHelium1BSwitch.Register(PSH, "SMRCSHelium1BSwitch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);
	SMRCSHelium1CSwitch.Register(PSH, "SMRCSHelium1CSwitch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);
	SMRCSHelium1DSwitch.Register(PSH, "SMRCSHelium1DSwitch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);

	SMRCSHelium1ATalkback.Register(PSH, "SMRCSHelium1ATalkback", true);
	SMRCSHelium1BTalkback.Register(PSH, "SMRCSHelium1BTalkback", true);
	SMRCSHelium1CTalkback.Register(PSH, "SMRCSHelium1CTalkback", true);
	SMRCSHelium1DTalkback.Register(PSH, "SMRCSHelium1DTalkback", true);

	SMRCSHelium2ASwitch.Register(PSH, "SMRCSHelium2ASwitch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);
	SMRCSHelium2BSwitch.Register(PSH, "SMRCSHelium2BSwitch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);
	SMRCSHelium2CSwitch.Register(PSH, "SMRCSHelium2CSwitch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);
	SMRCSHelium2DSwitch.Register(PSH, "SMRCSHelium2DSwitch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);

	SMRCSHelium2ATalkback.Register(PSH, "SMRCSHelium2ATalkback", true);
	SMRCSHelium2BTalkback.Register(PSH, "SMRCSHelium2BTalkback", true);
	SMRCSHelium2CTalkback.Register(PSH, "SMRCSHelium2CTalkback", true);
	SMRCSHelium2DTalkback.Register(PSH, "SMRCSHelium2DTalkback", true);

	SMRCSProp1ASwitch.Register(PSH, "SMRCSProp1ASwitch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);
	SMRCSProp1BSwitch.Register(PSH, "SMRCSProp1BSwitch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);
	SMRCSProp1CSwitch.Register(PSH, "SMRCSProp1CSwitch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);
	SMRCSProp1DSwitch.Register(PSH, "SMRCSProp1DSwitch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);

	SMRCSProp1ATalkback.Register(PSH, "SMRCSProp1ATalkback", false);
	SMRCSProp1BTalkback.Register(PSH, "SMRCSProp1BTalkback", false);
	SMRCSProp1CTalkback.Register(PSH, "SMRCSProp1CTalkback", false);
	SMRCSProp1DTalkback.Register(PSH, "SMRCSProp1DTalkback", false);

	SMRCSProp2ASwitch.Register(PSH, "SMRCSProp2ASwitch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);
	SMRCSProp2BSwitch.Register(PSH, "SMRCSProp2BSwitch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);
	SMRCSProp2CSwitch.Register(PSH, "SMRCSProp2CSwitch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);
	SMRCSProp2DSwitch.Register(PSH, "SMRCSProp2DSwitch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);

	SMRCSProp2ATalkback.Register(PSH, "SMRCSProp2ATalkback", false);
	SMRCSProp2BTalkback.Register(PSH, "SMRCSProp2BTalkback", false);
	SMRCSProp2CTalkback.Register(PSH, "SMRCSProp2CTalkback", false);
	SMRCSProp2DTalkback.Register(PSH, "SMRCSProp2DTalkback", false);

	CMUplinkSwitch.Register(PSH, "CMUplinkSwitch", 1);
	IUUplinkSwitch.Register(PSH, "CMUplinkSwitch", 1);
	CMRCSPressSwitch.Register(PSH, "CMRCSPressSwitch", 0, 0);
	SMRCSIndSwitch.Register(PSH, "SMRCSIndSwitch", 0);

	SMRCSHeaterASwitch.Register(PSH, "SMRCSHeaterASwitch", THREEPOSSWITCH_CENTER);
	SMRCSHeaterBSwitch.Register(PSH, "SMRCSHeaterBSwitch", THREEPOSSWITCH_CENTER);
	SMRCSHeaterCSwitch.Register(PSH, "SMRCSHeaterCSwitch", THREEPOSSWITCH_CENTER);
	SMRCSHeaterDSwitch.Register(PSH, "SMRCSHeaterDSwitch", THREEPOSSWITCH_CENTER);

	RCSCMDSwitch.Register(PSH, "RCSCMDSwitch", THREEPOSSWITCH_CENTER);
	RCSTrnfrSwitch.Register(PSH, "RCSTrnfrSwitch", THREEPOSSWITCH_CENTER);
	CMRCSIsolate1.Register(PSH, "CMRCSIsolate1", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);
	CMRCSIsolate2.Register(PSH, "CMRCSIsolate2", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);

	CMRCSIsolate1Talkback.Register(PSH, "CMRCSIsolate1Talkback", false);
	CMRCSIsolate2Talkback.Register(PSH, "CMRCSIsolate2Talkback", false);

	ManualAttRollSwitch.Register(PSH, "ManualAttRollSwitch", THREEPOSSWITCH_CENTER);
	ManualAttPitchSwitch.Register(PSH, "ManualAttPitchSwitch", THREEPOSSWITCH_CENTER);
	ManualAttYawSwitch.Register(PSH, "ManualAttYawSwitch", THREEPOSSWITCH_CENTER);

	LimitCycleSwitch.Register(PSH, "LimitCycleSwitch", 0);
	AttDeadbandSwitch.Register(PSH, "AttDeadbandSwitch", 0);
	AttRateSwitch.Register(PSH, "AttRateSwitch", 0);
	TransContrSwitch.Register(PSH, "TransContrSwitch", 0);

	BMAGRollSwitch.Register(PSH, "BMAGRollSwitch", THREEPOSSWITCH_CENTER);
	BMAGPitchSwitch.Register(PSH, "BMAGPitchSwitch", THREEPOSSWITCH_CENTER);
	BMAGYawSwitch.Register(PSH, "BMAGYawSwitch", THREEPOSSWITCH_CENTER);

	EntryModeSwitch.Register(PSH, "EntryModeSwitch", THREEPOSSWITCH_CENTER);
	CMCAttSwitch.Register(PSH, "CMCAttSwitch", 1);

	FDAIScaleSwitch.Register(PSH, "FDAIScaleSwitch", THREEPOSSWITCH_CENTER);
	FDAISourceSwitch.Register(PSH, "FDAISourceSwitch", THREEPOSSWITCH_CENTER);
	FDAISelectSwitch.Register(PSH, "FDAISelectSwitch", THREEPOSSWITCH_CENTER);
	FDAIAttSetSwitch.Register(PSH, "FDAIAttSetSwitch", 1);

	IMUGuardedCageSwitch.Register(PSH, "IMUGuardedCageSwitch", 1, 1);

	RCSIndicatorsSwitch.AddPosition(1, 280);
	RCSIndicatorsSwitch.AddPosition(2, 320);
	RCSIndicatorsSwitch.AddPosition(3, 340);	
	RCSIndicatorsSwitch.AddPosition(4, 20);	
	RCSIndicatorsSwitch.AddPosition(5, 40);	
	RCSIndicatorsSwitch.AddPosition(6, 70);
	RCSIndicatorsSwitch.Register(PSH, "RCSIndicatorsSwitch", 1);

	LVGuidanceSwitch.Register(PSH, "LVGuidanceSwitch", 1);
	SIISIVBSepSwitch.Register(PSH, "SIISIVBSepSwitch", 0, 0);
	TLIEnableSwitch.Register(PSH, "TLIEnableSwitch", 0);

	ECSIndicatorsSwitch.AddPosition(1, 340);
	ECSIndicatorsSwitch.AddPosition(2, 20);
	ECSIndicatorsSwitch.Register(PSH, "ECSIndicatorsSwitch", 1);

	CGSwitch.Register(PSH, "CGSwitch", 0);
	ELSLogicSwitch.Register(PSH, "ELSLogicSwitch", 0, 0);
	ELSAutoSwitch.Register(PSH, "ELSAutoSwitch", 1);
	CMRCSLogicSwitch.Register(PSH, "CMRCSLogicSwitch", 0);
	CMPropDumpSwitch.Register(PSH, "CMPropDumpSwitch", 0, 0);
	CPPropPurgeSwitch.Register(PSH, "CPPropPurgeSwitch", 0, 0);

	FCSMSPSASwitch.Register(PSH, "FCSMSPSASwitch", 0);
	FCSMSPSBSwitch.Register(PSH, "FCSMSPSBSwitch", 0);
	EventTimerUpDownSwitch.Register(PSH, "EventTimerUpDownSwitch", THREEPOSSWITCH_DOWN);
	EventTimerControlSwitch.Register(PSH, "EventTimerControlSwitch", THREEPOSSWITCH_DOWN);
	EventTimerMinutesSwitch.Register(PSH, "EventTimerMinutesSwitch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);
	EventTimerSecondsSwitch.Register(PSH, "EventTimerSecondsSwitch", THREEPOSSWITCH_CENTER, SPRINGLOADEDSWITCH_CENTER);

	MainReleaseSwitch.Register(PSH, "MainReleaseSwitch", 0, 0);

	PropDumpAutoSwitch.Register(PSH, "PropDumpAutoSwitch", 1);
	TwoEngineOutAutoSwitch.Register(PSH, "TwoEngineOutAutoSwitch", 1);
	LVRateAutoSwitch.Register(PSH, "LVRateAutoSwitch", 1);
	TowerJett1Switch.Register(PSH, "TowerJett1Switch", 0, 0);
	TowerJett2Switch.Register(PSH, "TowerJett2Switch", 0, 0);

	RotPowerNormal1Switch.Register(PSH, "RotPowerNormal1Switch", THREEPOSSWITCH_CENTER);
	RotPowerNormal2Switch.Register(PSH, "RotPowerNormal2Switch", THREEPOSSWITCH_CENTER);
	RotPowerDirect1Switch.Register(PSH, "RotPowerDirect1Switch", THREEPOSSWITCH_CENTER);
	RotPowerDirect2Switch.Register(PSH, "RotPowerDirect2Switch", THREEPOSSWITCH_CENTER);

	dVThrust1Switch.Register(PSH, "dVThrust1Switch", 0, 0);
	dVThrust2Switch.Register(PSH, "dVThrust2Switch", 0, 0);

	SPSswitch.Register(PSH, "SPSswitch", THREEPOSSWITCH_CENTER);

	//
	// Old stuff. Delete when no longer required.
	//

	RPswitch13=false;
	RPswitch14=false;
	RPswitch15=1;

	RPswitch17 = false;

	LPswitch5.SetActive(false);

	CMDswitch = false;
	CMDCswitch = false;

	CMPswitch = false;
	CMPCswitch = false;

	P231switch = 1;
	P232switch = 1;
	P233switch = 1;
	P234switch = 1;
	P235switch = 0;
	P236switch = 1;
	P237switch = 1;
	P238switch = 1;
	P239switch = 1;
	P240switch = 1;
	P241switch = 1;
	P242switch = 0;
	P243switch = 0;
	P244switch = 0;

	P31switch = false;
	P32switch = false;
	P33switch = false;
	P34switch = 1;
	P35switch = 1;
	P36switch = 1;

	P311switch = 1;
	P312switch = 0;
	P313switch = 1;
	P314switch = 1;
	P315switch = 1;
	P316switch = 0;
	P317switch = 1;
	P318switch = 1;
	P319switch = 0;
	P320switch = 1;
	P321switch = 1;
	P322switch = 1;
	P323switch = 1;
	P324switch = 1;
	P325switch = 1;
	P326switch = 0;
	P327switch = 0;
	P328switch = true;
	P329switch = true;
	P330switch = 0;
	P331switch = 1;
	P332switch = 1;
	P333switch = 1;
	P334switch = 1;
	P335switch = 0;
	P336switch = 1;

	P337switch = 1;
	P338switch = 1;
	P339switch = 1;
	P340switch = 1;
	P341switch = 1;
	P342switch = 1;
	P343switch = 1;
	P344switch = 1;
	P345switch = 1;
	P346switch = 1;
	P347switch = 1;

	DPswitch = false;
	DPCswitch = false;

	FCswitch1 = true;
	FCswitch2 = true;
	FCswitch3 = true;
	FCswitch4 = true;
	FCswitch5 = true;
	FCswitch6 = true;

	CMCswitch = true;

	EMSswitch = 1;

	EMSKswitch = false;
}

//
// Scenario state functions.
//

//
// The switch functions just pack the different switch areas from the control panel
// into 32-bit integers and unpack them from those integers. This provides a much more
// compact means of storing the switch states in the scenario file than saving them as
// individual values for each switch.
//

typedef union {
	struct {
		unsigned Cswitch1:1;
		unsigned Cswitch2:1;
		unsigned Cswitch3:1;
		unsigned Cswitch4:1;
		unsigned Cswitch5:1;
		unsigned Cswitch6:1;
		unsigned Cswitch7:1;
		unsigned Cswitch8:1;
		unsigned Cswitch9:1;
		unsigned DVCswitch:1;
		unsigned DVBCswitch:1;
		unsigned ELSCswitch:1;
		unsigned CMDCswitch:1;
		unsigned CMPCswitch:1;
		unsigned IMUCswitch:1;
		unsigned MRswitch:1;
		unsigned MRCswitch:1;
		unsigned TJ1switch:1;
		unsigned TJ1Cswitch:1;
		unsigned TJ2switch:1;
		unsigned TJ2Cswitch:1;
		unsigned IUswitch:1;
		unsigned IUCswitch:1;
		unsigned LVSswitch:1;
		unsigned LVSCswitch:1;
		unsigned DPswitch:1;
		unsigned DPCswitch:1;
		unsigned CMRHGswitch:1;
	} u;
	unsigned long word;
} CSwitchState;

int Saturn::GetCSwitchState()

{
	CSwitchState state;

	state.word = 0;
	state.u.Cswitch1 = CsmLmFinalSep1Switch.GetGuardState();
	state.u.Cswitch2 = CsmLmFinalSep2Switch.GetGuardState();
	state.u.Cswitch3 = CmSmSep1Switch.GetGuardState();
	state.u.Cswitch4 = CmSmSep2Switch.GetGuardState();
	state.u.Cswitch5 = CsmLvSepSwitch.GetGuardState();
	state.u.CMDCswitch = CMDCswitch;
	state.u.CMPCswitch = CMPCswitch;
	state.u.DPswitch = DPswitch;
	state.u.DPCswitch = DPCswitch;
	state.u.CMRHGswitch = CmRcsHeDumpSwitch.GetGuardState();

	return state.word;
}

void Saturn::SetCSwitchState(int s)

{
	CSwitchState state;

	state.word = s;
	CsmLmFinalSep1Switch.SetGuardState(state.u.Cswitch1);
	CsmLmFinalSep2Switch.SetGuardState(state.u.Cswitch2);
	CmSmSep1Switch.SetGuardState(state.u.Cswitch3);
	CmSmSep2Switch.SetGuardState(state.u.Cswitch4);
	CsmLvSepSwitch.SetGuardState(state.u.Cswitch5);
	CMDCswitch = state.u.CMDCswitch;
	CMPCswitch = state.u.CMPCswitch;;
	DPswitch = state.u.DPswitch;
	DPCswitch = state.u.DPCswitch;
	CmRcsHeDumpSwitch.SetGuardState(state.u.CMRHGswitch);
}

typedef union {
	struct {
		unsigned Sswitch1:1;
		unsigned Sswitch2:1;
		unsigned Sswitch3:1;
		unsigned Sswitch4:1;
		unsigned Sswitch5:1;
		unsigned Sswitch6:1;
		unsigned Sswitch7:1;
		unsigned Sswitch8:1;
		unsigned Sswitch9:1;
		unsigned DVAswitch:1;
		unsigned DVBswitch:1;
		unsigned ELSswitch:1;
		unsigned CMDswitch:1;
		unsigned CMPswitch:1;
		unsigned IMUswitch:1;
		unsigned CMRHDswitch:1;
	} u;
	unsigned long word;
} SSwitchState;

int Saturn::GetSSwitchState()

{
	SSwitchState state;

	state.word = 0;
	state.u.Sswitch1 = CsmLmFinalSep1Switch;
	state.u.Sswitch2 = CsmLmFinalSep2Switch;
	state.u.Sswitch3 = CmSmSep1Switch;
	state.u.Sswitch4 = CmSmSep2Switch;
	state.u.Sswitch5 = CsmLvSepSwitch;
	state.u.CMDswitch = CMDswitch;
	state.u.CMPswitch = CMPswitch;
	state.u.CMRHDswitch = CmRcsHeDumpSwitch;

	return state.word;
}

void Saturn::SetSSwitchState(int s)

{
	SSwitchState state;

	state.word = s;
	CsmLmFinalSep1Switch = state.u.Sswitch1;
	CsmLmFinalSep2Switch = state.u.Sswitch2;
	CmSmSep1Switch = state.u.Sswitch3;
	CmSmSep2Switch = state.u.Sswitch4;
	CsmLvSepSwitch = state.u.Sswitch5;
	CMDswitch = state.u.CMDswitch;
	CMPswitch = state.u.CMPswitch;
	CmRcsHeDumpSwitch = state.u.CMRHDswitch;
}

typedef union {
	struct {
		unsigned LPswitch4:1;
		unsigned LPswitch5:1;
		unsigned LPswitch6:1;
		unsigned LPswitch7:1;
		unsigned SPSswitch:1;
		unsigned EDSswitch:1;
		unsigned P11switch:1;
		unsigned P12switch:1;
		unsigned P13switch:1;
		unsigned P14switch:1;
		unsigned P15switch:1;
		unsigned P16switch:1;
		unsigned SCswitch:1;
		unsigned TLIswitch:1;
		unsigned P111switch:1;
		unsigned P112switch:1;
		unsigned P113switch:1;
		unsigned FCSMswitch:1;
		unsigned EMSKswitch:1;
	} u;
	unsigned long word;
} LPSwitchState;

int Saturn::GetLPSwitchState()

{
	LPSwitchState state;

	state.word = 0;
	state.u.LPswitch5 = LPswitch5;
	state.u.LPswitch6 = LPswitch6;
	state.u.LPswitch7 = LPswitch7;
	state.u.EDSswitch = EDSSwitch;
	state.u.SCswitch = SCswitch;
	state.u.EMSKswitch = EMSKswitch;

	return state.word;
}

void Saturn::SetLPSwitchState(int s)

{
	LPSwitchState state;

	state.word = s;
	LPswitch5 = state.u.LPswitch5;
	LPswitch6 = state.u.LPswitch6;
	LPswitch7 = state.u.LPswitch7;
	EDSSwitch = state.u.EDSswitch;
	SCswitch = state.u.SCswitch;
	EMSKswitch = state.u.EMSKswitch;
}

typedef union {
	struct {
		unsigned RPswitch1:1;
		unsigned RPswitch2:1;
		unsigned RPswitch3:1;
		unsigned RPswitch4:1;
		unsigned RPswitch5:1;
		unsigned RPswitch6:1;
		unsigned RPswitch7:1;
		unsigned RPswitch8:1;
		unsigned RPswitch9:1;
		unsigned RPswitch10:1;
		unsigned RPswitch11:1;
		unsigned RPswitch12:1;
		unsigned RPswitch13:1;
		unsigned RPswitch14:1;
		unsigned RPswitch16:1;
		unsigned RPCswitch:1;
		unsigned CMRswitch:1;
		unsigned CMRCswitch:1;
		unsigned CMCswitch:1;
	} u;
	unsigned long word;
} RPSwitchState;

int Saturn::GetRPSwitchState()

{
	RPSwitchState state;

	state.word = 0;
	state.u.RPswitch13 = RPswitch13;
	state.u.RPswitch14 = RPswitch14;
	state.u.RPswitch16 = SivbLmSepSwitch;
	state.u.RPCswitch = SivbLmSepSwitch.GetGuardState();
	state.u.CMCswitch = CMCswitch;

	return state.word;
}

void Saturn::SetRPSwitchState(int s)

{
	RPSwitchState state;

	state.word = s;
	RPswitch13 = state.u.RPswitch13;
	RPswitch14 = state.u.RPswitch14;
	SivbLmSepSwitch = state.u.RPswitch16;
	SivbLmSepSwitch.SetGuardState(state.u.RPCswitch);
	CMCswitch = state.u.CMCswitch;
}

typedef union {
	struct {
		unsigned CR1switch:1;
		unsigned CR2switch:1;
		unsigned SP1switch:1;
		unsigned SP2switch:1;
		unsigned SP3switch:1;
		unsigned SP4switch:1;
		unsigned Unused1:1;
		unsigned CFswitch1:1;
		unsigned CFswitch2:1;
	} u;
	unsigned long word;
} CP2SwitchState;

int Saturn::GetCP2SwitchState()

{
	CP2SwitchState state;

	state.word = 0;
	state.u.CFswitch1 = CabinFan1Switch;
	state.u.CFswitch2 = CabinFan2Switch;

	return state.word;
}

void Saturn::SetCP2SwitchState(int s)

{
	CP2SwitchState state;

	state.word = s;
	CabinFan1Switch = state.u.CFswitch1;
	CabinFan2Switch = state.u.CFswitch2;

}

typedef union {
	struct {
		unsigned P31switch:1;
		unsigned P32switch:1;
		unsigned P33switch:1;
		unsigned FCRswitch1:1;
		unsigned FCRswitch2:1;
		unsigned FCRswitch3:1;
		unsigned FCBswitch1:1;
		unsigned FCBswitch2:1;
		unsigned FCBswitch3:1;
	} u;
	unsigned long word;
} CP3SwitchState;

int Saturn::GetCP3SwitchState()

{
	CP3SwitchState state;

	state.word = 0;
	state.u.P31switch = P31switch;
	state.u.P32switch = P32switch;
	state.u.P33switch = P33switch;
	return state.word;
}

void Saturn::SetCP3SwitchState(int s)

{
	CP3SwitchState state;

	state.word = s;
	P31switch = state.u.P31switch;
	P32switch = state.u.P32switch;
	P33switch = state.u.P33switch;
}

typedef union {
	struct {
		unsigned SRHswitch1:1;
		unsigned SRHswitch2:1;
		unsigned FCswitch1:1;
		unsigned FCswitch2:1;
		unsigned FCswitch3:1;
		unsigned FCswitch4:1;
		unsigned FCswitch5:1;
		unsigned FCswitch6:1;
		unsigned P114switch:1;
		unsigned P115switch:1;
		unsigned P116switch:1;
		unsigned P117switch:1;
	} u;
	unsigned long word;
} CP4SwitchState;

int Saturn::GetCP4SwitchState()

{
	CP4SwitchState state;

	state.word = 0;
	state.u.FCswitch1 = FCswitch1;
	state.u.FCswitch2 = FCswitch2;
	state.u.FCswitch3 = FCswitch3;
	state.u.FCswitch4 = FCswitch4;
	state.u.FCswitch5 = FCswitch5;
	state.u.FCswitch6 = FCswitch6;

	return state.word;
}

void Saturn::SetCP4SwitchState(int s)

{
	CP4SwitchState state;

	state.word = s;
	FCswitch1 = state.u.FCswitch1;
	FCswitch2 = state.u.FCswitch2;
	FCswitch3 = state.u.FCswitch3;
	FCswitch4 = state.u.FCswitch4;
	FCswitch5 = state.u.FCswitch5;
	FCswitch6 = state.u.FCswitch6;
}

typedef union {
	struct {
		unsigned P328switch:1;
		unsigned P329switch:1;
	} u;
	unsigned long word;
} CP5SwitchState;

int Saturn::GetCP5SwitchState()

{
	CP5SwitchState state;

	state.word = 0;
	state.u.P328switch = P328switch;
	state.u.P329switch = P329switch;

	return state.word;
}

void Saturn::SetCP5SwitchState(int s)

{
	CP5SwitchState state;

	state.word = s;
	P328switch = state.u.P328switch;
	P329switch = state.u.P329switch;

}
