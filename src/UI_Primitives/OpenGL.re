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
                      ~children=React.empty,
                      ~onKeyDown=?,
                      ~onKeyUp=?,
                      ~onDimensionsChanged=?,
                      ~render=?,
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
          ~onDimensionsChanged?,
          (),
        );
      let node = (new openGLNode)();
      node#setEvents(events);
      node#setStyle(styles);
      node#setRender(render);
      Obj.magic(node);
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
          ~onDimensionsChanged?,
          (),
        );
      let oglNode: openGLNode = Obj.magic(node);
      node#setEvents(events);
      node#setStyle(styles);
      oglNode#setRender(render);
      node;
    },
    children,
    insertNode,
    deleteNode,
    moveNode,
  },
  hooks,
);
