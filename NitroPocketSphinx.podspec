require "json"

package = JSON.parse(File.read(File.join(__dir__, "package.json")))

Pod::Spec.new do |s|
  s.name         = "NitroPocketSphinx"
  s.version      = package["version"]
  s.summary      = package["description"]
  s.homepage     = package["homepage"]
  s.license      = package["license"]
  s.authors      = package["author"]

  s.platforms    = { :ios => min_ios_version_supported, :visionos => 1.0 }
  s.source       = { :git => "https://github.com/frankcalise/react-native-pocketsphinx.git", :tag => "#{s.version}" }

  # add the libpocketsphinx.xcframework to the podspec
  
  s.public_header_files = [
    "cpp/libpocketsphinx/**/*.h"
  ]
  s.vendored_frameworks = "ios/libpocketsphinx.xcframework"
  s.static_framework = true
  
  s.source_files = [
    # Implementation (Swift)
    "ios/**/*.{swift}",
    # Autolinking/Registration (Objective-C++)
    "ios/**/*.{m,mm}",
    # Implementation (C++ objects)
    "cpp/**/*.{hpp,cpp,h}"
  ]

  s.pod_target_xcconfig = {
    # C++ compiler flags, mainly for folly.
    "GCC_PREPROCESSOR_DEFINITIONS" => "$(inherited) FOLLY_NO_CONFIG FOLLY_CFG_NO_COROUTINES",
    "SWIFT_INCLUDE_PATHS" => "$(PODS_TARGET_SRCROOT)/cpp",
    "HEADER_SEARCH_PATHS" => "$(inherited) $(PODS_TARGET_SRCROOT)/cpp/libpocketsphinx $(PODS_TARGET_SRCROOT)/cpp/libpocketsphinx/pocketsphinx",
  }


  load 'nitrogen/generated/ios/NitroPocketSphinx+autolinking.rb'
  add_nitrogen_files(s)

  s.dependency 'React-jsi'
  s.dependency 'React-callinvoker'
  install_modules_dependencies(s)
end
