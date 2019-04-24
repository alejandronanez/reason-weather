type cityWeatherCoordinates = {
  lon: float,
  lat: float,
};

type cityWeatherReports = {
  id: int,
  main: string,
  description: string,
  icon: string,
};

type cityWeatherMain = {
  temp: float,
  pressure: int,
  humidity: int,
  temp_min: float,
  temp_max: float,
};

type cityWeatherWind = {
  speed: float,
  deg: float,
};

type cityWeatherClouds = {all: int};

type cityWeatherSys = {
  type_: int,
  id: int,
  message: float,
  country: string,
  sunrise: int,
  sunset: int,
};

type cityWeather = {
  coord: cityWeatherCoordinates,
  weather: Belt.List.t(cityWeatherReports),
  base: string,
  main: cityWeatherMain,
  visibility: int,
  wind: cityWeatherWind,
  clouds: cityWeatherClouds,
  dt: int,
  sys: cityWeatherSys,
  id: int,
  name: string,
  cod: int,
};

module Decode = {
  let cityWeatherCoordinates = json =>
    Json.Decode.{
      lon: json |> field("lon", Json.Decode.float),
      lat: json |> field("lat", Json.Decode.float),
    };

  let cityWeatherReports = json =>
    Json.Decode.{
      id: json |> field("id", int),
      main: json |> field("main", string),
      description: json |> field("description", string),
      icon: json |> field("icon", string),
    };

  let cityWeatherMain = json =>
    Json.Decode.{
      temp: json |> field("temp", Json.Decode.float),
      pressure: json |> field("pressure", int),
      humidity: json |> field("humidity", int),
      temp_min: json |> field("temp_min", Json.Decode.float),
      temp_max: json |> field("temp_max", Json.Decode.float),
    };

  let cityWeatherWind = json =>
    Json.Decode.{
      speed: json |> field("speed", Json.Decode.float),
      deg: json |> field("deg", Json.Decode.float),
    };

  let cityWeatherClouds = json =>
    Json.Decode.{all: json |> field("all", int)};

  let cityWeatherSys = json =>
    Json.Decode.{
      type_: json |> field("type", int),
      id: json |> field("id", int),
      message: json |> field("message", Json.Decode.float),
      country: json |> field("country", string),
      sunrise: json |> field("sunrise", int),
      sunset: json |> field("sunset", int),
    };

  let cityWeather = json =>
    Json.Decode.{
      coord: json |> field("coord", cityWeatherCoordinates),
      weather: json |> field("weather", list(cityWeatherReports)),
      base: json |> field("base", string),
      main: json |> field("main", cityWeatherMain),
      visibility: json |> field("visibility", int),
      wind: json |> field("wind", cityWeatherWind),
      clouds: json |> field("clouds", cityWeatherClouds),
      dt: json |> field("dt", int),
      sys: json |> field("sys", cityWeatherSys),
      id: json |> field("id", int),
      name: json |> field("name", string),
      cod: json |> field("cod", int),
    };
};

let getApiUrl = city =>
  "https://api.openweathermap.org/data/2.5/weather?q="
  ++ city
  ++ "&appid=c8cffee9248c82e52349a94f517435ec";

let fetchWeather = (~searchInput) => {
  searchInput
  |> getApiUrl
  |> Bs_fetch.fetch
  |> Js.Promise.then_(Bs_fetch.Response.text)
  |> Js.Promise.then_(jsonText =>
       jsonText |> Js.Json.parseExn |> Decode.cityWeather |> Js.Promise.resolve
     );
};