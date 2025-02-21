#include <jni.h>
#include "NitroPocketSphinxOnLoad.hpp"

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void*) {
  return margelo::nitro::pocketsphinx::initialize(vm);
}
