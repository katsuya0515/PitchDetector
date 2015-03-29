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
    
    string getPitchSound(int pitch);


    float * left;
    float * right;
    int 	bufferCounter;
    fft		myfft;
    
    float magnitude[BUFFER_SIZE];
    float phase[BUFFER_SIZE];
    float power[BUFFER_SIZE];
    vector <float> volHistory;
    float scaled;
    
    float freq[NUM_WINDOWS][BUFFER_SIZE/2];

    float freq_phase[NUM_WINDOWS][BUFFER_SIZE/2];

    aubioAnalyzer AA;
    ofTrueTypeFont dinFont;
    ofTrueTypeFont deviceFont;
    ofTrueTypeFont titleFont;
    
    ofFile file;

};
