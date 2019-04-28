type action =
  | SetSearchTerm(string)
  | SetError(string)
  | LoadingWeatherData(bool)
  | FetchWeatherData(Types.cityWeather);

type state = {
  searchTerm: string,
  loading: bool,
  error: option(string),
  city: option(string),
  cityWeather: option(Types.cityWeather),
};

let initialState = {
  searchTerm: "",
  city: None,
  error: None,
  loading: false,
  cityWeather: None,
};

let fetchWeather = (dispatch, ~searchInput) => {
  dispatch(LoadingWeatherData(true));
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
       dispatch(SetError(""));
       dispatch(LoadingWeatherData(false));
       Js.Promise.resolve();
     })
  |> Js.Promise.catch(err => {
       Js.log(
         "There was a problem getting weather data: " ++ Js.String.make(err),
       );
       dispatch(SetError("There was a problem loading your data"));
       dispatch(LoadingWeatherData(false));
       Js.Promise.resolve();
     })
  |> ignore;
};

let reducer = (state, action) =>
  switch (action) {
  | SetSearchTerm(searchTerm) => {...state, searchTerm}
  | LoadingWeatherData(loading) => {...state, loading}
  | FetchWeatherData(weatherData) => {
      ...state,
      cityWeather: Some(weatherData),
    }
  | SetError(errorMessage) => {...state, error: Some(errorMessage)}
  };

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
  let handleSearchFormSubmission = () =>
    fetchWeather(dispatch, ~searchInput=state.searchTerm);
  let handleSearchFormChange = newSearchTermValue =>
    dispatch(SetSearchTerm(newSearchTermValue));
  let error =
    switch (state.error) {
    | Some(message) => <span> message->React.string </span>
    | None => ReasonReact.null
    };
  let loading =
    state.loading ? <span> "Loading"->React.string </span> : ReasonReact.null;

  let cityWeather =
    switch (state.cityWeather) {
    | Some({forecasts, temp, name}) => <Forecasts forecasts temp name />
    | None => ReasonReact.null
    };

  <div>
    <SearchForm
      value={state.searchTerm}
      onChange=handleSearchFormChange
      onSubmit=handleSearchFormSubmission
    />
    error
    loading
    cityWeather
  </div>;
};