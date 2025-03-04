#include <pocketsphinx.h>
#include "HybridPocketSphinx.hpp"

#ifdef __ANDROID__
    #include <android/log.h>
#elif __APPLE__
    #include <os/log.h>
#endif

#include <errno.h>
#include <sys/stat.h>

bool fileExists(const std::string &path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

#define LOG_TAG "HybridPocketSphinx"
#ifdef defined(__ANDROID__)
    #define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
    #define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#elif defined(__APPLE__)
    #define LOGI(fmt, ...) os_log(OS_LOG_DEFAULT, "%{public}s INFO: " fmt, LOG_TAG, ##__VA_ARGS__)
    #define LOGE(fmt, ...) os_log_error(OS_LOG_DEFAULT, "%{public}s ERROR: " fmt, LOG_TAG, ##__VA_ARGS__)
#endif

namespace margelo::nitro::pocketsphinx {

std::string HybridPocketSphinx::getPhonesFromAudio(
    const std::string& audioPath,
    const std::string& acousticModelPath,
    const std::string& languageModelPath,
    const std::string& dictionaryPath
) {
    FILE *fh;
    size_t len;
    ps_config_t *config;

    /* Look for a single audio file as input parameter. */
    if ((fh = fopen(audioPath.c_str(), "rb")) == NULL) {
        LOGE("Failed to open audio file: %s. errno: %d, %s", audioPath.c_str(), errno, strerror(errno));
        throw std::runtime_error("Failed to open audio file");
    }

    /* Get the size of the input. */
    LOGI("Finding size of the input");
    if (fseek(fh, 0, SEEK_END) < 0) {
        throw std::runtime_error("Unable to find end of input file");

    }
    len = ftell(fh);
    rewind(fh);

    // Configure PocketSphinx
    LOGI("Initializing PocketSphinx");
    config =  ps_config_init(NULL);
    
    if (config == NULL) {
        throw std::runtime_error("PS config not initialized");
    }

    LOGI("Setting up config params");
    ps_default_search_args(config);

    // Set configuration parameters
    ps_config_set_str(config, "hmm", acousticModelPath.c_str());
    ps_config_set_str(config, "lm", languageModelPath.c_str());
    ps_config_set_str(config, "dict", dictionaryPath.c_str());
    
    LOGI("Loading audio file into PocketSphinx");
    if (ps_config_soundfile(config, fh, audioPath.c_str()) < 0) {
        throw std::runtime_error("Unsupported input file");
    }

    LOGI("Initializing PocketSphinx decoder");
    // Initialize PocketSphinx decoder
    ps_decoder_t *ps = ps_init(config);
    if (ps == NULL) {
        LOGE("Failed to initialize decoder. errno: %d, %s", errno, strerror(errno));
        throw std::runtime_error("Failed to initialize PocketSphinx decoder.");
    }

    LOGI("Start utterance processing");
    // Start utterance processing
    ps_start_utt(ps);
    int16_t buffer[512];
    size_t samplesRead;

    while ((samplesRead = fread(buffer, sizeof(int16_t), 512, fh)) > 0) {
        ps_process_raw(ps, buffer, samplesRead, FALSE, FALSE);
    }

    // End utterance processing
    ps_end_utt(ps);

    // Get segmentation for phonemes
    std::string words = "";
    ps_seg_t *seg = ps_seg_iter(ps);
    if (seg == NULL) {
        //std::cerr << "No segmentation available." << std::endl;
    } else {
        //std::cout << "Phonemes detected:\n";
        while (seg != NULL) {
            const char *word;
            int startFrame, endFrame;
            word = ps_seg_word(seg); // Get phoneme or word
            ps_seg_frames(seg, &startFrame, &endFrame); // Get start and end frame

            // build one string with all phonemes, comma separated
            LOGI("New word: %s", word);
            if (!words.empty()) {
                words += ", ";
            }
            words += word;

            seg = ps_seg_next(seg); // Move to the next segment
        }
    }
 
    LOGI("Cleaning up");
    // Clean up
    fclose(fh);
    ps_free(ps);
    ps_config_free(config);
    
    return words;
}

} // namespace margelo::nitro::pocketsphinx
