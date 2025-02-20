import { NitroModules } from 'react-native-nitro-modules'
import type { Pocketsphinx as PocketsphinxSpec } from './specs/pocketsphinx.nitro'

export const Pocketsphinx =
  NitroModules.createHybridObject<PocketsphinxSpec>('Pocketsphinx')