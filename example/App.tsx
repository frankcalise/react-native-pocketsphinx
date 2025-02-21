import React from 'react';
import {Text, View, StyleSheet} from 'react-native';
import {PocketSphinx} from 'react-native-pocketsphinx';

function App(): React.JSX.Element {
  return (
    <View style={styles.container}>
      <Text style={styles.text}>{PocketSphinx.sum(2, 1)}</Text>
      <Text style={styles.text}>
        {PocketSphinx.getPhonesFromAudio('path/to/audio')}
      </Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
  },
  text: {
    fontSize: 40,
    color: 'green',
  },
});

export default App;
