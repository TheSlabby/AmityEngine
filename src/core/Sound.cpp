#include "Sound.hpp"

namespace Core {

Sound::Sound(const std::string& path) {
    SF_INFO sfinfo;
    SNDFILE* sndfile = sf_open(path.c_str(), SFM_READ, &sfinfo);

    if (!sndfile)
        std::cerr << "couldnt load audio file: " << path << std::endl;
    
    std::vector<short> audioData(sfinfo.frames * sfinfo.channels);
    sf_readf_short(sndfile, audioData.data(), sfinfo.frames);
    sf_close(sndfile);

    setup(audioData, sfinfo.channels, sfinfo.samplerate);
}

void Sound::setup(const std::vector<short>& audioData, int channels, int sampleRate)
{
    ALenum format;
    if (channels == 1)
        format = AL_FORMAT_MONO16;
    else if (channels == 2)
        format = AL_FORMAT_STEREO16;
    else
    {
        std::cerr << "unsupported num audio channels: " << channels << std::endl;
        return;
    }

    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, audioData.data(), audioData.size() * sizeof(short), sampleRate);
    
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);

}

Sound::~Sound()
{
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);

}


}