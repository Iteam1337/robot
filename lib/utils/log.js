const chalk = require('chalk')

const logTranslation = ({ transcription, translation }) => {
  console.log(`${chalk.green(JSON.stringify(translation, null, 2))} (${transcription})`)
}

module.exports = {
  logTranslation,
}
