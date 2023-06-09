open Onta_UI;
open Onta_Core;
open Onta_UI_Primitives;

let noop = () => ();

let make =
    (
      ~title,
      ~onClick=noop,
      ~color as c=Colors.dodgerBlue,
      ~fontSize as size=40,
      ~width as w=300,
      ~height as h=100,
      ~disabled=false,
      ~tabindex=?,
      ~onFocus=?,
      ~onBlur=?,
      ~fontFamily as family="Roboto-Regular.ttf",
      (),
    ) =>
  <Clickable onClick={disabled ? noop : onClick} ?onFocus ?onBlur ?tabindex>
    <View
      style=Style.[
        position(`Relative),
        backgroundColor(disabled ? Colors.dimGrey : c),
        justifyContent(`Center),
        alignItems(`Center),
        border(~width=1, ~color=Colors.white),
        height(h),
        width(w),
      ]>
      <Text
        style=Style.[
          fontSize(size),
          fontFamily(family),
          color(Colors.white),
        ]
        text=title
      />
    </View>
  </Clickable>;
