'use strict'

const express = require('express')
const bodyParser = require('body-parser')
const app = express()
const cors = require('cors')
const translationService = require('./lib/translationService')
const audiorecorder = require('./lib/audiorecorder')
const socket = require('./lib/utils/socket')

const webport = 7887

app.use(cors())
app.options('*', cors())
app.use(bodyParser.json({ limit: '50mb' }))
app.use(bodyParser.urlencoded())

app.post('/translate', async (req, res) => {
  console.log('incoming post')
  const translation = await translationService.translateAudio(req.body.audio)
  res.json(translation)
})

app.get('/', async (req, res) => {
  console.log('incoming get')
  res.json({ message: 'it works' })
})

app.get('/translations', async (req, res) => {
  let translations = await audiorecorder.getFinishedTranslations()
  console.log('got translations', translations)
  res.json(translations)
})

app.post('/receivetranslation', async (req, res) => {
  console.log(req.body);
  let translation = req.body;
  translation.origin = 'other';
  console.log('Adding', translation);
  audiorecorder.addTranslation(translation);

  res.send(200);
});

app.listen(webport, () => {
  console.log('http://localhost:' + webport, 'Motpart ansluter på', )
})

audiorecorder.startRecording()