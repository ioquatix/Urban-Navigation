//
//  UNRoute.m
//  Urban Navigation
//
//  Created by Lab MIME on 12/4/12.
//  Copyright (c) 2012 Orion Transfer Ltd. All rights reserved.
//

#import "UNRoute.h"
#import "UNMarker.h"

#ifdef Q_MAP_ENGINE
#import "QMapEngine.h"
#import "Navigation.h"
const double Q_SCALE = 1000000.0;
#endif

#import "UNTurn.h"

@implementation UNRoute

@synthesize turns = _turns;

- (id)initWithCoder:(NSCoder *)aDecoder {
	self = [super init];
	
	if (self) {
		self.turns = [aDecoder decodeObjectForKey:@"turns"];
	}
	
	return self;
}

- (void)encodeWithCoder:(NSCoder *)coder {
	[coder encodeObject:self.turns forKey:@"turns"];
}

+ (UNRoute *)loadFromPath:(NSString*)path {
	NSDictionary * dictionary = [NSDictionary dictionaryWithContentsOfFile:path];

	return [dictionary objectForKey:@"route"];
}

- (void)saveToPath:(NSString*)path {
	NSDictionary * dictionary = [NSDictionary dictionaryWithObject:self forKey:@"route"];
	
	[dictionary writeToFile:path atomically:YES];
}

#ifdef Q_MAP_ENGINE
+ (QMapEngine *) sharedMapEngine {
	static QMapEngine * _sharedMapEngine = nil;
	
	if (_sharedMapEngine == nil) {
		_sharedMapEngine = [[QMapEngine alloc] init];
		_sharedMapEngine.nMode = 0;
		
	}
	
	return _sharedMapEngine;
}

+ (UNRoute *) bestRouteFrom:(CLLocationCoordinate2D)from to:(CLLocationCoordinate2D)to {
	QMapEngine * engine = [self sharedMapEngine];
	Navigation * navigation = [Navigation new];
	navigation.iMapEngine = engine;
	
	long avoid[1] = {0};
	CGPoint fromPoint, toPoint;
	fromPoint.x = from.longitude * Q_SCALE;
	fromPoint.y = from.latitude * Q_SCALE;
	toPoint.x = to.longitude * Q_SCALE;
	toPoint.y = to.latitude * Q_SCALE;
	
	[navigation findRouteFrom:fromPoint to:toPoint avoid:avoid option:Fastest reroute:NO startPtPrev:fromPoint];
		
	if ([navigation IsRouteAvailable]) {
		NSMutableArray * turns = [NSMutableArray array];
		
		for (TurnData * t in navigation.turnData) {
			CLLocationCoordinate2D at = {
				t.ptLocation.y / Q_SCALE,
				t.ptLocation.x / Q_SCALE
			};
			
			UNTurn * turn = [UNTurn new];
			turn.coordinate = at;
			turn.name = t.strNextRoadName1;
			
			[turns addObject:turn];
		}
		
		UNRoute * route = [UNRoute new];
		route.turns = turns;
		
		return route;
	}
	
	return nil;
}
#endif

- (NSString *)description {
	return [NSString stringWithFormat:@"<UNRoute turns=%@>", self.turns];
}

@end
