#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    ofBackground(0);

    images.resize(100);
    int counter = 0;
    for(int i=1; i<201; i++) {
        if(i%2 != 0) {
            stringstream s;
            string frames = "frames/";
            s << frames << i << ".png";
            string filePath = s.str();
            cout << filePath << endl;
            images[counter].loadImage(filePath);
            counter++;
        }
    }

    // this toggle will tell the sequence
    // be be indepent of the app fps
    bFrameIndependent = true;

    // this will set the speed to play
    // the animation back we set the
    // default to 24fps
    sequenceFPS = 24;

    // set the app fps
    appFPS = 5;
    ofSetFrameRate(appFPS);
    cout << "end setup" << endl;
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

    // we need some images if not return
    if((int)images.size() <= 0) {
        ofSetColor(255);
        ofDrawBitmapString("No Images...", 150, ofGetHeight()/2);
        return;
    }

    // this is the total time of the animation based on fps
    //float totalTime = images.size() / sequenceFPS;


    int frameIndex = 0;

    if(bFrameIndependent) {
        // calculate the frame index based on the app time
        // and the desired sequence fps. then mod to wrap
        frameIndex = (int)(ofGetElapsedTimef() * sequenceFPS) % images.size();
    }
    else {
        // set the frame index based on the app frame
        // count. then mod to wrap.
        frameIndex = ofGetFrameNum() % images.size();
    }

    // draw the image sequence at the new frame count
    ofSetColor(255);
    images[frameIndex].draw(0,0,ofGetWidth(),ofGetHeight());
    //cout << frameIndex << endl;


    // draw where we are in the sequence
    float x = 0;
    for(int offset = 0; offset < 5; offset++) {
			int i = (frameIndex + offset) % images.size();
        ofSetColor(255);
        images[i].draw(200+x, ofGetHeight()-40, 40, 40);
        x += 40;
    }


    // how fast is the app running and some other info
    ofSetColor(50);
    ofRect(0, 0, 200, 200);
    ofSetColor(200);
    string info;
    info += ofToString(frameIndex)+" sequence index\n";
    info += ofToString(appFPS)+"/"+ofToString(ofGetFrameRate(), 0)+" fps\n";
    info += ofToString(sequenceFPS)+" Sequence fps\n\n";
    info += "Keys:\nup & down arrows to\nchange app fps\n\n";
    info += "left & right arrows to\nchange sequence fps";
    info += "\n\n't' to toggle\nframe independent("+ofToString(bFrameIndependent)+")";

    ofDrawBitmapString(info, 15, 20);

    cout << frameIndex << endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){


    if(key == OF_KEY_UP)      appFPS ++;
    if(key == OF_KEY_DOWN)    appFPS --;
    if(key == OF_KEY_LEFT)    sequenceFPS --;
    if(key == OF_KEY_RIGHT)   sequenceFPS ++;
    if(key == 't')            bFrameIndependent = !bFrameIndependent;

    // check for less than zero...
    sequenceFPS = MAX(sequenceFPS, 1);
    appFPS      = MAX(appFPS, 1);

    ofSetFrameRate(appFPS);
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
