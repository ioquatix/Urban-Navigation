//
//  UNTurn.h
//  Urban Navigation
//
//  Created by Samuel Williams on 12/4/12.
//  Copyright (c) 2012 Samuel Williams. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@interface UNStep : NSObject

@property(nonatomic,assign) CLLocationCoordinate2D coordinate;
@property(nonatomic,retain) NSString * name;
@property(nonatomic,retain) NSString * action;
@property(nonatomic,assign) CGFloat distance;

@property(nonatomic,assign) BOOL intermediate;

- initWithCoder:(NSCoder *)aDecoder;
- (void)encodeWithCoder:(NSCoder *)coder;

@end
