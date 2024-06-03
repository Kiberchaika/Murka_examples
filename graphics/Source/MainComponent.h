#pragma once

#include <JuceHeader.h>
#include "juce_murka/JuceMurkaBaseComponent.h"

class MainComponent : public JuceMurkaBaseComponent
{
	MurImage murImage;
	MurFbo murFbo;
	MurShader murShaderNoise;
	MurShader murShaderBlur;

	struct AnimRect {
		MurkaPoint pos;
		MurkaPoint dir;
		MurkaColor col;
	};

	std::vector<AnimRect> animRects;


public:
	MainComponent() {
		setSize(332, 306);
	}

	float random(float min, float max) {
		static std::random_device rd;
		static std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dis(min, max);
		return dis(gen);
	}

	void MainComponent::initialise() override {
		JuceMurkaBaseComponent::initialise();

		// load fonts
		m.setFontFromRawData("InterThin", BinaryData::InterThin_ttf, BinaryData::InterThin_ttfSize, 19);
		m.setFontFromRawData("InterExtraLight", BinaryData::InterExtraLight_ttf, BinaryData::InterExtraLight_ttfSize, 17);
		m.setFontFromRawData("InterLight", BinaryData::InterLight_ttf, BinaryData::InterLight_ttfSize, 15);
		m.setFontFromRawData("InterRegular", BinaryData::InterRegular_ttf, BinaryData::InterRegular_ttfSize, 13);
		m.setFontFromRawData("InterMedium", BinaryData::InterMedium_ttf, BinaryData::InterMedium_ttfSize, 11);
		m.setFontFromRawData("InterSemiBold", BinaryData::InterSemiBold_ttf, BinaryData::InterSemiBold_ttfSize, 10);
		m.setFontFromRawData("InterBold", BinaryData::InterBold_ttf, BinaryData::InterBold_ttfSize, 8);
		m.setFontFromRawData("InterExtraBold", BinaryData::InterExtraBold_ttf, BinaryData::InterExtraBold_ttfSize, 6);

		// load image
		murImage.setOpenGLContext(m.getOpenGLContext());
		murImage.loadFromRawData(BinaryData::cat_png, BinaryData::cat_pngSize);

		// fbo
		murFbo.setOpenGLContext(m.getOpenGLContext());

		// shader for noise
		std::string fragmentShaderNoise = R"(
			varying vec2 vUv;
			uniform bool vflip;

			uniform float time;

			// Function to generate noise based on UV coordinates and time
			float noise(vec2 uv, float time) {
				return fract(sin(dot(uv.xy, vec2(12.9898, 78.233)) + time) * 43758.5453123);
			}

			void main() {
				vec2 uv = vUv;
				if (vflip) uv.y = 1 - uv.y;

				// Generate noise based on UV coordinates and time
				float n = noise(uv, time);

				// Set the fragment color based on the noise value
				gl_FragColor = vec4(vec3(n), 1.0);
			}
		)";

		murShaderNoise.setOpenGLContext(m.getOpenGLContext());
		murShaderNoise.load(m.vertexShaderBase, fragmentShaderNoise);

		// init rect anim
		for (int i = 0; i < 3; i++) {
			AnimRect animRect;
			animRect.pos.x = random(0.0, 50.0);
			animRect.pos.y = random(0.0, 50.0);
			animRect.dir.x = random(-2, 2);
			animRect.dir.y = random(-2, 2);
			animRects.push_back(animRect);
		}

		animRects[0].col = MurkaColor(175, 0, 0);
		animRects[1].col = MurkaColor(204, 222, 0);
		animRects[2].col = MurkaColor(204, 0, 222);

		std::string fragmentShaderBlur = R"(
			varying vec2 vUv;
			uniform sampler2D mainTexture;
			uniform bool vflip;
			uniform vec2 resolution;
			uniform float blurAmount;  

			// Function to apply blur effect
			vec4 applyBlur(sampler2D textureSampler, vec2 uv) {
				vec2 texelSize = 1.0 / resolution;
				vec4 sum = vec4(0.0);
        
				// Gaussian blur kernel
				float weights[9] = float[](0.0625, 0.125, 0.0625, 0.125, 0.25, 0.125, 0.0625, 0.125, 0.0625);
				int offsetX[9] = int[](-1, 0, 1, -1, 0, 1, -1, 0, 1);
				int offsetY[9] = int[](-1, -1, -1, 0, 0, 0, 1, 1, 1);
        
				for (int i = 0; i < 9; i++) {
					vec2 offset = vec2(offsetX[i], offsetY[i]) * texelSize * blurAmount;
					sum += texture(textureSampler, uv + offset) * weights[i];
				}
				sum.a = 1.0;
				return sum;
			}

