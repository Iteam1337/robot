const config = {
  audioRecorder: {
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
  },
}

module.exports = {
  audioRecorder: config.audioRecorder,
}
