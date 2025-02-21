import { NitroModules } from 'react-native-nitro-modules'
import type { PocketSphinx as PocketSphinxSpec } from './specs/PocketSphinx.nitro'

export const PocketSphinx =
  NitroModules.createHybridObject<PocketSphinxSpec>('PocketSphinx')
