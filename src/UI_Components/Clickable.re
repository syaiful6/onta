/*
 * Clickable.re
 *
 * This module provides a `<Clickable />` component, loosely inspired by the
 * `<Touchable />` component in React-Native, but geared towards the desktop.
 */

open Onta_UI;
open Onta_Core;
open Onta_Math;
open Onta_UI_Primitives;

module Hooks = Onta_UI_Hooks;

type clickFunction = unit => unit;
type clickFunctionWithEvt = NodeEvents.mouseButtonEventParams => unit;
let noop = () => ();
let noopEvt = _evt => ();

let isMouseInsideRef = (ref: node, mouseX: float, mouseY: float) => {
  let clickableDimensions: BoundingBox2d.t = ref#getBoundingBoxClipped();
  let pointVec = Vec2.create(mouseX, mouseY);
  BoundingBox2d.isPointInside(clickableDimensions, pointVec);
};

let%component make =
              (
                ~style=[],
                ~onClick: clickFunction=noop,
                ~onRightClick: clickFunction=noop,
                ~onAnyClick: clickFunctionWithEvt=noopEvt,
                ~componentRef=?,
                ~onBlur=?,
                ~onFocus=?,
                ~tabindex=0,
                ~onKeyDown=?,
                ~onKeyUp=?,
                ~onTextEdit=?,
                ~onTextInput=?,
                ~children,
                (),
              ) => {
  let%hook (clickableRef, setClickableRefOption) = Hooks.state(None);

  let setClickableRef = r => {
    switch (componentRef) {
    | Some(fn) => fn(r)
    | None => ()
    };
    setClickableRefOption(_ => Some(r));
  };

  let onMouseUp = (mouseEvt: NodeEvents.mouseButtonEventParams) => {
    switch (clickableRef) {
    | Some(clickable) =>
      if (isMouseInsideRef(clickable, mouseEvt.mouseX, mouseEvt.mouseY)) {
        switch (mouseEvt.button) {
        | MouseButton.BUTTON_LEFT => onClick()
        | MouseButton.BUTTON_RIGHT => onRightClick()
        | _ => ()
        };
        onAnyClick(mouseEvt);
      }
    | _ => ()
    };

    /* TODO Releasing capture in here means
       if multiple buttons are pressed simutaneously
       there would a race condition
       Not sure we need fix it though */
    Mouse.releaseCapture();
    ();
  };

  let onMouseDown = (mouseEvt: NodeEvents.mouseButtonEventParams) => {
    switch (mouseEvt.button) {
    | MouseButton.BUTTON_LEFT =>
      Mouse.setCapture(~onMouseUp=evt => onMouseUp(evt), ())
    | _ => Mouse.setCapture(~onMouseUp=evt => onMouseUp(evt), ())
    };
  };

  let style = Style.[cursor(MouseCursors.pointer), ...style];

  <View
    style
    onMouseDown
    ?onBlur
    ?onFocus
    ?onKeyDown
    ?onKeyUp
    ?onTextEdit
    ?onTextInput
    tabindex={Some(tabindex)}
    ref={r => setClickableRef(r)}>
    children
  </View>;
};
