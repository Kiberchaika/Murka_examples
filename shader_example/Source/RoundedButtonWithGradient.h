#pragma once

#include "Murka.h"
#include "MurkaView.h"
#include "MurShader.h"
#include "Label.h"

namespace murka {

class RoundedButtonWithGradient : public View<RoundedButtonWithGradient> {
public:

    ~RoundedButtonWithGradient() {
        if (murShader.isLoaded()) {
            murShader.unload();
        } 
    }

    void setupShader(Murka& m) {

        std::string fragmentShaderCustom = R"(
		    varying vec2 vUv;

		    uniform vec4 color1;
		    uniform vec4 color2;
		
		    uniform vec2 point1;
		    uniform vec2 point2;

		    uniform vec2 resolution;
	        uniform float cornerRadius;

	        uniform float scale;

	        uniform float time;

		    // from https://iquilezles.org/articles/distfunctions
		    float udRoundBox( vec2 p, vec2 b, float r )
		    {
			    return length(max(abs(p)-b+r,0.0))-r;
		    }

		    void main()
		    {
			    // wave effect
			    vec2 offset = vec2 (0., sin(vUv.x * 3.14 * 0.5 + time));

		        // calculate interpolation factor with vector projection.
			    vec2 v = point2 - point1;
			    float t = dot(vUv + offset  - point1, v) / dot(v, v);
			
			    // saturate and apply smoothstep to the factor
			    t = smoothstep(0.0, 1.0, clamp(t, 0.0, 1.0));
			
			    // interpolate
			    vec4 color = mix(color1, color2, t);

		        // compute box
 	 	        vec2 halfRes = 0.5 * resolution;
			    float roundedBox = udRoundBox(vUv * resolution - halfRes, halfRes * scale, cornerRadius );
 
			    // mask gradient with rounded box
	            color.a = 1. - smoothstep(0.0,1.0,roundedBox);

			    gl_FragColor = color;
		    };
	    )";

        murShader.setOpenGLContext(m.getOpenGLContext());
        if (murShader.load(m.vertexShaderBase, fragmentShaderCustom)) {
            m.bindShader(&murShader);
            murShader.setUniform4f("color1", 255 / 255.0, 0 / 255.0, 114 / 255.0, 1.);
            murShader.setUniform4f("color2", 197 / 255.0, 255 / 255.0, 80 / 255.0, 1.);
            murShader.setUniform2f("point1", 0., 0.);
            murShader.setUniform2f("point2", 1., 1.);
        }
    }

    void internalDraw(Murka& m) {

        bool inside = m.currentContext.isHovered();

        if ((m.currentContext.mouseDownPressed[0]) && (m.currentContext.isHovered())) {
            pressed = true;
            lastTimeClicked = m.getElapsedTime();
        }
        else pressed = false;

        auto font = m.getCurrentFont();

        float pushed = 0.2 - (m.getElapsedTime() - lastTimeClicked);
        if (pushed < 0) pushed = 0;
        pushed /= 0.2;

        if (!murShader.isLoaded()) {
            setupShader(m);
        }

        m.pushStyle();
        m.enableFill();

        m.bindShader(&murShader);
        murShader.setUniform2f("resolution", m.currentContext.getSize().x * m.getScreenScale(), m.currentContext.getSize().y * m.getScreenScale());
        murShader.setUniform1f("cornerRadius", 20 * m.getScreenScale());
        murShader.setUniform1f("scale", (1 - pushed));
        murShader.setUniform1f("time", m.getElapsedTime());
        m.setColor(255);
        m.drawRectangle(0, 0, m.currentContext.getSize().x, m.currentContext.getSize().y);
        m.unbindShader();
 
        m.setColor(255);
        float offset = (font->stringWidth(label) / 2);
        font->drawString(label, m.currentContext.getSize().x / 2 - offset, m.currentContext.getSize().y / 2 - font->getLineHeight() / 2);

        m.popStyle();
    };


    MURKA_PARAMETER(RoundedButtonWithGradient, // class name
        std::string, // parameter type
        label, // parameter variable name
        text, // setter
        "") // default

    // Whatever the parameters and the results are, the functions have to be defined here
    MurShader murShader;

    std::function<void()> Callback;


    bool pressed;

    // Internal state

    std::string Label;
    float lastTimeClicked = 0;
};

}

