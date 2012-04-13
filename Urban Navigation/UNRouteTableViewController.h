//
//  UNRouteTableViewDataSource.h
//  Urban Navigation
//
//  Created by Samuel Williams on 13/4/12.
//  Copyright (c) 2012 Samuel Williams. All rights reserved.
//

#import <Foundation/Foundation.h>

@class UNRoute;

@interface UNRouteTableViewController : UITableViewController

@property(nonatomic,retain) UNRoute * route;

@end
