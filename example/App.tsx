import React from 'react';
import {Text, View, StyleSheet, Button} from 'react-native';
import {PocketSphinx} from 'react-native-pocketsphinx';
import * as RNFS from '@dr.pogodin/react-native-fs';

const wavPath = `${RNFS.DocumentDirectoryPath}/hello-single.wav`;
const acousticModelPath = `${RNFS.DocumentDirectoryPath}/en-us`;
const languageModelPath = `${RNFS.DocumentDirectoryPath}/en-us.lm.bin`;
const dictionaryPath = `${RNFS.DocumentDirectoryPath}/cmudict-en-us.dict`;

async function copyRecursive(source: string, destination: string) {
  console.log(`${source} => ${destination}`);
  // reads items from source directory
  const items = await RNFS.readDirAssets(source);

  // creates destination directory
  console.log(`Output directory: ${destination}`);
  await RNFS.mkdir(destination);

  // for each item
  await items.forEach(async item => {
    //  checks if it is a file
    console.log({item});
    if (item.isFile() === true) {
      console.log(`Input file: ${item.path}`);
      const destinationFile = destination + '/' + item.name;

      // copies file
      console.log(`Output file: ${destinationFile}`);
      await RNFS.copyFileAssets(item.path, destinationFile);
    } else {
      console.log(`Input directory: ${item.path}`);

      const subDirectory = source + '/' + item.name;
      const subDestinationDirectory = destination + '/' + item.name;

      await copyRecursive(subDirectory, subDestinationDirectory);
    }
  });
}

function App(): React.JSX.Element {
  const [result, setResult] = React.useState('');

  /**
   * Copy the files from the assets folder to the document directory on Android
   *
   * Ultimately we want to let the user download/select these model files, but they're just
   * embedded for the test app right now
   */
  const copyFiles = () => {
    RNFS.readDirAssets('custom/')
      .then(files => {
        console.log('Files in assets/model:', files);
        const wavFile = files.find(file => file.name === 'hello-single.wav');
        console.log({wavFile, isdir: wavFile?.isDirectory()});
        if (wavFile) {
          const normalizedPath = wavFile.path.replace(/\/\//g, '/');
          RNFS.copyFileAssets(normalizedPath, wavPath)
            .then(() => {
              console.log('Wav file copied to:', wavPath);
            })
            .catch(error => console.log(error));
        }
      })
      .catch(error => {
        console.error('Error reading assets folder:', error);
      });

    RNFS.readDirAssets('custom/model')
      .then(files => {
        console.log('Files in assets/model:', files);
        const dictFile = files.find(file => file.name === 'cmudict-en-us.dict');
        const langFile = files.find(file => file.name === 'en-us.lm.bin');

        if (dictFile) {
          const normalizedPath = dictFile.path.replace(/\/\//g, '/');
          RNFS.copyFileAssets(normalizedPath, dictionaryPath)
            .then(() => {
              console.log('dict file copied to:', dictionaryPath);
            })
            .catch(error => console.log(error));
        }

        if (langFile) {
          const normalizedPath = langFile.path.replace(/\/\//g, '/');
          RNFS.copyFileAssets(normalizedPath, languageModelPath)
            .then(() => {
              console.log('lang file copied to:', languageModelPath);
            })
            .catch(error => console.log(error));
        }
      })
      .catch(error => {
        console.error('Error reading assets folder:', error);
      });

    // Do the acoustic model
    copyRecursive('custom/model/en-us', acousticModelPath)
      .then(() => {
        console.log('acoustic file copied to:', acousticModelPath);
      })
      .catch(error => console.log('here', error));
  };

  const readDocsDir = () => {
    RNFS.readDir(RNFS.DocumentDirectoryPath) // On Android, use "RNFS.DocumentDirectoryPath" (MainBundlePath is not defined)
      .then(result => {
        console.log('GOT RESULT', result);

        // stat the first file
        return Promise.all([RNFS.stat(result[0].path), result[0].path]);
      })
      .then(statResult => {
        if (statResult[0].isFile()) {
          // if we have a file, read it
          return RNFS.readFile(statResult[1], 'utf8');
        }

        return 'no file';
      })
      .catch(err => {
        console.log(err.message, err.code);
      });

    // read acoustic model dir
    RNFS.readDir(acousticModelPath)
      .then(result => {
        console.log(`acoustic model dir (${acousticModelPath}) RESULT`, result);

        // stat the first file
        return Promise.all([RNFS.stat(result[0].path), result[0].path]);
      })
      .then(statResult => {
        if (statResult[0].isFile()) {
          // if we have a file, read it
          return RNFS.readFile(statResult[1], 'utf8');
        }

        return 'no file';
      })

      .catch(err => {
        console.log(err.message, err.code);
      });
  };

  const getPhones = () => {
    try {
      const wavPath = `${RNFS.DocumentDirectoryPath}/hello-single.wav`;
      const result = PocketSphinx.getPhonesFromAudio(
        wavPath,
        acousticModelPath,
        languageModelPath,
        dictionaryPath,
      );
      setResult(result);
    } catch (e) {
      console.log('Error:', e);
    }
  };

  return (
    <View style={styles.container}>
      <Text style={styles.text}>Testing PocketSphinx!</Text>
      <Button title="Copy files" onPress={copyFiles} />
      <Button title="Read docs dir" onPress={readDocsDir} />
      <Button title="Get phones from audio" onPress={getPhones} />
      <Text>Result from hello-single.wav: {result}</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    gap: 10,
  },
  text: {
    fontSize: 40,
    color: 'green',
    textAlign: 'center',
  },
});

export default App;
