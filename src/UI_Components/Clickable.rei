open Onta_UI;

type clickFunction = unit => unit;
type clickFunctionWithEvt = NodeEvents.mouseButtonEventParams => unit;

/**
{2 Description:}

This module provides a `<Clickable />` component, loosely inspired by the
`<Touchable />` component in React-Native, but geared towards the desktop.

{2 Usage:}

{[
<Clickable onClick={(_) => print_endline("Clicked!")}>
  <Container width=100 height=100 />
</Clickable>
]}
 */

let make:
  (
    ~key: Brisk_reconciler.Key.t=?,
    ~style: list(Onta_UI.Style.viewStyleProps)=?,
    ~onClick: clickFunction=?,
    ~onRightClick: clickFunction=?,
    ~onAnyClick: clickFunctionWithEvt=?,
    ~componentRef: Onta_UI.node => unit=?,
    ~onBlur: Onta_UI.NodeEvents.focusHandler=?,
    ~onFocus: Onta_UI.NodeEvents.focusHandler=?,
    ~tabindex: int=?,
    ~onKeyDown: Onta_UI.NodeEvents.keyDownHandler=?,
    ~onKeyUp: Onta_UI.NodeEvents.keyUpHandler=?,
    ~onTextEdit: Onta_UI.NodeEvents.textEditHandler=?,
    ~onTextInput: Onta_UI.NodeEvents.textInputHandler=?,
    ~children: Brisk_reconciler.element(Onta_UI.React.node),
    unit
  ) =>
  Brisk_reconciler.element(Onta_UI.React.node);
