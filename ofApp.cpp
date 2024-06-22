#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(0);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	this->line.clear();

	auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
	for (int i = 0; i < 3; i++) {

		for (int x = -1200; x <= 1200; x += 4) {

			auto base_y = ofMap(ofNoise(noise_seed.x, x * 0.001 + (ofGetFrameNum() + i * 10000) * 0.002), 0, 1, -300, 300);
			auto base_z = ofMap(ofNoise(noise_seed.y, x * 0.001 + (ofGetFrameNum() + i * 10000) * 0.002), 0, 1, -300, 300);

			auto y = base_y + ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -50, 50);
			auto z = base_z + ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -50, 50);
			this->line.addVertex(glm::vec3(x, y, z));
		}
	}

	for (int i = 0; i < this->line.getNumVertices(); i++) {

		for (int k = i + 1; k < this->line.getNumVertices(); k++) {

			if (glm::distance(this->line.getVertex(i), this->line.getVertex(k)) < 35) {

				this->line.addIndex(i);	this->line.addIndex(k);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 1.44);

	for (int i = 0; i < this->line.getNumVertices(); i++) {

		ofDrawSphere(this->line.getVertex(i), 3);
	}

	this->line.drawWireframe();

	this->cam.end();
	
	/*
	int start = 150;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}