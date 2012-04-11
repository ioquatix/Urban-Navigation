//
//  UNMarker.m
//  Urban Navigation
//
//  Created by Samuel Williams on 10/04/12.
//  Copyright (c) 2012 Orion Transfer Ltd. All rights reserved.
//

#import "UNMarker.h"

@implementation UNMarker

@synthesize name = _name, description = _description, coordinate = _coordinate, image = _image;

- (NSString *)title {
	return self.name;
}

- (NSString *)subtitle {
	return self.description;
}

- (UIImage *)image {
	if (!_image) {
		NSString * imagePath = [[NSBundle mainBundle] pathForResource:self.name ofType:@"jpg" inDirectory:@"Markers"];
		
		self.image = [UIImage imageWithContentsOfFile:imagePath];
	}
	
	return _image;
}

@end
