type cityWeather = {
  forecasts: Belt.List.t(Api.cityWeatherReports),
  temp: float,
  name: string,
};