open Onta_UI;
open Onta_UI_Primitives;

let make = (~children=React.empty, ()) => {
  let style =
    Style.[flexGrow(1), justifyContent(`Center), alignItems(`Center)];

  <View style> children </View>;
};
