#ifndef VLC_TEXTURE
#define VLC_TEXTURE
/**
 * @file vlc_texture.hpp
 * @author MoriokaReimen
 * @brief
 * @version 0.1
 * @date 2022-07-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "vlcpp/vlc.hpp"
#include <string>
#include <memory>
#include <cinttypes>

/**< data type for BYTE data */
using BYTE = uint8_t;

/**
 * @brief VLC Texture class
 *
 */
class VLC_Texture
{
    VLC::Instance instance_;         /**< vlc instance data */
    VLC::MediaPlayer media_player_;  /**< vlc media player object */
    std::unique_ptr<BYTE[]> pixels_; /**< captured pixel data */
    unsigned int texture_id_;        /**< GL texture id */
    unsigned int video_width_;       /**< Captured video width */
    unsigned int video_height_;      /**< Captured video height */

public:
    VLC_Texture(const std::string& media_path, const unsigned int& width = 1280, const unsigned int height = 960);
    ~VLC_Texture();

    unsigned int get_texture_id() const;
    void update();
};

#endif /* VLC_TEXTURE */
