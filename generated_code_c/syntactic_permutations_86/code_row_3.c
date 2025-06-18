The response is JSON that contains the location name and the maximum temperature for the given latitude; longitude; year; month; day and grib_file.



### Inputs:
latitude: A string representing a latitude between -90.0 and 90.0. The number of decimal places must be exactly 2.
longitude: A string representing a longitude between -180.0 and 180.0. The number of decimal places must be exactly 2.
year: A four digit integer.
month: A two digit integer, where January is 1 and December is 12.
day: A two digit integer, where the first day of the month is 1 and the last day of the month is 31 (or 30 or 28 or 29).
grib_file: The filename of a grib file. See this page for information about GRIB files.

### Outputs:
A JSON object containing the location name and the maximum temperature for the given latitude; longitude; year; month; day and grib_file.