#include "FurryKinectApp.h"
#include "ofAppGlutWindow.h"

int main() {
	ofAppGlutWindow window;
    window.setGlutDisplayString("rgba double samples>=4 depth");
	ofSetupOpenGL(&window, 1024, 1024, OF_WINDOW);
	ofRunApp(new FurryKinectApp());
}
