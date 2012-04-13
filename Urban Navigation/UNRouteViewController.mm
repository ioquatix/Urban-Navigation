//
//  UNRouteViewController.m
//  Urban Navigation
//
//  Created by Samuel Williams on 13/4/12.
//  Copyright (c) 2012 Samuel Williams. All rights reserved.
//

#import "UNRouteViewController.h"
#import "UNRoute.h"

#import "UNRouteController.h"
#import "ARABrowserViewController.h"

@implementation UNRouteViewController

@synthesize route = _route;

- (void)setRoute:(UNRoute *)route {
	[self willChangeValueForKey:@"route"];
	
	_route = route;
	
	[self didChangeValueForKey:@"route"];
	
	routeTableViewController.route = route;
}

- (void)viewDidLoad {
	routeTableViewController.route = self.route;
}

- (IBAction)startAugmentedReality:(id)sender {
	ARABrowserViewController * browserViewController = [[ARABrowserViewController new] autorelease];
	UNRouteController * routeController = [[UNRouteController new] autorelease];
	[routeController setRoute:self.route];
	
	browserViewController.pathController = routeController;
	
	self.view.window.rootViewController = browserViewController;
}

@end
