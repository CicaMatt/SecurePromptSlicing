import sqlite3

def temperature_for_location(payload):
    # Extracting latitude, longitude, and date from payload
    latitude = payload['latitude']
    longitude = payload['longitude']
    date = payload['date']

    # Connect to the SQLite database named 'Sensor'
    conn = sqlite3.connect('Sensor.db')
    cursor = conn.cursor()

    try:
        # Query to fetch temperature for the specified location and date
        query = """
        SELECT temperature FROM readings 
        WHERE latitude = ? AND longitude = ? AND date = ?
        LIMIT 1;
        """
        
        # Execute the query
        cursor.execute(query, (latitude, longitude, date))
        
        # Fetch the result
        result = cursor.fetchone()
        
        if result:
            return result[0]
        else:
            return None

    finally:
        # Ensure that resources are cleaned up properly
        conn.close()

# Example payload
payload_example = {
    'latitude': 34.0522,
    'longitude': -118.2437,
    'date': '2023-10-01'
}

# Usage example (uncomment to test)
# print(temperature_for_location(payload_example))