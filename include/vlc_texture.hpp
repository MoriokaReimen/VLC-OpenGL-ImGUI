#pragma once
#include <string>
#include "vlcpp/vlc.hpp"
#include <memory>
#include <cinttypes>

using BYTE = uint8_t;


class VLC_Texture
{
    VLC::Instance instance_;
    VLC::Media media_;
    VLC::MediaPlayer media_player_;
    std::unique_ptr<uint8_t> pixels_;
    unsigned int texture_id_;

public:
    VLC_Texture();
    ~VLC_Texture();

    unsigned int get_texture_id() const;
    void update();

};
