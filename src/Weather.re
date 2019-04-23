type props = {
  forecasts: array(Api.cityWeatherReports),
  temp: float,
  name: string,
};

[@react.component]
let make = (~forecasts, ~temp, ~name) => {
  <div>
    <h1> name->React.string </h1>
    <h2> {temp->string_of_float->React.string} </h2>
  </div>;
};