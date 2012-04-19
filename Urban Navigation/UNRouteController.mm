//
//  UNRouteController.m
//  Urban Navigation
//
//  Created by Lab MIME on 13/4/12.
//  Copyright (c) 2012 Samuel Williams. All rights reserved.
//

#import "UNRouteController.h"
#import "UNRoute.h"
#import "UNStep.h"

@implementation UNRouteController

- (void)setRoute:(UNRoute *)route {
	NSMutableArray * points = [NSMutableArray arrayWithCapacity:route.steps.count];
	
	for (UNStep * step in route.steps) {
		ARWorldPoint * point = [[ARWorldPoint new] autorelease];
		[point setCoordinate:step.coordinate altitude:EARTH_RADIUS];
		
		point.model = self.markerModel;
		
		[points addObject:point];
	}
	
	ARAPath * path = [[[ARAPath alloc] initWithPoints:points] autorelease];
	
	self.path = path;
}

@end
