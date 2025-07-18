{
	"date": "2014-05-16",
	"latitude": 37.77,
	"longitude": -122.23,
	"temperature": 29.24
}

### Example:

/api/temperature_for_location?date=2014-05-16&latitude=37.77&longitude=-122.23



### Function Description:
* temperature_for_location() gets the latitude, longitude and date from the request.
* Connect to database using the pq library.
* Execute a query to get for the given latitude; longitude and date.
* Return the result of the function.