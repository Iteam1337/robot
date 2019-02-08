import * as React from 'react'
import styled from '@emotion/styled'

interface DropdownProps {
  name: string
  onChange: (value: string) => void
  options: string[]
  value: string
}

const Select = styled.select`
  font-size: 16px;
  padding: 10px;
`

const Dropdown: React.FC<DropdownProps> = ({
  name,
  onChange,
  options,
  value,
}) => {
  return (
    <Select
      name={name}
      onChange={e => onChange(e.currentTarget.value)}
      value={value}
    >
      <option value="">Select a language</option>
      {options.map(opt => (
        <option key={opt} value={opt}>
          {opt}
        </option>
      ))}
    </Select>
  )
}

export default Dropdown
