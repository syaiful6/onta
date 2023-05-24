open Onta_UI;
open Onta_Core;
open Onta_UI_Primitives;

module Hooks = Onta_UI_Hooks;
module Make = (Type: {type t;}) => {
  type item = {
    value: Type.t,
    label: string,
  };

  type items = list(item);

  type state = {
    items,
    selected: item,
    _open: bool,
  };

  type action =
    | ShowDropdown
    | SelectItem(item);

  let reducer = (action, state) =>
    switch (action) {
    | ShowDropdown => {...state, _open: !state._open}
    | SelectItem(item) => {...state, selected: item, _open: false}
    };

  let textStyles =
    Style.[
      fontFamily("Roboto-Regular.ttf"),
      fontSize(20),
      color(Colors.black),
    ];

  let noop = _item => ();

  let%component make =
                (
                  ~items: list(item),
                  ~onItemSelected,
                  ~width as w=200,
                  ~height as h=50,
                  (),
                ) => {
    let initialState = {items, selected: List.nth(items, 0), _open: false};

    let%hook (state, dispatch) = Hooks.reducer(~initialState, reducer);

    let items =
      state._open
        ? List.map(
            item =>
              <Clickable
                style=Style.[
                  height(h),
                  justifyContent(`Center),
                  alignItems(`FlexStart),
                  paddingHorizontal(5),
                  backgroundColor(
                    item == state.selected
                      ? Color.hex("#0078D7") : Colors.transparentWhite,
                  ),
                  borderBottom(
                    ~color=Colors.black,
                    ~width=float_of_int(h) *. 0.05 |> int_of_float,
                  ),
                ]
                onClick={() => {
                  dispatch(SelectItem(item));
                  onItemSelected(item);
                }}>
                <Text style=textStyles text={item.label} />
              </Clickable>,
            state.items,
          )
        : [];

    <View
      style=Style.[
        position(`Relative),
        backgroundColor(Colors.white),
        width(w),
      ]>
      <Clickable onClick={() => dispatch(ShowDropdown)}>
        <View
          style=Style.[
            flexDirection(`Row),
            height(h),
            justifyContent(`SpaceBetween),
            paddingHorizontal(5),
            border(
              ~width=float_of_int(h) *. 0.05 |> int_of_float,
              ~color=Colors.black,
            ),
          ]>
          <View
            style=Style.[
              width(float_of_int(w) *. 0.8 |> int_of_float),
              justifyContent(`Center),
              overflow(`Hidden),
            ]>
            <Text style=textStyles text={state.selected.label} />
          </View>
          <Text
            style=Style.[
              fontSize(30),
              color(Colors.black),
              fontFamily("FontAwesome5FreeSolid.otf"),
              paddingRight(5),
              alignSelf(`Center),
            ]
            text={||}
          />
        </View>
      </Clickable>
      <View
        style=Style.[
          position(`Absolute),
          top(h),
          backgroundColor(Colors.white),
          borderHorizontal(
            ~width=float_of_int(h) *. 0.05 |> int_of_float,
            ~color=Colors.black,
          ),
          overflow(`Hidden),
        ]>
        {items |> React.listToElement}
      </View>
    </View>;
  };
};
