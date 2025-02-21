#include <pocketsphinx.h>
#include "HybridPocketSphinx.hpp"

namespace margelo::nitro::pocketsphinx {

double HybridPocketSphinx::sum(double a, double b) {
    return a + b;
}

std::string HybridPocketSphinx::getPhonesFromAudio(const std::string &audioPath) {
    ps_config_t *config;
    config =  ps_config_init(NULL);
    
    if (config == NULL) {
        return "Error calling ps_config_init";
    } else {
        ps_config_free(config);
    }

    return "ps_config_init call worked!";
}

} // namespace margelo::nitro::pocketsphinx
