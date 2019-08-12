#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/app/Window.h"
#include "cinder/gl/gl.h"
#include "cinder/Capture.h"
#include "cinder/Log.h"
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
#include "cinder/qtime/QuickTimeGl.h"
#include "cinder/Text.h"
#include <vector>


using namespace ci;
using namespace ci::app;
using namespace std;

class VideoMixerApp : public App {
  public:
	void setup() override;
    void keyDown( KeyEvent event ) override;
	void update() override;
	void draw() override;
    void loadMovieFile( const fs::path &path, const uint8_t &n );
    void stopMovies();
    void muteMovies();
    void changeInput(const int mInput);
    
private:
    void printDevices();
    
    CaptureRef            mCapture;
    gl::TextureRef        mTexture;
    gl::TextureRef        mFrameTexture;
    float                 fade=0.5;
    bool                  showInfo=true;
    bool                  setMovieSize=false;
    bool                  presentation = false;
    bool                  inputChanged =false;
    Font                  myFont;
    array<qtime::MovieGlRef, 5> mMovies;
    array<fs::path, 5>    movieFileNames;
    array<string, 5>      mDeviceNames;
    array<bool,5>         movieFileLoaded;
    int                   currentCam=0;
    int                   currentMovie=0;
    Rectf                 centeredRect;
    int                   inputVideoWidth=1440;
    int                   inputVideoHeight=900;
    int                   maxInputWidth;
    int                   maxInputHeight;

    
};

void VideoMixerApp::setup()
{
    setFullScreen( true );

    movieFileLoaded[0]=false;
    movieFileLoaded[1]=false;
    movieFileLoaded[2]=false;
    movieFileLoaded[3]=false;
    movieFileLoaded[4]=false;
 
    myFont = Font ("Verdana", 16);

    try {
        mCapture = Capture::create( inputVideoWidth, inputVideoHeight );
        mCapture->start();
        maxInputWidth = mCapture->getWidth();
        maxInputHeight = mCapture->getHeight();
    }
    catch( ci::Exception &exc ) {
        CI_LOG_EXCEPTION( "Failed to init capture ", exc );
    }
    printDevices();
}

void VideoMixerApp::keyDown( KeyEvent event )
{
    if( event.getChar() == 'a' ) {
        fade+=0.01;
    } else if( event.getChar() == 's' ) {
        fade-=0.01;
    } else if( event.getChar() == 'f' ) {
        if(isFullScreen()){
        setFullScreen( false );
        } else {
        setFullScreen( true );
        }
    }
    else if( event.getChar() == 'h' ) {
        showInfo=!showInfo;
    } else if( event.getChar() == 'c' ) {
        if(mDeviceNames[currentCam].length()>0){
            changeInput(currentCam);
            // printDevices();
            inputChanged=true;
        }
        printDevices();
    } else if( event.getChar() == 'z' ) {
        if(currentCam<3){
            currentCam++;
        }
    } else if( event.getChar() == 'x' ) {
        if(currentCam>0){
            currentCam--;
        }
    } else if( event.getChar() == 'p' ) {
        if(!presentation){
            mMovies[currentMovie]->play();
        } else {
            stopMovies();
        }
        presentation=!presentation;
    } else if( event.getChar() == '<' ) {
        if(inputVideoWidth>10){
        inputVideoWidth-=10;
        }
    } else if( event.getChar() == '>' ) {
        if(inputVideoWidth<maxInputWidth){
        inputVideoWidth+=10;
        }
    } else if( event.getChar() == 'v' ) {
        if(inputVideoHeight>10){
            inputVideoHeight-=10;
        }
    } else if( event.getChar() == 'b' ) {
        if(inputVideoHeight<maxInputHeight){
            inputVideoHeight+=10;
        }
    } else if( event.getChar() == '1' ) {
        if( ! movieFileNames[1].empty()) {
            mMovies[currentMovie]->stop();
            currentMovie=0;
            if (presentation){
                mMovies[currentMovie]->play();
                muteMovies();
                mMovies[currentMovie]->setVolume(1.0f);
            }
        }
    } else if( event.getChar() == '2' ) {
        if( ! movieFileNames[1].empty()) {
            mMovies[currentMovie]->stop();
            currentMovie=1;
            if (presentation){
                mMovies[currentMovie]->play();
                muteMovies();
                mMovies[currentMovie]->setVolume(1.0f);
            }
        }
    } else if( event.getChar() == '3' ) {
        if( ! movieFileNames[2].empty()) {
            mMovies[currentMovie]->stop();
            currentMovie=2;
            if (presentation){
                mMovies[currentMovie]->play();
                muteMovies();
                mMovies[currentMovie]->setVolume(1.0f);
            }
        }
    } else if( event.getChar() == '4' ) {
        if( ! movieFileNames[3].empty()) {
            mMovies[currentMovie]->stop();
            currentMovie=3;
            if (presentation){
                mMovies[currentMovie]->play();
                muteMovies();
                mMovies[currentMovie]->setVolume(1.0f);
            }
        }
    } else if( event.getChar() == '5' ) {
        if( ! movieFileNames[1].empty()) {
            mMovies[currentMovie]->stop();
            currentMovie=4;
            if (presentation){
                mMovies[currentMovie]->play();
                muteMovies();
                mMovies[currentMovie]->setVolume(1.0f);
            }
        }
    } else if( event.getChar() == 'q' ) {
        movieFileNames[0] = getOpenFilePath();
            if( ! movieFileNames[0].empty() )
            loadMovieFile( movieFileNames[0], 0 );
    } else if( event.getChar() == 'w' ) {
        if(movieFileLoaded[0]){
        movieFileNames[1] = getOpenFilePath();
        if( ! movieFileNames[1].empty() )
        loadMovieFile( movieFileNames[1], 1 );
        }
    } else if( event.getChar() == 'e' ) {
        if(movieFileLoaded[1]){
        movieFileNames[2] = getOpenFilePath();
        if( ! movieFileNames[2].empty() )
            loadMovieFile( movieFileNames[2], 2 );
        }
    } else if( event.getChar() == 'r' ) {
        if(movieFileLoaded[2]){
        movieFileNames[3] = getOpenFilePath();
        if( ! movieFileNames[3].empty() )
            loadMovieFile( movieFileNames[3], 3 );
        }
    } else if( event.getChar() == 't' ) {
         if(movieFileLoaded[3]){
        movieFileNames[4] = getOpenFilePath();
        if( ! movieFileNames[4].empty() )
            loadMovieFile( movieFileNames[4], 4 );
         }
    }

}

