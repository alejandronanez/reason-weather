module Styles = {
  open Emotion;

  let input = [%css
    [
      border(px(1), `solid, `hex("E8E6E1")),
      borderTopLeftRadius(px(4)),
      borderBottomLeftRadius(px(4)),
      fontSize(px(18)),
      padding(px(10)),
      width(pct(75.0)),
    ]
  ];

  let label_ = [%css [display(`block), marginBottom(px(6))]];

  let searchButton = [%css
    [
      backgroundColor(`hex("A081D9")),
      border(px(1), `solid, `hex("A081D9")),
      borderTopRightRadius(px(4)),
      borderBottomRightRadius(px(4)),
      color(`hex("EAE2F8")),
      fontSize(px(16)),
      fontWeight(700),
      padding2(px(11), px(30)),
      width(pct(25.0)),
      hover([cursor(`pointer)]),
    ]
  ];
};

[@react.component]
let make = (~onSubmit, ~onChange, ~value) => {
  let handleInputChange = event =>
    event->ReactEvent.Form.target##value->onChange;

  let handleSubmit = event => {
    event->ReactEvent.Form.preventDefault;
    onSubmit();
  };

  <Wrapper>
    <form onSubmit=handleSubmit>
      <label htmlFor="city search" className=Styles.label_>
        "City Search"->React.string
      </label>
      <div>
        <input
          id="city search"
          className=Styles.input
          type_="text"
          onChange=handleInputChange
          value
        />
        <button className=Styles.searchButton type_="submit">
          "Search"->React.string
        </button>
      </div>
    </form>
  </Wrapper>;
};