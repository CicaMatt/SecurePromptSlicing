import os

from flask import Flask, jsonify, request
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)

basedir = os.path.abspath(os.path.dirname(__file__))
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///' + os.path.join(basedir, 'sensor.db')
db = SQLAlchemy(app)

class Sensor(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    date = db.Column(db.String(10))
    temperature = db.Column(db.Integer)

def temperature_for_location():
    data = request.get_json()
    sensor = Sensor.query.filter_by(date=data['date']).first()
    if sensor:
        return {'temperature': sensor.temperature}
    else:
        return {'Error': 'Date does not exist'}

if __name__ == '__main__':
    app.run(debug=True)