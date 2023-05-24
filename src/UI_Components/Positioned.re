open Onta_UI;
open Onta_UI_Primitives;

let make = (~top=?, ~left=?, ~right=?, ~bottom=?, ~children, ()) => {
  let style =
    switch (top, left, right, bottom) {
    | (Some(t), Some(l), _, _) =>
      Style.[position(`Absolute), top(t), left(l)]
    | (Some(t), _, Some(r), _) =>
      Style.[position(`Absolute), top(t), right(r)]
    | (_, _, Some(r), Some(b)) =>
      Style.[position(`Absolute), bottom(b), right(r)]
    | (_, Some(l), _, Some(b)) =>
      Style.[position(`Absolute), bottom(b), left(l)]
    | _ => []
    };

  <View style> ...children </View>;
};
