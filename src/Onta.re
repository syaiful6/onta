/*
 * Include Onta_Core in the top level 'Onta' module
 * Otherwise it's confusing when to open 'Onta' vs 'Onta.Core'
 */
include Onta_Core;

/* Courtesy of @reason-native/console - a console-like API for native! */
module Console = Console;

module Font = Onta_Font;
module Draw = Onta_Draw;
module Geometry = Onta_Geometry;
module Math = Onta_Math;
module Shaders = Onta_Shaders;
module Native = Onta_Native;

module UI = {
  include Onta_UI;
  include Onta_UI_Primitives;

  /*
   * Include Components such that consumers access it via:
   * Onta.UI.Components
   */
  module Components = Onta_UI_Components;
  module Hooks = Onta_UI_Hooks;
};

module Platform = {
  include Platform;
};
