/**
{2 Description:}

Simple out-of-box checkbox component

{2 Usage:}

{[
    <Checkbox checked=true onChange={(_) => print_endline("Checkbox changed!")}/>
]}
*/

let make:
  (
    ~checked: bool=?,
    ~checkedColor: Onta_Core.Color.t=?,
    ~style: list(Onta_UI.Style.viewStyleProps)=?,
    ~onChange: unit => unit=?,
    unit
  ) =>
  Brisk_reconciler.element(Onta_UI.React.node);