			void main()
			{
				vec2 uv = vUv;
				if (vflip) uv.y = 1 - uv.y;

				gl_FragColor = applyBlur(mainTexture, uv);
			}
		)";

		murShaderBlur.setOpenGLContext(m.getOpenGLContext());
		murShaderBlur.load(m.vertexShaderBase, fragmentShaderBlur);
	}

	void draw() override {
		m.clear(39, 39, 39);
		m.setColor(255);


		// text
		m.setFont("InterThin", 19);
		m.drawString("Thin", 10, 17);

		m.setFont("InterExtraLight", 17);
		m.drawString("Extra light", 10, 46);

		m.setFont("InterLight", 15);
		m.drawString("Light", 10, 72);

		m.setFont("InterRegular", 13);
		m.drawString("Regular", 10, 96);

		m.setFont("InterMedium", 11);
		m.drawString("Medium", 10, 118);

		m.setFont("InterSemiBold", 10);
		m.drawString("Semi bold", 10, 139);

		m.setFont("InterBold", 8);
		m.drawString("Bold", 10, 159);

		m.setFont("InterExtraBold", 6);
		m.drawString("Extra bold", 10, 176);

		// line
		m.pushMatrix();
		m.translate(170, 50, 0);
		m.rotateZRad(m.getElapsedTime() * 50.0f * M_PI / 180);
		m.drawLine(-20, 0, 20, 0);
		m.popMatrix();

		// star
		m.pushMatrix();
		m.pushStyle();
		m.disableFill();
		m.translate(260, 50, 0);
		m.scale(20, 20, 1);
		m.drawPath({
			{0.0f, -0.5f, 0.0f},
			{0.118f, -0.154f, 0.0f},
			{0.475f, -0.154f, 0.0f},
			{0.191f, 0.062f, 0.0f},
			{0.293f, 0.404f, 0.0f},
			{0.0f, 0.25f, 0.0f},
			{-0.293f, 0.404f, 0.0f},
			{-0.191f, 0.062f, 0.0f},
			{-0.475f, -0.154f, 0.0f},
			{-0.118f, -0.154f, 0.0f},
			{0.0f, -0.5f, 0.0f}
			});
		m.popStyle();
		m.popMatrix();

		// rect
		m.pushMatrix();
		m.pushStyle();
		m.translate(170, 130, 0);
		m.disableFill();
		m.drawRectangle(-25, -25, 50, 50);
		m.enableFill();
		m.drawRectangle(-20, -20, 40, 40);
		m.popStyle();
		m.popMatrix();

		//DBG(">> " +  std::to_string(m.mouseScroll().x) + " , " +  std::to_string(m.mouseScroll().y));

		// circle
		m.pushMatrix();
		m.translate(260, 130, 0);
		m.drawCircle(0, 0, 25);
		m.popMatrix();

		// cat image
		m.drawImage(murImage, 10, 210, 105, 76);


		// noise shader
		m.pushMatrix();
		m.pushStyle();
		m.translate(170, 250, 0);
		m.bindShader(&murShaderNoise);
		murShaderNoise.setUniform1f("time", m.getElapsedTime());
		m.drawRectangle(-35, -35, 70, 70);
		m.unbindShader();
		m.popStyle();
		m.popMatrix();

		// fbo with 
		if (!murFbo.isAllocated()) {
			murFbo.allocate(70 * m.getScreenScale(), 70 * m.getScreenScale());
		}
		m.beginFbo(murFbo);
		m.pushStyle();
		m.clear(0, 0);
		for (int i = 0; i < animRects.size(); i++) {
			m.setColor(animRects[i].col);
			m.drawRectangle(animRects[i].pos.x, animRects[i].pos.y, 20, 20);

			animRects[i].pos.x += animRects[i].dir.x;
			animRects[i].pos.y += animRects[i].dir.y;
			if (animRects[i].pos.x < 0 || animRects[i].pos.x > 50) animRects[i].dir.x = -animRects[i].dir.x;
			if (animRects[i].pos.y < 0 || animRects[i].pos.y > 50) animRects[i].dir.y = -animRects[i].dir.y;
		}
		m.popStyle();
		m.endFbo(murFbo);

		m.enableAlphaBlending();
		m.pushMatrix();
		m.pushStyle();
		m.translate(260, 250, 0);

		m.bindShader(&murShaderBlur);
		murShaderBlur.setUniform1f("blurAmount", 3);
		murShaderBlur.setUniform2f("resolution", murFbo.getWidth(), murFbo.getHeight());
		m.bind(murFbo, 0);
		m.drawRectangle(-35, -35, 70, 70);
		m.unbind(murFbo, 0);
		m.unbindShader();

		m.disableFill();
		m.drawRectangle(-35, -35, 70, 70);
		m.popStyle();
		m.popMatrix();
	}

private:
  
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
