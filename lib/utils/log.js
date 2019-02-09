const chalk = require('chalk')

const logTranslation = ({ transcription, translation }) => {
  console.log(`${chalk.green(translation)} (${transcription})`)
}

module.exports = {
  logTranslation,
}
