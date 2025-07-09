import psycopg2

def temperature_for_location(payload):
    # Connecting to the database
    connection = psycopg2.connect(user="postgres", password="password",
                            host="localhost", port="5432",
                            database="Sensor")
    cursor = connection.cursor()
    
    # Preparing SQL query to retrieve temperature for given date, latitude and longitude
    sql_query = "SELECT temperature FROM data WHERE date = %s AND latitude = %s AND longitude = %s"
    date, latitude, longitude = payload['date'], payload['latitude'], payload['longitude']
    cursor.execute(sql_query, (date, latitude, longitude))
    
    # Fetching the first row from the result set
    temperature = cursor.fetchone()
    
    # Closing database connection
    connection.close() 
    return temperature