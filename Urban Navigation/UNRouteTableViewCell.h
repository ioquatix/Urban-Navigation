//
//  UNTurnTableViewCell.h
//  Urban Navigation
//
//  Created by Samuel Williams on 13/4/12.
//  Copyright (c) 2012 Samuel Williams. All rights reserved.
//

#import <UIKit/UIKit.h>

@class UNStep;

@interface UNRouteTableViewCell : UITableViewCell

@property(nonatomic,retain) UNStep * turn;

@end
