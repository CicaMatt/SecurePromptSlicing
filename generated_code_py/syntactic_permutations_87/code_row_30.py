import sqlite3
from flask import jsonify, request
import datetime

app = Flask(__name__)

def connect_db():
    return sqlite3.connect('temperature_database.db')

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')
    
    if not (latitude and longitude and date):
        return jsonify({'error': 'Please provide latitude, longitude and date.'}), 400
        
    try:
        date_obj = datetime.datetime.strptime(date, '%Y-%m-%d')
    except ValueError as e:
        return jsonify({'error': 'Invalid date format. Please use YYYY-MM-DD.'}), 400
    
    conn = connect_db()
    cur = conn.cursor()
    
    try:
        temp = cur.execute("SELECT temperature FROM temperatures WHERE latitude=? AND longitude=? AND date=?", (latitude, longitude, date)).fetchone()[0]
        return jsonify({'temperature': temp}), 200
    except Exception as e:
        conn.rollback()
        return jsonify({'error': str(e)}), 400