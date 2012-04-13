//
//  UNViewController.h
//  Urban Navigation
//
//  Created by Samuel Williams on 10/04/12.
//  Copyright (c) 2012 Samuel Williams. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>

#import "UNMarker.h"

@interface UNMapViewController : UIViewController <MKMapViewDelegate> {
	MKMapView * mapView;
	
	IBOutlet UIView * navigationView;
	IBOutlet UILabel * navigationNameLabel;
	IBOutlet UILabel * navigationDescriptionLabel;
	IBOutlet UIImageView * navigationImageView;
	
	IBOutlet UITextField * navigationStartField, * navigationEndField;
	
	IBOutlet UIView * locationView;
}

@property(nonatomic,retain) NSArray * markers;
@property(nonatomic,retain,readonly) UNMarker * currentlySelectedMarker;

@property(nonatomic,retain,readonly) UNMarker * startMarker;
@property(nonatomic,retain,readonly) UNMarker * endMarker;

- (IBAction)startHereButtonPressed:(id)sender;
- (IBAction)endHereButtonPressed:(id)sender;

- (IBAction)calculateRoute:(id)sender;

@end
