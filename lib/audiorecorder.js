const AudioRecorder = require('node-audiorecorder')
const MemoryStream = require('memorystream')
const translationService = require('./translationService')
const { logTranslation } = require('./utils/log')
const { sendTranslation } = require('./utils/socket')

const audioRecorder = new AudioRecorder({
  program: process.platform === 'win32' ? 'sox' : 'rec',
  silence: 0.5,
  thresholdStart: 0,
  thresholdStop: 0.5,
  bits: 16,
  channels: 1,
  encoding: 'signed-integer',
  format: 'S16_LE',
  rate: 16000,
  type: 'wav',
  duration: 10,
})

const startRecording = () => {
  let buffer = null
  const stream = new MemoryStream(null, { readable: false })

  audioRecorder
    .start()
    .stream()
    .pipe(stream)

  // Don't record more than 10 seconds even if there is no silence.
  // Helps with noisy backgrounds and longwinded speakers
  const timeout = setTimeout(audioRecorder.stop, 10000)

  audioRecorder.stream().on('close', async () => {
    clearTimeout(timeout)
    const audioBytes = new Uint16Array(buffer)
    const translation = await translationService.translateAudio(audioBytes)

    if (translation.transcription) {
      logTranslation(translation)
      sendTranslation(translation)
    }

    // This could probably be converted into something less recursive
    // if heap becomes a problem...
    startRecording()
  })

  audioRecorder.stream().on('error', () => console.warn('Recording error.'))
  audioRecorder.stream().on('data', chunk => {
    buffer = !buffer ? new Buffer(chunk) : Buffer.concat([buffer, chunk])
  })
}

module.exports = {
  startRecording,
}
