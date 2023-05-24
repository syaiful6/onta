open Onta_Core;

module Draw = Onta_Draw;

module Layout = Layout;
module LayoutTypes = Layout.LayoutTypes;

open Node;

let uiToDrawResizeMode: ImageResizeMode.t => Onta_Draw.ImageResizeMode.t =
  rm =>
    switch (rm) {
    | Stretch => Onta_Draw.ImageResizeMode.Stretch
    | Repeat => Onta_Draw.ImageResizeMode.Repeat
    };

class imageNode (imagePath: string) = {
  as _this;
  val mutable src = imagePath;
  inherit (class node)() as _super;
  val mutable _opacity = 1.0;
  val mutable _resizeMode = ImageResizeMode.Stretch;
  pub! draw = (parentContext: NodeDrawContext.t) => {
    /* Draw background first */
    _super#draw(parentContext);
    let dimensions = _this#measurements();
    let world = _this#getWorldTransform();

    Draw.Image.drawImage(
      ~imagePath=src,
      ~transform=world,
      ~width=float_of_int(dimensions.width),
      ~height=float_of_int(dimensions.height),
      ~resizeMode=uiToDrawResizeMode(_resizeMode),
      ~tint=Colors.white,
      ~opacity=_opacity,
      (),
    );
  };
  pub setOpacity = f => _opacity = f;
  pub setResizeMode = (mode: ImageResizeMode.t) => {
    _resizeMode = mode;
  };
  pub setSrc = newSrc => {
    src = newSrc;
  };
};
