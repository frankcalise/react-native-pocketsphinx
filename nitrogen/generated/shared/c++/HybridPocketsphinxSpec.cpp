///
/// HybridPocketSphinxSpec.cpp
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/nitro
/// Copyright © 2025 Marc Rousavy @ Margelo
///

#include "HybridPocketSphinxSpec.hpp"

namespace margelo::nitro::pocketsphinx {

  void HybridPocketSphinxSpec::loadHybridMethods() {
    // load base methods/properties
    HybridObject::loadHybridMethods();
    // load custom methods/properties
    registerHybrids(this, [](Prototype& prototype) {
      prototype.registerHybridMethod("sum", &HybridPocketSphinxSpec::sum);
      prototype.registerHybridMethod("getPhonesFromAudio", &HybridPocketSphinxSpec::getPhonesFromAudio);
    });
  }

} // namespace margelo::nitro::pocketsphinx
