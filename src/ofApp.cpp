#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    srand((unsigned int)time((time_t *)NULL));
    
    // 0 output channels,
    // 2 input channels
    // 44100 samples per second
    // BUFFER_SIZE samples per buffer
    // 4 num buffers (latency)
     smallFont.loadFont("DIN.otf", 10);
     midFont.loadFont("DIN.otf", 20);
     largeFont.loadFont("DIN.otf", 30);
    
     AA1.setup();
     AA2.setup();

    soundStream.listDevices();
    soundStream.setup(this, 0, 2, 44100, BUFFER_SIZE, 4);
    
    left = new float[BUFFER_SIZE];
    right = new float[BUFFER_SIZE];
    
    for (int i = 0; i < NUM_WINDOWS; i++)
    {
        for (int j = 0; j < BUFFER_SIZE/2; j++)
        {
            freq[i][j] = 0;	
        }
    }
    
    ofSetColor(0x666666);
    volHistory1.assign(400, 0.0);
    volHistory2.assign(400, 0.0);
 
    
    file.open("filename.txt",ofFile::WriteOnly);
    int startTime = ofGetElapsedTimeMillis();
    file << "Time, Master, Novice"<< endl;

}

//--------------------------------------------------------------
void ofApp::update(){
ofBackground(0);
    
    
    //Change the mapping ratio for graphs
    	scaled1= ofMap((int)AA1.pitch, 500.0, 5000, 0.0, 10.0, true);
    	scaled2= ofMap((int)AA2.pitch, 200.0, 5000, 0.0, 10.0, true);
    //lets record the volume into an array
    volHistory1.push_back(scaled1);
    volHistory2.push_back(scaled2);
    
    //if we are bigger the the size we want to record - lets drop the oldest value
    if( volHistory1.size() >= 400 ){
        volHistory1.erase(volHistory1.begin(), volHistory1.begin()+1);
    }
    
    if( volHistory2.size() >= 400 ){
        volHistory2.erase(volHistory2.begin(), volHistory2.begin()+1);
    }
    
    elapsedTime=ofGetElapsedTimeMillis();
    
    // write in a file every 300ms 
    if(elapsedTime-startTime>300){
    file << elapsedTime <<", "<<(int)AA1.pitch <<", "<<(int)AA2.pitch<< endl;
        startTime=elapsedTime;
    }
   // file.close();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    static int index=0;
    float avg_power = 0.0f;
    
    if(index < 80)
        index += 1;
    else
        index = 0;
    
    /* do the FFT	*/
    myfft.powerSpectrum(0,(int)BUFFER_SIZE/2, left,BUFFER_SIZE,&magnitude[0],&phase[0],&power[0],&avg_power);
    
    /* start from 1 because mag[0] = DC component */
    /* and discard the upper half of the buffer */
    for(int j=1; j < BUFFER_SIZE/2; j++) {
        freq[index][j] = magnitude[j];
    }
    
    int maxIndex=maximumValue(magnitude,(int)BUFFER_SIZE/2);
    //printf("freq is %lf \n",freq[index][maxIndex]);
    
    
    largeFont.drawString( "Haptic Learning System", 290,80);
    
    midFont.drawString( "Master", 50,170);
    
    smallFont.drawString( "pitch is : " + ofToString((int)AA1.pitch), 500,170);
    smallFont.drawString( "amplitude is : " + ofToString(AA1.amplitude,3), 500,190);
    
    //midFont.drawString(ofToString(getPitchSound((int)AA1.pitch)), 700,180);
    
    
    midFont.drawString( "Novice", 50,450);
    
    smallFont.drawString( "pitch is : " + ofToString((int)AA2.pitch), 500,450);
    smallFont.drawString( "amplitude is : " + ofToString(AA2.amplitude,3), 500,470);
    
   
    //midFont.drawString(ofToString(getPitchSound((int)AA2.pitch)), 700,460);
    
    
    /* draw the FFT */
    for (int i = 1; i < (int)(BUFFER_SIZE/2); i++){
        ofLine(500+(i*8),400,500+(i*8),400-magnitude[i]*10.0f);
    }
    
    for (int i = 1; i < (int)(BUFFER_SIZE/2); i++){
        ofLine(500+(i*8),700,500+(i*8),700-magnitude[i]*10.0f);
    }
    
    
 
    //dinFont.drawString( "confidence is : " + ofToString(AA.confidence), 50,110);
    
    //lets draw the volume history as a graph
    ofNoFill();
    ofBeginShape();
    for (unsigned int i = 0; i < volHistory1.size(); i++){
        if( i == 0 ) ofVertex(i+50, 400);
        
        ofVertex(i+50, 400 - volHistory1[i] * 70);
        
        if( i == volHistory1.size() -1 ) ofVertex(i+50, 400);
    }
    ofEndShape(false);
    
    ofBeginShape();
    for (unsigned int i = 0; i < volHistory2.size(); i++){
        if( i == 0 ) ofVertex(i+50, 700);
        
        ofVertex(i+50, 700 - volHistory2[i] * 70);
        
        if( i == volHistory2.size() -1 ) ofVertex(i+50, 700);
    }
    ofEndShape(false);
    
    
}

int ofApp::maximumValue(float *array, int length)
{
  // establish size of array
    float max = array[0];       // start with max = first element
    int maxIndex=0;
    for(int i = 1; i<length; i++)
    {
        if(array[i] > max){
            max = array[i];
            maxIndex=i;
        }
    
    }
    return maxIndex;                // return highest value in array
}

string ofApp::getPitchSound(int pitch){
    if(pitch >= 0 && pitch <250) return "A";
    else if (pitch >= 250 && pitch <500) return "B";
    else if (pitch >= 500 && pitch <750) return "C";
    else if (pitch >= 750 && pitch <1000) return "D";
    else if (pitch >= 1000 && pitch <1250) return "E";
    else if (pitch >= 1250 && pitch <1500) return "F";
    else return "";
   // else if (pitch >= 1500 && pitch <1750) return "B";

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::audioReceived 	(float * input, int bufferSize, int nChannels){
    // samples are "interleaved"
    for (int i = 0; i < bufferSize; i++){
        left[i] = input[i*2];
        right[i] = input[i*2+1];
        //cout << left << " : " << right <<endl;
    }
    AA1.processAudio(left, bufferSize);
    AA2.processAudio(right, bufferSize);
    
    bufferCounter++;
}

