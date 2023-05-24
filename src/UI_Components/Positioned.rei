let make:
  (
    ~top: int=?,
    ~left: int=?,
    ~right: int=?,
    ~bottom: int=?,
    ~children: Onta_UI.React.React.element(Onta_UI.React.node),
    unit
  ) =>
  Brisk_reconciler.element(Onta_UI.viewNode);
