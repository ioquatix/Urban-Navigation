//
//  UNRoundedBox.m
//  Urban Navigation
//
//  Created by Samuel Williams on 10/04/12.
//  Copyright (c) 2012 Samuel Williams. All rights reserved.
//

#import "UNRoundedBox.h"

@implementation UNRoundedBox

- (void)setupBoxView {
	[super setupBoxView];
	
	self.backgroundColor = [UIColor clearColor];
}

// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
	CGContextRef context = UIGraphicsGetCurrentContext();
	CGContextSaveGState(context);
	
	UIBezierPath * path = [UIBezierPath bezierPathWithRoundedRect:CGRectInset(self.bounds, 6.0, 6.0) cornerRadius:10];
	
	//CGContextAddPath(context, [path CGPath]);
	//CGContextClip(context);
	
	CGContextSetShadow(context, CGSizeMake(3.0, 3.0), 3.0);
	
	[self.backgroundFill setFill];
	//[[UIColor blackColor] setFill];
	[path fill];
	
	//CGContextAddPath(context, path.CGPath);
	//CGContextClip(context);
	
	//UIImage * background = [UIImage imageNamed:@"Background.jpg"];
	//[background drawAsPatternInRect:self.bounds];
	
	CGContextRestoreGState(context);
}

@end
