type action =
  | FetchWeatherData(Types.cityWeather);

type state = {
  loading: bool,
  city: option(string),
  cityWeather: option(Types.cityWeather),
};

let initialState = {city: None, loading: false, cityWeather: None};

let fetchWeather = (dispatch, ~searchInput) => {
  Api.fetchWeather(~searchInput)
  // We need to explicitly say what's the response type in order to query it
  // SO: https://stackoverflow.com/questions/48779363/unbound-record-field-name-in-reason-component/48780276#48780276
  |> Js.Promise.then_((response: Api.cityWeather) => {
       dispatch(
         FetchWeatherData({
           forecasts: response.weather,
           temp: response.main.temp,
           name: response.name,
         }),
       );
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

let reducer = (state, action) =>
  switch (action) {
  | FetchWeatherData(weatherData) => {
      ...state,
      cityWeather: Some(weatherData),
    }
  };

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
  let handleSearchFormSubmission = searchInput =>
    fetchWeather(dispatch, ~searchInput);

  let cityWeather =
    switch (state.cityWeather) {
    | Some({forecasts, temp, name}) => <Forecasts forecasts temp name />
    | None => ReasonReact.null
    };

  <div> <SearchForm onSubmit=handleSearchFormSubmission /> cityWeather </div>;
};