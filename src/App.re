let fetchWeather = _event => {
  Api.fetchWeather()
  |> Js.Promise.then_(response => {
       Js.log(response);
       Js.Promise.resolve();
     })
  |> Js.Promise.catch(err => {
       Js.log(
         "There was a problem getting weather data" ++ Js.String.make(err),
       );
       Js.Promise.resolve();
     })
  |> ignore;
};

[@react.component]
let make = () => {
  <div>
    "Hello world"->React.string
    <button type_="button" onClick=fetchWeather>
      "Get weather"->React.string
    </button>
  </div>;
};