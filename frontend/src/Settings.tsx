import styled from '@emotion/styled'
import { RouteComponentProps } from '@reach/router'
import * as React from 'react'
import Dropdown from './Dropdown'

interface TranslationResponse {
  timestamp: number
  transcription: string
  translation: string
}

const Wrap = styled.div`
  padding: 40px;
`

const Dropdowns = styled.div`
  position: fixed;
  right: 40px;
  top: 40px;
`

const Translate = styled.ul`
  align-items: center;
  display: flex;
  flex-direction: column;
  height: 100vh;
  justify-content: center;
`

const Spoken = styled.div`
  color: hsl(175, 34%, 10%);
  font-size: 16px;
  font-weight: 400;
  margin-top: 10px;
`

const Response = styled.div`
  color: hsl(175, 34%, 50%);
  font-size: 60px;
  font-weight: 700;
`

const languages = ['en-US', 'sv-SE']

const Settings: React.FC<RouteComponentProps> = () => {
  const [input, setInput] = React.useState('')
  const [output, setOutput] = React.useState('')
  const [response, setResponse] = React.useState<TranslationResponse[]>([])

  const fetchTranslation = async () => {
    try {
      const resp = await fetch('http://localhost:7887/translations')
      const data = await resp.json()

      setResponse([...response, ...data])
    } catch {
      // nothing
    }
  }

  React.useEffect(() => {
    const interval = setInterval(fetchTranslation, 2000)
    return () => clearInterval(interval)
  }, [])

  return (
    <Wrap>
      <Dropdowns>
        <Dropdown
          name="input"
          onChange={setInput}
          options={languages}
          value={input}
        />
        <Dropdown
          name="output"
          onChange={setOutput}
          options={languages}
          value={output}
        />
      </Dropdowns>

      <Translate>
        {response.map(({ transcription, timestamp, translation }) => {
          return (
            <li key={timestamp}>
              <Response>{translation}</Response>
              <Spoken>{transcription}</Spoken>
            </li>
          )
        })}
      </Translate>
    </Wrap>
  )
}

export default Settings
