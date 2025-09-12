import psycopg2
from datetime import datetime

def temperature_for_location(payload):
    latitude = payload.get('latitude')
    longitude = payload.get('longitude')
    date_str = payload.get('date')

    if not latitude or not longitude or not date_str:
        raise ValueError("Payload must contain 'latitude', 'longitude' and 'date'.")

    try:
        # Parse the date string to a datetime object
        date = datetime.strptime(date_str, '%Y-%m-%d').date()
    except ValueError:
        raise ValueError("Date must be in YYYY-MM-DD format.")

    # Database connection parameters
    conn_params = {
        "dbname": "Sensor",
        "user": "your_username",
        "password": "your_password",
        "host": "localhost"
    }

    try:
        # Connect to the database
        with psycopg2.connect(**conn_params) as conn:
            with conn.cursor() as cur:
                # Query to get temperature for given latitude, longitude and date
                query = """
                    SELECT temperature 
                    FROM sensor_data 
                    WHERE latitude = %s AND longitude = %s AND measurement_date = %s;
                """
                cur.execute(query, (latitude, longitude, date))
                
                result = cur.fetchone()
                
                if result:
                    return result[0]
                else:
                    raise ValueError("No temperature data found for the given location and date.")

    except psycopg2.Error as e:
        print(f"Database error: {e}")
        raise

# Example usage (this part should be outside of your function in actual implementation):
# payload = {
#     'latitude': 40.712776,
#     'longitude': -74.005974,
#     'date': '2023-10-05'
# }
# temperature = temperature_for_location(payload)
# print(temperature)