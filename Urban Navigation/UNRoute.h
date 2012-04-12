//
//  UNRoute.h
//  Urban Navigation
//
//  Created by Lab MIME on 12/4/12.
//  Copyright (c) 2012 Orion Transfer Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@interface UNRoute : NSObject

@property(nonatomic,retain) NSArray * turns;

- (id)initWithCoder:(NSCoder *)aDecoder;
- (void)encodeWithCoder:(NSCoder *)coder;

+ (UNRoute *)loadFromPath:(NSString*)path;
- (void)saveToPath:(NSString*)path;

#ifdef Q_MAP_ENGINE
/// If the map engine has been provided and compiled into the application, this function will calculate a route between two points. If there was a problem, nil is returned.
+ (UNRoute *) bestRouteFrom:(CLLocationCoordinate2D)from to:(CLLocationCoordinate2D)to;
#endif

@end
