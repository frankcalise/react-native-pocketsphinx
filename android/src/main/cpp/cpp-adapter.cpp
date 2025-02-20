#include <jni.h>
#include "PocketsphinxOnLoad.hpp"

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void*) {
  return margelo::nitro::pocketsphinx::initialize(vm);
}
