// See https://github.com/notnullnotvoid/msf_gif/blob/7829c8f439d013deeb54eba94761403e1da2a960/msf_gif.h#L4
#define MSF_GIF_IMPL
#include "msf_gif.h"

#include "../../World.hpp"
#include "Application.hpp"
#include "GifPainter.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>

Application::Application(const char* name)
    :buffer{1280, 960}{

    if (msf_gif_begin(&gif, int(buffer.width()), int(buffer.height())) == 0) {
        throw std::logic_error("GifRenderApp::msf_gif_begin failed");
    }
}

void Application::run(World& world) {
    const double scale = 0.2;
    const double step = 0.03;

    std::cout << "Render animation ..." << std::endl;

    for (double time = 0.; time < 10.; /**/) {
        world.update(step);
        GifPainter painter(buffer,
                           Point(buffer.width() / 2., buffer.height() / 2),
                           scale);
        world.show(painter);

        time += step;
        const double frameDelayCoef = time < 10. ? 100. : 10000.;

        if (msf_gif_frame(&gif, const_cast<uint8_t*>(buffer.data()),
                      step * frameDelayCoef, 16, buffer.width() * 4) == 0) {
            throw std::logic_error("GifRenderApp::msf_gif_frame failed");
        }
    }
    MsfGifResult result = msf_gif_end(&gif);
    if (result.data) {
        std::cout << "Save animation to file ..." << std::endl;
        std::ofstream("animation.gif", std::ios::binary)
            .write(static_cast<const char*>(result.data), result.dataSize);
    } else {
        throw std::logic_error("GifRenderApp::msf_gif_end return nodata");
    }
    msf_gif_free(result);
}
