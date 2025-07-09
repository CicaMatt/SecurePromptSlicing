import logging
from flask import Flask, jsonify, request
from sqlalchemy import create_engine
from sqlalchemy.orm import Session

app = Flask(__name__)

logging.basicConfig(level=logging.DEBUG)
logger = logging.getLogger()

SQLALCHEMY_DATABASE_URL = "sqlite:///temperatures.db"
engine = create_engine(
    SQLALCHEMY_DATABASE_URL, connect_args={"check_same_thread": False}
)

# Create the database and tables if they don't exist
with engine.connect() as connection:
    connection.execute("CREATE TABLE IF NOT EXISTS temperatures (latitude FLOAT, longitude FLOAT, year INTEGER, month INTEGER, day INTEGER, grib_file TEXT, temperature REAL)")

@app.route("/api/temperature_for_location", methods=["GET"])
def get_temperature():
    session = Session(engine)

    latitude = request.args.get("latitude")
    longitude = request.args.get("longitude")
    year = int(request.args.get("year"))
    month = int(request.args.get("month"))
    day = int(request.args.get("day"))
    grib_file = request.args.get("grib_file")

    temperature = session.query(Temperature).filter_by(latitude=latitude, longitude=longitude, year=year, month=month, day=day, grib_file=grib_file)
    
    if not temperature:
        return jsonify({"message": "No temperature found for this location."}), 404

    max_temperature = temperature.temperature.max()

    response = {"temperature": float(max_temperature)}
    session.close()
    return jsonify(response)

if __name__ == '__main__':
    app.run(debug=True, port=8080)