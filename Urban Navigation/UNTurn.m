//
//  UNTurn.m
//  Urban Navigation
//
//  Created by Samuel Williams on 12/4/12.
//  Copyright (c) 2012 Samuel Williams. All rights reserved.
//

#import "UNTurn.h"

@implementation UNTurn

@synthesize coordinate = _coordinate, name = _name;

- (id)initWithCoder:(NSCoder *)aDecoder {
	self = [super init];
	
	if (self) {
		_coordinate.latitude = [aDecoder decodeDoubleForKey:@"latitude"];
		_coordinate.longitude = [aDecoder decodeDoubleForKey:@"longitude"];
		self.name = [aDecoder decodeObjectForKey:@"name"];
	}
	
	return self;
}

- (void)encodeWithCoder:(NSCoder *)coder {
	[coder encodeDouble:_coordinate.latitude forKey:@"latitude"];
	[coder encodeDouble:_coordinate.longitude forKey:@"longitude"];
	[coder encodeObject:self.name forKey:@"name"];
}

- (NSString *)description {
	return [NSString stringWithFormat:@"<UNTurn latitude=%0.6f longitude=%0.6f %@>", _coordinate.latitude, _coordinate.longitude, self.name];
}

@end
