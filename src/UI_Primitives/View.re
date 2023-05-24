open Onta_UI;
open React;

let%nativeComponent make =
                    (
                      ~onMouseDown=?,
                      ~onMouseMove=?,
                      ~onMouseUp=?,
                      ~onMouseWheel=?,
                      ~onMouseEnter=?,
                      ~onMouseLeave=?,
                      ~onMouseOver=?,
                      ~onMouseOut=?,
                      ~onBlur=?,
                      ~onFocus=?,
                      ~ref=?,
                      ~style=Style.emptyViewStyle,
                      ~tabindex=None,
                      ~children=React.empty,
                      ~onKeyDown=?,
                      ~onKeyUp=?,
                      ~onTextInput=?,
                      ~onTextEdit=?,
                      ~onDimensionsChanged=?,
                      (),
                      hooks,
                    ) => (
  {
    make: () => {
      let styles = Style.create(~style, ());
      let events =
        NodeEvents.make(
          ~ref?,
          ~onMouseDown?,
          ~onMouseMove?,
          ~onMouseUp?,
          ~onMouseWheel?,
          ~onMouseEnter?,
          ~onMouseLeave?,
          ~onMouseOver?,
          ~onMouseOut?,
          ~onBlur?,
          ~onFocus?,
          ~onKeyDown?,
          ~onKeyUp?,
          ~onTextEdit?,
          ~onTextInput?,
          ~onDimensionsChanged?,
          (),
        );
      let node = PrimitiveNodeFactory.get().createViewNode();
      node#setEvents(events);
      node#setStyle(styles);
      node#setTabIndex(tabindex);
      node;
    },
    configureInstance: (~isFirstRender as _, node) => {
      let styles = Style.create(~style, ());
      let events =
        NodeEvents.make(
          ~ref?,
          ~onMouseDown?,
          ~onMouseMove?,
          ~onMouseUp?,
          ~onMouseWheel?,
          ~onMouseEnter?,
          ~onMouseLeave?,
          ~onMouseOver?,
          ~onMouseOut?,
          ~onBlur?,
          ~onFocus?,
          ~onKeyDown?,
          ~onKeyUp?,
          ~onTextEdit?,
          ~onTextInput?,
          ~onDimensionsChanged?,
          (),
        );
      node#setEvents(events);
      node#setStyle(styles);
      node#setTabIndex(tabindex);
      node;
    },
    children,
    insertNode,
    deleteNode,
    moveNode,
  },
  hooks,
);
