#pragma once
#include <vector>
#include "HybridPocketSphinxSpec.hpp"

namespace margelo::nitro::pocketsphinx {
class HybridPocketSphinx : public HybridPocketSphinxSpec {
    public:
    HybridPocketSphinx() : HybridObject(TAG), HybridPocketSphinxSpec() {}
       
        double sum(double a, double b) override;
        std::string getPhonesFromAudio(const std::string& audioPath, const std::string& acousticModelPath, const std::string& languageModelPath, const std::string& dictionaryPath) override;
    };
} // namespace margelo::nitro::pocketsphinx
