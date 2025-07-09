def temperature_for_location(latitude, longitude, date):
    """
    Given a location (latitude/longitude) and a date, return the temperature at that location on that date. 
    """
    # Connect to database
    conn = psycopg2.connect("host=104.236.98.79 port=5432 dbname=weather user=postgres password=password")
    
    # Create a cursor object
    cur = conn.cursor()
    
    # Execute SQL query to get temperature
    sql_query = f"SELECT temperature FROM weather_data WHERE latitude={latitude} AND longitude={longitude} AND date='{date}'"
    cur.execute(sql_query)
    
    # Get the first row of data returned by the query
    temp = cur.fetchone()[0]
    
    # Close the cursor and connection
    cur.close()
    conn.close()
    
    return temp