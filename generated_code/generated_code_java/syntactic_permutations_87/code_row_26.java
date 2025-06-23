The temperature for the given latitude, longitude and date is returned in the form of a list of dictionaries.


[{
   "temperature": 27,
    "date": "1985-03-20"
}]



### Sample Request:
http://localhost:5000/api/temperature_for_location?latitude=36.778259&longitude=-119.417931&date=2019-01-01

### Sample Response:

[{
   "temperature": 27,
    "date": "1985-03-20"
}]