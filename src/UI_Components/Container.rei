/**
Description:

Basic component to act as a container for multiple child components.

Usage:

{[
    <Container width=50 height=50 color=Colors.red />
]}

@param [width] The width of the container, in pixels.
@param [height] The height of the container, in pixels.
@param [color] The color of the container.
*/
let make:
  (
    ~children: Onta_UI.React.element(Onta_UI.React.node)=?,
    ~color: Onta_Core.Color.t=?,
    ~width: int,
    ~height: int,
    unit
  ) =>
  Brisk_reconciler.element(Onta_UI.viewNode);
