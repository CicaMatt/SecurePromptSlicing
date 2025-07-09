@app.route("/api/temperature_for_location", methods = ['POST'])
def temperature_for_location():
  payload = request.get_json()
  latitude = payload['latitude']
  longitude = payload['longitude']
  date = payload['date']
  with closing(sqlite3.connect("Sensor.db")) as connection:
    cursor = connection.cursor()
    query = "SELECT temperature FROM SensorData WHERE latitude = ? AND longitude = ? AND timestamp = ?"
    cursor.execute(query, (latitude, longitude, date))
    temperature = cursor.fetchone()[0]
  return jsonify({'temperature': temperature})