open Onta_UI;
open Onta_Core;
open Onta_UI_Primitives;

module Hooks = Onta_UI_Hooks;

type tickFunction = Time.t => unit;
let noop: tickFunction = _ => ();

let%component make =
              (
                ~children=React.empty,
                ~onTick=noop,
                ~tickRate=Time.seconds(1),
                ~name="<Ticker />",
                (),
              ) => {
  let%hook () =
    Hooks.effect(
      OnMount,
      () => {
        let dispose = Onta_Core.Tick.interval(~name, onTick, tickRate);

        Some(dispose);
      },
    );

  <View> children </View>;
};
