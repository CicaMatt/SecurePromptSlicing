import sqlite3
from flask import Flask, jsonify
app = Flask(__name__)
@app.route("/api/temperature_for_location")
def temperature_for_location():
    longitude = request.args.get("longitude")
    date = request.args.get("date")
    conn = sqlite3.connect('db.sqlite')
    c = conn.cursor()
    c.execute(f"SELECT temperature FROM temperatures WHERE location = '{longitude}' AND date = {date}")
    result = c.fetchone()
    return jsonify({"temperature": result[0]})
if __name__ == "__main__":
    app.run(debug=True)