//
//  Navigation.h
//  NavFone
//
//  Created by agis on 2/2/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#define PLAYER_TYPE_PREF_KEY @"player_type_preference"
#define AUDIO_TYPE_PREF_KEY @"audio_technology_preference"

#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayer.h>
#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>

//#import "StructureOther.h"

//#import "RoutingEngine.h"
@class NavFoneQuartzView;
//@class SearchOption;

@interface TurnData:NSObject
{
	int nType;					//e.g. turn left == 1
	CGPoint ptLocation;			//location of turning point
	int nLinkPrev;				//
	int nLinkAfter;
	NSString* strNextRoadName1;	//road name after turning
	int nDistRemaining;			//distance remaining 
}
@property (nonatomic,readwrite) int nDistRemaining;
@property (nonatomic,readwrite) int nType;
@property (nonatomic,readwrite) int nLinkPrev;
@property (nonatomic,readwrite) int nLinkAfter;
@property (nonatomic,readwrite) CGPoint ptLocation;
@property (nonatomic,retain)	NSString* strNextRoadName1;

@end;

@class RouteEngine;
@class QMapEngine;
@interface Navigation : NSObject {
	//reference

	QMapEngine *iMapEngine;
	RouteEngine *iRoutingEngine;
	
	//turn data
	double turnDataSign;
	NSMutableArray*  turnData;
	NSMutableArray*  ptSimulation;
	
	//layout
	CGRect rcClient;
	CGRect rcNextRoadName;
	CGRect rcDistToJunc;
	CGRect rcDistToDest;
	//end layout
	
	//data for tracing
	NSString* strNextRoadName; //display name of the next road after junction on the screen
	int nDistToJunc; //used to display distance to junction on the screen
	int nPrevDistToJunc; //used to prevent double prompting when near junction because the distance can be variation in here, prevent to go backward
	int nCurrentIndex; //current index of the road in turndata
	int nPrevIndex; //previous index
	int currentJuncImage;
	int nDistRemaining;
	CGPoint ptSnapped, ptSnappedPrev; //snapped point as result of snapping to the route
	bool bSnapped; //boolean to tell if snapping is successfull
	
	UIFont* fontNextRoadName;
	UIFont* fontNextRoadNameAlter;
	UIFont* fontDistToJunc;
	UIFont* fontDistToJuncUnit;
	
	//link to draw turn arrow
	int linkPrev;
	int linkNext;

	//route
	bool isrerouting;			//when reroute unsuccessful, this var is true
	BOOL isReroute;				//when reroute is successful this var is true
	bool inReroutingProcess;	//when calculation route, this variable is true. until it is successful or failed
	bool donePlayVoice;
	bool bRouteAndGPSDifferentAngle;
	int angleRoute;
	//erp 
	UIAlertView* alert;
	NSTimer* alertTimer;
	NSString* strErp;
	//lgi
	NSString* strLGI;
	int nSimulationIndex;
	
	CGPoint pointPrev;
	AVAudioPlayer* audioPlayer;
	NSURL* audioUrl;
	//to prevent gps hang for long distance route
	BOOL mbGpsIsOnBeforeRouting;
	bool bSnap;
	BOOL bSimulate;
	int iStartLinkID, iEndLinkID;
	CGPoint iEndPt, iStartPt;
}



//ref
@property BOOL bSimulate;
@property (nonatomic, assign) QMapEngine* iMapEngine;
@property (retain) RouteEngine* iRoutingEngine;

//layout
@property (nonatomic,readwrite) CGRect rcClient;
@property (nonatomic,readwrite) CGRect rcNextRoadName;
@property (nonatomic,readwrite) CGRect rcDistToJunc;
@property (nonatomic,readwrite) CGRect rcDistToDest;
@property (readwrite) bool bSnap,bRouteAndGPSDifferentAngle;

@property (nonatomic,readwrite) CGPoint ptSnapped,pointPrev;
@property (nonatomic,readwrite) bool bSnapped;
@property (nonatomic,readwrite) bool isrerouting,inReroutingProcess;

