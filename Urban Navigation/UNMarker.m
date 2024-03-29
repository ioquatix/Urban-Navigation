//
//  UNMarker.m
//  Urban Navigation
//
//  Created by Samuel Williams on 10/04/12.
//  Copyright (c) 2012 Samuel Williams. All rights reserved.
//

#import "UNMarker.h"

@implementation UNMarker

@synthesize name = _name, description = _description, coordinate = _coordinate, image = _image, selectionColor = _selectionColor;

- (NSString *)title {
	return self.name;
}

- (NSString *)subtitle {
	return self.description;
}

- (UIImage *)image {
	if (!_image) {
		//NSString * imagePath = [[NSBundle mainBundle] pathForResource:self.name ofType:@"jpg" inDirectory:@"Markers"];
		
		self.image = [UIImage imageNamed:[NSString stringWithFormat:@"Markers/%@.jpg", self.name]];
	}
	
	return _image;
}

@end
