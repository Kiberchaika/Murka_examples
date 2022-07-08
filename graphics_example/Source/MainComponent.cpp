/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
	// Make sure you set the size of the component after
	 // you add any child components.
	openGLContext.setOpenGLVersionRequired(OpenGLContext::OpenGLVersion::openGL3_2);
	openGLContext.setMultisamplingEnabled(true);

	OpenGLPixelFormat pixelFormat;
	pixelFormat.multisamplingLevel = 8;
	openGLContext.setPixelFormat(pixelFormat);
	
	// Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);
}

MainComponent::~MainComponent()
{
	// This shuts down the GL system and stops the rendering calls.
	openGLContext.deactivateCurrentContext();
	openGLContext.detach();

}

//==============================================================================
void MainComponent::initialise()
{
	/*
	murkaRender.setAppComponent(this);
	murkaRender.setOpenGLContext(&openGLContext);
	murkaRender.setup();

	murkaRender.setupScreen();

	*/

	std::string vertexShader =
		"varying vec2 vUv;\n"
		"varying vec4 vCol;\n"
		"uniform mat4 matrixModel;\n"
		"uniform mat4 matrixView;\n"
		"uniform mat4 matrixProj;\n"
		"uniform vec4 color;\n"
		"attribute vec3 position;\n"
		"attribute vec2 uv;\n"
		"attribute vec4 col;\n"
		"\n"
		"void main()\n"
		"{\n"
		"    vUv = uv;"
		"    vCol = col;"
		"    vec4 pos = matrixProj * matrixView * matrixModel * vec4(position, 1.0) ; \n"
		"    gl_Position =  pos; \n"
		"}\n";

	std::string fragmentShader =
		"varying vec2 vUv;\n"
		"varying vec4 vCol;\n"
		"uniform sampler2D mainTexture;\n"
		"uniform vec4 color;\n"
		//"uniform bool useTexture;\n"
		"\n"
		"void main()\n"
		"{\n"
		//"    gl_FragColor = color * vCol * (useTexture ? texture(mainTexture, vUv) : vec4 (1.0, 1.0, 1.0, 1.0));\n"
		"    gl_FragColor = vec4 (vUv.x, vUv.y, 1.0, 1.0);\n"
		"}\n";

	murShader.setOpenGLContext(&openGLContext);
	bool shaderLoaded = murShader.load(vertexShader, fragmentShader);

	murImage.setOpenGLContext(&openGLContext);
	murImage.load("D:/Developer/Crossplatform/JUCE/JUCE_MURKA_TEST/Resources/lenin.jpg");

	// murka
	m.setAppComponent(this);
	m.setOpenGLContext(&openGLContext);
	m.setup();

	m.setResourcesPath("D:/Developer/Crossplatform/JUCE/JUCE_MURKA_TEST/Resources");
	m.shape = { 0, 0, getWidth(), getHeight() };
	m.setScreenScale((float)openGLContext.getRenderingScale());
	m.setupScreen();
}

void MainComponent::reload()
{
	// setup();
}

void MainComponent::shutdown()
{ 
	// Free any GL objects created for rendering here.
}

void MainComponent::render()
{
	m.startFrame();
	m.setScreenScale((float)openGLContext.getRenderingScale());

   // This clears the context with a black background.
	//OpenGLHelpers::clear (Colours::black);

	// TODO
	m.clear(20);
	m.setColor(255);

	m.setFont("Roboto-Regular.ttf", 12);

	m.begin();

	m.setColor(255);

	//m.scale(10, 10, 10);
	m.draw<murka::Label>({ 50, 100, 150, 30 }).text("112344");
	m.commitDeferredView();
	 
	auto button = m.draw<murka::Button>({ 50, 150, 150, 75 }).text("Dynamic button 1");
	m.commitDeferredView();

	if (button.pressed) {
		std::cout << "woah this works" << std::endl;
	}
	 
	m.bindShader(&murShader);
	m.setColor(0, 255, 0);
	m.drawRectangle(10, 10, 100, 100);
	m.unbindShader();


	m.getCurrentFont()->drawString("HELLO!", 200, 100);

	m.setColor(220, 0, 220, 255);
	m.drawLine(1, 1, 100, 100);
	// Commit deferred view calls the base class draw() instead of derived one. Fix this somehow.
   // m.currentContext.commitDeferredView();

	/*
	Label::purr(m, { 50, 50, 200, 50 })
		.label = "yo";

	Label().draw3(m, { 50, 50, 200, 50 });
//    commit();
	 */
	m.setColor(255); 
	m.drawImage(murImage , 200, 200, 0, 100, 100);
	 
	m.viewport(100, 200, 100, 100);
	

	//MurFbo fbo; 

	m.drawImage(murImage, 0, 50, 0, 150, 150);

	m.end();


	//m.setColor(255, 0, 0, 255);


	/*
	murkaRender.translate(100, 100, 0);
	murkaRender.rotateZRad(degreesToRadians(-35.0f + i));
	murkaRender.scale(1, 3, 1);
	murkaRender.pushMatrix();
	murkaRender.translate(-10, -50, 0);
	murkaRender.popMatrix();
	*/
	//murkaRender.drawRectangle(0, 22, 100, 100); // desktopScale * getWidth()/2, desktopScale * getHeight()/2
	//murkaRender.drawCircle(100, 100, 100);

	//murkaRender.viewport(20, 20, 100, 100);
	//murkaRender.pushView();
	//murkaRender.viewport(0, 0, 100, 100);
	//murkaRender.popView();
	
	//murkaRender.draw(murImage, 0, 122, 0, 100, 100);
	//murkaRender.drawRectangle(0, 22, 100, 100);


	//m.drawRectangle(0, 22, 100, 100);

	/*
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_POINTS);
    glVertex3f(0.0, 0.5, 0.0);//drawn white or default color first loop and green all other loops
    glColor3f(1.0, 0.5, 0.0);//set red 100% green 50% blue 0%
    glVertex3f(0.1, 0.5, 0.0);//drawn orange
    glVertex3f(0.2, 0.5, 0.0);//drawn orange
    glColor3f(1.0, 0.0, 0.0);//set red 100% green 0% blue 0%
    glVertex3f(0.3, 0.5, 0.0);//drawn red
    glEnd();
    glBegin(GL_POINTS);
    glVertex3f(0.4, 0.5, 0.0);//drawn red
    glColor3f(0.0, 1.0, 0.0);//set red 0% green 100% blue 0%
    glVertex3f(0.5, 0.5, 0.0);//drawn green
    glVertex3f(0.6, 0.5, 0.0);//drawn green
    glEnd();
    
	// draw
	*/
} 

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // You can add your component specific drawing code here!
    // This will draw over the top of the openGL background.
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
