#include "vlc_texture.hpp"
#include <GL/gl.h>


VLC_Texture::VLC_Texture()
{
    instance_ = VLC::Instance();
    std::string path = "/dev/video0";
    media_ = VLC::Media(instance_, path, VLC::Media::FromPath);
    media_player_ = VLC::MediaPlayer(media_);
    media_player_.setVideoFormat("NV24", 600, 800, 800 * 3);
    pixels_ = std::make_unique<BYTE>(600 * 800 * 3);
    media_player_.setVideoCallbacks(
        [this](void** pbuffer)
        {
            *pbuffer = this->pixels_.get();
            return nullptr;
        },
        [](void*, void* const*)
        {
        },
        nullptr);

    /* Create Texture */
    glGenTextures(1, &texture_id_);

    media_player_.play();
}

VLC_Texture::~VLC_Texture()
{
    media_player_.stop();
    glDeleteTextures(1, &texture_id_);
}

unsigned int VLC_Texture::get_texture_id() const
{
    return texture_id_;
}

void VLC_Texture::update()
{
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels_.get());
    glBindTexture(GL_TEXTURE_2D, 0);

}
