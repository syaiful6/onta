open Onta_UI;
open Onta_UI_Primitives;

let make = (~children=React.empty, ()) => {
  let style =
    Style.[
      flexDirection(`Row),
      alignItems(`Stretch),
      justifyContent(`Center),
    ];

  <View style> children </View>;
};
