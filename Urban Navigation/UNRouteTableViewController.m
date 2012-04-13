//
//  UNRouteTableViewDataSource.m
//  Urban Navigation
//
//  Created by Samuel Williams on 13/4/12.
//  Copyright (c) 2012 Samuel Williams. All rights reserved.
//

#import "UNRouteTableViewController.h"

#import "UNRouteTableViewCell.h"
#import "UNRoute.h"

@implementation UNRouteTableViewController

@synthesize route = _route;

- (void)setRoute:(UNRoute *)route {
	[self willChangeValueForKey:@"route"];
	
	[_route autorelease];
	[route retain];
	
	_route = route;
	
	[self didChangeValueForKey:@"route"];
	
	NSLog(@"Reload table data");
	[self.tableView reloadData];
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
	return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	if (section == 0) {
		return [self.route.steps count];
	}
	
	return 0;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
	static NSString * CellIdentifier = @"UNTurnTableViewCell";
	
    UNRouteTableViewCell * cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];

	if (cell == nil) {
		cell = [[UNRouteTableViewCell new] autorelease];
	}
	
	cell.turn = [self.route.steps objectAtIndex:indexPath.row];
	
    return cell;
}


@end
