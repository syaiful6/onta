open Onta;
open Onta.UI;
open Onta.UI.Components;

module SpringyLogo = {
  let make = (~width, ~onMouseDown, ~onMouseUp, ()) => {
    let intWidth = int_of_float(width);

    <View onMouseDown onMouseUp>
      <Image
        src="outrun-logo.png"
        style=Style.[
          width(intWidth),
          height(128),
          cursor(MouseCursors.pointer),
        ]
      />
    </View>;
  };
};

module SliderControl = {
  module Styles = {
    let sliderContainerStyle =
      Style.[
        margin(10),
        borderBottom(~width=1, ~color=Colors.darkGray),
        flexDirection(`Row),
        justifyContent(`Center),
        alignItems(`Center),
      ];

    let textStyle =
      Style.[
        color(Colors.white),
        width(100),
        fontFamily("Roboto-Regular.ttf"),
        fontSize(16),
        margin(14),
      ];
  };

  let float_rounded_string = v => v |> int_of_float |> string_of_int;

  let make =
      (~text, ~minimumValue, ~maximumValue, ~value, ~onValueChanged, ()) => {
    <View style=Styles.sliderContainerStyle>
      <Text style=Styles.textStyle text />
      <Slider
        onValueChanged={v => onValueChanged(v)}
        value
        minimumValue
        maximumValue
      />
      <Text
        style=Styles.textStyle
        text={"Value: " ++ float_rounded_string(value)}
      />
    </View>;
  };
};

module Example = {
  module Styles = {
    let containerStyle =
      Style.[
        flexGrow(1),
        justifyContent(`Center),
        alignItems(`Center),
        flexDirection(`Column),
      ];
  };
  let%component make = () => {
    let%hook (stiffness, setStiffness) = Hooks.state(160.);
    let%hook (damping, setDamping) = Hooks.state(10.);
    let%hook (targetPosition, setTargetPosition) =
      Hooks.reducer(~initialState=256.0, (value, _) => value);
    let%hook (logoWidth, setImmediately) =
      Hooks.spring(
        ~name="Spring",
        ~target=targetPosition,
        ~initialState=
          Spring.{
            value: 256.,
            velocity: 100.,
            acceleration: 0.,
            time: Time.now(),
          },
        ~restThreshold=1.0,
        Spring.Options.create(~damping, ~stiffness, ()),
      );
    let setImmediately = value => {
      setTargetPosition(value);
      setImmediately(value);
    };
    let onMouseDown = _ => {
      setTargetPosition(512.0);
    };
    let onMouseUp = _ => setTargetPosition(256.0);

    <Center>
      <Center> <SpringyLogo width=logoWidth onMouseDown onMouseUp /> </Center>
      <View style=Styles.containerStyle>
        <SliderControl
          text="Damping: "
          minimumValue=1.
          maximumValue=100.
          value=damping
          onValueChanged={v => setDamping(_ => v)}
        />
        <SliderControl
          text="Stiffness: "
          minimumValue=1.
          maximumValue=500.
          value=stiffness
          onValueChanged={v => setStiffness(_ => v)}
        />
        <SliderControl
          text="Width: "
          minimumValue=128.
          maximumValue=640.
          value=logoWidth
          onValueChanged={v => setImmediately(v)}
        />
      </View>
    </Center>;
  };
};

let render = () => <Example />;
