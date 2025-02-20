///
/// HybridPocketsphinxSpec.hpp
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/nitro
/// Copyright © 2025 Marc Rousavy @ Margelo
///

#pragma once

#if __has_include(<NitroModules/HybridObject.hpp>)
#include <NitroModules/HybridObject.hpp>
#else
#error NitroModules cannot be found! Are you sure you installed NitroModules properly?
#endif





namespace margelo::nitro::pocketsphinx {

  using namespace margelo::nitro;

  /**
   * An abstract base class for `Pocketsphinx`
   * Inherit this class to create instances of `HybridPocketsphinxSpec` in C++.
   * You must explicitly call `HybridObject`'s constructor yourself, because it is virtual.
   * @example
   * ```cpp
   * class HybridPocketsphinx: public HybridPocketsphinxSpec {
   * public:
   *   HybridPocketsphinx(...): HybridObject(TAG) { ... }
   *   // ...
   * };
   * ```
   */
  class HybridPocketsphinxSpec: public virtual HybridObject {
    public:
      // Constructor
      explicit HybridPocketsphinxSpec(): HybridObject(TAG) { }

      // Destructor
      ~HybridPocketsphinxSpec() override = default;

    public:
      // Properties
      

    public:
      // Methods
      virtual double sum(double num1, double num2) = 0;

    protected:
      // Hybrid Setup
      void loadHybridMethods() override;

    protected:
      // Tag for logging
      static constexpr auto TAG = "Pocketsphinx";
  };

} // namespace margelo::nitro::pocketsphinx
