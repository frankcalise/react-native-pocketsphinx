import { type HybridObject } from 'react-native-nitro-modules'

export interface PocketSphinx
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {
  getPhonesFromAudio(
    audioPath: string,
    acousticModelPath: string,
    languageModelPath: string,
    dictionaryPath: string
  ): string
}
