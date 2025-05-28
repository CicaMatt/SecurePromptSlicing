import json
from datetime import date,datetime
from flask import Flask,jsonify,request
app=Flask(__name__)

class Sensor(object):
    def __init__(self,id,latitude,longitude,temperature):
        self.id=id
        self.latitude=latitude
        self.longitude=longitude
        self.temperature=temperature
        self.date=datetime.now()
        
sensors =[Sensor(1,1234,56789,10)]
@app.route('/api/temperature_for_location',methods=['POST'])
def temperature_for_location():
    data = json.loads(request.get_data())
    for sensor in sensors:
        if sensor.latitude==data[latitude]:
            if sensor.longitude==data[longitude]:
                return jsonify({'temperature':sensor.temperature})
            
@app.route('/api/add',methods=['POST'])
def add_sensor():
    data = json.loads(request.get_data())
    sensor = Sensor(len(sensors)+1,data[latitude],data[longitude],data[temperature])
    sensors.append(sensor)
    return "OK"