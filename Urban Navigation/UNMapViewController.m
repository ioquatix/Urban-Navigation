//
//  UNViewController.m
//  Urban Navigation
//
//  Created by Samuel Williams on 10/04/12.
//  Copyright (c) 2012 Samuel Williams. All rights reserved.
//

#import "UNMapViewController.h"
#import "UNTexturedBox.h"
#import "UNRoute.h"

#import "UNRouteViewController.h"

@interface UNMapViewController ()
@property(nonatomic,retain,readwrite) UNMarker * currentlySelectedMarker;
@property(nonatomic,retain,readwrite) UNMarker * startMarker;
@property(nonatomic,retain,readwrite) UNMarker * endMarker;

@property(nonatomic,retain) MKPolyline * currentRoutePolyline;
@end

@implementation UNMapViewController

@synthesize markers = _markers, currentlySelectedMarker = _currentlySelectedMarker;
@synthesize startMarker = _startMarker, endMarker = _endMarker;
@synthesize currentRoutePolyline = _currentRoutePolyline;

- (void)loadMarkersFromPath:(NSString*)path {
	NSDictionary * records = [NSDictionary dictionaryWithContentsOfFile:path];
	NSMutableArray * markers = [NSMutableArray array];
	
	for (NSDictionary * markerRecord in [records objectForKey:@"Markers"]) {
		UNMarker * marker = [[UNMarker new] autorelease];
		
		CLLocationCoordinate2D coordinate;
		coordinate.latitude = [[markerRecord objectForKey:@"Latitude"] doubleValue];
		coordinate.longitude = [[markerRecord objectForKey:@"Longitude"] doubleValue];
		
		marker.coordinate = coordinate;
		marker.name = [markerRecord objectForKey:@"Name"];
		marker.description = [markerRecord objectForKey:@"Description"];
		
		[markers addObject:marker];
	}
	
	self.markers = markers;
}

- init {
	self = [super initWithNibName:@"UNMapView" bundle:[NSBundle mainBundle]];
	
	if (self) {
		NSString * markersPath = [[NSBundle mainBundle] pathForResource:@"Markers" ofType:@"plist"];
		
		[self loadMarkersFromPath:markersPath];
	}
	
	return self;
}

- (void)setMarkers:(NSArray *)markers {
	[self willChangeValueForKey:@"markers"];
	
	if (mapView) {
		if (_markers) {
			[mapView removeAnnotations:_markers];
		}
		
		if (markers) {
			[mapView addAnnotations:markers];
		}
	}
	
	[_markers autorelease];
	[markers retain];
	
	_markers = markers;
	
	[self didChangeValueForKey:@"markers"];
}

- (void) focusOnSingapore {
	MKCoordinateRegion region = { {0.0, 0.0 }, { 0.0, 0.0 } }; 
	region.center.latitude = 1.3667; 
	region.center.longitude = 103.8;
	region.span.longitudeDelta = 0.25f;
	region.span.latitudeDelta = 0.25f;
	[mapView setRegion:region animated:YES];     
	[mapView regionThatFits:region];
}

- (void)loadView {
	[super loadView];
	
	CGRect frame = {0, 0, 320, 460};
	mapView = [[MKMapView alloc] initWithFrame:frame];
	[mapView addAnnotations:self.markers];
	[mapView setDelegate:self];
	
	//navigationView = [[UNTexturedBox alloc] initWithFrame:CGRectMake(10, 10, 330, 100)];
	navigationView.frame = CGRectMake(10, 10, 330, 100);
	[mapView addSubview:navigationView];
	[self focusOnSingapore];
	
	[mapView setShowsUserLocation:YES];
	
	UILongPressGestureRecognizer * dropPinGesture = [[[UILongPressGestureRecognizer alloc] initWithTarget:self action:@selector(handleDropPinGesture:)] autorelease];
	dropPinGesture.minimumPressDuration = 2.0; //user needs to press for 2 seconds
	[mapView addGestureRecognizer:dropPinGesture];
	
	CGRect locationViewFrame = locationView.frame;
	locationViewFrame.origin.x = 0;
	locationViewFrame.origin.y = frame.size.height;
	locationView.frame = locationViewFrame;
	[mapView addSubview:locationView];
	
	[self.view addSubview:mapView];
}

