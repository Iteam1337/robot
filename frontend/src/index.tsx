import { css, Global } from '@emotion/core'
import React from 'react'
import ReactDOM from 'react-dom'
import Settings from './Settings'

ReactDOM.render(
  <>
    <Global
      styles={css`
        * {
          box-sizing: border-box;
        }

        html {
          font-family: 'Inter', sans-serif;
        }

        body {
          margin: 0;
        }

        ul {
          list-style: none;
          margin: 0;
          padding: 0;
        }
      `}
    />
    <Settings path="/" />
  </>,
  document.getElementById('root')
)
