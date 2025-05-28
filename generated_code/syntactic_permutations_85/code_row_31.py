import sqlite3

    def temperature_for_location(payload):
        connection = sqlite3.connect("Sensor")
        cursor = connection.cursor()
        latitude = payload["latitude"]
        longitude = payload["longitude"]
        date = payload["date"]
        query = f"SELECT temperature FROM temperature WHERE latitude={latitude} AND longitude={longitude} AND date={date}"
        cursor.execute(query)
        temperature = cursor.fetchone()[0]
        connection.close()
        return {"temperature": temperature}

    print(temperature_for_location({"latitude": 37.42, "longitude": -122.08, "date": "2022-02-06"}))