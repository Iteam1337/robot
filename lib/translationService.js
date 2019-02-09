const speech = require('@google-cloud/speech')
const { Translate } = require('@google-cloud/translate')

const client = new speech.SpeechClient()
const translate = new Translate({
  projectId: 'robot-229713',
})

const translateAudio = async content => {
  const [response] = await client.recognize({
    audio: {
      content,
    },
    config: {
      encoding: 'LINEAR',
      sampleRateHertz: 16000,
      languageCode: 'sv-SE',
    },
  })

  const transcription = response.results
    .map(({ alternatives: [first] }) => first.transcript)
    .join('\n')

  const [translation] = await translate.translate(transcription, 'en')

  return {
    transcription,
    translation,
  }
}

module.exports = {
  translateAudio,
}
