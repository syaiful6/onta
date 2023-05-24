open Onta_Core;
open Onta_UI;
open Onta_UI_Primitives;

let make =
    (~children, ~color=Colors.transparentWhite, ~width as w, ~height as h, ()) => {
  let c = color;
  let style =
    Style.[width(w), height(h), overflow(`Hidden), backgroundColor(c)];

  <View style> ...children </View>;
};
