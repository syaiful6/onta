/**
    Onta_Font.re

    Module exposing font-related functionality, like:
    - Discovering fonts
    - Loading fonts
*/
module Weight = FontManager.FontWeight;
module Width = FontManager.FontWidth;
module Discovery = Discovery;

type t = FontManager.FontDescriptor.t;

let find = Discovery.find;
let toString = Discovery.toString;
