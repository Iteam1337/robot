const WebSocket = require('ws')

const PORT = 8080

const wss = new WebSocket.Server({ port: PORT }, () => {
  console.log(`Started WebSocket server ${PORT}`)
})

wss.on('connection', () => {
  console.log('Client connected to WS')
})

const sendTranslation = ({ transcription, translation }) => {
  wss.clients.forEach(ws => {
    ws.send(
      JSON.stringify({
        timestamp: Date.now(),
        transcription,
        translation,
      })
    )
  })
}

module.exports = {
  sendTranslation,
}
