#pragma once

#include "ofMain.h"
#include "MathHelpers.h"

class Particle
{
	public:
	
		// ---------------------------------------------------------------
		Particle( ofVec2f _startPoint, ofVec2f _endPoint,
				  float _startTime, float _animationLength,
				  ofFloatColor _color )
		{
			startPoint		= _startPoint;
			endPoint		= _endPoint;
			
			startTime		= _startTime;
			animationLength = _animationLength;
			
			color			= _color;
			
			animationFraction = 0.0f;
			
			cout << "New Particle " << startPoint << " " << endPoint << " " << startTime << " " << animationLength << endl;
			
			deleteMe 		= false;
		}
	
		// ---------------------------------------------------------------
		void update( float _currTime )
		{
			animationFraction = (_currTime - startTime) / animationLength;

			if( animationFraction > 1.0f )
			{
				// mark for deletion
				deleteMe = true;
			}
			
			//timeFrac = ofClamp( timeFrac, 0.0f, 1.0f );
			
			currPos = startPoint.interpolated( endPoint, animationFraction );
		}
	
		// ---------------------------------------------------------------
		void draw()
		{
			if( animationFraction >= 0.0f && animationFraction <= 1.0f )
			{
				color.a = MathHelpers::smoothStepInOut( animationFraction, 0.0f, 0.1f, 0.9f, 1.0f); // fade the particle in and out depending on the time fraction
				ofSetColor( color );
				
				ofDrawCircle( currPos, 30 );
				
				ofDrawCircle( startPoint, 3 );
				ofDrawCircle( endPoint, 3 );				
				ofDrawLine( startPoint, endPoint );
			}
		}
	
		ofVec2f currPos;
	
		ofVec2f startPoint;
		ofVec2f endPoint;
		
		float animationFraction;
	
		float startTime;
		float animationLength;
		
		ofFloatColor color;
	
		bool	deleteMe;
};
