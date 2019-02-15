const AudioRecorder = require('node-audiorecorder')
const MemoryStream = require('memorystream')
const translationService = require('./translationService')
const { logTranslation } = require('./utils/log')
const { sendTranslation } = require('./utils/socket')
const config = require('./config')

const audioRecorder = new AudioRecorder(config.audioRecorder)

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

    try {
      const translation = await translationService.translateAudio(audioBytes)

      if (translation.transcription) {
        logTranslation(translation)
        sendTranslation(translation)
      }

      // This could probably be converted into something less recursive
      // if heap becomes a problem...
      startRecording()
    } catch (error) {
      console.log(error)
    }
  })

  audioRecorder.stream().on('error', () => console.warn('Recording error.'))
  audioRecorder.stream().on('data', chunk => {
    buffer = !buffer ? new Buffer.from(chunk) : Buffer.concat([buffer, chunk])
  })
}

module.exports = {
  startRecording,
}
