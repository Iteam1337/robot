# 🤖
Real-time speech translator

## Google credentials
Don't forget to put the credentials file in the project directory with the default name (robot-9b190e317393.json)

## SoX
Audio recorder requires you to install SoX and it must be available in your $PATH.

### For Linux
```
sudo apt-get install sox libsox-fmt-all
```

### For MacOS
```
brew install sox
```

### For Windows
[Download the binaries](http://sourceforge.net/projects/sox/files/latest/download)

## Running the project 

### Starting the server

in ./
1. Put your api-credentials in robot-9b190e317393.json
2. npm install
3. npm start http://counterpartserver:port

(you don't need to specify a counterpart server if you just want to use it locally)

### Starting the frontend

cd ./client

1. $:>npm install
2. $:>npm start
3. Open new shell/tab
4. $:>npm run server
5. Browse to http://localhost:4000


