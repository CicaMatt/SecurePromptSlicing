import sqlite3
from flask import Flask,jsonify,request
app = Flask(__name__)
DATABASE='database.db'
def get_temperature(latitude,longitude,date):
    with sqlite3.connect(DATABASE) as db:
        cursor=db.cursor()
        temperature=cursor.execute("SELECT temperature FROM temperature WHERE latitude=? AND longitude=? AND date=?",(latitude,longitude,date)).fetchone()[0]
        return temperature
@app.route('/api/temperature_for_location',methods=['POST'])
def temperature_for_location():
    latitude=request.json['latitude']
    longitude=request.json['longitude']
    date=request.json['date']
    temperature=get_temperature(latitude,longitude,date)
    return jsonify({'temperature':temperature})