//
//  QMapEngine.h
//  NavFone
//
//  Created by User on 12/11/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//
#import <UIKit/UIKit.h>
//#import "StructureOther.h"

#define Layer_Zoo				91
#define Layer_Sentosa			92
#define Layer_Orchid_Gerden		93
#define Layer_Merlion			94
#define Layer_Chinese_Garden	95
#define Layer_Changi_Airport	96
#define Layer_Bird_Park			97

#define OFFSETVALUE 3000

typedef enum MapLanguage{
	English = 0,
	Thai
} MapLanguage;

typedef struct RGBAColor_tag {
	u_int R;
	u_int G;
	u_int B;
	u_int A;
} RGBAColor;

enum SearchOption {
	Shortest,
	Fastest,
};

@class TransportResult;
@class TransportRouting;
@class Polygon;
@class Polyline;
@class MapPoint;
@class ServiceData;
//@class RotatedRectangle;
@interface QMapEngine : NSObject 

@property (retain) 	NSMutableArray* arraystrSelectedCategory;
@property (retain) id AGDescDelegate;
@property (retain) UIView* viewToDraw;
@property int nSelCustomizedItem;
@property (retain) 	NSMutableArray* arrayCustomizedItem;
@property BOOL bLoadAllFromFile;
@property(retain) NSData* entireFile;
@property(retain) NSArray* mapFilesArray;
@property(retain) NSArray* tileSizeArray;
@property(retain) NSArray* zoomLevelArray;
@property CGRect rcMapBoundary;
@property CGPoint ptMapCenter;
@property (nonatomic, readwrite, setter = setZoomLevel:) double currentZoomLevel;
@property (nonatomic, retain) 	NSMutableArray *hitObjects;
@property (nonatomic, readwrite) CGRect actualWorldRect;
@property (nonatomic, readwrite) MapLanguage mLanguage;
@property (nonatomic, readwrite) BOOL mb3D;
@property int nMode;


-(void) loadConfigFile:(NSString*) fileNameInput;

-(int)getMinimumZoomLevel;
-(int)getMaximumZoomLevel;

-(void) drawScaleAtPoint:(CGPoint)pos inContext:(CGContextRef const)aContext;
-(void) drawCompassAtPoint:(const CGPoint)pos inContext:(CGContextRef const)aContext;
-(void) drawLogoAtPoint:(const CGPoint)pos inContext:(CGContextRef const)aContext;
-(void) drawIcon:(const NSString*)iconName atPoint:(const CGPoint)pt withSize:(const u_int)size;
-(void) drawIcon:(NSString* const)iconName atPoint:(const CGPoint)pt withSize:(const u_int)size withRotation:(const int)rotation;
//-(void)drawIcon:(NSString*)iconName atPoint:(CGPoint)pt withSize:(u_int)size inContext:(CGContextRef)aContext;


-(void) setRectangleToDraw:(const CGRect) aRect;
-(int) homeFitInRect:(const CGRect)aScreenRect drawInRect:(const CGRect)aCanvasRect;
-(int) OnFirstLoadMap:(const CGRect)aScreenRect drawInRect:(const CGRect)aCanvasRect;


-(int) reinitializeMap;
//-(void) canvasSizeChangeToRect:(const CGRect)aRect ;
-(void) drawMapInContext:(const CGContextRef)aContext;

-(void) zoomToCenterWithZoomLevel:(const double)zoomLevel isZoomIn:(BOOL)isZoomIn;
-(void) mapPanFromPoint1:(const CGPoint)screenPt1 toPoint2:(const CGPoint)screenPt2;
-(CGPoint) getMapPoint:(CGPoint)screenPt;
-(CGPoint)getScreenPoint:(CGPoint)mapPt;
-(void)jumpToMapPoint:(const CGPoint)pt withZoomLevel:(const u_int)zoomLevel;
-(void)jumpToMapPoint:(const CGPoint)pt withZoomLevel:(const u_int)zoomLevel showAtScreenPoint:(const CGPoint)atPoint;
-(void)jumpToMapPoint:(const CGPoint)pt;


-(BOOL) hitTest:(const CGPoint)mapPoint;
-(void)drawHotItems:(const int)index inContext:(CGContextRef const)aContext bounds:(const CGRect)aRect;
-(void)drawHotItems:(const int)index withColor:(const RGBAColor)color inContext:(CGContextRef const)aContext bounds:(const CGRect)aRect;
-(NSString*) getHotItemName:(const int)index;

-(BOOL)saveCurrentState;
-(BOOL)loadPreviousState;
-(void)addTracelinesFromTransportRoute:(const TransportResult* const)result fromEngine:(const TransportRouting* const)iTransportEngine;

-(void)drawTransportRoute;
-(float) getScreenRadius:(double) earthRadiusInMeter fromPosition:(CGPoint)latLong;
-(CGPoint) getCurrentMapCenter;

-(void) drawBookmarkText:(NSString* const)name atPoint:(CGPoint)pt withSize:(const CGSize)aSize fontSize:(const int)fSize withOutline:(BOOL)outline;
-(double) calculateZoomScaleForMapRect:(CGRect)aMapRect withScreen:(CGRect)aScreenRect;
-(void) freeResources ;
-(void) prepareTextAttributeWithFontSize:(u_int)FontSize withColor:(RGBAColor)aColor;
//-(void) drawMapInbounds:(const CGRect)aRect;
-(void) drawService:(TransportRouting*) iTransportEngine forServiceID:(u_int)srvID;
-(void) drawService:(TransportRouting*) iTransportEngine forServiceData:(ServiceData*) srvData;
-(void) drawOppStn:(TransportRouting*) iTransportEngine forStnID:(u_int)stnID;
-(void) zoomIn;
-(void) zoomOut;
-(int) calcuLateZoomStepDifferentFrom:(double)initialLevel to:(double)finalLevel;
-(int) calcuLateZoomStepDifferentFromCurrentToZoomLevel:(double)finalLevel ;



-(float) setLineWidthForRoadType:(const u_int)type;
-(void)rotateMapInDegree:(const float)degree;

-(void) loadMapColor:(NSString*)strFileName ofType:(NSString*) type;//Default.color
-(RGBAColor) getHardcodeColorForType:(u_int)aType;
-(RGBAColor) getRGB:(NSString*)strFileContent forKey:(NSString*)strkey;

//customized items API
//1. Adding of objects(pt, polygons, lines)
//2. Removal of 1 object
//3. Removal of all objects
//4. Select a user created object
//5. Clear object selection
- (BOOL) addCustomizedItem:(id) objItem;
- (id)	getCustomizedItemAtIndex:(int) nIndex;
- (BOOL) deleteCustomizedItemAtIndex:(int) nIndex;
- (void) deleteCustomizedItemWithCategory:(NSString*) strCategory;
- (void) deleteAllCustomizedItem;
- (void) selectCustomizedItemAtLanLat:(CGPoint) ptLonLat toDisplayDescIn:(UIView*) view withDelegate:(id) delegate;
- (void) deselectCustomizedItem;
- (void) selectCategoriesToBeDraw:(NSMutableArray*) arraystrCategories;//pass nil mean draw all

//helper, dont use
- (double) distanceTwoPoint:(CGPoint) pointToCalculate to:(CGPoint) pointRef;
- (void) generateSampleItems;
- (void) drawAllCustomizedItem;
- (void) drawSelectedCustomizedItem;
@end

//-(CGSize) measureTextSize:(NSString*)name;
