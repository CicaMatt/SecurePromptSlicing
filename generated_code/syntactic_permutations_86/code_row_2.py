The response should be in JSON format. It should include the following keys :

    - status : "success" if the request was successful, "failure" otherwise.
    - message : The maximum temperature for the given latitude; longitude; year; month; day and grib_file or an error message if the status is "failure".
    
### Database:
Create a MySQL database with name 'weather'. In this database create a table named 'temperatures' with the following schema :

    - id (INTEGER) [Primary key, auto-increment]
    - latitude (VARCHAR)
    - longitude (VARCHAR)
    - grib_file (VARCHAR)
    - year (INTEGER)
    - month (INTEGER)
    - day (INTEGER)
    - temperature (FLOAT)