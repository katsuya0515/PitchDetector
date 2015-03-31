#pragma once

#include "ofMain.h"
#include "fft.h"
#include "aubioAnalyzer.h"

#define BUFFER_SIZE 256
#define NUM_WINDOWS 80
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    void audioReceived 	(float * input, int bufferSize, int nChannels);
    int maximumValue(float *array, int length);
    
    ofSoundStream soundStream;
    
    string getPitchSound(int pitch);// Not developed. Work in Progress 2015/03/31


    float * left;
    float * right;
    int 	bufferCounter;
    fft		myfft;
    
    float magnitude[BUFFER_SIZE];
    float phase[BUFFER_SIZE];
    float power[BUFFER_SIZE];
    vector <float> volHistory1;
    vector <float> volHistory2;
    
    float scaled1;
    float scaled2;
    
    float freq[NUM_WINDOWS][BUFFER_SIZE/2];
    float freq_phase[NUM_WINDOWS][BUFFER_SIZE/2];

    aubioAnalyzer AA1;
    aubioAnalyzer AA2;
    
    
    ofTrueTypeFont smallFont;
    ofTrueTypeFont midFont;
    ofTrueTypeFont largeFont;
    
    ofFile file;
    int startTime;
    int elapsedTime;

};
