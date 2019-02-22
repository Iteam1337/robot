const speech = require('@google-cloud/speech')
const { Translate } = require('@google-cloud/translate')

const targetLanguage = 'en';

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

  const translations = []

  const targetLanguages = ['en', 'es', 'fr', 'de', 'ru', 'ro', 'zh']

  const promisesPromises = targetLanguages.reduce((acc, lang) => {
    acc.push(translate.translate(transcription, lang))
    return acc
  }, [])

  await Promise.all(promisesPromises).then(result => {
    result.forEach((trans, i) => {
      translations.push({
        text: trans[0],
        language: targetLanguages[i]
      })
    })
  })

  return {
    transcription,
    translations,
  }
}

module.exports = {
  translateAudio,
}
