const WebSocket = require('ws')

const wss = new WebSocket.Server({ port: 8080 })

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
