/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "MainComponent.h"

//==============================================================================
/**
*/
class Juce_murka_testAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    Juce_murka_testAudioProcessorEditor   (Juce_murka_testAudioProcessor&);
    ~Juce_murka_testAudioProcessorEditor  ();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Juce_murka_testAudioProcessor& processor;
    
    MainComponent* mainComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Juce_murka_testAudioProcessorEditor  )
};
