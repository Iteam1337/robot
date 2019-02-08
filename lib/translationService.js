'use strict';

const speech = require('@google-cloud/speech');
const fs = require('fs');
const { Translate } = require('@google-cloud/translate');
// Your Google Cloud Platform project ID
const projectId = 'robot-229713';

// Creates a client
const client = new speech.SpeechClient();

const translateAudio = async (audioBytes) => {
  // The audio file's encoding, sample rate in hertz, and BCP-47 language code
  const audio = {
    content: audioBytes,
  };
  const config = {
    encoding: 'LINEAR',
    sampleRateHertz: 16000,
    languageCode: 'sv-SE',
  };
  const request = {
    audio: audio,
    config: config,
  };

  // Detects speech in the audio file
  const [response] = await client.recognize(request);
  const transcription = response.results
    .map(result => result.alternatives[0].transcript)
    .join('\n');

  const translate = new Translate({
    projectId: projectId,
  });

  // The target language
  const target = 'en';

  return translate
    .translate(transcription, target)
    .then(results => {
      const translation = results[0];
      
      return {
        transcription,
        translation
      };
    })
    .catch(err => {
      console.error('ERROR:', err);
    });
}

module.exports = {
  translateAudio
}