The maximum temperature is then returned as JSON object in the response.

### Implementation:
1) Connect to mysql with credentials
2) Listen on a port for HTTP request
3) Extract latitude, longitude, year, month, day and grib_file from the request
4) Query the database and find the maximum temperature
5) Return the response as JSON object

### Testing:
Testing can be done by sending an HTTP request to the endpoint with the query parameters.