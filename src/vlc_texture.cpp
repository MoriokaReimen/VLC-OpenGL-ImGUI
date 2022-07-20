/**
 * @file vlc_texture.cpp
 * @author MoriokaReimen
 * @brief VLC Texture class
 * @version 0.1
 * @date 2022-07-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "vlc_texture.hpp"
#ifdef WIN32
#include <glad/glad.h>
#endif
#include <GL/gl.h>

/**
 * @brief Construct a new vlc texture::vlc texture object
 * 
 * @param media_path path/url for media
 * @param width video width
 * @param height video height
 */
VLC_Texture::VLC_Texture(const std::string &media_path, const unsigned int &width, const unsigned int height)
    : video_width_(width), video_height_(height)
{
    /* Create  */
    char const *vlc_argv[] =
        {
            "--no-audio",            /* skip any audio track */
            "--no-xlib",             /* tell VLC to not use Xlib */
            "-vvv",                  /* Maximum verbosity */
            "--file-caching=1",      /* disable caching */
            "--network-caching=1", /* disable network caching */
            "--live-caching=1",      /* disable live caching */
            "--sout-mux-caching=1",  /* disable stream caching */
            "--sout-display-delay=1", /* disable display caching */
            "--ignore-config",
            "--clock-jitter=1",
            "--clock-synchro=1",
            "--intf=dummy",
            "--dshow-fps=20",
            "--screen-fps=10",
            "--h264-fps=10"
        };
    const int vlc_argc = sizeof(vlc_argv) / sizeof(*vlc_argv);
    instance_ = VLC::Instance(vlc_argc, vlc_argv);

    /* Create media */
    auto media_ = VLC::Media(instance_, media_path, VLC::Media::FromLocation);

    /* create media player */
    media_player_ = VLC::MediaPlayer(media_);
    media_player_.setVideoFormat("RV24", video_width_, video_height_, video_width_ * 3);
    pixels_ = std::make_unique<BYTE[]>(video_height_ * video_width_ * 3);
    media_player_.setVideoCallbacks(
        [this](void **pbuffer)
        {
            *pbuffer = this->pixels_.get();
            return nullptr;
        },
        [](void *, void *const *) {
        },
        nullptr);

    /* Create GL Texture */
    glGenTextures(1, &texture_id_);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);

    /* Start Capturing */
    media_player_.play();
}

/**
 * @brief Destroy the vlc texture::vlc texture object
 *
 */
VLC_Texture::~VLC_Texture()
{
    media_player_.stop();
    glDeleteTextures(1, &texture_id_);
}

/**
 * @brief get GL texture id
 *
 * @return texture id
 */
unsigned int VLC_Texture::get_texture_id() const
{
    return texture_id_;
}

/**
 * @brief update captured texture data
 *
 */
void VLC_Texture::update()
{
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, video_width_, video_height_, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels_.get());
    glBindTexture(GL_TEXTURE_2D, 0);
}
