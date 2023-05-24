open Onta;
open Onta.UI;
open Onta.UI.Components;

open Onta.Native;

module NativeExamples = {
  let%component make = () => {
    let%hook (fileListOpt, setFileListOpt) = Hooks.state(None);
    let%hook (allowMultiple, setAllowMultiple) = Hooks.state(false);
    let%hook (showHidden, setShowHidden) = Hooks.state(false);

    let openFile = () => {
      let o =
        Dialog.openFiles(
          ~allowMultiple,
          ~showHidden,
          ~title="Onta Open File Example",
          ~buttonText=
            allowMultiple ? "Open file(s) in Onta" : "Open file in Onta",
          (),
        );
      setFileListOpt(_ => o);
    };

    let optionStyle =
      Style.[
        color(Colors.white),
        fontFamily("Roboto-Regular.ttf"),
        fontSize(20),
      ];

    let renderFilePath = (path: string) =>
      <Text
        style=Style.[
          color(Colors.white),
          fontFamily("Roboto-Regular.ttf"),
          fontSize(12),
        ]
        text=path
      />;

    let containerStyle =
      Style.[
        position(`Absolute),
        justifyContent(`Center),
        alignItems(`Center),
        bottom(0),
        top(0),
        left(0),
        right(0),
      ];

    <View style=containerStyle>
      <Row>
        <Text style=optionStyle text="Allow multiple?" />
        <Checkbox
          checked=allowMultiple
          checkedColor=Colors.green
          onChange={() => setAllowMultiple(am => !am)}
        />
      </Row>
      <Row>
        <Text style=optionStyle text="Show hidden?" />
        <Checkbox
          checked=showHidden
          checkedColor=Colors.green
          onChange={() => setShowHidden(sh => !sh)}
        />
      </Row>
      <Button title="Open File" onClick=openFile />
      {switch (fileListOpt) {
       | Some(fileList) =>
         fileList
         |> Array.map(renderFilePath)
         |> Array.to_list
         |> React.listToElement
       | None => <View />
       }}
    </View>;
  };
};

let render = () => <NativeExamples />;
