#include "ofMath.h"
#include "ofNoise.h"
#include "ofPolyline.h"
#include "ofRandomDistributions.h"

#include <float.h>

#ifndef TARGET_WIN32
	#include <sys/time.h>
#endif

//--------------------------------------------------
int ofNextPow2(int a) {
	// from nehe.gamedev.net lesson 43
	int rval = 1;
	while (rval < a)
		rval <<= 1;
	return rval;
}

//--------------------------------------------------
void ofSeedRandom() {
	of::random::Engine::destruct();
	of::random::Engine::construct();
}

//--------------------------------------------------
void ofSetRandomSeed(unsigned long new_seed) {
	of::random::seed(new_seed);
}

void ofSeedRandom(int val) {
	ofSetRandomSeed(val);
}

//--------------------------------------------------
float ofRandom(float max) {
	return of::random::uniform<float>(0, max);
}

//--------------------------------------------------
float ofRandom(float min, float max) {
	return of::random::uniform<float>(min, max);
}

//--------------------------------------------------
float ofRandomf() {
	return of::random::uniform<float>(-1, 1);
}

//--------------------------------------------------
float ofRandomuf() {
	return of::random::uniform<float>(0, 1);
}

//--------------------------------------------------
float ofNormalize(float value, float min, float max) {
	return ofClamp((value - min) / (max - min), 0, 1);
}

//check for division by zero???
//--------------------------------------------------
float ofMap(float value, float inputMin, float inputMax, float outputMin, float outputMax, bool clamp) {

	if (std::abs(inputMin - inputMax) < std::numeric_limits<float>::epsilon()) {
		return outputMin;
	} else {
		float outVal = ((value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin);

		if (clamp) {
			if (outputMax < outputMin) {
				if (outVal < outputMax)
					outVal = outputMax;
				else if (outVal > outputMin)
					outVal = outputMin;
			} else {
				if (outVal > outputMax)
					outVal = outputMax;
				else if (outVal < outputMin)
					outVal = outputMin;
			}
		}
		return outVal;
	}
}

//--------------------------------------------------
float ofDist(float x1, float y1, float x2, float y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

//--------------------------------------------------
float ofDist(float x1, float y1, float z1, float x2, float y2, float z2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2));
}

//--------------------------------------------------
float ofDistSquared(float x1, float y1, float x2, float y2) {
	return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

//--------------------------------------------------
float ofDistSquared(float x1, float y1, float z1, float x2, float y2, float z2) {
	return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2));
}

//--------------------------------------------------
float ofClamp(float value, float min, float max) {
	return value < min ? min : value > max ? max
										   : value;
}

//--------------------------------------------------
int ofSign(float n) {
	if (n > 0)
		return 1;
	else if (n < 0)
		return -1;
	else
		return 0;
}

//--------------------------------------------------
bool ofInRange(float t, float min, float max) {
	return t >= min && t <= max;
}

//--------------------------------------------------
float ofRadToDeg(float radians) {
	return glm::degrees(radians);
}

//--------------------------------------------------
float ofDegToRad(float degrees) {
	return glm::radians(degrees);
}

//--------------------------------------------------
float ofLerp(float start, float stop, float amt) {
	return start + (stop - start) * amt;
}

float ofWrap(float value, float from, float to) {
	// algorithm from http://stackoverflow.com/a/5852628/599884
	if (from > to) {
		std::swap(from, to);
	}
	float cycle = to - from;
	if (ofIsFloatEqual(cycle, 0.0f)) {
		return to;
	}
	return value - cycle * std::floor((value - from) / cycle);
}

//--------------------------------------------------
float ofWrapRadians(float angle, float from, float to) {
	return ofWrap(angle, from, to);
}

float ofWrapDegrees(float angle, float from, float to) {
	return ofWrap(angle, from, to);
}

//--------------------------------------------------
float ofLerpDegrees(float currentAngle, float targetAngle, float pct) {
	return currentAngle + ofAngleDifferenceDegrees(currentAngle, targetAngle) * pct;
}

//--------------------------------------------------
float ofLerpRadians(float currentAngle, float targetAngle, float pct) {
	return currentAngle + ofAngleDifferenceRadians(currentAngle, targetAngle) * pct;
}

//--------------------------------------------------
float ofNoise(float x) {
	return _slang_library_noise1(x) * 0.5f + 0.5f;
}

//--------------------------------------------------
float ofNoise(float x, float y) {
	return _slang_library_noise2(x, y) * 0.5f + 0.5f;
}

//--------------------------------------------------
float ofNoise(const glm::vec2 & p) {
	return ofNoise(p.x, p.y);
}

//--------------------------------------------------
float ofNoise(float x, float y, float z) {
	return _slang_library_noise3(x, y, z) * 0.5f + 0.5f;
}

//--------------------------------------------------
float ofNoise(const glm::vec3 & p) {
	return ofNoise(p.x, p.y, p.z);
}

//--------------------------------------------------
float ofNoise(float x, float y, float z, float w) {
	return _slang_library_noise4(x, y, z, w) * 0.5f + 0.5f;
}

//--------------------------------------------------
float ofNoise(const glm::vec4 & p) {
	return ofNoise(p.x, p.y, p.z, p.w);
}

//--------------------------------------------------
float ofSignedNoise(float x) {
	return _slang_library_noise1(x);
}

//--------------------------------------------------
float ofSignedNoise(float x, float y) {
	return _slang_library_noise2(x, y);
}

//--------------------------------------------------
float ofSignedNoise(const glm::vec2 & p) {
	return ofSignedNoise(p.x, p.y);
}

//--------------------------------------------------
float ofSignedNoise(float x, float y, float z) {
	return _slang_library_noise3(x, y, z);
}

//--------------------------------------------------
float ofSignedNoise(const glm::vec3 & p) {
	return ofSignedNoise(p.x, p.y, p.z);
}

//--------------------------------------------------
float ofSignedNoise(float x, float y, float z, float w) {
	return _slang_library_noise4(x, y, z, w);
}

//--------------------------------------------------
float ofSignedNoise(const glm::vec4 & p) {
	return ofSignedNoise(p.x, p.y, p.z, p.w);
}

//--------------------------------------------------
float ofAngleDifferenceDegrees(float currentAngle, float targetAngle) {
	return ofWrapDegrees(targetAngle - currentAngle);
}

//--------------------------------------------------
float ofAngleDifferenceRadians(float currentAngle, float targetAngle) {
	return ofWrapRadians(targetAngle - currentAngle);
}