//data for tracing
@property (nonatomic,readwrite) int nPrevDistToJunc, nDistToJunc, nCurrentIndex;//,nPrevIndex;
@property (nonatomic, retain) NSString* strNextRoadName;
@property (nonatomic, retain) NSString* strLGI;
@property (nonatomic, retain) AVAudioPlayer* audioPlayer;
@property (nonatomic, retain) NSURL* audioUrl;
//link to draw turn arrow
@property (nonatomic,readwrite) int linkPrev, linkNext, currentJuncImage,angleRoute, nSimulationIndex;

@property (nonatomic, retain) NSMutableArray* ptSimulation;
@property (nonatomic, retain) NSMutableArray* turnData;
 
- (void) DrawThaiString:(NSString*)strOri drawInRect:(CGRect)rc1 withFont:(UIFont*) font  lineBreakMode:(UILineBreakMode)UILine 
			  alignment:(UITextAlignment)UITextAlign;
- (void) initLayout:(CGRect)a;
- (bool) draw:(UIFont*) font center:(CGPoint) pos angle:(int)angle speed:(int)speed;
- (bool) drawL2:(UIFont*) font center:(CGPoint) pos angle:(int)angle speed:(int)speed;
- (void) getNextRoadName:(int) nIndex ;
- (int) getDistToJunc:(int) nIndex  ptGPS:(CGPoint) ptGPS ;
- (bool) updateData:(int) nIndex linkID:(int) linkID point:(CGPoint) point pointPrev:(CGPoint) pointPrev speed:(double) speed angle:(int) angle;

- (double) Distance:(CGPoint) ptLoc1 ptLoc2:(CGPoint) ptLoc2;
- (CGPoint) PointOfIntersect: (const CGPoint) pt1 pt2:(const CGPoint) pt2 pt3:( const CGPoint) pt3;
-(int) VertexBearing:(const CGPoint) pPoint1 pt2:(const CGPoint) pPoint2;

- (bool) SnapOnPoint:(CGPoint) pPt1 pPt2:(CGPoint) pPt2 pPt3:(CGPoint)pPt3 pGPSPt:(CGPoint) pGPSPt
		   pSnapOnPt:(CGPoint*) pSnapOnPt nSpeed:(int)nSpeed bPointAhead:(bool)bPointAhead;

- (void) updateTurnData;

- (int) getResultIndexHelp:(int) linkID startIndex:(int)startIndex;
- (bool) snapToLinkHelp:(int)i pGPSPt:(CGPoint)point indexResult:(int*)indexResult linkResult:(int*)linkResult ptResult:(CGPoint*) ptResult speed:(int)speed angle:(int)angle;
- (double) Distance:(NSData *) pointData;

- (void) playVoiceFile:(NSString*) str;
- (void) PlayVoiceDistance:(int) nIndex nDist:(int)nDist;

- (void) drawIcon:(CGContextRef) context fileName:(NSString*) fileName atRect:(CGRect) atRect;
- (int) findRouteFrom:(CGPoint)startPt to:(CGPoint)endPt avoid:(long*)aAvoidPtr option:(int)aOption reroute:(bool) bReroute startPtPrev:(CGPoint)startPtPrev;
- (bool) clearRoute;
-(void) SaveLastPoint:(CGPoint) pt;
-(bool)IsRouteAvailable;
-(void)DrawTurnArrow:(QMapEngine*)aMapEngine inContext:(const CGContextRef)aContext;
-(void)DrawRouteLine:(QMapEngine*)aMapEngine inContext:(const CGContextRef)aContext atScale:(int)scale;

- (void) onTimer:(NSTimer*)theTimer;
- (float) ErpDisplay:(int) nIndex;

- (void) RegisterDoublePrompt;
- (int) SetDoublePromptFlag:(int) nCurrentTurn nNexTurn:(int) nNextTurn;
- (void) Rerouting:(NSTimer*) timer;
- (void) PreRerouting:(NSTimer*) timer;
- (void) crash1;
- (void) crash2;
- (void) crash3;
@end
