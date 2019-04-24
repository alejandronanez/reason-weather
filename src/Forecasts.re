let getForecasts = (forecast: Types.weatherInformation) => {
  <li key={forecast.name}> <Forecast /> </li>;
};

[@react.component]
let make = (~forecasts: Belt.List.t(Api.cityWeatherReports), ~temp, ~name) => {
  <div>
    <h1> name->React.string </h1>
    <h2> {temp->Js.Float.toString->React.string} </h2>
    <ul>
      {forecasts
       ->Belt.List.map(weatherReport =>
           <li key={weatherReport.id->string_of_int}>
             weatherReport.description->React.string
           </li>
         )
       ->Belt.List.toArray
       ->React.array}
    </ul>
  </div>;
};