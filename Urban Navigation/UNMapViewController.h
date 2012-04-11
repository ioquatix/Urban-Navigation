//
//  UNViewController.h
//  Urban Navigation
//
//  Created by Samuel Williams on 10/04/12.
//  Copyright (c) 2012 Orion Transfer Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>

@interface UNMapViewController : UIViewController <MKMapViewDelegate> {
	MKMapView * mapView;
	
	IBOutlet UIView * navigationView;
	IBOutlet UILabel * navigationNameLabel;
	IBOutlet UILabel * navigationDescriptionLabel;
	IBOutlet UIImageView * navigationImageView;
	
	IBOutlet UIView * locationView;
}

@property(nonatomic,retain) NSArray * markers;

@end
