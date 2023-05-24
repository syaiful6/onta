open Node;
open NodeEvents;

module BubbledEvent = {
  type bubbledEvent = {
    id: int,
    event,
    shouldPropagate: bool,
    defaultPrevented: bool,
    stopPropagation: unit => unit,
    preventDefault: unit => unit,
  };

  let generateId = () => {
    let id = ref(1);
    () => {
      id := id^ + 1;
      id^;
    };
  };

  let getId = generateId();
  let activeEvent = ref(None);

  let stopPropagation = (id, ()) =>
    switch (activeEvent^) {
    | Some(evt) =>
      if (id == evt.id) {
        activeEvent := Some({...evt, shouldPropagate: false});
      }
    | None => ()
    };

  let preventDefault = (id, ()) =>
    switch (activeEvent^) {
    | Some(evt) =>
      if (id == evt.id) {
        activeEvent := Some({...evt, defaultPrevented: true});
      }
    | None => ()
    };

  let make = event => {
    let id = getId();
    let wrappedEvent =
      Some({
        id,
        event,
        shouldPropagate: true,
        defaultPrevented: false,
        stopPropagation: stopPropagation(id),
        preventDefault: preventDefault(id),
      });

    activeEvent := wrappedEvent;
    wrappedEvent;
  };
};

let isNodeImpacted = (n, pos) => n#hitTest(pos);

let rec getFirstFocusable = (node: node, pos) =>
  if (!isNodeImpacted(node, pos)) {
    None;
  } else if (node#canBeFocused()) {
    Some(node);
  } else if (List.length(node#getChildren()) !== 0) {
    checkChildren(node#getChildren(), pos);
  } else {
    None;
  }
and checkChildren = (children, pos) =>
  switch (children) {
  | [] => None
  | [x, ...xs] =>
    switch (getFirstFocusable(x, pos)) {
    | Some(node) => Some(node)
    | None => checkChildren(xs, pos)
    }
  };

type pointerEventMode =
  | Default
  | Ignore;

let getTopMostNode = (node: node, pos) => {
  open Style;

  let rec f = (node: node, pointerEventMode) => {
    let style = node#getStyle();

    if (!isNodeImpacted(node, pos)) {
      None;
    } else {
      let mode =
        switch (style.pointerEvents) {
        | PointerEvents.Allow => Default
        | PointerEvents.Ignore => Ignore
        | PointerEvents.Default => pointerEventMode
        };

      let ignored = mode == Ignore;

      let revChildren = List.rev(node#getChildren());
      let ret =
        switch (revChildren) {
        | [] => ignored ? None : Some(node)
        | children =>
          List.fold_left(
            (prev, curr) =>
              switch (prev) {
              | Some(v) => Some(v)
              | None => f(curr, mode)
              },
            None,
            children,
          )
        };

      switch (ret) {
      | None => ignored ? None : Some(node)
      | Some(v) => Some(v)
      };
    };
  };

  let ret: option(node) = f(node, Default);
  ret;
};

let rec traverseHeirarchy = (node: node, bubbled) =>
  BubbledEvent.(
    /*
     track if default prevent or propagation stopped per node
     stop traversing node hierarchy if stop propagation is called
      */
    if (bubbled.shouldPropagate) {
      node#handleEvent(bubbled.event);
      let parent = node#getParent();
      switch (parent) {
      | Some(parent) => traverseHeirarchy(parent, bubbled)
      | None => ()
      };
    }
  );

let bubble = (node, event: event) => {
  /* Wrap event with preventDefault and stopPropagation */
  let evt = BubbledEvent.make(event);
  switch (evt) {
  | Some(e) => traverseHeirarchy(node, e)
  | None => ()
  };
};
