open Onta;
open Onta.UI;
open Onta.UI.Components;

let containerStyle =
  Style.[
    position(`Absolute),
    top(0),
    bottom(0),
    left(0),
    right(0),
    alignItems(`Center),
    justifyContent(`Center),
    flexDirection(`Column),
  ];

let outerBox =
  Style.[width(128), height(128), backgroundColor(Colors.black)];

let innerBox =
  Style.[
    width(450),
    height(450),
    backgroundColor(Color.rgba(0., 1., 0., 0.5)),
  ];

module Sample = {
  let%component make = () => {
    let%hook (bounce, setBounce) = Hooks.state(true);

    <View style=containerStyle>
      <Text
        text="Bounce"
        style=Style.[
          marginBottom(10),
          fontFamily("Roboto-Regular.ttf"),
          fontSize(20),
        ]
      />
      <Checkbox
        onChange={() => setBounce(isBounce => !isBounce)}
        checked=bounce
        style=Style.[marginBottom(10)]
      />
      <ScrollView style=outerBox bounce>
        <Image
          src="outrun-logo.png"
          /* Exercise the case in #579 */
          style=Style.[overflow(`Hidden), width(512), height(256)]
        />
        <Image
          src="outrun-logo.png"
          style=Style.[width(512), height(256)]
        />
        <Image
          src="outrun-logo.png"
          style=Style.[width(512), height(256)]
        />
      </ScrollView>
    </View>;
  };
};

let render = () => <Sample />;
