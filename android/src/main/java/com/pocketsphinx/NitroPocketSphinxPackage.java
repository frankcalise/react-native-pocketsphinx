package com.pocketsphinx;

import android.util.Log;

import androidx.annotation.Nullable;

import com.facebook.react.bridge.NativeModule;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.module.model.ReactModuleInfoProvider;
import com.facebook.react.TurboReactPackage;
import com.margelo.nitro.core.HybridObject;
import com.margelo.nitro.core.HybridObjectRegistry;
import com.margelo.nitro.pocketsphinx.NitroPocketSphinxOnLoad;


import java.util.HashMap;
import java.util.function.Supplier;

public class NitroPocketSphinxPackage extends TurboReactPackage {
  @Nullable
  @Override
  public NativeModule getModule(String name, ReactApplicationContext reactContext) {
    return null;
  }

  @Override
  public ReactModuleInfoProvider getReactModuleInfoProvider() {
    return () -> {
        return new HashMap<>();
    };
  }

  static {
    NitroPocketSphinxOnLoad.initializeNative();
  }
}
