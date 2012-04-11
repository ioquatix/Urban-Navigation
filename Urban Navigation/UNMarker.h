//
//  UNMarker.h
//  Urban Navigation
//
//  Created by Samuel Williams on 10/04/12.
//  Copyright (c) 2012 Orion Transfer Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>

@interface UNMarker : NSObject <MKAnnotation>

@property(strong,nonatomic) NSString * name;
@property(strong,nonatomic) NSString * description;
@property(assign,nonatomic) CLLocationCoordinate2D coordinate;
@property(strong,nonatomic) UIImage * image;

- (NSString *)title;
- (NSString *)subtitle;

@end
