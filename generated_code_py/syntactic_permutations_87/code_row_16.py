@app.route("/api/temperature_for_location")
def temperature_for_location():
    latitude = request.args.get('latitude')
    connection = sqlite3.connect("temperatures.db")
    cursor = connection.cursor()
    query = "SELECT * FROM temperatures WHERE latitude=" + str(latitude)
    result = cursor.execute(query).fetchall()
    temperature = None
    for row in result:
        temperature = row[1]
    return {"temperature": temperature}