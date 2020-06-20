#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);

	this->noise_param = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();

	int width = 20;
	int deg_span = 5;
	for (int x = 90; x < ofGetWidth(); x += 180) {

		for (int y = 90; y < ofGetHeight(); y += 180) {

			for (int deg = 0; deg < 360; deg += deg_span) {

				int radius = ofMap(ofNoise(ofRandom(1000), this->noise_param), 0, 1, 20, 50);

				this->setRingToMesh(this->mesh, glm::vec3(x, y, 0), radius, width, deg, deg + deg_span);
			}
		}
	}

	if (ofGetFrameNum() % 60 < 45) {

		this->noise_param += ofMap(ofGetFrameNum() % 60, 0, 45, 0.1, 0);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->mesh.draw();
}

//--------------------------------------------------------------
void ofApp::setRingToMesh(ofMesh& mesh, glm::vec3 location, float radius, float width, int deg_start, int deg_end) {

	if (deg_start == deg_end) { return; }

	int deg_span = 5;
	for (int deg = deg_start; deg < deg_end; deg += deg_span) {

		auto index = mesh.getNumVertices();

		vector<glm::vec3> vertices;
		vertices.push_back(location + glm::vec3((radius + width * 0.5) * cos(deg * DEG_TO_RAD), (radius + width * 0.5) * sin(deg * DEG_TO_RAD), 0));
		vertices.push_back(location + glm::vec3((radius + width * 0.5) * cos((deg + deg_span) * DEG_TO_RAD), (radius + width * 0.5) * sin((deg + deg_span) * DEG_TO_RAD), 0));
		vertices.push_back(location + glm::vec3((radius - width * 0.5) * cos((deg + deg_span) * DEG_TO_RAD), (radius - width * 0.5) * sin((deg + deg_span) * DEG_TO_RAD), 0));
		vertices.push_back(location + glm::vec3((radius - width * 0.5) * cos(deg * DEG_TO_RAD), (radius - width * 0.5) * sin(deg * DEG_TO_RAD), 0));

		mesh.addVertices(vertices);

		mesh.addIndex(index + 0); mesh.addIndex(index + 1); mesh.addIndex(index + 2);
		mesh.addIndex(index + 0); mesh.addIndex(index + 2); mesh.addIndex(index + 3);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}