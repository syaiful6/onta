open Onta_UI.React.Hooks;

module Time = Onta_Core.Time;

let tick:
  (
    ~tickRate: Time.t=?,
    ~name: string,
    Time.t => unit,
    t((ref(Time.t => unit), Effect.t(Effect.onMount)) => 'a, 'b)
  ) =>
  (unit, t('a, 'b));