open Onta_Core;
open Onta_UI;
open Onta_UI_Primitives;

let make =
    (
      ~children=React.empty,
      ~color=Colors.transparentWhite,
      ~width as w,
      ~height as h,
      (),
    ) => {
  let c = color;
  let style = Style.[width(w), height(h), backgroundColor(c)];

  <View style> children </View>;
};
