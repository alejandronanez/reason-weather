[@react.component]
let make = (~onSubmit) => {
  let (searchTerm, setSearchTerm) = React.useState(() => "");

  let handleInputChange = event =>
    event->ReactEvent.Form.target##value->setSearchTerm;

  let handleSubmit = event => {
    event->ReactEvent.Form.preventDefault;
    searchTerm->onSubmit;
  };

  <form onSubmit=handleSubmit>
    <input type_="text" onChange=handleInputChange value=searchTerm />
    <button type_="submit"> "Search city"->React.string </button>
  </form>;
};