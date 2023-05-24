open Onta;
open Onta.UI;
open Onta.UI.Components;

module Check = {
  type checkboxState = {
    first: bool,
    second: bool,
  };

  let getCheckboxText = checked => checked ? "Checked!" : "Not Checked!";

  let%component make = () => {
    let initialCheckboxState = {first: false, second: true};
    let%hook ({first, second}, setCheckboxState) =
      Hooks.state(initialCheckboxState);

    <View
      style=Style.[
        width(500),
        height(500),
        justifyContent(`Center),
        alignItems(`Center),
      ]>
      <Checkbox
        checked=first
        onChange={() => setCheckboxState(_ => {first: !first, second})}
        style=Style.[marginBottom(10)]
      />
      <Text
        text={getCheckboxText(first)}
        style=Style.[
          marginBottom(10),
          fontFamily("Roboto-Regular.ttf"),
          fontSize(20),
        ]
      />
      <Checkbox
        checkedColor=Colors.green
        onChange={() => setCheckboxState(_ => {second: !second, first})}
        style=Style.[border(~width=2, ~color=Colors.green)]
        checked=second
      />
      <Text
        text={
          "Default state: " ++ getCheckboxText(initialCheckboxState.second)
        }
        style=Style.[
          marginTop(10),
          fontFamily("Roboto-Regular.ttf"),
          fontSize(20),
        ]
      />
    </View>;
  };
};

let render = () => {
  <Check />;
};
