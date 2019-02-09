// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE

import * as Block from "bs-platform/lib/es6/block.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as ReasonReact from "reason-react/lib/es6/src/ReasonReact.js";
import * as AppStyle$ReactTemplate from "./AppStyle.bs.js";
import * as Dropdown$ReactTemplate from "./Dropdown.bs.js";
import * as WebSocket$ReactTemplate from "./WebSocket.bs.js";

var component = ReasonReact.reducerComponent("App-ReactTemplate");

var languages = /* array */[
  "en-US",
  "sv-SE"
];

var socket = new WebSocket("ws://localhost:8080");

function make(_children) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */(function (self) {
              return socket.addEventListener("message", (function (data) {
                            var message = WebSocket$ReactTemplate.Decode[/* message */1](data);
                            var translation = WebSocket$ReactTemplate.Decode[/* translation */0](message);
                            return Curry._1(self[/* send */3], /* UpdateTranslation */Block.__(0, [translation]));
                          }));
            }),
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (param) {
              var send = param[/* send */3];
              var state = param[/* state */1];
              return React.createElement("div", {
                          className: AppStyle$ReactTemplate.wrap
                        }, React.createElement("div", {
                              className: AppStyle$ReactTemplate.dropdowns
                            }, ReasonReact.element(undefined, undefined, Dropdown$ReactTemplate.make((function (v) {
                                        return Curry._1(send, /* UpdateInput */Block.__(1, [v]));
                                      }), languages, state[/* input */0], /* array */[])), ReasonReact.element(undefined, undefined, Dropdown$ReactTemplate.make((function (v) {
                                        return Curry._1(send, /* UpdateOutput */Block.__(2, [v]));
                                      }), languages, state[/* output */1], /* array */[]))), React.createElement("ul", {
                              className: AppStyle$ReactTemplate.translate
                            }, React.createElement("li", {
                                  key: String(state[/* translation */2][/* timestamp */0])
                                }, React.createElement("div", {
                                      className: AppStyle$ReactTemplate.response
                                    }, state[/* translation */2][/* translation */1]), React.createElement("div", {
                                      className: AppStyle$ReactTemplate.spoken
                                    }, state[/* translation */2][/* transcription */2]))));
            }),
          /* initialState */(function (param) {
              return /* record */[
                      /* input */"",
                      /* output */"",
                      /* translation : record */[
                        /* timestamp */0,
                        /* translation */"",
                        /* transcription */""
                      ]
                    ];
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, state) {
              var exit = 0;
              switch (action.tag | 0) {
                case 0 : 
                    return /* Update */Block.__(0, [/* record */[
                                /* input */state[/* input */0],
                                /* output */state[/* output */1],
                                /* translation */action[0]
                              ]]);
                case 1 : 
                case 2 : 
                    exit = 1;
                    break;
                
              }
              if (exit === 1) {
                return /* Update */Block.__(0, [/* record */[
                            /* input */action[0],
                            /* output */state[/* output */1],
                            /* translation */state[/* translation */2]
                          ]]);
              }
              
            }),
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

export {
  component ,
  languages ,
  socket ,
  make ,
  
}
/* component Not a pure module */