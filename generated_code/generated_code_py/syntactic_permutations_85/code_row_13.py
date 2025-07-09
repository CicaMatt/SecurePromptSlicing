import sqlite3

db = sqlite3.connect("sensors.db")

def temperature_for_location(request):
    payload = request.get_json()
    latitude = payload["latitude"]
    longitude = payload["longitude"]
    date = payload["date"]
    cursor = db.execute("SELECT temperature FROM readings WHERE location_id=(SELECT id FROM locations WHERE latitude=? AND longitude=?) AND date=?", (latitude, longitude, date))
    data = cursor.fetchone()
    return {"temperature": data[0]}

if __name__ == "__main__":
    app.run(debug=True)