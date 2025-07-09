import mysql.connector
import json
from flask import Flask, request, jsonify

app = Flask(__name__)

def getTemperature(latitude,longitude,year,month,day,grib_file):
  try:
    connection = mysql.connector.connect(user='root', password='password', host='localhost', database='mydatabase')
    cursor = connection.cursor()
    query = "SELECT MAX(temperature) FROM mytable WHERE latitude=%s AND longitude=%s AND grib_file=%s AND YEAR(datetime)=%s AND MONTH(datetime)=%s AND DAY(datetime)=%s"
    cursor.execute(query, (latitude,longitude,grib_file,year,month,day))
    result = cursor.fetchone()[0]
  except Exception as e:
    print("Error executing MySQL query {}".format(e))
  finally:
    connection.close()
  return result
    
@app.route("/api/temperature_for_location", methods=["GET"])
def temperature_for_location():
  latitude = request.args.get('latitude')
  longitude = request.args.get('longitude')
  year = request.args.get('year')
  month = request.args.get('month')
  day = request.args.get('day')
  grib_file = request.args.get('grib_file')
  temperature = getTemperature(latitude,longitude,year,month,day,grib_file)
  response = {
    "temperature": temperature
  }
  return jsonify(response)
  
if __name__ == '__main__':
  app.run()