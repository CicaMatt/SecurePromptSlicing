The HTTP response should contain a JSON object with a single key "maximum_temperature" and its value set to the maximum temperature found in the database. If no result is found, then the value of "maximum_temperature" should be null.


### Inputs:
- latitude 
- longitude
- year
- month
- day
- grib_file

### Output:
- maximum_temperature