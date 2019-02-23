const speech = require('@google-cloud/speech')
const { Translate } = require('@google-cloud/translate')

const client = new speech.SpeechClient()
const translator = new Translate({
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

  const targetLanguages = ['en', 'es', 'fr', 'de', 'ru', 'ro', 'zh']
  const languagePromises = targetLanguages.map(language =>
    translator.translate(transcription, language)
  )

  const result = await Promise.all(languagePromises)
  const translations = result.map(([text], i) => ({
    text,
    language: targetLanguages[i],
  }))

  return {
    transcription,
    translations,
  }
}

module.exports = {
  translateAudio,
}
