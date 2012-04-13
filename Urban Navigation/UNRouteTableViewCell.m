//
//  UNTurnTableViewCell.m
//  Urban Navigation
//
//  Created by Samuel Williams on 13/4/12.
//  Copyright (c) 2012 Samuel Williams. All rights reserved.
//

#import "UNRouteTableViewCell.h"
#import "UNStep.h"

@implementation UNRouteTableViewCell

- (id)init
{
    self = [super initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:@"UNTurnTableViewCell"];
    if (self) {
        
    }
    return self;
}

@synthesize turn = _turn;

- (void)setTurn:(UNStep *)turn {
	[self willChangeValueForKey:@"turn"];
		
	_turn = turn;
	
	[self didChangeValueForKey:@"turn"];
	
	self.textLabel.text = turn.name;
	self.detailTextLabel.text = turn.action;
}

@end
