open Onta;
open Onta.UI;

let parentStyles =
  Style.[
    position(`Relative),
    flexGrow(1),
    alignItems(`Center),
    justifyContent(`Center),
    flexDirection(`Column),
  ];

let firstBoxStyle =
  Style.[
    backgroundColor(Colors.blue),
    position(`Relative),
    width(100),
    height(100),
  ];

let secondBoxStyle =
  Style.[
    backgroundColor(Colors.red),
    position(`Relative),
    width(100),
    height(100),
  ];

let firstShadow =
  Style.BoxShadow.make(
    ~yOffset=-10.,
    ~xOffset=0.,
    ~blurRadius=15.,
    ~color=Colors.black,
    ~spreadRadius=10.,
    (),
  );

let secondShadow =
  Style.BoxShadow.make(
    ~yOffset=10.,
    ~xOffset=-30.,
    ~blurRadius=20.,
    ~color=Colors.green,
    ~spreadRadius=0.,
    (),
  );

let render = () =>
  <View style=parentStyles>
    <Padding padding=30>
      <BoxShadow boxShadow=firstShadow>
        <View style=firstBoxStyle />
      </BoxShadow>
    </Padding>
    <Padding padding=30>
      <BoxShadow boxShadow=secondShadow>
        <View style=secondBoxStyle />
      </BoxShadow>
    </Padding>
  </View>;
