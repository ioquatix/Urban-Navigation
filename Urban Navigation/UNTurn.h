//
//  UNTurn.h
//  Urban Navigation
//
//  Created by Samuel Williams on 12/4/12.
//  Copyright (c) 2012 Samuel Williams. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@interface UNTurn : NSObject

@property(nonatomic,assign) CLLocationCoordinate2D coordinate;
@property(nonatomic,retain) NSString * name;

- initWithCoder:(NSCoder *)aDecoder;
- (void)encodeWithCoder:(NSCoder *)coder;

@end
