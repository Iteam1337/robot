'use strict'

const speech = require('@google-cloud/speech')
const fs = require('fs')
const { Translate } = require('@google-cloud/translate')

const projectId = 'robot-229713'
const client = new speech.SpeechClient()

const translateAudio = async audioBytes => {
  const config = {
    encoding: 'LINEAR',
    sampleRateHertz: 16000,
    languageCode: 'sv-SE',
  }

  const [response] = await client.recognize({
    audio: {
      content: audioBytes,
    },
    config,
  })

  const transcription = response.results
    .map(result => result.alternatives[0].transcript)
    .join('\n')

  const translate = new Translate({
    projectId,
  })

  // The target language
  const target = 'en'

  return translate
    .translate(transcription, target)
    .then(results => {
      const translation = results[0]

      return {
        transcription,
        translation,
      }
    })
    .catch(err => {
      console.error('ERROR:', err)
    })
}

module.exports = {
  translateAudio,
}
