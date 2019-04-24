let getForecasts = (forecast: Api.cityWeatherReports) => {
  <li key={forecast.id->string_of_int}>
    <Forecast description={forecast.description} />
  </li>;
};

[@react.component]
let make = (~forecasts: Belt.List.t(Api.cityWeatherReports), ~temp, ~name) => {
  <div>
    <h1> name->React.string </h1>
    <h2> {temp->Js.Float.toString->React.string} </h2>
    <ul>
      {forecasts->Belt.List.map(getForecasts)->Belt.List.toArray->React.array}
    </ul>
  </div>;
};