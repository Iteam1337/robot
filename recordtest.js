// Imports modules.
const fs = require(`fs`),
  path = require(`path`);
const AudioRecorder = require(`node-audiorecorder`);
// Constants.
const DIRECTORY = `examples-recordings`;
const MemoryStream = require('memorystream');
const translationService = require('./lib/translationService');

// Initialize recorder and file stream.
const audioRecorder = new AudioRecorder({
  program: process.platform === `win32` ? `sox` : `rec`,
  silence: 0.5,
  thresholdStart: 0,
  thresholdStop: 0.5,
  bits: 16,           // Sample size. (only for `rec` and `sox`)
  channels: 1,        // Channel count.
  encoding: `signed-integer`,  // Encoding type. (only for `rec` and `sox`)
  format: `S16_LE`,   // Encoding type. (only for `arecord`)
  rate: 16000,        // Sample rate.
  type: `wav`        // Format type.
});

// Create path to write recordings to.
if (!fs.existsSync(DIRECTORY)) {
  fs.mkdirSync(DIRECTORY);
}

function startRecording () {
  let buffer = null;

  // Create file path with random name.
  /*const fileName = path.join(DIRECTORY, Math.random().toString(36).replace(/[^a-z]+/g, ``).substr(0, 4).concat(`.wav`));
  console.log(`Writing new recording file at: `, fileName);*/

  // Create write stream.
  const stream = new MemoryStream(null, { readable: false });
//  const fileStream = fs.createWriteStream(fileName, { encoding: `binary` });
  // Start and write to the file.
  audioRecorder.start().stream().pipe(stream);

  // Log information on the following events
  audioRecorder.stream().on(`close`, function (code) {
    //console.log('data', buffer.length);
    const audioBytes = new Uint16Array(buffer);
    translationService.translateAudio(audioBytes)
      .then (translation => {
        if (translation.transcription) {
          console.log('\x1b[36m%s\x1b[0m', '(', translation.transcription, ')');
          console.log('\x1b[33m%s\x1b[0m', translation.translation);
        }
      });

    startRecording();
  });
  audioRecorder.stream().on(`end`, function () {
    //console.warn(`Recording ended.`);
    //console.log(buffer.length);
  });
  audioRecorder.stream().on(`error`, function () {
    console.warn(`Recording error.`);
  });
  // Write incoming data out the console.
  audioRecorder.stream().on('data', function(chunk) {
    buffer = (!buffer) ? new Buffer(chunk) : Buffer.concat([buffer, chunk]);
    //console.log('chunk', buffer.length);
  });
}

startRecording();

// Keep process alive.
process.stdin.resume();
console.warn(`Press ctrl+c to exit.`);