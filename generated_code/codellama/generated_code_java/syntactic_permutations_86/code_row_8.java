The response should include the following headers:
    
Content-type: application/json
Access-Control-Allow-Origin: * 

And the following JSON object as the body: {
"latitude": latitude,
"longitude": longitude,
"year": year,
"month": month,
"day": day,
"grib_file": grib_file,
"temperature": maximum_temperature
}
The temperature should be the value returned from the MySQL query, and all other fields should be as provided in the request.

### Example:
    Request: GET /api/temperature_for_location?latitude=12.3&longitude=45.6&year=2020&month=8&day=9&grib_file=filename.txt HTTP/1.1
    Host: localhost:8000
    Accept: application/json
    Response: HTTP/1.1 200 OK
    Content-type: application/json
    Access-Control-Allow-Origin: *
    {
        "latitude": 12.3,
        "longitude": 45.6,
        "year": 2020,
        "month": 8,
        "day": 9,
        "grib_file": "filename.txt",
        "temperature": 27.1
    }