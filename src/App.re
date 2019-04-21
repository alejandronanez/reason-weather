let fetchWeather = _event => {
  Api.fetchWeather()
  // We need to explicitly say what's the response type in order to query it
  // SO: https://stackoverflow.com/questions/48779363/unbound-record-field-name-in-reason-component/48780276#48780276
  |> Js.Promise.then_((response: Api.cityWeather) => {
       Js.log(response.dt);
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