void VideoMixerApp::loadMovieFile( const fs::path &moviePath, const uint8_t &n )
{
    try {
        // load up the movie, set it to loop, and begin playing
        mMovies[n] = qtime::MovieGl::create( movieFileNames[n] );
        mMovies[n]->setLoop();
        mMovies[n]->setVolume(1.0f);
        mMovies[n]->stop();
        console() << "Playing: " << mMovies[n]->isPlaying() << std::endl;
        movieFileLoaded[n]=true;
    }
    catch( ci::Exception &exc ) {
        console() << "Exception caught trying to load the movie from path: " << moviePath << ", what: " << exc.what() << std::endl;
        mMovies[n].reset();
    }

    mFrameTexture.reset();
}

void VideoMixerApp::stopMovies()
{
    for (int i=0; i<5; i++){
        if(movieFileLoaded[i]){
            mMovies[i]->stop();
            
        }
    }
}
void VideoMixerApp::muteMovies()
{
    for (int i=0; i<5; i++){
        if(movieFileLoaded[i]){
            mMovies[i]->setVolume(0.0f);
        }
    }
}

void VideoMixerApp::update()
{
    if( mMovies[currentMovie] ){
        mFrameTexture = mMovies[currentMovie]->getTexture();
    }
    if( mCapture && mCapture->checkNewFrame() ) {
        if( ! mTexture || inputChanged) {
            // Capture images come back as top-down, and it's more efficient to keep them that way
            mTexture = gl::Texture::create( *mCapture->getSurface(), gl::Texture::Format().loadTopDown() );
            inputChanged=false;
        }
        else {
            mTexture->update( *mCapture->getSurface() );
        }
    }
}

