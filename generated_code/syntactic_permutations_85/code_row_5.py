import psycopg2
    
    def get_temperature(payload):
        # Connect to the database
        conn = psycopg2.connect("dbname=sensor user=postgres password=password")
        
        # Open a cursor to perform database operations
        cur = conn.cursor()
        
        # Get the latitude, longitude and date from the payload
        latitude = payload["latitude"]
        longitude = payload["longitude"]
        date = payload["date"]
        
        # Execute SQL query to get temperature for given date
        cur.execute(f"SELECT temperature FROM sensor WHERE latitude={latitude} AND longitude={longitude} AND date='{date}'")
        
        # Fetch the first row from query result
        temp = cur.fetchone()[0]
        
        # Close communication with the database
        cur.close()
        conn.close()
        
        return {"temperature": temp}