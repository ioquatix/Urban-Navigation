//
//  UNRouteViewController.h
//  Urban Navigation
//
//  Created by Samuel Williams on 13/4/12.
//  Copyright (c) 2012 Samuel Williams. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "UNRouteTableViewController.h"

@class UNRoute;

@interface UNRouteViewController : UIViewController <UITableViewDelegate> {
	IBOutlet UNRouteTableViewController * routeTableViewController;
}

@property(nonatomic,retain) UNRoute * route;

- (IBAction)startAugmentedReality:(id)sender;

@end
