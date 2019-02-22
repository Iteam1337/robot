const WebSocket = require('ws')

const PORT = 8080

const wss = new WebSocket.Server({ port: PORT }, () => {
  console.log(`Started WebSocket server ${PORT}`)
})

wss.on('connection', () => {
  console.log('Client connected to WS')
})

const sendTranslationToFrontend = (translation) => {
  wss.clients.forEach(ws => {
    console.log('Sending', JSON.stringify(translation))
    ws.send(
      JSON.stringify(translation)
    )
  })
}

module.exports = {
  sendTranslationToFrontend,
}
