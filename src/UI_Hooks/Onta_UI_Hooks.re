module SpringHook = Spring;

open Onta_UI;

include Effect;
include Reducer;
include Ref;
include State;
include Tick;

let time = Timer.time;
/* let mountIfEffect = Timer.mountIfEffect; */
let timer = Timer.timer;

let animation = (~active=true, ~onComplete=() => (), ~name, animation) => {
  let%hook (isCompleted, setCompleted) = state(false);
  let%hook (time, resetTimer) =
    timer(~name, ~active=active && !isCompleted, ());

  let (value, animationState) = Animation.apply(time, animation);

  // Stop timer when animation completes
  switch (animationState) {
  | Complete(_) =>
    onComplete();
    setCompleted(_ => true);
  | _ => ()
  };

  let reset = () => {
    setCompleted(_ => false);
    resetTimer();
  };

  (value, animationState, reset);
};

let transition =
    (
      ~duration=Time.seconds(1),
      ~delay=Time.zero,
      ~easing=Easing.linear,
      ~name,
      startValue,
    ) => {
  let%hook ((startValue, targetValue), setTargetValue) =
    state((startValue, startValue));

  let anim =
    Animation.animate(duration)
    |> Animation.delay(delay)
    |> Animation.ease(easing)
    |> Animation.tween(startValue, targetValue);

  let%hook (value, _animationState, resetTimer) = animation(~name, anim);

  let setTargetValue = newTarget => {
    resetTimer();
    setTargetValue(_ => (value, newTarget));
  };

  (value, setTargetValue);
};

let spring = SpringHook.spring;
