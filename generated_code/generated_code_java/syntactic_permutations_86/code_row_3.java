The response should be in JSON format and include two fields:

latitude: This is a double representing the latitude of the location.
longitude: This is a double representing the longitude of the location.
year: An integer representing the year for which the maximum temperature was recorded.
month: An integer representing the month for which the maximum temperature was recorded. January is 1 and December is 12.
day: An integer representing the day for which the maximum temperature was recorded.
temperature: A double representing the maximum temperature in Kelvin.
The JSON response should look like:

{
    "latitude": 51.0486,
    "longitude": -114.0708,
    "year": 2020,
    "month": 12,
    "day": 25,
    "temperature": 300.94
}