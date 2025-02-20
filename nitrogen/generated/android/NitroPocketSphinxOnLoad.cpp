///
/// NitroPocketSphinxOnLoad.cpp
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/nitro
/// Copyright © 2025 Marc Rousavy @ Margelo
///

#ifndef BUILDING_NITROPOCKETSPHINX_WITH_GENERATED_CMAKE_PROJECT
#error NitroPocketSphinxOnLoad.cpp is not being built with the autogenerated CMakeLists.txt project. Is a different CMakeLists.txt building this?
#endif

#include "NitroPocketSphinxOnLoad.hpp"

#include <jni.h>
#include <fbjni/fbjni.h>
#include <NitroModules/HybridObjectRegistry.hpp>

#include "HybridPocketSphinx.hpp"

namespace margelo::nitro::pocketsphinx {

int initialize(JavaVM* vm) {
  using namespace margelo::nitro;
  using namespace margelo::nitro::pocketsphinx;
  using namespace facebook;

  return facebook::jni::initialize(vm, [] {
    // Register native JNI methods
    

    // Register Nitro Hybrid Objects
    HybridObjectRegistry::registerHybridObjectConstructor(
      "PocketSphinx",
      []() -> std::shared_ptr<HybridObject> {
        static_assert(std::is_default_constructible_v<HybridPocketSphinx>,
                      "The HybridObject \"HybridPocketSphinx\" is not default-constructible! "
                      "Create a public constructor that takes zero arguments to be able to autolink this HybridObject.");
        return std::make_shared<HybridPocketSphinx>();
      }
    );
  });
}

} // namespace margelo::nitro::pocketsphinx
