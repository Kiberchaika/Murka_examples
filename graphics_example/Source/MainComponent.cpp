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
	setSize(800, 600);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::initialise()
{ 
	JuceMurkaBaseComponent::initialise();

	m.setFontFromRawData("Roboto-Regular.ttf", BinaryData::CamingoCodeRegular_ttf, BinaryData::CamingoCodeRegular_ttfSize, 12);

	murImage.setOpenGLContext(&openGLContext);
	murImage.loadFromRawData(BinaryData::lenin_jpg, BinaryData::lenin_jpgSize);

	murFbo.setOpenGLContext(&openGLContext);
}

void MainComponent::render()
{
	int mouseX = m.eventState.mousePosition.x;
	int mouseY = m.eventState.mousePosition.y;

	m.setScreenScale((float)openGLContext.getRenderingScale());
	m.begin();

	if (!murFbo.isAllocated()) {
		murFbo.allocate(400 * m.getScreenScale(), 400 * m.getScreenScale());
	}

	m.clear(20);

	m.beginFbo(murFbo);
	m.setColor(255);
	m.drawImage(murImage, 0, 0, 0, 400, 400);
	m.endFbo(murFbo);

	m.setColor(255);
	m.setFont("Roboto-Regular.ttf", 12);
	m.setColor(0, 0, 255, 255);
	m.drawRectangle(0, 0, 1000, 1000);
	m.setColor(255, 255);


	{
		m.pushMatrix();
		m.translate(20, 20, 0);

		m.getCurrentFont()->drawString("HELLO!", 0, 0);

		auto& button = m.draw<murka::Button>({ 0, 50, 150, 75 });
		button.text("Button");
		button.commit();

		if (button.pressed) {
			std::cout << "woah this works" << std::endl;
		}

		m.popMatrix();
	}

	{
		m.pushMatrix();
		m.translate(400, 20, 0);

		m.setColor(255);
		m.drawImage(murImage, 0, 0, 0, 100, 100);

		m.popMatrix();
	}

	m.end();

	//

	/*
	m.translate(100, 100, 0);
	m.rotateZRad(degreesToRadians(-35.0f + i));
	m.scale(1, 3, 1);
	m.pushMatrix();
	m.translate(-10, -50, 0);
	m.popMatrix();
	*/
	//m.drawRectangle(0, 22, 100, 100); // desktopScale * getWidth()/2, desktopScale * getHeight()/2
	//m.drawCircle(100, 100, 100);

	//m.viewport(20, 20, 100, 100);
	//m.pushView();
	//m.viewport(0, 0, 100, 100);
	//m.popView();

	//m.draw(murImage, 0, 122, 0, 100, 100);
	//m.drawRectangle(0, 22, 100, 100);


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
void MainComponent::paint(Graphics& g)
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
