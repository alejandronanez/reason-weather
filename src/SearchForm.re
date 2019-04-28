[@react.component]
let make = (~onSubmit, ~onChange, ~value) => {
  let handleInputChange = event =>
    event->ReactEvent.Form.target##value->onChange;

  let handleSubmit = event => {
    event->ReactEvent.Form.preventDefault;
    onSubmit();
  };

  <form onSubmit=handleSubmit>
    <input type_="text" onChange=handleInputChange value />
    <button type_="submit"> "Search city"->React.string </button>
  </form>;
};