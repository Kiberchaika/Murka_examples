#include "MainComponent.h"
#include "RoundedButtonWithGradient.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================

void MainComponent::initialise()
{
	JuceMurkaBaseComponent::initialise();

	m.setFontFromRawData("Roboto-Regular.ttf", BinaryData::CamingoCodeRegular_ttf, BinaryData::CamingoCodeRegular_ttfSize, 12);
}

void MainComponent::render()
{ 
	m.setScreenScale((float)openGLContext.getRenderingScale());
	m.begin();

	m.clear(20);

	m.setColor(255);
	m.setFont("Roboto-Regular.ttf", 12);
	
	//m.drawImage(murImage, 0, 0, 0, 100, 100);
	auto& button = m.draw<murka::RoundedButtonWithGradient>({ 50, 50, 100, 50 }).text("Test");
	button.commit();

	if (button.pressed) {
		std::cout << "woah this works" << std::endl;
	}

	m.end();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
