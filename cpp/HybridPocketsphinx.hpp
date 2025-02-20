#pragma once
#include <vector>
#include "HybridPocketsphinxSpec.hpp"

namespace margelo::nitro::pocketsphinx {
class HybridPocketsphinx : public HybridPocketsphinxSpec {
    public:
        HybridPocketsphinx() : HybridObject(TAG), HybridPocketsphinxSpec() {}
       
        double sum(double a, double b) override;
        std::string getPhonesFromAudio(const std::string &audioPath) override;
    };
} // namespace margelo::nitro::pocketsphinx
