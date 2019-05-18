module Styles = {
  open Emotion;

  let wrapper = [%css
    [
      display(`grid),
      margin2(`zero, `auto),
      maxWidth(px(1024)),
      paddingTop(px(20)),
    ]
  ];
};

type action =
  | SetSearchTerm(option(string))
  | SetError(option(string))
  | LoadingWeatherData(bool)
  | FetchWeatherData(option(Types.cityWeather));

type state = {
  searchTerm: option(string),
  loading: bool,
  error: option(string),
  city: option(string),
  cityWeather: option(Types.cityWeather),
};

let initialState = {
  searchTerm: None,
  city: None,
  error: None,
  loading: false,
  cityWeather: None,
};

let fetchWeather = (dispatch, ~searchInput) => {
  dispatch(LoadingWeatherData(true));
  dispatch(SetError(None));
  dispatch(FetchWeatherData(None));

  Api.fetchWeather(~searchInput)
  // We need to explicitly say what's the response type in order to query it
  // SO: https://stackoverflow.com/questions/48779363/unbound-record-field-name-in-reason-component/48780276#48780276
  |> Js.Promise.then_((response: Api.cityWeather) => {
       dispatch(
         FetchWeatherData(
           Some({
             forecasts: response.weather,
             temp: response.main.temp,
             name: response.name,
           }),
         ),
       );
       dispatch(LoadingWeatherData(false));
       Js.Promise.resolve();
     })
  |> Js.Promise.catch(err => {
       Js.log(
         "There was a problem getting weather data: " ++ Js.String.make(err),
       );
       dispatch(SetError(Some("There was a problem loading your data")));
       dispatch(LoadingWeatherData(false));
       Js.Promise.resolve();
     })
  |> ignore;
};

let reducer = (state, action) =>
  switch (action) {
  | SetSearchTerm(None) => {...state, searchTerm: None}
  | SetSearchTerm(Some(searchTerm)) => {
      ...state,
      searchTerm: Some(searchTerm),
    }
  | LoadingWeatherData(loading) => {...state, loading}
  | FetchWeatherData(None) => {...state, cityWeather: None}
  | FetchWeatherData(Some(weatherData)) => {
      ...state,
      cityWeather: Some(weatherData),
    }
  | SetError(None) => {...state, error: None}
  | SetError(Some(errorMessage)) => {...state, error: Some(errorMessage)}
  };

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
  let searchTerm = Belt.Option.getWithDefault(state.searchTerm, "");
  let handleSearchFormSubmission = () =>
    fetchWeather(dispatch, ~searchInput=searchTerm);
  let handleSearchFormChange = newSearchTermValue =>
    dispatch(SetSearchTerm(newSearchTermValue));
  let error =
    switch (state.error) {
    | Some(message) => <Wrapper> message->React.string </Wrapper>
    | None => ReasonReact.null
    };
  let loading =
    state.loading
      ? <Wrapper> "Loading"->React.string </Wrapper> : ReasonReact.null;

  let cityWeather =
    switch (state.cityWeather) {
    | Some({forecasts, temp, name}) =>
      <Wrapper> <Forecasts forecasts temp name /> </Wrapper>
    | None => ReasonReact.null
    };

  <div className=Styles.wrapper>
    <SearchForm
      value=searchTerm
      onChange=handleSearchFormChange
      onSubmit=handleSearchFormSubmission
    />
    error
    loading
    cityWeather
  </div>;
};