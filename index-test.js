async function main() {
  // Imports the Google Cloud client library
  const speech = require('@google-cloud/speech');
  const fs = require('fs');
  const { Translate } = require('@google-cloud/translate');
  // Your Google Cloud Platform project ID
  const projectId = 'robot-229713';
  
  // Creates a client
  const client = new speech.SpeechClient();

  // The name of the audio file to transcribe
  const fileName = './scratched.flac';

  // Reads a local audio file and converts it to base64
  const file = fs.readFileSync(fileName);
  const audioBytes = file.toString('base64');

  // The audio file's encoding, sample rate in hertz, and BCP-47 language code
  const audio = {
    content: audioBytes,
  };
  const config = {
    encoding: 'LINEAR',
    sampleRateHertz: 32000,
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
  console.log(`Transcription: ${transcription}`);

  const translate = new Translate({
    projectId: projectId,
  });

  // The target language
  const target = 'sv';

  // Translates some text into Russian
  translate
    .translate(transcription, target)
    .then(results => {
      const translation = results[0];

      console.log(`Translation: ${translation}`);
    })
    .catch(err => {
      console.error('ERROR:', err);
    });
}
main().catch(console.error);
