The response should be in JSON format, with a single key-value pair where the key is "maximum_temperature" and the value is the actual maximum temperature found. The code must include error handling, including a 400 HTTP status code for requests that do not provide all necessary parameters, and a 500 HTTP status code if an internal error occurs while querying the database.

### Test case:
The code will be tested with a POST request containing the following JSON data:

{
    "latitude": 41.782,
    "longitude": -93.606,
    "month": 5,
    "day": 25,
    "grib_file": "gfs.t00z.pgrb2.0p25.f004"
}

The code should respond with the following JSON data:

{
    "maximum_temperature": 286.97
}