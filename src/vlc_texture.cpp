#include "vlc_texture.hpp"
#include <GL/gl.h>

constexpr unsigned int VIDEO_WIDTH = 1280;
constexpr unsigned int VIDEO_HEIGHT = 720;

VLC_Texture::VLC_Texture()
{
    char const *vlc_argv[] =
        {
            "--no-audio", /* skip any audio track */
            "--no-xlib",  /* tell VLC to not use Xlib */
            "-vvv",
            "--file-caching=0",
            "--network-caching=300",
            "--live-caching=0",
            "--sout-mux-caching=0",
            "--sout-display-delay=0"
        };
    int vlc_argc = sizeof(vlc_argv) / sizeof(*vlc_argv);
    instance_ = VLC::Instance(vlc_argc, vlc_argv);
    std::string path = "v4l2:///dev/video0";
    media_ = VLC::Media(instance_, path, VLC::Media::FromLocation);
    media_player_ = VLC::MediaPlayer(media_);
    media_player_.setVideoFormat("RV24", VIDEO_WIDTH, VIDEO_HEIGHT, VIDEO_WIDTH * 3);
    pixels_ = std::make_unique<BYTE[]>(VIDEO_HEIGHT * VIDEO_WIDTH * 3);

    media_player_.setVideoCallbacks(
        [this](void **pbuffer)
        {
            *pbuffer = this->pixels_.get();
            return nullptr;
        },
        [](void *, void *const *) {
        },
        nullptr);

    /* Create Texture */
    glGenTextures(1, &texture_id_);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

    glBindTexture(GL_TEXTURE_2D, 0);

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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, VIDEO_WIDTH, VIDEO_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels_.get());
    glBindTexture(GL_TEXTURE_2D, 0);
}