void VideoMixerApp::draw()
{
    gl::clear(Color( 0.0f, 0.0f, 0.0f ) );
    
    if( mFrameTexture ) {
        if(!setMovieSize){
            centeredRect = Rectf( mFrameTexture->getBounds() ).getCenteredFill( getWindowBounds(), true );
            setMovieSize=true;
        }
        gl::ScopedColor( ColorA( 1.0f, 1.0f, 1.0f,1.0f ) );
       // gl::color( ColorA(1.0f, 1.0f, 1.0f,1.0f) );
        
        gl::color( ColorA( 1.0f, 1.0f, 1.0f,1.0f-fade ) );
        gl::draw( mFrameTexture, centeredRect );
        gl::color( ColorA( 1.0f, 1.0f, 1.0f,fade ) );
        gl::draw( mTexture, centeredRect );
        
    }
    

    
    
    if(showInfo){
        const uint8_t leftMargin = 50;
        
        gl::drawString("Start by creating your own preset of 1-5 different videos, follow the instructions below. All videos are scaled automatically to fill the screen.", vec2(leftMargin,20), ColorA(1,1,1,1), myFont );

        gl::drawString("Video 1 (press 'q' to open and select a video file from finder): ", vec2(leftMargin,60), ColorA(1,1,1,1), myFont );
        gl::drawString(movieFileNames[0].string(), vec2(leftMargin,80), ColorA(0,1,0,1), myFont );
        if(movieFileLoaded[0]){
        gl::drawString("Video 2 (press 'w' to open and select a video file from finder): ", vec2(leftMargin,110), ColorA(1,1,1,1), myFont );
        gl::drawString(movieFileNames[1].string(), vec2(leftMargin,130), ColorA(0,1,0,1), myFont );
        }
        if(movieFileLoaded[1]){
        gl::drawString("Video 3 (press 'e' to open and select a video file from finder): ", vec2(leftMargin,160), ColorA(1,1,1,1), myFont );
        gl::drawString(movieFileNames[2].string(), vec2(leftMargin,180), ColorA(0,1,0,1), myFont );
        }
        if(movieFileLoaded[2]){
        gl::drawString("Video 4 (press 'r' to open and select a video file from finder): ", vec2(leftMargin,210), ColorA(1,1,1,1), myFont );
        gl::drawString(movieFileNames[3].string(), vec2(leftMargin,230), ColorA(0,1,0,1), myFont );
        }
        if(movieFileLoaded[4]){
        gl::drawString("Video 5 (press 't' to open and select a video file from finder): ", vec2(leftMargin,260), ColorA(1,1,1,1), myFont );
        gl::drawString(movieFileNames[4].string(), vec2(leftMargin,280), ColorA(0,1,0,1), myFont );
        }
        if(movieFileLoaded[currentMovie]){
            gl::drawString("Press '1', '2', '3', '4' and '5' to switch between videos. Current video: "+to_string(currentMovie+1), vec2(leftMargin,330), ColorA(1,1,1,1), myFont );
            gl::drawString("Press 'a' or 's' to adjust opacity of the live image. Current opacity: " + to_string(fade*100.0f)+" %", vec2(leftMargin,350), ColorA(1,1,1,1), myFont );
            gl::drawString("Press 'h' to hide/show info - all keycodes are in function also when info is hidden.", vec2(leftMargin,370), ColorA(1,1,1,1), myFont );
            gl::drawString("Press 'f' to exit fullscreen.", vec2(leftMargin,390), ColorA(1,1,1,1), myFont );
            gl::drawString("If you want to change live camera source, press 'z' or 'x' to select correct camera and 'c' to confirm. Current resolution: "+to_string(inputVideoWidth)+"x"+to_string(inputVideoHeight), vec2(leftMargin,410), ColorA(1,1,1,1), myFont );
            if(mDeviceNames[currentCam].length()>0){
                gl::drawString("Camera found: " + mDeviceNames[currentCam], vec2(leftMargin,430), ColorA(0,1,0,1), myFont );
            } else {
                gl::drawString("Camera not found("+ to_string(currentCam)+"): select different source!" , vec2(leftMargin,430), ColorA(1,0,0,1), myFont );
            }
            if (presentation){
                gl::drawString("Presentation running", vec2(leftMargin,310), ColorA(0,1,0,1), myFont );
            } else {
                gl::drawString("NOTE: All videos are paused until you hit 'p' to play", vec2(leftMargin,310), ColorA(1,0,0,1), myFont );
            }
        }
        gl::drawString("Made with Cinder by Tuomo Rainio in Academy of Fine Art Helsinki 2018", vec2(leftMargin,600), ColorA(0,0,0,1), myFont );
    }
}

void VideoMixerApp::printDevices()
{
    int laskuri = 0;
    for( const auto &device : Capture::getDevices() ) {
        console() << "Device: " << device->getName() << " "  << endl;
        mDeviceNames[laskuri] = device->getName();
        laskuri++;
    }
}

void VideoMixerApp::changeInput(const int mInput)
{
    int laskuri = 0;
    vector <Capture::DeviceRef> mDev;
    
    for( const auto &device : Capture::getDevices(true) ) {
        mDeviceNames[laskuri] = device->getName();
        mDev = Capture::getDevices();
        laskuri++;
    }
    mCapture->stop();
    try {
        mCapture = Capture::create( inputVideoWidth, inputVideoHeight, mDev.at(mInput));
        maxInputWidth = mCapture->getWidth();
        maxInputHeight = mCapture->getHeight();
        mCapture->start();
    }
    catch( ci::Exception &exc ) {
        CI_LOG_EXCEPTION( "Failed to init capture ", exc );
    }
}

CINDER_APP( VideoMixerApp, RendererGl )
