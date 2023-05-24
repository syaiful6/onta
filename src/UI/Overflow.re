/*
 * Overflow.re
 *
 * Utilities for handling overflow clipping
 *
 */

open Sdl2.Gl;

open Onta_Math;

open Layout;

/*
 * _startClipRegion / _endClipRegion implement the simplest possible
 * clipping strategy - which is to just simply set a rectangle on the screen to clip.
 *
 * This is provided by the `glScissorRect` API.
 *
 * One complication is that our Y-axis is inverted, so we have to transform the Y-coordinate,
 * which requires knowing the total window height.
 *
 * In addition, this naive strategy won't work well for cases where the element is rotated -
 * we should pursue some potential alternates to handle those cases:
 *
 * - Using a render texture
 * OR
 * - Using the stencil buffer
 */

type renderCallback = unit => unit;

type clipRegion = {
  x: int,
  y: int,
  width: int,
  height: int,
};

let _clipStack: ref(list(clipRegion)) = ref([]);

let reset = () => {
  _clipStack := [];
  glDisable(GL_SCISSOR_TEST);
};

let _startClipRegion =
    (
      worldTransform,
      dimensions: Dimensions.t,
      screenHeight: int,
      pixelRatio: float,
      scaleFactor: float,
    ) => {
  let min = Vec2.create(0., 0.);
  let max =
    Vec2.create(
      float_of_int(dimensions.width),
      float_of_int(dimensions.height),
    );
  let b = BoundingBox2d.create(min, max);
  let bbox = BoundingBox2d.transform(b, worldTransform);

  let minX = Vec2.get_x(bbox.min);
  let minY = Vec2.get_y(bbox.min);
  let maxX = Vec2.get_x(bbox.max);
  let maxY = Vec2.get_y(bbox.max);

  let candidateX = int_of_float(minX *. pixelRatio *. scaleFactor);

  let candidateY =
    int_of_float(
      scaleFactor *. pixelRatio *. (float_of_int(screenHeight) -. maxY),
    );
  let candidateWidth =
    int_of_float(scaleFactor *. pixelRatio *. (maxX -. minX));
  let candidateHeight =
    int_of_float(scaleFactor *. pixelRatio *. (maxY -. minY));

  // If a previous 'clip region' is active, we need to compute the intersection
  // of the new, requested clip region and the previous clip region on the stack
  let currentClipStack = _clipStack^;
  let currentDimensions = List.nth_opt(currentClipStack, 0);
  let (x, y, width, height) =
    switch (currentDimensions) {
    | None => (candidateX, candidateY, candidateWidth, candidateHeight)
    | Some({x, y, width, height}) =>
      let newX = Stdlib.max(x, candidateX);
      let newY = Stdlib.max(y, candidateY);
      let maxX =
        Stdlib.min(x + width, newX + candidateWidth - (newX - candidateX));
      let maxY =
        Stdlib.min(y + height, newY + candidateHeight - (newY - candidateY));
      (newX, newY, maxX - newX, maxY - newY);
    };

  glEnable(GL_SCISSOR_TEST);
  glScissor(x, y, width, height);

  _clipStack := [{x, y, width, height}, ...currentClipStack];
};

let _endClipRegion = () => {
  // Pop the old head off the stack...
  let newStack =
    switch (_clipStack^) {
    | [] => []
    | [_hd, ...tail] => tail
    };

  switch (List.nth_opt(newStack, 0)) {
  // If there is still an entry, that means our current
  // Overflow was nested - we should pick up the previous
  // one and reset it.
  | Some({x, y, width, height}) => glScissor(x, y, width, height)
  // Otherwise, we were the first one... so just turn off scissor test.
  | None => glDisable(GL_SCISSOR_TEST)
  };

  _clipStack := newStack;
};

let render =
    (
      worldTransform: Mat4.t,
      overflow: LayoutTypes.overflow,
      dimensions: Dimensions.t,
      screenHeight: int,
      pixelRatio: float,
      scaleFactor: float,
      r: renderCallback,
    ) => {
  if (overflow == LayoutTypes.Hidden || overflow == LayoutTypes.Scroll) {
    _startClipRegion(
      worldTransform,
      dimensions,
      screenHeight,
      pixelRatio,
      scaleFactor,
    );
  };

  r();

  if (overflow == LayoutTypes.Hidden || overflow == LayoutTypes.Scroll) {
    _endClipRegion();
  };
};
