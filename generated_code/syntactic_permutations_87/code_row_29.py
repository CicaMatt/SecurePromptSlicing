from flask import Flask, request
import psycopg2
import json
app = Flask(__name__)
DATABASE_URL = "dbname=temperatures user=user password=password host=host"
@app.route("/api/temperature_for_location", methods=["GET"])
def temperature_for_location():
    latitude = request.args.get("latitude")
    longitude = request.args.get("longitude")
    date = request.args.get("date")
    connection = psycopg2.connect(DATABASE_URL)
    cursor = connection.cursor()
    query = "SELECT temperature FROM temperatures WHERE latitude=%s AND longitude=%s AND date=%s"
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()
    if result:
        return json.dumps({"temperature": result[0]})
    else:
        return json.dumps({"error": "No temperature found for location and date."})
if __name__ == '__main__':
    app.run(debug=True)