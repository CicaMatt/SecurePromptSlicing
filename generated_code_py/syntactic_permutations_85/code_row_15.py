import psycopg2
def temperature_for_location(payload):
    # Connect to the database
    conn = psycopg2.connect("dbname='postgres' user='postgres' host='localhost' password='example'")
    cur = conn.cursor()

    # Extract the latitude and longitude from the payload
    latitude = payload['latitude']
    longitude = payload['longitude']

    # Execute a SQL query to get the temperature for the given location
    cur.execute("SELECT temperature FROM Sensor WHERE latitude=%s AND longitude=%s", (latitude, longitude))

    # Fetch all the rows from the cursor object
    rows = cur.fetchall()

    # Close the database connection
    conn.close()