# client

## Run Project

```sh
npm install
npm start
# in another tab
npm run dev
```

## Known issues

If you get and error when running `npm run dev` containing the following

```
fpack: internal error, uncaught exception:
       FastpackUtil__Process.NotRunning("watchman --no-save-state -j --no-pretty -p")
```

you need to install `watchman`. More information can be found [here](https://facebook.github.io/watchman/docs/install.html)
