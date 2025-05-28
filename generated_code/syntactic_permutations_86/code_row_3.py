import datetime as dt
from flask import Flask, jsonify, request
from sqlalchemy import create_engine


app = Flask(__name__)


def connect_to_database():
    return create_engine("mysql+pymysql://{user}:{pw}@localhost/{db}"
                         .format(user="", pw="", db=""))


@app.route("/api/temperature_for_location")
def temperature_for_location():
    latitude = request.args["latitude"]
    longitude = request.args["longitude"]
    year = request.args["year"]
    month = request.args["month"]
    day = request.args["day"]
    grib_file = request.args["grib_file"]
    query = "SELECT Max(temperature) FROM weather_data WHERE latitude={0} AND longitude={1} AND year={2} AND month={3} AND day={4} AND grib_file={5}".format(latitude, longitude, year, month, day, grib_file)
    engine = connect_to_database()
    with engine.connect() as con:
        result = con.execute(query).fetchone()[0]
    return jsonify({"maximum temperature": result})