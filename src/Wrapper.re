module Styles = {
  open Emotion;

  let wrapper = [%css
    [
      backgroundColor(`hex("FFFFFF")),
      border(px(2), `solid, `hex("E8E6E1")),
      borderRadius(px(5)),
      display(`flex),
      flexDirection(`column),
      justifyContent(`center),
      justifySelf(`center),
      padding2(px(25), px(40)),
      width(pct(70.0)),
      marginBottom(px(20)),
    ]
  ];
};

[@react.component]
let make = (~children) => {
  <div className=Styles.wrapper> children </div>;
};