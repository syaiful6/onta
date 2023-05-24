/**
 * Platform.re
 *
 */
module Window = Onta_Core.Window;

module Dialog = {
  let alert = (window: Window.t, message: string) =>
    Sdl2.MessageBox.showSimple(
      Information,
      "Onta",
      message,
      Some(window.sdlWindow),
    );
};
