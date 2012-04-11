//
//  UNTexturedBox.m
//  Urban Navigation
//
//  Created by Samuel Williams on 10/04/12.
//  Copyright (c) 2012 Orion Transfer Ltd. All rights reserved.
//

#import "UNTexturedBox.h"

#import <QuartzCore/QuartzCore.h>

@implementation UNTexturedBox

@synthesize backgroundFill = _backgroundFill;

- (void)setupBoxView {
	self.opaque = NO;
	self.backgroundFill = [UIColor colorWithPatternImage:[UIImage imageNamed:@"Background.jpg"]];
	self.backgroundColor = self.backgroundFill;
}

- (id)initWithFrame:(CGRect)frame {
	self = [super initWithFrame:frame];
	
	if (self) {
		[self setupBoxView];
	}
	
	return self;
}

- (id) initWithCoder:(NSCoder *)aDecoder {
	self = [super initWithCoder:aDecoder];
	
	if (self) {
		[self setupBoxView];
	}
	
	return self;
}

@end
