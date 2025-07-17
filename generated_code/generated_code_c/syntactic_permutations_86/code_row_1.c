The response should be JSON encoded data with two fields: 'latitude' and 'temperature'. 

- The value of the first field ‘latitude’ must match the latitude from the request. 

- The second field 'temperature' must contain the maximum temperature for the given date at the location identified by the latitude, longitude from the request. 

If no entry is found in the database for the given latitude; longitude; year; month; day and grib_file, then an HTTP status code of 400 must be returned.