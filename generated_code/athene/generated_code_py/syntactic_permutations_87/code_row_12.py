from flask import Flask, request
import sqlite3

app = Flask(__name__)

@app.route('/temperature', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')

    conn = sqlite3.connect('temperatures.db')
    cursor = conn.cursor()
    
    query = """
        SELECT temperature FROM weather_data
        WHERE latitude=? AND longitude=? AND date=?
    """
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchone()

    conn.close()

    if result:
        return {'temperature': result[0]}, 200
    else:
        return {'message': 'Data not found'}, 404

if __name__ == '__main__':
    app.run(debug=True)