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

