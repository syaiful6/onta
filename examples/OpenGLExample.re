open Sdl2;

open Onta;
/* open Onta.Draw; */
open Onta.UI;

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
  Style.[width(450), height(450), backgroundColor(Colors.black)];

module Sample = {
  let make = () => {
    <View style=containerStyle>
      <OpenGL
        style=outerBox
        render={(transform, _pctx) => {
          Gl.glClearColor(1.0, 0.0, 0.0, 1.0);
          let window = getActiveWindow();

          Onta.Draw.Text.drawString(
            ~backgroundColor=Colors.red,
            ~color=Colors.white,
            ~fontFamily="Roboto-Regular.ttf",
            ~fontSize=20,
            ~transform,
            ~x=25.,
            ~y=25.,
            ~window,
            "Hello!",
          );

          Onta.Draw.Shapes.drawRect(
            ~transform,
            ~color=Colors.green,
            ~x=25.,
            ~y=50.,
            ~width=10.,
            ~height=20.,
            (),
          );
        }}
        /* STRESS TEST:
           let iterations = 50000;
           let i = ref(0);
           while (i^ < iterations) {
             Onta.Draw.Shapes.drawRect(
               ~transform,
               ~color=Colors.green,
               ~x=25.,
               ~y=50.,
               ~width=10.,
               ~height=20.,
               (),
             );
             incr(i);
           };
           */
      />
    </View>;
  };
};

let render = () => <Sample />;
