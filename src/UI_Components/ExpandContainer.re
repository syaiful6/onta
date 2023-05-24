open Onta_Core;
open Onta_UI;
open Onta_UI_Primitives;

let make = (~children, ~color=Colors.transparentWhite, ()) => {
  let c = color;
  let style = Style.[flexGrow(1), backgroundColor(c)];

  <View style> ...children </View>;
};
