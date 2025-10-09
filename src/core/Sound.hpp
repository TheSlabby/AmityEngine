#pragma once
#include <AL/al.h>
#include <AL/alc.h>
#include <vector>
#include <string>
#include <sndfile.h>
#include <iostream>

namespace Core {

class Sound {
public:
    Sound(const std::string& path);
    ~Sound();

    void play() { alSourcePlay(source); }
    
    void setLooping(bool loop) { alSourcei(source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE); }
    void setPosition(float x, float y, float z) { alSource3f(source, AL_POSITION, x, y, z); }
    void setVelocity(float x, float y, float z) { alSource3f(source, AL_VELOCITY, x, y, z); }

    bool valid() { return m_valid; }

private:
    bool setup(const std::vector<short>& audioData, int channels, int sampleRate);
    ALuint buffer = 0;
    ALuint source = 0;
    bool m_valid = true;
};

}