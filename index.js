'use strict';

const express = require('express');
const bodyParser = require('body-parser');
const app = express();
const cors = require('cors');
const translationService = require('./lib/translationService');

app.use(cors());
app.options('*', cors());
app.use(bodyParser.json({ limit: '50mb' }));
app.use(bodyParser.urlencoded());

app.post('/translate', async (req, res) => {
  console.log('incoming post');
  const translation = await translationService.translateAudio(req.body.audio);
  res.json(translation);
});

app.get('/', async (req, res) => {
  console.log('incoming get');
  res.json({ message: 'it works' });
});

app.listen(7887, () => {
  console.log('http://localhost:7887')
});