open Onta;
open ExampleStubs;

module SliderExample = Slider;
module ScrollViewExample = ScrollView;

open Onta.UI;
open Onta.UI.Components;

let bgColor = Color.hex("#212733");
let activeBackgroundColor = Color.hex("#2E3440");
let inactiveBackgroundColor = Color.hex("#272d39");
let selectionHighlight = Color.hex("#90f7ff");

type example = {
  name: string,
  render: Window.t => React.element(React.node),
  source: string,
};

type state = {
  examples: list(example),
  selectedExample: string,
};

let state: state = {
  examples: [
    {name: "Animation", render: _w => Hello.render(), source: "Hello.re"},
    {
      name: "Spring",
      render: _w => SpringExample.render(),
      source: "SpringExample.re",
    },
    {
      name: "CanQuit",
      render: _ => CanQuitExample.render(),
      source: "CanQuit.re",
    },
    {
      name: "Button",
      render: _ => DefaultButton.render(),
      source: "DefaultButton.re",
    },
    {
      name: "Checkbox",
      render: _ => CheckboxExample.render(),
      source: "CheckboxExample.re",
    },
    {
      name: "Slider",
      render: _ => SliderExample.render(),
      source: "Slider.re",
    },
    {name: "Border", render: _ => Border.render(), source: "Border.re"},
    {
      name: "ScrollView",
      render: _ => ScrollViewExample.render(),
      source: "ScrollView.re",
    },
    {
      name: "Calculator",
      render: w => Calculator.render(w),
      source: "Calculator.re",
    },
    {name: "Flexbox", render: _ => Flexbox.render(), source: "Flexbox.re"},
    {
      name: "Box Shadow",
      render: _ => Boxshadow.render(),
      source: "Boxshadow.re",
    },
    {name: "Focus", render: _ => FocusExample.render(), source: "Focus.re"},
    {name: "Fonts", render: _ => FontsExample.render(), source: "Fonts.re"},
    {
      name: "Stopwatch",
      render: _ => Stopwatch.render(),
      source: "Stopwatch.re",
    },
    {
      name: "Native",
      render: _ => NativeExample.render(),
      source: "NativeExample.re",
    },
    {
      name: "Input",
      render: _ => InputExample.render(),
      source: "InputExample.re",
    },
    {
      name: "Radio Button",
      render: _ => RadioButtonExample.render(),
      source: "RadioButtonExample.re",
    },
    {
      name: "Game Of Life",
      render: _ => GameOfLife.render(),
      source: "GameOfLife.re",
    },
    {
      name: "Screen Capture",
      render: w => ScreenCapture.render(w),
      source: "ScreenCapture.re",
    },
    {
      name: "Tree View",
      render: w => TreeView.render(w),
      source: "TreeView.re",
    },
    {
      name: "Analog Clock",
      render: _ => AnalogClock.render(),
      source: "AnalogClock.re",
    },
    {
      name: "TodoMVC",
      render: _ => TodoExample.render(),
      source: "TodoExample.re",
    },
    {
      name: "Dropdown",
      render: _ => DropdownExample.render(),
      source: "DropdownExample.re",
    },
    {
      name: "Text",
      render: _w => TextExample.render(),
      source: "TextExample.re",
    },
    {
      name: "Hover Example",
      render: _ => HoverExample.render(),
      source: "HoverExample.re",
    },
    {
      name: "OpenGL Example",
      render: _ => OpenGLExample.render(),
      source: "OpenGLExample.re",
    },
    {
      name: "Zoom Example",
      render: _ => ZoomExample.render(),
      source: "ZoomExample.re",
    },
  ],
  selectedExample: "Animation",
};

let getExampleByName = (state: state, example: string) =>
  List.filter(x => String.equal(x.name, example), state.examples) |> List.hd;

let getSourceForSample = (state: state, example: string) =>
  getExampleByName(state, example) |> (s => s.source);

let noop = () => ();

let getRenderFunctionSelector: (state, Window.t) => React.element(React.node) =
  (s: state) => getExampleByName(s, s.selectedExample) |> (a => a.render);

module ExampleButton = {
  let make = (~isActive, ~name, ~onClick, ()) => {
    let highlightColor =
      isActive ? selectionHighlight : Colors.transparentWhite;

    let buttonOpacity = 1.0;
    let bgColor = isActive ? activeBackgroundColor : inactiveBackgroundColor;

    let wrapperStyle =
      Style.[
        borderLeft(~width=4, ~color=highlightColor),
        backgroundColor(bgColor),
      ];

    let textColor = isActive ? Colors.white : Colors.grey;
    let textHeaderStyle =
      Style.[
        color(textColor),
        fontFamily("Roboto-Regular.ttf"),
        fontSize(14),
        margin(16),
      ];

    <Opacity opacity=buttonOpacity>
      <Clickable style=wrapperStyle onClick>
        <Text style=textHeaderStyle text=name />
      </Clickable>
    </Opacity>;
  };
};

type action =
  | SelectExample(string);

let reducer = (action: action, state: state) =>
  switch (action) {
  | SelectExample(name) => {...state, selectedExample: name}
  };

module ExampleHost = {
  let%component make = (~win, ()) => {
    let%hook (state, dispatch) = Hooks.reducer(~initialState=state, reducer);

    let renderButton = (x: example) => {
      let isActive = String.equal(x.name, state.selectedExample);
      <ExampleButton
        isActive
        name={x.name}
        onClick={_ => {
          Window.setTitle(win, "Onta Example - " ++ x.name);

          let sourceFile = getSourceForSample(state, x.name);
          prerr_endline("SOURCE FILE: " ++ sourceFile);
          notifyExampleSwitched(sourceFile);
          dispatch(SelectExample(x.name));
          ();
        }}
      />;
    };

    let buttons = List.map(renderButton, state.examples);

    let exampleRender = getRenderFunctionSelector(state);
    let example = exampleRender(win);

    <View
      onMouseWheel={_evt => ()}
      style=Style.[
        position(`Absolute),
        justifyContent(`Center),
        alignItems(`Center),
        backgroundColor(bgColor),
        bottom(0),
        top(0),
        left(0),
        right(0),
        flexDirection(`Row),
      ]>
      <ScrollView
        style=Style.[
          position(`Absolute),
          top(0),
          left(0),
          width(175),
          bottom(0),
          backgroundColor(bgColor),
        ]>
        <View> {buttons |> React.listToElement} </View>
      </ScrollView>
      <View
        style=Style.[
          position(`Absolute),
          top(0),
          left(175),
          right(0),
          bottom(0),
          backgroundColor(activeBackgroundColor),
        ]>
        example
      </View>
    </View>;
  };
};

let init = app => {
  // let _ignore = Log.listen((_, msg) => print_endline(msg));

  let maximized = Environment.webGL;

  let windowWidth = 800;
  let windowHeight = 480;

  Console.log("Hello from example app");
  Console.log([1, 2, 3]);

  let win =
    App.createWindow(
      ~createOptions=
        WindowCreateOptions.create(
          ~width=windowWidth,
          ~height=windowHeight,
          ~maximized,
          ~icon=Some("revery-icon.png"),
          (),
        ),
      app,
      "Welcome to Onta!",
    );

  if (Environment.webGL) {
    Window.maximize(win);
    ();
  } else {
    Window.center(win);
    ();
  };

  let _ignore = UI.start(win, <ExampleHost win />);
  ();
};

let onIdle = () => print_endline("Example: idle callback triggered");
App.start(~onIdle, init);
