import sqlite3
from datetime import datetime, timedelta

def temperature_for_location(latitude, longitude, date):
    # Connect to the database
    conn = sqlite3.connect("Sensor")
    c = conn.cursor()

    # Convert the date to a string in the format YYYY-MM-DD
    date_str = datetime.strftime(date, "%Y-%m-%d")

    # Query the database for the temperature at the given location and date
    c.execute("SELECT temperature FROM sensor WHERE latitude=? AND longitude=? AND date=?", (latitude, longitude, date_str))

    # Get the result of the query
    result = c.fetchone()

    # If there is no matching row in the database, return None
    if result is None:
        return None

    # Otherwise, return the temperature value
    return result[0]