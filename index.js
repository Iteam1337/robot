'use strict'

const express = require('express')
const bodyParser = require('body-parser')
const app = express()
const cors = require('cors')
const translationService = require('./lib/translationService')
const audiorecorder = require('./lib/audiorecorder')
require('./lib/utils/socket')
const ifaces = require('os').networkInterfaces()
const rp = require('request-promise')

const webport = 7887
const receivingServer = process.argv[2]

const serveraddresses = []

Object.keys(ifaces).forEach(ifaceName => {
  const iface = ifaces[ifaceName]

  iface.forEach(setting => {
    if ('IPv4' === setting.family && setting.internal === false) {
      // skip over internal (i.e. 127.0.0.1) and non-ipv4 addresses
      serveraddresses.push(`http://${setting.address}:${webport}`)
    }
  })
})

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
  const translations = await audiorecorder.getFinishedTranslations()
  console.log('got translations', translations)
  res.json(translations)
})

app.post('/receivetranslation', async (req, res) => {
  const { translation } = req.body
  translation.origin = 'other'
  audiorecorder.addTranslation(translation)

  res.sendStatus(200)
})

app.listen(webport, () => {
  console.log(
    '\n\n==> Motpart ansluter på',
    serveraddresses.join(' eller '),
    '\n\n'
  )
})

audiorecorder.translationEvents.on('translation', translation => {
  if (translation.origin !== 'other' && receivingServer) {
    // todo: check for ip
    delete translation.origin
    const options = {
      method: 'POST',
      uri: `${receivingServer}/receivetranslation`,
      body: {
        translation,
      },
      json: true, // Automatically stringifies the body to JSON
    }

    rp(options)
      .then(result => {
        console.log('Translation sent', translation)
      })
      .catch(error => {
        console.error('Could not send translation', error)
      })
  }
})

audiorecorder.startRecording()