- (void)handleDropPinGesture:(UIGestureRecognizer *)gestureRecognizer {
    if (gestureRecognizer.state != UIGestureRecognizerStateBegan)
        return;
	
    CGPoint touchPoint = [gestureRecognizer locationInView:mapView];   
    CLLocationCoordinate2D coordinate = [mapView convertPoint:touchPoint toCoordinateFromView:mapView];	
	
	UNMarker * marker = [[UNMarker new] autorelease];
	
	marker.coordinate = coordinate;
	marker.name = [NSString stringWithFormat:@"Generic Marker: %0.3f, %0.3f", coordinate.latitude, coordinate.longitude];

	// Add a marker to the list of markers:
	NSMutableArray * markers = [[self.markers mutableCopy] autorelease];
	[markers addObject:marker];
	
	self.markers = markers;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
	if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
	    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
	} else {
	    return YES;
	}
}

- (void)mapView:(MKMapView *)mapView didSelectAnnotationView:(MKAnnotationView *)view {
	if (![view.annotation isKindOfClass:[UNMarker class]]) return;
	
	UNMarker * marker = (UNMarker *)view.annotation;
	
	navigationNameLabel.text = marker.title;
	navigationDescriptionLabel.text = marker.subtitle;
	navigationImageView.image = marker.image;
	
	self.currentlySelectedMarker = marker;
	
	CGRect locationViewFrame = locationView.frame;
	locationViewFrame.origin.x = 0;
	locationViewFrame.origin.y =locationView.superview.frame.size.height - locationViewFrame.size.height;
	
	[UIView animateWithDuration:0.5 animations:^{
		locationView.frame = locationViewFrame;
	}];
}

- (void)hideLocationView {
	CGRect locationViewFrame = locationView.frame;
	locationViewFrame.origin.x = 0;
	locationViewFrame.origin.y = locationView.superview.frame.size.height;
	
	self.currentlySelectedMarker = nil;
	
	[UIView animateWithDuration:0.5 animations:^{
		locationView.frame = locationViewFrame;
	}];
}

- (void)mapView:(MKMapView *)mapView didDeselectAnnotationView:(MKAnnotationView *)view {

}

- (MKOverlayView *)mapView:(MKMapView *)mapView viewForOverlay:(id)overlay {
	if (overlay == self.currentRoutePolyline) {
		MKPolylineView * routeView = [[[MKPolylineView alloc] initWithPolyline:self.currentRoutePolyline] autorelease];
		
		routeView.fillColor = [UIColor redColor];
		routeView.strokeColor = [UIColor redColor];
		routeView.lineWidth = 3;
					
		return routeView;
	}
	
	return nil;
}

- (void)startHereButtonPressed:(id)sender {
	self.startMarker = self.currentlySelectedMarker;
}

- (void)endHereButtonPressed:(id)sender {
	self.endMarker = self.currentlySelectedMarker;
}

- (void)updateRouteOverlay {
	UNRoute * route = [UNRoute bestRouteFrom:self.startMarker.coordinate to:self.endMarker.coordinate];
	
	if (route) {
		if (self.currentRoutePolyline) {
			[mapView removeOverlay:self.currentRoutePolyline];
		}
		
		self.currentRoutePolyline = [route polylineValue];
		
		[mapView addOverlay:self.currentRoutePolyline];
	}
}

- (void)setStartMarker:(UNMarker *)startMarker {
	[self willChangeValueForKey:@"startMarker"];
	
	navigationStartField.text = startMarker.title;
	
	_startMarker = startMarker;
	
	[self didChangeValueForKey:@"startMarker"];

	[self updateRouteOverlay];
}

- (void)setEndMarker:(UNMarker *)endMarker {
	[self willChangeValueForKey:@"endMarker"];
	
	navigationEndField.text = endMarker.title;
	
	_endMarker = endMarker;
	
	[self didChangeValueForKey:@"endMarker"];
	
	[self updateRouteOverlay];
}

- (void)calculateRoute:(id)sender {
	UNRoute * route = [UNRoute bestRouteFrom:self.startMarker.coordinate to:self.endMarker.coordinate];
	
	if (route) {
		NSLog(@"Route: %@", route);
		
		UNRouteViewController * routeViewController = [[UNRouteViewController new] autorelease];
		routeViewController.route = route;
		
		 self.view.window.rootViewController = routeViewController;
	} else {
		NSLog(@"No route found!");
	}
}

@end
