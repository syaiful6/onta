open Onta_UI;
open Onta_UI_Primitives;

let make = (~children, ()) => {
  let style =
    Style.[
      flexDirection(`Column),
      alignItems(`Stretch),
      justifyContent(`Center),
    ];

  <View style> ...children </View>;
};
